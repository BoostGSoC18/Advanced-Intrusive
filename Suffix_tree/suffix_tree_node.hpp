#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>

namespace boost {
    namespace intrusive {

template<class VoidPointer>
class suffix_tree_node
{
    public:
        typedef typename boost::intrusive::pointer_rebind<VoidPointer, suffix_tree_node>::type  node_ptr;
    public:
        node_ptr children[26];
        node_ptr suffix_link;
        int start,end;
        int suffix_index;
};
template<class VoidPointer>
class suffix_tree_node_traits
{
    public:
    typedef suffix_tree_node<VoidPointer>      node;
    typedef typename node::node_ptr     node_ptr;
    typedef typename pointer_rebind<VoidPointer, const node>::type   const_node_ptr;
    BOOST_INTRUSIVE_FORCEINLINE static void set_children(node_ptr &target,int child_index,node_ptr &child)
    {
        target->children[child_index]=child;
    }
    BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_children(node_ptr &target,int child_index)
    {
        return target->children[child_index];
    }
    BOOST_INTRUSIVE_FORCEINLINE static void set_start(node_ptr &target,int start)
    {
        target->start=start;
    }
    BOOST_INTRUSIVE_FORCEINLINE static int get_start(node_ptr &target)
    {
        return target->start;
    }
    BOOST_INTRUSIVE_FORCEINLINE static void set_end(node_ptr &target,int end)
    {
        target->end=end;
    }
    BOOST_INTRUSIVE_FORCEINLINE static int get_end(node_ptr &target)
    {
        return target->end;
    }
    BOOST_INTRUSIVE_FORCEINLINE static void set_suffix_link(node_ptr &target,node_ptr &suffix_link)
    {
        target->suffix_link=suffix_link;
    }
    BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_suffix_link(node_ptr &target)
    {
        return target->suffix_link;
    }
    BOOST_INTRUSIVE_FORCEINLINE static void set_suffix_index(node_ptr &target,int suffix_index)
    {
        target->suffix_index=suffix_index;
    }
    BOOST_INTRUSIVE_FORCEINLINE static int get_start(node_ptr &target)
    {
        return target->suffix_index;
    }
};
    }
}