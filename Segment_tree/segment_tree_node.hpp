
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#include </home/hari/BoostGsoc18/boost_1_65_1/boost/intrusive/detail/workaround.hpp>
#include </home/hari/BoostGsoc18/boost_1_65_1/boost/intrusive/pointer_rebind.hpp>

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
    typedef typename boost::intrusive::pointer_rebind<VoidPointer, const node>::type   const_node_ptr;
    void set_position(int position , int )
    {

    }
    void set_start()
    {

    }
    void set_end()
    {

    }
    void get_position()
    {

    }
    void get_start()
    {

    }
    void get_end()
    {

    }
};

} //endof namespaces
}