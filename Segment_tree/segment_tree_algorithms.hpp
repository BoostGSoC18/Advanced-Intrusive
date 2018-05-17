#include<bits/stdc++.h>
#include <boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree_node.hpp>
#include<boost/intrusive/detail/algo_type.hpp>

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
    BOOST_INTRUSIVE_FORCEINLINE static void init(const node_ptr &this_node)
    {
        //to be filled
    }
    BOOST_INTRUSIVE_FORCEINLINE static bool unique(const const_node_ptr &this_node)
    {
        // to be filled
        return true;
    }    
};

template<class NodeTraits>
struct  get_algo<SegTreeAlgorithms, NodeTraits>
{
   typedef segment_tree_algorithms<NodeTraits> type;
};

}
}
