#include <boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree_algorithms.hpp>
#include <boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree_hook.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>
#include "boost/intrusive/options.hpp"
#include "boost/GSOC18/Advanced-Intrusive/Segment_tree/merging_function.hpp"

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
};


template<typename value_traits>
class segment_tree_impl
{
    public:
    typedef typename value_traits::node_traits node_traits;
    typedef typename node_traits::node node;
    typedef typename node::node_ptr node_ptr;
    typedef typename value_traits::pointer pointer;
    typedef typename pointer_traits<pointer>::element_type            value_type;
    typedef typename pointer_traits<pointer>::reference               reference;
    typedef segment_tree_algorithms<node_traits> algo;
    typedef typename value_type::data_type data_type;
    value_type *ptr;
    int n;
    public:
    segment_tree_impl(int n)
    {
        ptr=(value_type*)malloc(4*n*sizeof(value_type));
        this->n=n;
    }
    private:
    void set_values(int start,int end,int position)
    {
        if(start==end)
        {
            node_ptr poiner=value_traits::to_node_ptr(ptr[position]);
            algo::set_all_values(poiner,start,end,position);
            return ;
        }
        int mid=(start+end)/2;
        node_ptr poiner=value_traits::to_node_ptr(ptr[position]);
        algo::set_all_values(poiner,start,end,position);
        set_values(start,mid,2*position+1);
        set_values(mid+1,end,2*position+2);    
    }
    public:
    void build(data_type input[],int start,int end,int position,auto func)
    {
        set_values(start,end,0);
        build_comp(input,start,end,0,func);
    }
    private:
    data_type build_comp(data_type input[],int start,int end,int position,auto func)
    {
        if(start==end)
        {
            ptr[position].value=input[start];
            return input[start];
        }
        int mid=(start+end)/2;
        node_ptr poiner=value_traits::to_node_ptr(ptr[position]);
        int left_child=algo::left_index(poiner);
        int right_child=algo::right_index(poiner);
        ptr[position].value=func(build_comp(input,start,mid,left_child,func),build_comp(input,mid+1,end,right_child,func));
        return ptr[position].value;
    }
    public:
    data_type update(data_type input[],int start,int end,int position,auto func,int index)
    {
        if(start==end && start==index)
        {
            ptr[position].value=input[start];
            return ptr[position].value;
        }
        if(index>end || index<start)
        {
            return ptr[position].value;
        }
        int mid=(start+end)/2;
        ptr[position].value=func(update(input,start,mid,2*position+1,func,index),update(input,mid+1,end,2*position+2,func,index));    
        return ptr[position].value;
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
      <value_traits> implementation_defined;
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
    typedef typename make_segment_tree<T,O1>::type Base;
    typedef typename make_segment_tree<T,O1>::value_traits value_traits;    
    public:
    segment_tree(int n)
        : Base(n)
    {

    };
};

}
}
#endif 