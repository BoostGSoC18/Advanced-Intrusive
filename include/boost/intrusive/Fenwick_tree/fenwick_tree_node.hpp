#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>

namespace boost {
    
    namespace intrusive {

template<class VoidPointer>
class fenwick_tree_node
{
    public:
        typedef typename boost::intrusive::pointer_rebind<VoidPointer, fenwick_tree_node>::type  node_ptr;
    public:
        node_ptr *children;
        int child_cnt;
};
template<class VoidPointer>
class fenwick_tree_node_traits
{
    public:
    typedef fenwick_tree_node<VoidPointer>      node;
    typedef typename node::node_ptr     node_ptr;
    typedef typename pointer_rebind<VoidPointer, const node>::type   const_node_ptr;
    BOOST_INTRUSIVE_FORCEINLINE static void set_child_count(node_ptr &target,int n)
    {
        target->n=n;
    }
    BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_child_count(node_ptr &target)
    {
        return target->n;
    }
    BOOST_INTRUSIVE_FORCEINLINE static void set_child(node_ptr &target,int n,node_ptr &child)
    {
        target->child[n]=child;
    }
    BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_child(node_ptr &target,int n)
    {
        return target->child[n];
    }
};
    }
}
