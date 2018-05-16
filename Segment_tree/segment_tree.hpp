#include</home/hari/BoostGsoc18/boost_1_65_1/boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree_algorithms.hpp>
#include</home/hari/BoostGsoc18/boost_1_65_1/boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree_hook.hpp>


struct default_segtree_hook_applier
{  template <class T> struct apply{ typedef typename T::default_segtree_hook type;  };  };

// template<typename >
// struct is_default_hook_tag<default_segtree_hook_applier>
// {  static const bool value = true;  2};

struct segtree_defaults
{
   typedef default_segtree_hook_applier proto_value_traits;
};


namespace boost {
    namespace intrusive {


template<typename T>
class segment_tree_impl
{
    public:
 //   typedef segment_tree_algorithms node_algorithms;
    T * ptr;
    segment_tree_algorithms<T> algo;
    public:
    segment_tree_impl(int n)
    {
        algo.inited(n,ptr);
    }   
};
template<typename T>
class segment_tree: public segment_tree_impl<T>
{
    public:
    segment_tree(int n)
        : segment_tree_impl<T>(n)
    {

    };
};

}
}