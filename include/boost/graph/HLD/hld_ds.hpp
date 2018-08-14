namespace boost{
    namespace graph{

/*!
<ul>
<li>This is the main class which contains all the methods related to Heavy light decomposition.</li>
<li>This is a very popular decomposition because it has many applications in solving tree based problems.</li>
<li>With this decomposition we can travel between any 2 nodes in tree with just O(log(N)) chains.</li>
</ul>
*/
template<typename Graph>
class HLD
{
private:
    int chainNo=0;
    int *subtree,*visit,*chainHead,*chainPos,*chainInd,*chainSize,*heavy_child;
private:
    typedef typename graph_traits<Graph>::adjacency_iterator adj_itr;
    void subtreesize(int cur,Graph &graph)
    {
        visit[cur]=1;
        adj_itr ai,ai_end;
        for (boost::tie(ai, ai_end) = adjacent_vertices(cur, graph);ai != ai_end; ++ai)
        {
            if(visit[*ai]!=1)
            {
                subtreesize(*ai,graph);
                subtree[cur]+=subtree[*ai];
            }
        }
        subtree[cur]++;
    }
    void hld_impl(int cur,Graph &graph) 
    {
        if(chainHead[chainNo] == -1)
        {
            chainHead[chainNo]=cur;
        }
        visit[cur]=1;
        chainInd[cur] = chainNo;
        chainPos[cur] = chainSize[chainNo];
        chainSize[chainNo]++;
        int ind = -1,mai = -1;
        adj_itr ai,ai_end;
        for (boost::tie(ai, ai_end) = adjacent_vertices(cur, graph);ai != ai_end; ++ai)
        {
            if(visit[*ai]!=1 && subtree[*ai] > mai)
            {
                mai = subtree[*ai];
                ind = *ai;
            }
        }
        if(ind >= 0)
        {
            hld_impl( ind,graph );
            heavy_child[cur]=ind;
        }
        for (boost::tie(ai, ai_end) = adjacent_vertices(cur, graph);ai != ai_end; ++ai)
        {
            if(visit[*ai]!=1 && *ai != ind) 
            {
                chainNo++;
                hld_impl(*ai,graph);
            }
        }
    }
public:
    /*!
        <ul>
        <li> This function decomposes the input tree into chains by selecting heavy child.
        </li>
        </ul>
        \param root root of input tree
        \param num_nodes total number of vertices in input tree
        \param graph input tree
        \return Nothing
        <p> </p>
        <b> Complexity: </b> O(N)
    */
    HLD(int root,int num_nodes,Graph &graph)
    {
        subtree=(int*)malloc((num_nodes+1)*sizeof(int));
        chainHead=(int*)malloc((num_nodes+1)*sizeof(int));
        chainPos=(int*)malloc((num_nodes+1)*sizeof(int));
        chainInd=(int*)malloc((num_nodes+1)*sizeof(int));
        chainSize=(int*)malloc((num_nodes+1)*sizeof(int));
        visit=(int*)malloc((num_nodes+1)*sizeof(int));
        heavy_child=(int*)malloc((num_nodes+1)*sizeof(int));
        for(int i=0;i<num_nodes;i++)
        {
            chainHead[i]=-1;
            subtree[i]=0;
            visit[i]=0;
            heavy_child[i]=-1;
        }
        subtreesize(root,graph);
        for(int i=0;i<num_nodes;i++)
        {
            visit[i]=0;
        }
        hld_impl(root,graph);
    }
    /*!
    <ul>
        <li> This function gives the head node of the chain to which input node belongs to.
        </li>
        </ul>
    \param node a vertex from input graph
    \return head vertex of chain to which input node belongs to.
    <p> </p>
    <b> Complexity: </b> O(1) - constant time

    */
    int get_chain_head(int node)
    {
        int chain=chainInd[node];
        return chainHead[chain];
    }
    /*!
        <ul>
        <li> This function gives the size of the chain to which input node belongs to.
        </li>
        </ul>
    \param node a vertex from input graph
    \return size of chain to which input node belongs to.
            <p> </p>
        <b> Complexity: </b> O(1) - constant time

    */
    int get_chain_size(int node)
    {
        int chain=chainInd[node];
        return chainSize[chain];
    }
    /*!
        <ul>
        <li> This function gives the heavy child of input node.
        </li>
        </ul>
    \param node a vertex from input graph
    \return if input node is leaf node returns -1 else returns heavy child of input node.
            <p> </p>
        <b> Complexity: </b> O(1) - constant time

    */
    int get_heavy_child(int node)
    {
        int child=heavy_child[node];
        return child;
    }

};

    }
}
