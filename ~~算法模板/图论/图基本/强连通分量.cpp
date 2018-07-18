/*
    有向图的强连通分量
    定义lowlink（u）为u及其后代能追溯到的最早（最先被发现）祖先点v的pre（v）值
    用一个附加栈S保存当前SCC中的结点（这些结点形成一棵子树而不一定是一个链）
    初始下标从0开始 （若要从1开始 只需该find_scc函数中的i=0）
*/
const int maxn=1e5+5;
vector<int> G[maxn];//存原图 初始化仅需初始此
int pre[maxn],lowlink[maxn],sccno[maxn],dfs_clock,scc_cnt;//scc_cnt为SCC计数器 sccno[i]为i所在的SCC编号
stack<int>S;
void dfs(int u)
{
    pre[u]=lowlink[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            dfs(v);
            lowlink[u]=min(lowlink[u],lowlink[v]);
        }
        else if(!sccno[v])
            lowlink[u]=min(lowlink[u],pre[v]);
    }
    if(lowlink[u]==pre[u])
    {
        scc_cnt++;
        for(;;)
        {
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u)break;
        }
    }
}
void find_scc(int n)
{
    dfs_clock=scc_cnt=0;
    memset(sccno,0,sizeof(sccno));
    memset(pre,0,sizeof(pre));
    for(int i=0;i<n;i++)
        if(!pre[i])dfs(i);
}
