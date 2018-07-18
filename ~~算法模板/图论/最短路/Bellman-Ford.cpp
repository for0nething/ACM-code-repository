/*
单源最短路
Bellman-Ford算法

设从起点s出发到顶点i的最短距离为d[i].则下述等式成立
d[i]=min{d[j]+（从j到i的边的权值）|e=(j,i)∈E}
若满足DAG，可以按拓扑序给顶点编号，利用递推求解
不然，设初值 d[s]=0，d[i]=INF（足够大的常数）
只要无负圈，更新操作就是有限的

*/

struct edge
{
    int from,to,cost;
};
//从顶点from 指向顶点 to的权值为const的边

edge es[MAX_E];//边
int d[MAX_V];//最短距离
int V,E;//V是顶点数，E是边数

void shortest_path(int s)
{
    for(int i=0;i<V;i++)
        d[i]=INF;
    d[s]=0;
    while(1)
    {
        bool update=false;
        for(int i=0;i<E;i++)
        {
            edge e=es[i];
            if(d[e.from]!=INF&&d[e.to]>d[e.from]+e.cost)
            {
                d[e.to]=d[e.from]+e.cost;
                update=true;
            }
        }
        if(!update)
            break;
    }

}
//求解从顶点s出发到所有点的最短距离

/*
如果图中不存在从s可到达的负圈，那么最短路不会经过同一个顶点两次
（即最多通过|V|-1条边）
while(1)最多循环|V|-1次
而若有，在第|V|次循环中也会更新d的值，故可用此性质检查负圈
（此时初始时将所有d[i]初始化为0）
*/

bool find_negative_loop()
{
    memset(d,0,sizeof(d));
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<E;j++)
        {
            edge e=es[j];
            if(d[e.to]>d[e.from]+e.cost)
            {
                d[e.to]=d[e.from]+e.cost;
                if(i==V-1)//到第n次仍然更新了，则存在负圈
                    return true;
            }
        }
    }
    return false;
}
//如果返回true则存在负圈
