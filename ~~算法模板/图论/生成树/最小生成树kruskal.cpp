/*
    kruskal最小生成树算法
    按照边的权值的顺序从小到大看一遍，如果不产生圈（重边也考虑在内）
    就把当前这条边加入到生成树中
    是否产生圈只需看两点之前是否在同一连通分量里
    使用并查集判断是否属于同一个连通分量
*/
#define rank rankk  //由于与某个库名称相同，故事先define
/*
并查集
复杂度为阿克曼函数的反函数，比O(log(n))还快
*/

int par[MAX];//父亲
int rank[MAX];//树的高度
//初始化n个元素
void init(int n)
{
    for(int i=0;i<=n;i++)
    {
        par[i]=i;
        rank[i]=0;
    }
}
//查询树的根，期间加入了路径压缩
int find(int x)
{
    if(par[x]==x)
        return x;
    else
        return par[x]=find(par[x]);
}
//合并x和y所属的集合
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y)
        return ;
    if(rank[x]<rank[y])
        par[x]=y;
    else
    {
        par[y]=x;
        if(rank[x]==rank[y])
            rank[x]++;
    }
}
//判断x和y是否属于同一个集合
bool same(int x,int y)
{
    return find(x)==find(y);
}
/*
建立结构体记录边
*/
struct edge
{
    int u,v,cost;
};
/*储存边的数组*/
edge es[MAX];
int V,E;//顶点数、边数
bool cmp(const edge &e1,const edge &e2)
{
    return e1.cost<e2.cost;
}
ll kruskal(edge *e,int edge_num,int vertice_num)//e为存储边的数组，下标从0开始
{
    sort(e,e+edge_num,cmp);//按照edge.cost顺序从小到大排序
    init(vertice_num);//初始化并查集
    ll re=0;
    for(int i=0;i<edge_num;i++)
    {
        edge tem=e[i];
        if(!same(tem.u,tem.v))
        {
            unite(tem.u,tem.v);
            re+=(ll)tem.cost;
        }
    }
    return re;
}
