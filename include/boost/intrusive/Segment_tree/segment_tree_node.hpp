
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
    node_ptr left_child;
    node_ptr right_child;
};
template<class VoidPointer>
class segment_tree_node_traits
{
    public:
    typedef segment_tree_node<VoidPointer>      node;
    typedef typename node::node_ptr     node_ptr;
    typedef typename pointer_rebind<VoidPointer, const node>::type   const_node_ptr;
    BOOST_INTRUSIVE_FORCEINLINE static void set_left_child(const node_ptr &target,const node_ptr &left_child)
    {
        target->left_child=left_child;
    }
    BOOST_INTRUSIVE_FORCEINLINE static void set_right_child(const node_ptr &target,const node_ptr &right_child)
    {
        target->right_child=right_child;
    }
    BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left_child(const node_ptr &target)
    {
       return target->left_child;
    }
    BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left_child(const const_node_ptr &target)
    {
       return target->left_child;
    }
    BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right_child(const node_ptr &target)
    {
        return target->right_child;
    }
    BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right_child(const const_node_ptr &target)
    {
        return target->right_child;
    }
};

} //endof namespaces
}
