#include<bits/stdc++.h>
#include "boost/intrusive/Segment_tree/segment_tree.hpp"
using namespace boost::intrusive;
//Internal data type which stores the value of the segment tree node.
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
//Define node structure of segment tree node
struct Myclass : public segment_tree_base_hook<>
{
    typedef type_used data_type;
    data_type value;
};
int main()
{
    //Input on which segment tree is built.
    Myclass input[100];
    //Input initialisation
    for(int i=0;i<100;i++)
    {
        input[i].value.a=1;
    }
    //Initialising segment tree object
    segment_tree<Myclass> tree(input,0,99);
    //Building the segment tree based on given input and merging function
    tree.build(single_sum);
    //Updating single value
    input[2].value.a=0;
    //Updating segment tree
    tree.update(single_sum,2);
    //Querying the segment tree for some range 
    type_used query_value=tree.query(single_sum,0,5);
    //iterator declaration
    segment_tree<Myclass>::iterator itr;
    //iterator pointing to root
    itr=tree.get_root();
    //getting the value stored by a node pointed by iterator
    std::cout << itr->value.a << "\n";


    return 0;
}