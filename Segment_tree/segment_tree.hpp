#include <boost/GSOC18/Advanced-Intrusive/Segment_tree/check/segment_tree_algorithms.hpp>
#include <boost/GSOC18/Advanced-Intrusive/Segment_tree/check/segment_tree_hook.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>


namespace boost {
    namespace intrusive {

struct default_segtree_hook_applier
{  
public: 
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
public:
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
    value_type *ptr;
    public:
    segment_tree_impl(int n)
    {
        ptr=(value_type*)malloc(4*n*sizeof(value_type));
    }   
};
template<typename T>
struct make_segment_tree
{
   /// @cond
   typedef typename pack_options
      < segtree_defaults>::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;
   typedef segment_tree_impl
      <value_traits> implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

template<typename T>
class segment_tree: public make_segment_tree<T>::type
{
    public:
    typedef typename make_segment_tree<T>::type Base;
    typedef typename make_segment_tree<T>::value_traits value_traits;    
    public:
    segment_tree(int n)
        : Base(n)
    {

    };
};

}
}
