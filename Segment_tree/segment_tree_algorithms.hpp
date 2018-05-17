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
    template<typename Pointer>
    Pointer* inited(int n)
    {
       Pointer *ptr=(node*)malloc(4*n*sizeof(node));
       std::cout << "hari\n";
       std::cout << ptr[0].position;
       return ptr;     
    }
    template<typename pointer>
    void pos_set(int n,pointer ptr)
    {
       //4 node_traits::set_position<pointer>(n,ptr);
    }

};

template<class NodeTraits>
struct  get_algo<SegTreeAlgorithms, NodeTraits>
{
   typedef segment_tree_algorithms<NodeTraits> type;
};

}
}
