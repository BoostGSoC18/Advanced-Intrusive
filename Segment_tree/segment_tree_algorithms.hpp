#include<bits/stdc++.h>
#include </home/hari/BoostGsoc18/boost_1_65_1/boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree_node.hpp>
#include</home/hari/BoostGsoc18/boost_1_65_1/boost/intrusive/detail/algo_type.hpp>
namespace boost {
    namespace intrusive {

template<typename NodeTraits>
class segment_tree_algorithms
{
public:
   typedef typename NodeTraits::node            node;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;
   typedef NodeTraits                           node_traits;
    node_ptr ptr;
    public:
    BOOST_INTRUSIVE_FORCEINLINE static void init(const node_ptr &this_node)
    {
      std::cout << "junnu\n";
    }
    BOOST_INTRUSIVE_FORCEINLINE static bool unique(const const_node_ptr &this_node)
    {
        return true;
    }

    node_ptr inited(int n,node_ptr)
    {
       ptr=(node_ptr)malloc(4*n*sizeof(node));
       return ptr;     
    }

};

template<class NodeTraits>
struct  get_algo<SegTreeAlgorithms, NodeTraits>
{
   typedef segment_tree_algorithms<NodeTraits> type;
};

}
}
