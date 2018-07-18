/*
LCA 最近公共祖先

1、基于二分搜索的算法

*/
//原始版   O(n) n为节点最大深度
vector<int> G[MAX_V];//图的邻接表表示
int root;//根节点的编号
int parent[MAX_V];//父亲节点（根节点父亲记为-1）
int depth[MAX_V];//节点的深度
void dfs(int v,int p,int d)
{
    parent[v]=p;
    depth[v]=d;
    for(int i=0;i<G[v].size();i++)
    {
        if(G[v][i]!=p)
            dfs(G[v][i],v,d+1);
    }
}
void init()
{   //预处理
    dfs(root,-1,0);
}
int lca(int u,int v)
{
    while(depth[u]>depth[v])
        u=parent[u];
    while(depth[v]>depth[u])
        v=parent[v];
    while(u!=v)
    {
        u=parent[u];v=parent[v];
    }
    return u;
}


//预处理 二分搜索版
//MAX_LOG_V 最少开到 log2(MAX_V)+1
vector<int> G[MAX_V];//图的邻接表表示
int root;//根节点编号
int parent[MAX_LOG_V][MAX_V];//向上走2^k步时到达的节点   （超过根时记为-1）
int depth[MAX_V];//节点的深度
void dfs(int v,int p,int d)
{
    parent[0][v]=p;
    depth[v]=d;
    for(int i=0;i<G[v].size();i++)
    {
        if(G[v][i]!=p)
            dfs(G[v][i],v,d+1);
    }
}
//预处理
void init(int V)
{
    //预处理出 parent[0]和depth
    dfs(root,-1,0);
    //预处理出parent
    for(int k=0;k+1<MAX_LOG_V;k++)
        for(int v=0;v<V;v++)
        {
            if(parent[k][v]<0)
                parent[k+1][v]=-1;
            else
                parent[k+1][v]=parent[k][parent[k][v]];
        }
}
//计算u和v的LCA
int lca(int u,int v)
{
    //让u和v向上走到同一深度
    if(depth[u]>depth[v])
        swap(u,v);
    for(int k=0;k<MAX_LOG_V;k++)
    {
        if(((depth[v]-depth[u])>>k)&1)
            v=parent[k][v];
    }
    if(u==v)
        return u;
    for(int k=MAX_LOG_V-1;k>=0;k--)
    {
        if(parent[k][u]!=parent[k][v])
        {
            u=parent[k][u];v=parent[k][v];
        }
    }
    return parent[0][u];
}



