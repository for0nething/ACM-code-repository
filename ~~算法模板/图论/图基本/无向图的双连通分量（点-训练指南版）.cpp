/*
    对于一个连通图，如果任意两点至少存在两条“点不重复”的路径，则说这个图是点-双连同的（一般简称双连通，biconnected）
    该要求等价于任意两条边都在同一个简单环中，即内部无割顶
    如果任意两点至少存在两条“边不重复”的路径，则说这个图是“边-双连通”的
    该要求只需要 每条边都至少在一个简单环中，即所有边都不是桥

    对于一无向图，点-双连通的极大子图称为双连通分量或块
    每条边恰属于一个双连通分量  （？？ 不理解）   但不同双连通分量可能会有公共点
    可以证明不同双连通分量最多只有一个公共点，且它一定是割顶。
    另一方面，任意割顶都是至少两个不同双连同分量的公共点

    同理，边-双连通分量的极大子图称为边-双连通分量
    除了桥不属于任何边-连通分量之外，其他每条边恰好属于一个边-双连通分量
    且把所有桥删除之后，每个连通分量对应原图中的一个边-双连通分量

    以下为 计算 点-双连通分量 的算法
    该算法用一个栈S来保留当前BCC中的边
    与计算割顶的算法一样 最初的dfs fa需要赋负值
    初始仅G（原图）需要初始化
    默认图顶点编号0开始 如果需要1开始可以直接更改
*/
//割顶的bccno无意义
const int maxn=1e5+5;
struct Edge{int u,v;};
int pre[maxn],iscut[maxn],bccno[maxn],dfs_clock,bcc_cnt;//bccno记录每一点所属的BCC的编号
vector<int> G[maxn],bcc[maxn];//bcc数组存储某一BCC中所有的点  G存原图
stack<Edge>S;
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    int child=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        Edge e=(Edge){u,v};
        if(!pre[v])//未访问过v
        {
            S.push(e);child++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);//用后代的low函数更新自己
            if(lowv>=pre[u])
            {
                iscut[u]=true;//是割顶
                bcc_cnt++;//双连通分量个数++
                bcc[bcc_cnt].clear();//注意！bcc从1开始编号
                for(;;)
                {
                    Edge x=S.top();S.pop();
                    if(bccno[x.u]!=bcc_cnt){bcc[bcc_cnt].push_back(x.u);bccno[x.u]=bcc_cnt;}
                    if(bccno[x.v]!=bcc_cnt){bcc[bcc_cnt].push_back(x.v);bccno[x.v]=bcc_cnt;}
                    if(x.u==u&&x.v==v)break;//到了当前割顶的边
                }
            }
        }
        else if(pre[v]<pre[u]&&v!=fa)
        {
            S.push(e);lowu=min(lowu,pre[v]);//用反向边更新自己
        }
    }
    if(fa<0&&child==1)iscut[u]=0;
    return lowu;
}
void find_bcc(int n)
{
    //调用结束后S保证为空 所以不用清空
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    dfs_clock=bcc_cnt=0;
    for(int i=0;i<n;i++)//默认图顶点编号0开始 如果需要1开始可以直接更改
        if(!pre[i])dfs(i,-1);
}

/*
    边-双连通分量可以用更简单的方法求出
    先做依次dfs标记出所有的桥，再做一次dfs找出边-双连通分量
    因为边-双连通分量是无公共结点的，所以只要在第二次dfs的时候保证不经过桥即可

*/
