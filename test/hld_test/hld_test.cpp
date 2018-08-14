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
#include "boost/graph/HLD/hld_ds.hpp"
using namespace boost::graph;
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
void check(int cur,Graph &graph,bool visited[],int subtree_size[],int heavy_child[],bool result[])
{
    visited[cur] = true;
    subtree_size[cur] = 1; 
    typedef typename graph_traits<Graph>::adjacency_iterator adj_itr;
    adj_itr ai,ai_end;
    int maxi=-1;
    for (boost::tie(ai, ai_end) = adjacent_vertices(cur,graph);ai != ai_end; ++ai)
    {
        if (!visited[*ai])
        {
            check(*ai,graph,visited,subtree_size,heavy_child,result);
            if (maxi<subtree_size[*ai])
            {
                maxi=subtree_size[*ai];
            }
        }
    }
    if(heavy_child[cur]!=-1 && subtree_size[heavy_child[cur]]==maxi)
    {
        result[cur]=true;
    }
    else if(heavy_child[cur]==-1)
    {
        result[cur]=true;
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
    bool visited[1030],result[1030];
    int subtree_size[1030];

    for(int i=0;i<n;i++)
    {
        visited[i]=false;
        subtree_size[i]=0;
        result[i]=false;
    }
    
    HLD<Graph_list> first(0,n,graph_list);
    treesize_vertices<Graph_list>(0,graph_list,visited,subtree_size);
    
    int heavy_child[1030];
    for(i=0;i<n;i++)
    {
        heavy_child[i]=first.get_heavy_child(i);
        visited[i]=false;
    }
    check<Graph_list>(0,graph_list,visited,subtree_size,heavy_child,result);
    for(int i=0;i<n;i++)
    {
        if(result[i]==false)
        {
            cout << "fail\n";
            return 0;
        }
    }
    cout << "success\n";
    
    return 0;

}