
/*
    调用前将所有节点的pre初始化为0
    且第一次调用时fa应为负数
    （为训练指南P314 缺少桥的判定的代码）
    low[u]为u及其后代所能连回的最早的祖先的pre值
*/

int dfs(int u,int fa)//u在DFS树中的父节点是fa
{
    int lowu=pre[u]=++dfs_clock;
    int child=0;//子节点数目
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(!pre[v])//没访问过v
        {
            child++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);//用后代的low函数更新u的low函数
            if(lowv>=pre[u])
                iscut[u]=true;
        }
        else if(pre[v]<pre[u]&&v!=fa)
            lowu=min(lowu,pre[v]);//用反向边更新u的low函数
    }
    if(fa<0&&child==1)iscut[u]=0;
    low[u]=lowu;
    return lowu;
}

