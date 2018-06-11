#include <boost/GSOC18/Advanced-Intrusive/Fenwick_tree/fenwick_tree_algorithms.hpp>
#include <boost/GSOC18/Advanced-Intrusive/Fenwick_tree/fenwick_tree_hook.hpp>
//#include "boost/GSOC18/Advanced-Intrusive/Fenwick_tree/merging_function.hpp"
#include <boost/GSOC18/Advanced-Intrusive/Fenwick_tree/fenwick_tree_iterator.hpp>


#include<boost/intrusive/any_hook.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>
#include "boost/intrusive/options.hpp"
#include <boost/intrusive/detail/is_stateful_value_traits.hpp>
#include <boost/intrusive/detail/default_header_holder.hpp>
#include "boost/intrusive/detail/size_holder.hpp"
#include<iostream>
#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/reverse_iterator.hpp>
#include <boost/intrusive/detail/uncast.hpp>
#include <boost/intrusive/detail/array_initializer.hpp>
#include <boost/intrusive/detail/exception_disposer.hpp>
#include <boost/intrusive/detail/equal_to_value.hpp>
#include <boost/intrusive/detail/key_nodeptr_comp.hpp>
#include <boost/intrusive/detail/simple_disposers.hpp>
#include <boost/intrusive/detail/algorithm.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#include <boost/intrusive/detail/minimal_less_equal_header.hpp>//std::less
#include <cstddef>   //std::size_t, etc.

#include <queue>

namespace boost {
    namespace intrusive {

struct default_fenwick_tree_hook_applier
{  
    template <class T> 
    struct apply
    { 
        typedef typename T::default_fenwick_tree_hook type;  
    };  
};

template<>
struct is_default_hook_tag<default_fenwick_tree_hook_applier>
{  static const bool value = true;  };

struct fenwick_tree_defaults
{
   typedef default_fenwick_tree_hook_applier proto_value_traits;
   static const bool constant_time_size = true;
   typedef std::size_t size_type;
   typedef void header_holder_type;
};

template<typename ValueTraits, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
class fenwick_tree_impl
{
    public:
    typedef ValueTraits                                               value_traits;
    typedef typename value_traits::node_traits node_traits;
    typedef typename node_traits::node node;
    typedef typename node::node_ptr node_ptr;
    typedef typename value_traits::pointer pointer;
    typedef typename pointer_traits<pointer>::element_type            value_type;
    typedef typename pointer_traits<pointer>::reference               reference;
    typedef fenwick_tree_algorithms<node_traits> algo;
    typedef typename node_traits::const_node_ptr                      const_node_ptr;
    typedef SizeType                                                  size_type;
    typedef typename value_type::data_type data_type;
    typedef typename detail::get_header_holder_type
      < value_traits, HeaderHolder >::type                           header_holder_type;
    
   static const bool constant_time_size = ConstantTimeSize;
   static const bool stateful_value_traits = detail::is_stateful_value_traits<value_traits>::value;
   static const bool has_container_from_iterator =
        detail::is_same< header_holder_type, detail::default_header_holder< node_traits > >::value;

   /// @cond

   private:
    typedef detail::size_holder<constant_time_size, size_type>          size_traits;
    
    private:
    
    value_type *ptr;
    value_type *input;

    int start,end;
    int total_nodes=0,max_index=0,level_one_nodes=0;
    int leaf_nodes=0;
    
    node_ptr root;
   
   public:
    fenwick_tree_impl(value_type input[],int start,int end)
    {
        this->input=input;
        this->start=start;
        this->end=end;
        total_nodes=end-start+2;
        leaf_nodes=(total_nodes-1)/2+(total_nodes-1)%2;
        max_index=total_nodes-1;
        ptr=(value_type*)malloc((total_nodes-leaf_nodes)*sizeof(value_type));
        root=value_traits::to_node_ptr(ptr[0]);
        int nearest_pow=1;
        while(nearest_pow<=max_index)
        {
            level_one_nodes++;
            nearest_pow*=2;
        }
        root->children=(node_ptr*)malloc((level_one_nodes)*sizeof(node_ptr));
        int nt=0;
        std::queue<int> node_index;
        node_index.push(0);
        std::map<int,int> index_new,new_index;
        while(!node_index.empty())
        {
            int index=node_index.front();
            node_ptr temp_node;
            if(index%2==1)
            {
                temp_node=value_traits::to_node_ptr(input[index-1]);
            }
            else
            {
                temp_node=value_traits::to_node_ptr(ptr[nt]);
                index_new.insert(std::make_pair(nt,index));
                new_index.insert(std::make_pair(index,nt));
                nt++;
            }
            int temp=1,child_cnt=0;
            while((index&temp)!=temp && (index|temp)<=max_index)
            {
                child_cnt++;
                node_index.push(index|temp);
                temp*=2;
            }
            temp_node->children=(node_ptr*)malloc(child_cnt*sizeof(node_ptr));
            temp_node->child_cnt=child_cnt;
            node_index.pop();
        }
        for(int i=0;i<total_nodes-leaf_nodes;i++)
        {
            node_ptr node=value_traits::to_node_ptr(ptr[i]);
            int index=index_new[i];
            int temp=1,child_par=0;
            while((index&temp)!=temp && (index|temp)<=max_index)
            {
                int a=index|temp;
                if(temp==1)
                {
                    node->children[child_par]=value_traits::to_node_ptr(input[(index|temp)-1]);
                }
                else
                {
                    node->children[child_par]=value_traits::to_node_ptr(ptr[new_index[index|temp]]);
                }
                child_par++;
                temp*=2;
            }      
        }
    }
    private:
        int cnt_run=1;
    public:
    void build(auto func)
    {
        for(int i=0;i<total_nodes-leaf_nodes;i++)
        {
            ptr[i].value.a=0;
        }
        build_computation(func);
       // check();
    }
    void check()
    {
        node_ptr temp=root->children[2];
        temp=temp->children[1];
        pointer p=value_traits::to_value_ptr(temp);
        //std::cout << p->value.a << "\n";
    }
    void build_computation(auto func)
    {
        for(int i=0;i<=end;i++)
        {
            check();
            update(func,i,input[i]);
        }
    }
    void update(auto func,int index,value_type val)
    {
        std::stack<int> bit_pos;
        int temp=1,position=0;
        while(temp<=index+1)
        {
            int sb=temp&(index+1);
            if(sb==temp)
            {
                bit_pos.push(position);
            }    
            position++;
            temp*=2;
        }
        update_computation(root,func,bit_pos,val);
    }
    private:
    void update_computation(node_ptr curr_node,auto func,std::stack<int> &bit_pos,value_type val)
    {
        while(bit_pos.size()!=0)
        {
            int child=bit_pos.top();
            bit_pos.pop();
            int curr_cnt=curr_node->child_cnt;
            int size=bit_pos.size();
            if(bit_pos.size()!=0)
            {
                for(int i=child+1;i<curr_cnt;i++)
                {
                    if(i!=0)
                    {
                        pointer p=value_traits::to_value_ptr(curr_node->children[i]);
                        p->value=func(p->value,val.value);
                    }
                }
            }
            else
            {
                for(int i=child;i<curr_cnt;i++)
                {
                    if(i!=0)
                    {
                        pointer p=value_traits::to_value_ptr(curr_node->children[i]);
                        p->value=func(p->value,val.value);
                    }
                }
            }
            curr_node=curr_node->children[child];
        }
    }
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_fenwick_tree
{
   /// @cond
   typedef typename pack_options
      < fenwick_tree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4
         #else
         Options...
         #endif
         >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;
   typedef fenwick_tree_impl
      <value_traits,
        typename packed_options::size_type,
         packed_options::constant_time_size,
         typename packed_options::header_holder_type
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4>
#else
template<class T, class ...Options>
#endif
class fenwick_tree 
   : public make_fenwick_tree<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
   >::type
{
    public:
       typedef typename make_fenwick_tree
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type      Base;

 public:
   typedef typename Base::value_traits          value_traits;
   
    public:
    fenwick_tree(T input[],int start,int end)
        : Base(input,start,end)
    {

    };
};

}
}
#endif 