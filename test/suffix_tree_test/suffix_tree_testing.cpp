#include<bits/stdc++.h>
using namespace std;
#include "boost/Advanced-Intrusive-master/Suffix_tree/suffix_tree.hpp"
using namespace boost::intrusive;
struct test_node
{
    struct test_node *children[256];
    int leaf;
    int start,end;
};
void search_extend(struct test_node *temp,int start,int end,char *text)
{
    struct test_node *parent;
    for(int i=start;i<=end;)
    {
        if(temp->children[text[i]]!=NULL)
        {
            parent=temp;
            temp=temp->children[text[i]];
        }
        else
        {
            if(temp->leaf==1)
            {
                int cnt=temp->end-temp->start+1;
                temp->end=end;
                temp->start=temp->end-cnt;
            }
            else
            {
                temp->children[text[end]]=(struct test_node*)malloc(sizeof(struct test_node));
                temp->children[text[end]]->start=end;
                temp->children[text[end]]->end=end;
                temp->children[text[end]]->leaf=1;
            }
            i++;
        }
        for(int m=temp->start;(m<=temp->end && i<=end);)
        {
            if(text[i]==text[m])
            {
                i++;m++;
            }
            else
            {
                struct test_node *newnode=(struct test_node*)malloc(sizeof(struct test_node));
                newnode->start=temp->start;
                newnode->end=m-1;
                newnode->leaf=0;
                newnode->children[text[m]]=temp;
                parent->children[text[temp->start]]=newnode;
                temp->start=m;
                newnode->children[text[i]]=(struct test_node*)malloc(sizeof(struct test_node));
                newnode->children[text[i]]->start=i;
                newnode->children[text[i]]->end=i;
                newnode->children[text[i]]->leaf=1;
                i++;
                break;
            }
        }
    }
}
void extend_suffix_tree(struct test_node *root,int pos,char *text,int start)
{
	if(pos==start)
    {
        root->children[text[pos]]=(struct test_node*)malloc(sizeof(struct test_node));
        root->children[text[pos]]->start=0;
        root->children[text[pos]]->end=0;
        root->children[text[pos]]->leaf=1;
    }
    else
    {
        for(int i=0;i<=pos;i++)
        {
            search_extend(root,i,pos,text);
        }
    }
}
void construct_suffix_tree(struct test_node *root,char *text,int start,int end)
{
    for(int i=start;i<=end;i++)
    {
        extend_suffix_tree(root,i,text,start);
    }
} 
template<typename iterator>
void testing(char *text,struct test_node *test_root,iterator root)
{
    stack<struct test_node*> test_stack;
    queue<struct test_node*> test_queue;
    test_queue.push(test_root);
    while(!test_queue.empty())
    {
        struct test_node *temp=test_queue.front();
        for(int i=0;i<256;i++)
        {
            if(temp->children[i]!=NULL)
            {
                test_stack.push(temp->children[i]);
                test_queue.push(temp->children[i]);
            }
        }
        test_queue.pop();
    }
    
    stack<iterator> base_stack;
    queue<iterator> base_queue;
    base_queue.push(root);
    while(!base_queue.empty())
    {
        iterator temp=base_queue.front();
        printf("base %d %d\n",temp->start,*temp->end);
        for(int i=0;i<256;i++)
        {
            if(temp->children[i]!=NULL)
            {
                iterator child;
                child=temp;
                char ch=i;
                child.get_child(ch);
                base_stack.push(child);
                base_queue.push(child);
            }
        }
        base_queue.pop();
    }
    int flag=0;
    while(!test_stack.empty() && !base_stack.empty())
    {
        struct test_node *test_temp=test_stack.top();
        iterator base_temp=base_stack.top();
        if(test_temp->start==base_temp->start && test_temp->end==*base_temp->end)
        {

        }
        else
        {
            flag=1;
        }
        test_stack.pop();base_stack.pop();
    }
    if(flag==0)
    {
        printf("Checking done\n");
    }
    else
    {
        printf("Wrong\n");
    }
} 

class Myclass :public suffix_tree_base_hook<>
{

};
int main()
{
    char text[100];
    scanf("%s",text);
    suffix_tree<Myclass> first_tree(text,0,strlen(text)-1);
    typedef suffix_tree<Myclass>::iterator iterator;
    iterator itr=first_tree.get_root();
    struct test_node *test_root=(struct test_node*)malloc(sizeof(struct test_node));
    for(int i=0;i<256;i++)
    {
    	test_root->children[i]=NULL;
	}
    construct_suffix_tree(test_root,text,0,strlen(text)-1);
    testing<iterator>(text,test_root,itr);
    return 0;
}