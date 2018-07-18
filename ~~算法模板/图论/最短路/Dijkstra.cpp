/*
单源最短路 2
Dijkstra算法

考虑没有负边的情况
在Bellman-Ford 算法中，如果d[i]还不是最短距离，
即使进行d[j]=d[i]+(从i到j的边的权值)的更新，d[j]也不会变成最短距离
并且，即使d[i]没有变化，每一次循环也要检查一遍从i出发的所有边，这很浪费时间。
故可作如下优化
1、找到最短距离已经确定的顶点，从它出发更新相邻顶点的最短距离
2、此后不需再关心1中的最短距离已经确定的顶点

*/

int cost[MAX_V][MAX_V];//cost[u][v]表示边e=(u,v)的权值（不存在这条边时设为INF)
int d[MAX_V];//顶点s出发的最短距离
bool used[MAX_V];//已经使用过的图
int V;//顶点数

//求从起点s出发到各个顶点的最短距离
void dijkstra(int s)
{
    fill(d,d+V,INF);
    fill(used,used+V,false);
    d[s]=0;
    while(true)
    {
        int v=-1;
        //从尚未使用过的顶点中选择一个距离最小的顶点
        for(int u=0;u<V;u++)
        {
            if(!used[u]&&(v==-1||d[u]<d[v]))
                v=u;
        }
        if(v==-1)
            break;//没有找到就break
        used[v]=true;
        for(int u=0;u<V;u++)
        {
            d[u]=min(d[u],d[v]+cost[v][u]);
        }
    }
}

//使用邻接表算法的复杂度是 O(|E|log|V|)
//当所有边权值相等时，单源最短路可以通过BFS求解，此时，Dijkstra算法使用的
//priority_queue和queue具有相同效果，因此复杂度会发生变化 变为O（V）
struct edge
{
    int to,cost;
    edge(int x,int y){to=x;cost=y;}
};
typedef pair<int,int> P;//first是最短距离，second是顶点的编号
int V;
vector <edge>G[MAX_V];
int d[MAX_V];
void add_edge(int u,int v,int cost)
{
    G[u].pb(edge(v,cost));
}
void dijkstra(int s)
{
    //通过指定greater<P>参数，堆按照first从小到大的顺序取出值
    priority_queue<P,vector<P>,greater<P> >que;
    fill(d,d+V,INF);
    d[s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top();que.pop();
        int v=p.second;
        if(d[v]<p.first)
            continue;
        for(int i=0;i<G[v].size();i++)
        {
            edge e=G[v][i];
            if(d[e.to]>d[v]+e.cost)
            {
                d[e.to]=d[v]+e.cost;
                que.push(P(d[e.to],e.to));
            }
        }
    }
}
/*
相对于Bellman-Ford的O（|V||E|）的复杂度，Dijkstra算法的复杂度更高效
但仅适用于没有负边的情况
*/
