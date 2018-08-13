#include<bits/stdc++.h>
using namespace std;
#include "boost/intrusive/Suffix_tree/suffix_tree.hpp"
using namespace boost::intrusive;
class Myclass :public suffix_tree_base_hook<>
{

};
int main()
{
    char text[100];
    //Taking the input string
    scanf("%s",text);
    Myclass input;
    //Initialising suffix tree object and building suffix tree
    suffix_tree<Myclass> first_tree(text,0,strlen(text)-1);
    //Declaration of an iterator
    suffix_tree<Myclass>::iterator itr;
    //Getting the root of suffix tree
    itr=first_tree.get_root();
    //Traversing the tree
    itr.get_child(text[1]);
    printf("%d %d\n",itr->start,*itr->end);
    return 0;
}