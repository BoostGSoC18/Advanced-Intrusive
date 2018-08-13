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
#include "boost/Advanced-Intrusive-master/HLD/hld_ds.hpp"
using namespace boost::graph;
int main()
{
    int i,n,a,b;
    scanf("%d",&n);
    //Graph type 
    typedef adjacency_list<vecS, vecS, undirectedS> Graph_list;
    //Initialisation of Graph object
    Graph_list graph_list(n);
    for(i=1;i<n;i++)
    {
        scanf("%d %d",&a,&b);
        add_edge(a,b,graph_list);        
    }
    //Decomposition of input graph by HLD
    HLD<Graph_list> decomposed_tree(0,n,graph_list);
    //getting head of chain to which a node belongs to
    std::cout << decomposed_tree.get_chain_head(0) << "\n";
    //getting size of chain to which node belongs to
    std::cout << decomposed_tree.get_chain_size(0) << "\n";
    //returns the heavy child of input node
    std::cout << decomposed_tree.get_heavy_child(0) << "\n";
    



    return 0;

}