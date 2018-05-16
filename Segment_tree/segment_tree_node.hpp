#ifndef BOOST_INTRUSIVE_LIST_NODE_HPP
#define BOOST_INTRUSIVE_LIST_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>


class segment_tree_node
{
    int position;
    int start;
    int end;
};
class segment_tree_node_traits
{
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
#endif