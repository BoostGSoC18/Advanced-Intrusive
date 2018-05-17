#include "boost/intrusive/pointer_traits.hpp"
#include "boost/intrusive/trivial_value_traits.hpp"
#include "boost/intrusive/pointer_rebind.hpp"
#include "boost/intrusive/link_mode.hpp"
#include<bits/stdc++.h>
template<typename VoidPointer>
class single_node
{
    public:
    typedef typename boost::intrusive::pointer_rebind<VoidPointer, single_node>::type  node_ptr;
    int a;
};

template<typename VoidPointer>
class node_traits
{
    public:
    typedef single_node<VoidPointer>      node;
    typedef typename node::node_ptr     node_ptr;
    typedef typename boost::intrusive::pointer_rebind<VoidPointer, const node>::type   const_node_ptr;
    static void set_position(int position , node_ptr &n)
    {
        n->a=position;
    }
    
};
int main()
{
    typedef boost::intrusive::trivial_value_traits<node_traits<void*>,boost::intrusive::normal_link> value_traits;
    typedef value_traits::node_ptr node_ptr;
    single_node<void*> first;
    node_ptr ptr=value_traits::to_node_ptr(first);
    if(first.a==value_traits::to_value_ptr(ptr)->a)
    {
        std::cout << "success\n";
    }
    return 0;
}