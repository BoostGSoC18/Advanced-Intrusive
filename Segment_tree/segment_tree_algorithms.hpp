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

    }
    BOOST_INTRUSIVE_FORCEINLINE static bool unique(const const_node_ptr &this_node)
    {
        return true;
    }
    BOOST_INTRUSIVE_FORCEINLINE static int left_index(node_ptr &node)
    {
        if(node->start!=node->end)
        {
            return 2*node->position+1;
        }
        return -1;
    }
    BOOST_INTRUSIVE_FORCEINLINE static int right_index(node_ptr &node)
    {
        if(node->start!=node->end)
        {
            return 2*node->position+2;
        }
        return -1;
    }
    BOOST_INTRUSIVE_FORCEINLINE static void set_all_values(node_ptr &node,int start,int end,int position)
    {
        node->start=start;
        node->end=end;
        node->position=position;          
    }    

};

template<class NodeTraits>
struct  get_algo<SegTreeAlgorithms, NodeTraits>
{
   typedef segment_tree_algorithms<NodeTraits> type;
};

}
}
