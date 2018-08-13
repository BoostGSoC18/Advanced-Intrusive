#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>

namespace boost {
    namespace intrusive {

template<class VoidPointer>
class suffix_automata_node
{
    public:
        typedef typename boost::intrusive::pointer_rebind<VoidPointer, suffix_automata_node>::type  node_ptr;
    public:
        node_ptr children[26];
        node_ptr suffix_link;
        int length;
};
template<class VoidPointer>
class suffix_automata_node_traits
{
    public:
    typedef suffix_automata_node<VoidPointer>      node;
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
    BOOST_INTRUSIVE_FORCEINLINE static void set_suffix_link(node_ptr &target,node_ptr &link)
    {
        target->suffix_link=link;
    }
    BOOST_INTRUSIVE_FORCEINLINE static int get_suffix_link(node_ptr &target)
    {
        return target->suffix_link;
    }
    BOOST_INTRUSIVE_FORCEINLINE static void set_length(node_ptr &target,int length)
    {
        target->length=length;
    }
    BOOST_INTRUSIVE_FORCEINLINE static int get_length(node_ptr &target)
    {
        return target->length;
    }
   
};
    }
}