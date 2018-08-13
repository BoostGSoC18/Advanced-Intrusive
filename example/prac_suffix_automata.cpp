#include<bits/stdc++.h>
//This header file needs to be included for using Suffix automata data structure.
#include "boost/intrusive/Suffix_automata/suffix_automata.hpp"

using namespace std;
using namespace boost::intrusive;

//This class needs to be passed on to the initialisation function.
//Base hook or Member hook anything can be used.
class Myclass :public suffix_automata_base_hook<>
{

};
int main()
{
    char text[100];
    //Scanning for input string.
    scanf("%s",text);
    //This builds the suffix automata for the input string.
    suffix_automata<Myclass> first_tree(text);
    //Declaring an iterator
    suffix_automata<Myclass>::iterator itr;
    //Making the iterator point to root
    itr=first_tree.get_root();
    
    return 0;
}