#include <boost/GSOC18/Advanced-Intrusive/New_segment_tree/segment_tree_algorithms.hpp>
#include <boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree_hook.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>
#include "boost/intrusive/options.hpp"
#include "boost/GSOC18/Advanced-Intrusive/Segment_tree/merging_function.hpp"
#include <boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree_iterator.hpp>
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

#include<queue>
namespace boost {
    namespace intrusive {

struct default_segtree_hook_applier
{  
    template <class T> 
    struct apply
    { 
        typedef typename T::default_segtree_hook type;  
    };  
};

template<>
struct is_default_hook_tag<default_segtree_hook_applier>
{  static const bool value = true;  };

struct segtree_defaults
{
   typedef default_segtree_hook_applier proto_value_traits;
   static const bool constant_time_size = true;
   typedef std::size_t size_type;
   typedef void header_holder_type;
};


template<typename ValueTraits, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
class segment_tree_impl
{
    public:
    typedef ValueTraits                                               value_traits;
    typedef typename value_traits::node_traits node_traits;
    typedef typename node_traits::node node;
    typedef typename node::node_ptr node_ptr;
    typedef typename value_traits::pointer pointer;
    typedef typename pointer_traits<pointer>::element_type            value_type;
    typedef typename pointer_traits<pointer>::reference               reference;
    typedef segment_tree_algorithms<node_traits> algo;
    typedef typename value_type::data_type data_type;
    typedef segtree_iterator<value_traits, false>                        iterator;
    typedef segtree_iterator<value_traits, true>                         const_iterator;
    typedef typename node_traits::const_node_ptr                      const_node_ptr;
    typedef SizeType                                                  size_type;
   
    typedef typename detail::get_header_holder_type
      < value_traits, HeaderHolder >::type                           header_holder_type;

   static const bool constant_time_size = ConstantTimeSize;
   static const bool stateful_value_traits = detail::is_stateful_value_traits<value_traits>::value;
   static const bool has_container_from_iterator =
        detail::is_same< header_holder_type, detail::default_header_holder< node_traits > >::value;

   /// @cond

   private:
   
   typedef detail::size_holder<constant_time_size, size_type>          size_traits;
   
   public:
   
    node_ptr root;
    int n;
    int total_nodes=0;
    value_type *ptr;
    struct node_queue
    {
        int start;
        int end;
    };
    public:
    segment_tree_impl(int ss,int se,int n)
    {
        nodes_count(ss,se);
        ptr=(value_type*)malloc(total_nodes*sizeof(value_type));
        initialisation(ss,se,n,0);
        root=value_traits::to_node_ptr(ptr[0]);
    }
    private:
    void initialisation(int ss,int se,int n,int pos)
    {
        if(ss==se)
        {
            return ;
        }
        node_ptr parent=value_traits::to_node_ptr(ptr[pos]);
        node_ptr left_child=value_traits::to_node_ptr(ptr[2*pos+1]);
        node_ptr right_child=value_traits::to_node_ptr(ptr[2*pos+2]);
        node_traits::set_left_child(parent,left_child);
        node_traits::set_right_child(parent,right_child);
        int mid=(ss+se)/2;
        initialisation(ss,mid,n,2*pos+1);
        initialisation(mid+1,se,n,2*pos+2);
    }
    private:
    void nodes_count(int ss,int se)
    {
       if(ss==se)
       {
           total_nodes++;
           return ;
       }
       total_nodes++;
       int mid=(ss+se)/2;
       nodes_count(ss,mid);
       nodes_count(mid+1,se); 
    }
    public:
    void build(data_type input[],int start,int end,auto func)
    {
        build_computation(input,start,end,func,root);
    }
    data_type build_computation(data_type input[],int start,int end,auto func,node_ptr &curr_node)
    {
        value_type* p=value_traits::to_value_ptr(curr_node);
        if(start==end)
        {
           p->value=input[start];
           return p->value;
        }
        int mid=(start+end)/2;
        node_ptr left_ptr=node_traits::get_left_child(curr_node);
        node_ptr right_ptr=node_traits::get_right_child(curr_node);
        data_type left_value=build_computation(input,start,mid,func,left_ptr);
        data_type right_value=build_computation(input,mid+1,end,func,right_ptr);
        p->value=func(left_value,right_value);
        return p->value;
    }
    data_type update(data_type input[],int start,int end,auto func,int index)
    {
        update_computation(input,start,end,func,index,root);
    }
    data_type update_computation(data_type input[],int start,int end,auto func,int index,node_ptr &curr_node)
    {
        pointer p=value_traits::to_value_ptr(curr_node);
        if(start==end && start==index)
        {
            p->value=input[start];
            return p->value;
        }
        if(index>end || index<start)
        {
            return p->value;
        }
        int mid=(start+end)/2;
        p->value=func(update_computation(input,start,mid,func,index,p->left_child),update_computation(input,mid+1,end,func,index,p->right_child));    
        return p->value;
    }
};
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_segment_tree
{
   /// @cond
   typedef typename pack_options
      < segtree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4
         #else
         Options...
         #endif
         >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;
   typedef segment_tree_impl
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
class segment_tree 
   : public make_segment_tree<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
   >::type
{
    public:
       typedef typename make_segment_tree
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type      Base;

 public:
   typedef typename Base::value_traits          value_traits;
   typedef typename Base::iterator              iterator;
   
    public:
    segment_tree(int ss,int se,int n)
        : Base(ss,se,n)
    {

    };
};

}
}
#endif 