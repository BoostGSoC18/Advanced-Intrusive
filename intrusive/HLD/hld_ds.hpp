template<typename Graph>
class HLD
{
private:
    int chainNo=0;
    int *subtree,*visit,*chainHead,*chainPos,*chainInd,*chainSize;
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
    HLD(int root,int num_nodes,Graph &graph)
    {
        subtree=(int*)malloc((num_nodes+1)*sizeof(int));
        chainHead=(int*)malloc((num_nodes+1)*sizeof(int));
        chainPos=(int*)malloc((num_nodes+1)*sizeof(int));
        chainInd=(int*)malloc((num_nodes+1)*sizeof(int));
        chainSize=(int*)malloc((num_nodes+1)*sizeof(int));
        visit=(int*)malloc((num_nodes+1)*sizeof(int));
        for(int i=0;i<num_nodes;i++)
        {
            chainHead[i]=-1;
            subtree[i]=0;
            visit[i]=0;
        }
        subtreesize(root,graph);
        for(int i=0;i<num_nodes;i++)
        {
            visit[i]=0;
        }
        hld_impl(root,graph);
    }
    int get_chain_head(int node)
    {
        int chain=chainInd[node];
        return chainHead[chain];
    }
    int get_chain_size(int node)
    {
        int chain=chainInd[node];
        return chainSize[chain];
    }
};