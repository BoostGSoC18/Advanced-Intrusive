
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>

namespace boost {
    namespace intrusive {

template<class VoidPointer>
class segment_tree_node
{
    public:
    typedef typename boost::intrusive::pointer_rebind<VoidPointer, segment_tree_node>::type  node_ptr;
    int position;
    int start;
    int end;
};
template<class VoidPointer>
class segment_tree_node_traits
{
    public:
    typedef segment_tree_node<VoidPointer>      node;
    typedef typename node::node_ptr     node_ptr;
    typedef typename pointer_rebind<VoidPointer, const node>::type   const_node_ptr;
    BOOST_INTRUSIVE_FORCEINLINE static void set_position(int position , pointer &n)
    {
        n->position=position;
    }
    BOOST_INTRUSIVE_FORCEINLINE static void set_start(int start , node_ptr &n)
    {
        n->start=start;
    }
    BOOST_INTRUSIVE_FORCEINLINE static void set_end(int end , node_ptr &n)
    {
        n->end=end;
    }
    BOOST_INTRUSIVE_FORCEINLINE static int get_position(node_ptr &n)
    {
       return n->position;
    }
    BOOST_INTRUSIVE_FORCEINLINE static int get_start(node_ptr &n)
    {
        return n->start;
    }
    BOOST_INTRUSIVE_FORCEINLINE static int get_end(node_ptr &n)
    {
        return n->end;
    }



};

} //endof namespaces
}
