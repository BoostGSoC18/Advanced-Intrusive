#include<bits/stdc++.h>
using namespace std;
#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace boost;
#include "boost/Advanced-Intrusive-master/CND/cnd_function.hpp"

template<typename Graph>
void treesize_vertices(int cur,Graph &graph,bool visited[],int subtree_size[])
{
    visited[cur] = true;
    subtree_size[cur] = 1; 
    typedef typename graph_traits<Graph>::adjacency_iterator adj_itr;
    adj_itr ai,ai_end;
    for (boost::tie(ai, ai_end) = adjacent_vertices(cur,graph);ai != ai_end; ++ai)
    {
        if (!visited[*ai])
        {
            treesize_vertices(*ai,graph,visited,subtree_size);
            subtree_size[cur]+=subtree_size[*ai];
        }
    }
}
template<typename Graph>
void check_centroid(int cur,Graph &graph,bool visited[],int subtree_size[],int *check)
{
    visited[cur] = true;
    typedef typename graph_traits<Graph>::adjacency_iterator adj_itr;
    adj_itr ai,ai_end;
    for (boost::tie(ai, ai_end) = adjacent_vertices(cur,graph);ai != ai_end; ++ai)
    {
        if (!visited[*ai])
        {
            if(subtree_size[*ai]>(subtree_size[cur]/2))
            {
                *check=0;
            }
            check_centroid(*ai,graph,visited,subtree_size,check);
        }
    }
}
int main()
{
    int i,n,a,b;
    scanf("%d",&n);
    typedef adjacency_list<vecS, vecS, undirectedS> Graph_list;
    Graph_list graph_list(n);
    for(i=1;i<n;i++)
    {
        scanf("%d %d",&a,&b);
        add_edge(a,b,graph_list);        
    }
    pair<Graph_list,int> copy_graph;
    copy_graph=CND(graph_list,0,n);
    printf("%d\n",copy_graph.second);
    int root=copy_graph.second;
    bool visited[1030];
    int subtree_size[1030];
    for(i=0;i<n;i++)
    {
        visited[i]=false;
        subtree_size[i]=0;
    }
    treesize_vertices<Graph_list>(root,copy_graph.first,visited,subtree_size);
    int check=1;
    for(i=0;i<n;i++)
        visited[i]=false;
    check_centroid<Graph_list>(root,copy_graph.first,visited,subtree_size,&check);
    if(check)
    {
        printf("Success\n");
    }

    return 0;

}
