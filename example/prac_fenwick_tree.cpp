#include<bits/stdc++.h>
#include "boost/intrusive/Fenwick_tree/fenwick_tree.hpp"
using namespace boost::intrusive;
//Internal data type which stores the value of the fenwick tree node.
struct type_used
{
    int a;
};
//Merging function takes 2 values and merges them to single output.
auto single_sum=[](auto a,auto b)
{
    //output value
    type_used c;
    //merging
    c.a=a.a+b.a;
    return c;
};
//Define node structure of fenwick tree node
struct Myclass : public fenwick_tree_base_hook<>
{
    typedef type_used data_type;
    data_type value;
};
int main()
{
    //Input on which fenwick tree is built.
    Myclass input[100];
    //Input initialisation
    for(int i=0;i<100;i++)
    {
        input[i].value.a=1;
    }
    //Initialising fenwick tree object
    fenwick_tree<Myclass> tree(input,0,99);
    //Building the fenwick tree based on given input and merging function
    tree.build(single_sum);
    //Updating fenwick tree
    Myclass update_value;
    //Fenwick tree supports only additions to the input array you cannot undo the changes
    update_value.value.a=1;
    tree.update(single_sum,2,update_value);
    //Querying the fenwick tree for some range 
    type_used query_value=tree.query(single_sum,5);
    //iterator declaration
    fenwick_tree<Myclass>::iterator itr;
    //iterator pointing to root
    itr=tree.get_root();
    //getting the value stored by a node pointed by iterator
    std::cout << itr->value.a << "\n";
    //Traversing the fenwick tree
    itr.get_child(1);
    std::cout << itr->value.a << "\n";
    

    return 0;
}