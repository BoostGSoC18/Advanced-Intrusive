int chainNo=0;
int *subtree,*visit,*chainHead,*chainPos,*chainInd,*chainSize;
void subtreesize(int cur,vector<int> *graph)
{
    visit[cur]=1;
    vector<int>::iterator itr;
    for(itr=graph[cur].begin();itr!=graph[cur].end();itr++)
    {
        if(visit[*itr]!=1)
        {
            subtreesize(*itr,graph);
            subtree[cur]+=subtree[cur]+1;
        }
    }
    subtree[cur]++;
}
void hld_impl(int cur,vector<int> *graph) 
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
    for(int i = 0; i < graph[cur].size(); i++)
    {   
        if(visit[graph[cur][i]]!=1 && subtree[graph[cur][i]] > mai)
        {
            mai = subtree[graph[cur][i]];
            ind = i;
        }
    }
    if(ind >= 0)
    {
        hld_impl( graph[cur][ind],graph );
    }
    for(int i = 0; i < graph[cur].size(); i++)
    {
        if(visit[graph[cur][i]]!=1 && i != ind) 
        {
            chainNo++;
            hld_impl(graph[cur][i],graph);
        }
    }
}
void HLD(int root,int num_nodes,vector<int> graph[])
{
    subtree=(int*)malloc((num_nodes+1)*sizeof(int));
    chainHead=(int*)malloc((num_nodes+1)*sizeof(int));
    chainPos=(int*)malloc((num_nodes+1)*sizeof(int));
    chainInd=(int*)malloc((num_nodes+1)*sizeof(int));
    chainSize=(int*)malloc((num_nodes+1)*sizeof(int));
    visit=(int*)malloc((num_nodes+1)*sizeof(int));
    for(int i=1;i<=num_nodes;i++)
    {
        chainHead[i]=-1;
        subtree[i]=0;
        visit[i]=0;
    }
    subtreesize(root,graph);
    for(int i=1;i<=num_nodes;i++)
    {
        visit[i]=0;
    }
    hld_impl(root,graph);
}
