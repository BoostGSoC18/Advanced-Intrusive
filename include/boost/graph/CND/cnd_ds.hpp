#define MAXN 1025
namespace boost{
    namespace graph{
/*!
<ul>
<li>This is the main class which contains all the methods related to Centroid decomposition.</li>
<li>This is a very popular decomposition because it has many applications in solving tree based problems.</li>
<li>This decomposition creates a tree of height O(log(N))</li>  
</ul>
*/
        template<typename Graph>
        class CND
        {
            public:
            /*!
            This contains decomposed tree formed by centroid decomposition
            */
            Graph decomposed_rooted_tree;
            /*!
            This contains the root of decomposed tree.
            */
            int decomposed_root;
            private:
            void DFS(int src, Graph input_tree, bool visited[], int subtree_size[],bool centroidMarked[], int* n)
            {
                visited[src] = true;
                *n += 1;
                subtree_size[src] = 1; 
                typedef typename graph_traits<Graph>::adjacency_iterator adj_itr;
                adj_itr ai,ai_end;
                for (boost::tie(ai, ai_end) = adjacent_vertices(src, input_tree);ai != ai_end; ++ai)
                {
                    if (!visited[*ai] && !centroidMarked[*ai])
                    {
                        DFS(*ai, input_tree,visited, subtree_size,centroidMarked, n);
                        subtree_size[src]+=subtree_size[*ai];
                    }
                }
            }
            int getCentroid(int src, Graph input_tree,bool visited[], int subtree_size[], bool centroidMarked[],int n)
            {
                bool is_centroid = true;
                visited[src] = true;
                int heaviest_child = 0; 
                typedef typename graph_traits<Graph>::adjacency_iterator adj_itr;
                adj_itr ai,ai_end;
                for (boost::tie(ai, ai_end) = adjacent_vertices(src, input_tree);ai != ai_end; ++ai)
                {
                    if (!visited[*ai] && !centroidMarked[*ai])
                    {
                        if (subtree_size[*ai]>n/2)
                            is_centroid=false;
                        if (heaviest_child==0 || subtree_size[*ai]>subtree_size[heaviest_child])
                            heaviest_child = *ai;
                    }
                }
                if (is_centroid && n-subtree_size[src]<=n/2)
                    return src;
                return getCentroid(heaviest_child,input_tree, visited, subtree_size,centroidMarked, n);
            }
            int getCentroid(bool centroidMarked[],Graph input_tree,int src)
            {
                bool visited[MAXN]; 
                int subtree_size[MAXN];
                memset(visited, false, sizeof visited);
                memset(subtree_size, 0, sizeof subtree_size);
                int n = 0;
                DFS(src, input_tree,visited, subtree_size,centroidMarked, &n); 
                for (int i=0; i<MAXN; i++)
                    visited[i] = false;
                int centroid = getCentroid(src,input_tree, visited, subtree_size,centroidMarked, n);
                centroidMarked[centroid]=true;
                return centroid;
            }
            int decomposeTree(Graph input_tree,int root,bool centroidMarked[],Graph &out_tree)
            {
                int cend_tree = getCentroid(centroidMarked,input_tree,root); 
                typedef typename graph_traits<Graph>::adjacency_iterator adj_itr;
                adj_itr ai,ai_end;
                for (boost::tie(ai, ai_end) = adjacent_vertices(cend_tree, input_tree);ai != ai_end; ++ai)
                {
                    if (!centroidMarked[*ai])
                    {
                        int cend_subtree = decomposeTree(input_tree,*ai,centroidMarked,out_tree);
                        add_edge(cend_tree,cend_subtree,out_tree);
                    }
                }
                return cend_tree;
            }
        /*!
        <ul>
        <li> This function creates a tree of height O(log(N)) by recursively selecting centroid and decomposing tree.
        </li>
        </ul>
        \param input_tree input tree
        \param root root of input tree
        \param ver_cnt total number of vertices in input tree
        \return Nothing
        <p> </p>
        <b> Complexity: </b> O(N)
    */
            public:
            CND(Graph input_tree,int root,int ver_cnt)
            {
                bool centroidMarked[MAXN];
                for(int i=0;i<MAXN;i++)
                    centroidMarked[i]=false;
                Graph decomposed_tree(ver_cnt);
                int centroid=decomposeTree(input_tree,root,centroidMarked,decomposed_tree);
                decomposed_rooted_tree=decomposed_tree;
                decomposed_root=centroid;
            }
        };
    }
}
