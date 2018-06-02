#include <boost/GSOC18/Advanced-Intrusive/New_segment_tree/segment_tree_algorithms.hpp>
#include <boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree_hook.hpp>
#include "boost/GSOC18/Advanced-Intrusive/Segment_tree/merging_function.hpp"
#include <boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree_iterator.hpp>

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
   


   node_ptr get_root_node()
   { return data_.root_plus_size_.m_header.get_node(); }

   const_node_ptr get_root_node() const
   { return data_.root_plus_size_.m_header.get_node(); }

   struct root_plus_size : public size_traits
   {
      header_holder_type m_header;
   };

   struct data_t : public ValueTraits
   {
      typedef typename segment_tree_impl::value_traits value_traits;
      root_plus_size root_plus_size_;
   } data_;

   size_traits &priv_size_traits()
   {  return data_.root_plus_size_;  }

   const size_traits &priv_size_traits() const
   {  return data_.root_plus_size_;  }

   const value_traits &priv_value_traits() const
   {
     return data_;  
   }

   value_traits &priv_value_traits()
   {
      return data_;
   }

   typedef typename boost::intrusive::value_traits_pointers
      <ValueTraits>::const_value_traits_ptr const_value_traits_ptr;

   const_value_traits_ptr priv_value_traits_ptr() const
   {  return pointer_traits<const_value_traits_ptr>::pointer_to(this->priv_value_traits());  }

   public:
    node_ptr root;
    int n;
    int total_nodes=0,internal_nodes=0;
    value_type *ptr;
    private:
    int nodecnt_run=1;
    public:
    segment_tree_impl(int start,int end,int n)
    {
        nodes_count(start,end);
        ptr=(value_type*)malloc((total_nodes)*sizeof(value_type));
        initialisation(start,end,0);
        root=value_traits::to_node_ptr(ptr[0]);
    }
    private:
    void initialisation(int start,int end,int parent_pos)
    {
       if(start==end)
       {
           return ;
       }
       int left,right;
       node_ptr parent=value_traits::to_node_ptr(ptr[parent_pos]);
       node_ptr left_child=value_traits::to_node_ptr(ptr[nodecnt_run]);
       left=nodecnt_run;
       nodecnt_run++;
       node_ptr right_child=value_traits::to_node_ptr(ptr[nodecnt_run]);
       right=nodecnt_run;
       nodecnt_run++;
       parent->left_child=left_child;
       parent->right_child=right_child;
       int mid=(start+end)/2;
       initialisation(start,mid,left);
       initialisation(mid+1,end,right); 
    }
    private:
    void nodes_count(int start,int end)
    {
       total_nodes++;
       if(start==end)
       {
           return ;
       }
       internal_nodes++;
       int mid=(start+end)/2;
       nodes_count(start,mid);
       nodes_count(mid+1,end); 
    }
    public:
    void build(data_type *input,int start,int end,auto func)
    {
       build_computation(input,start,end,func,root);
    }
    data_type build_computation(data_type  *input,int start,int end,auto func,node_ptr &curr_node)
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
        node_ptr left_ptr=node_traits::get_left_child(curr_node);
        node_ptr right_ptr=node_traits::get_right_child(curr_node);
        p->value=func(update_computation(input,start,mid,func,index,left_ptr),update_computation(input,mid+1,end,func,index,right_ptr));    
        return p->value;
    }
    private:
    int range_nodes=0;
    public:
    data_type query(data_type input[],int start,int end,auto func,int query_start,int query_end)
    {
        data_type *required_values;
        required_values=(data_type*)malloc(4*total_nodes*sizeof(data_type));
        query_computation(input,start,end,func,query_start,query_end,required_values,root);
        data_type final_value;
        final_value=required_values[0];
        for(int each=1;each<range_nodes;each++)
        {
            final_value=func(final_value,required_values[each]);
        }
        return final_value;
    }
    private:
    void query_computation(data_type input[],int start,int end,auto func,int query_start,int query_end,data_type *required_values,node_ptr &curr_node)
    {
        pointer p=value_traits::to_value_ptr(curr_node);
        
        if(query_start<=start && end<=query_end)
        {
            required_values[range_nodes]=p->value;
            range_nodes++;
            return ;
        }
        if(query_start>end || start>query_end)
        {
            return ;
        }
        int mid=(start+end)/2;
        node_ptr left_ptr=node_traits::get_left_child(curr_node);
        node_ptr right_ptr=node_traits::get_right_child(curr_node);
        query_computation(input,start,mid,func,query_start,query_end,required_values,left_ptr);
        query_computation(input,mid+1,end,func,query_start,query_end,required_values,right_ptr);
    }
    public:
    iterator get_root()
    {
        return iterator(root, this->priv_value_traits_ptr());
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