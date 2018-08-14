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
template<typename iterator>
void substring_present(char *text,int index,int j,iterator curr_node,int &ans)
{
    if(curr_node->children[text[index]-97]==NULL)
    {
        ans=0;
    }
    else
    {
        curr_node.get_child(text[index]);
        if(index<j)
            substring_present(text,index+1,j,curr_node,ans);
        else
            ans=1;
    }
}
template<typename iterator>
void check(char *text,iterator root)
{
    int len=strlen(text);
    int ans=-1;
    for(int i=0;i<len;i++)
    {
        for(int j=i;j<len;j++)
        {
            substring_present<iterator>(text,i,j,root,ans);
            if(ans==0)
            {
                cout << "fail\n";    
                break;
            }
        }
        if(ans==0)
        {
            break;
        }
    }
    if(ans==1)
    {
        cout << "Success\n";
    }
}
int main()
{
    vector<string> testcases;
    vector<string>::iterator itr;
    ifstream file("suffix_automata_testcases");
    string line;
    while(getline(file, line))
    {
        testcases.push_back(line);
    }
    for(int t=0;t<testcases.size();t++)
    {
        char text[100];int i;
        for(i=0;i<testcases[t].size();i++)
        {
            text[i]=testcases[t][i];
        }
        text[i]='\0';
        suffix_automata<Myclass> first_tree(text);
        suffix_automata<Myclass>::iterator itr;
        itr=first_tree.get_root();
        check(text,itr);
    }    
    return 0;
}
