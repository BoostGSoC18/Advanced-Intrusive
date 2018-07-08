#include <bits/stdc++.h>
using namespace std;
struct node{
    struct node *children[256];
    int leaf;
    int start,end;
};
void search_extend(struct node *temp,int start,int end,char *text)
{
    struct node *parent;
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
                temp->children[text[end]]=(struct node*)malloc(sizeof(struct node));
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
                struct node *newnode=(struct node*)malloc(sizeof(struct node));
                printf("HA %d %d %d\n",i,m,temp->start);
                newnode->start=temp->start;
                newnode->end=m-1;
                newnode->leaf=0;
                newnode->children[text[m]]=temp;
                parent->children[text[temp->start]]=newnode;
                temp->start=m;
                newnode->children[text[i]]=(struct node*)malloc(sizeof(struct node));
                newnode->children[text[i]]->start=i;
                newnode->children[text[i]]->end=i;
                newnode->children[text[i]]->leaf=1;
                i++;
                break;
            }
        }
    }
}
void extend_suffix_tree(struct node *root,int pos,char *text)
{
    if(pos==0)
    {
        root->children[text[pos]]=(struct node*)malloc(sizeof(struct node));
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
void construct_suffix_tree(struct node *root,char *text,int n)
{
    for(int i=0;i<n;i++)
    {
        extend_suffix_tree(root,i,text);
    }
}
void testing(struct node *root,char *text,int len)
{
    queue<struct node*> test_queue;
    test_queue.push(root);
    while(!test_queue.empty())
    {
        struct node *temp=test_queue.front();
        printf("%d %d %d\n",temp->start,temp->end,temp->leaf);
        for(int i=0;i<256;i++)
        {
            if(temp->children[i]!=NULL)
            {
                test_queue.push(temp->children[i]);
            }
        }
        test_queue.pop();
    }


}
int main()
{
    struct node *root=(struct node*)malloc(sizeof(struct node));
    for(int i=0;i<256;i++)
    {
    	root->children[i]=NULL;
	}
    char text[100];
    scanf("%s",text);
    int len=strlen(text);
    construct_suffix_tree(root,text,len);
	testing(root,text,len);

	return 0;
}
