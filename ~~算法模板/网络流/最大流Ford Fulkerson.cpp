/*
    复杂度上界 FE  （F为最大流）
*/
//用于表示边的结构体（终点、容量、反向边）
struct edge
{
    int to,cap,rev;
};
vector <edge> G[MAX];//图的邻接表表示
bool used[MAX];//DFS中用到的访问标记
//向图中增加一条从s到t容量为cap的边
void add_edge(int from,int to,int cap)
{
    G[from].push_back((edge){to,cap,G[to].size()});
    G[to].push_back((edge){from,0,G[from].size()-1});
}
//通过dfs寻找增广路
int dfs(int v,int t,int f)
{
    if(v==t)
        return f;
    used[v]=true;
    for(int i=0;i<G[v].size();i++)
    {
        edge &e=G[v][i];
        if(!used[e.to]&&e.cap>0)
        {
            int d=dfs(e.to,t,min(f,e.cap));//测试这样分配的流量能否增大总流量
            if(d>0)//若增大了总流量
            {
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
int max_flow(int s,int t)
{
    int flow=0;
    for(;;)
    {
        memset(used,0,sizeof(used));
        int f=dfs(s,t,INF);
        if(f==0)//流量已经不会继续增加
            return flow;
        flow+=f;
    }
}
int main()
{

    return 0;
}
