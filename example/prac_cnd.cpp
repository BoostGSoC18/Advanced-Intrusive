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
#include "boost/graph/CND/cnd_function.hpp"
//using namespace boost::graph;
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
    pair<Graph,int> decomposed_graph;
    // "CND" function is called which returns a pair which consists of centroid decomposition of input tree and
    // root of the decomposition.
    decomposed_graph=CND<Graph>(graph,0,n);
    
    // Printing the centroid of entire input tree or root of the centroid decomposition of input tree.
    printf("%d\n",decomposed_graph.second);

    return 0;

}