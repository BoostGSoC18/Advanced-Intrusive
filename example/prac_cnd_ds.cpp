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

// This header file needs to be included for using Centroid decomposition.
#include "boost/graph/CND/cnd_ds.hpp"
using namespace boost::graph;
int main()
{
    int i,n,a,b;
    scanf("%d",&n);
    //Graph type 
    typedef adjacency_list<vecS, vecS, undirectedS> Graph;
    //Initialisation of Graph object
    Graph graph(n);
    for(i=1;i<n;i++)
    {
        scanf("%d %d",&a,&b);
        add_edge(a,b,graph);        
    }
    // "CND" class is called which constructs an object which contains the decomposed tree and its root.
    CND<Graph> decomposed_tree(graph,0,n);
    
    // Printing the centroid of entire input tree or root of the centroid decomposition of input tree.
    printf("%d\n",decomposed_tree.decomposed_root);

    return 0;

}