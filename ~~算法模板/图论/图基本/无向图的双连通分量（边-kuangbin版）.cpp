/*
    ********  不考虑重边版  *******
    无向图的边-双连通分量
    去掉桥，其余的连通分支就是边双连通分支了
    一个有桥的连通图要变成 边-双连通图的话，把双连通子图缩为1个点，形成一棵树。
    最少需要加的边数为 (leaf+1)/2  (leaf为叶子结点的个数，无向图中即为度数为1点的个数）

    模版代码以POJ3177为例 给定一个连通的无向图G，至少要添加几条边，才能使其变为双连通图
    此模版有重边无影响 将重边视为只存在1条
    例：
        1 2之间如果连了两条边 亦只视作1条
    第一次调用Tarjan pre取0即可
*/

const int MAXN=5010;//点数
const int MAXM=20010;//边数，因为是无向图，所以值要*2
struct Edge
{
    int to,next;
    bool cut;//是否是桥标记
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong数组的值是1——block
int Index,top;
int block;//边双连通分量个数
bool Instack[MAXN];
int bridge;//桥的数目
void addedge(int u,int v)
{
    edge[tot].to=v;edge[tot].next=head[u];edge[tot].cut=false;head[u]=tot++;
}
void Tarjan(int u,int pre)//调用此之前调用init初始化各个变量
{
    int v;
    Low[u]=DFN[u]=++Index;
    Stack[top++]=u;Instack[u]=true;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].to;
        if(v==pre)continue;
        if(!DFN[v])
        {
            Tarjan(v,u);
            if(Low[u]>Low[v])Low[u]=Low[v];
            if(Low[v]>DFN[u])//u的后代只能连回v自己 则u、v是桥
            {
                bridge++;edge[i].cut=true;
                edge[i^1].cut=true;
            }
        }
        else if(Instack[v]&&Low[u]>DFN[v])
            Low[u]=DFN[v];
    }
    if(Low[u]==DFN[u])
    {
        block++;
        do
        {
            v=Stack[--top];Instack[v]=false;Belong[v]=block;
        }
        while(v!=u);
    }
}
void init()
{
    tot=Index=top=block=bridge=0;
    memset(head,-1,sizeof(head));
//    memset(Instack,false,sizeof(Instack));//不加可能可以
    memset(DFN,0,sizeof(DFN));
}

int f,r,u,v,cnt;
int idx[MAXN];
int main()
{
    scanf("%d%d",&f,&r);
    init();
    for(int i=1;i<=r;i++)
    {
        scanf("%d%d",&u,&v);addedge(u,v);addedge(v,u);
    }
    Tarjan(1,0);
    for(int i=1;i<=f;i++)
        for(int j=head[i];j!=-1;j=edge[j].next)
            if(edge[j].cut)
                idx[Belong[i]]++;
    for(int i=1;i<=block;i++)
        if(idx[i]==1)
            ++cnt;
    printf("%d\n",(cnt+1)/2);
}


/*
    ******** 考虑重边版 *********

    在边的属性中增加重边标记 两点之间如果有重边仍只添加1条 不过重边标记需为true
    e.g. 1、2之间有多条边，全都考虑，则1、2构成边连通分量 其之间的边不再视为桥


*/
const int MAXN=2e5+5;//点数
const int MAXM=2e6+5;//边数，因为是无向图，所以值要*2
struct Edge
{
    int to,next;
    bool cut;//是否是桥标记
    bool chong;
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong数组的值是1——block
int Index,top;
int block;//边双连通分量个数
bool Instack[MAXN];
int bridge;//桥的数目
void addedge(int u,int v,bool ch)
{
    edge[tot].to=v;edge[tot].next=head[u];edge[tot].chong=ch;edge[tot].cut=false;head[u]=tot++;
}
void Tarjan(int u,int pre,bool ff)//调用此之前调用init初始化各个变量   ff表示此边是否为重边（即有多条的）
{
    int v;
    Low[u]=DFN[u]=++Index;
    Stack[top++]=u;Instack[u]=true;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].to;
        if(v==pre&&(!ff))continue;//与无重边的区别所在 如果不是重边才continue
        if(!DFN[v])
        {
            Tarjan(v,u,edge[i].chong);
            if(Low[u]>Low[v])Low[u]=Low[v];
            if(Low[v]>DFN[u])//u的后代只能连回v自己 则u、v是桥
            {
                bridge++;edge[i].cut=true;
                edge[i^1].cut=true;
            }
        }
        else if(Instack[v]&&Low[u]>DFN[v])
            Low[u]=DFN[v];
    }
    if(Low[u]==DFN[u])
    {
        block++;
        do
        {
            v=Stack[--top];Instack[v]=false;Belong[v]=block;
        }
        while(v!=u);
    }
}
void init()
{
    tot=Index=top=block=bridge=0;
    memset(head,-1,sizeof(head));
//    memset(Instack,false,sizeof(Instack));//不加可能可以
    memset(DFN,0,sizeof(DFN));
}
int n,m,u,v;
int main()
{
    memset(head,-1,sizeof(head));
    while(scanf("%d%d",&n,&m)&&n)
    {
        init();
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);if(u==v)continue;
            if(u>v)swap(u,v);
            s.insert(mp(u,v));
        }
        while(!s.empty())
        {
            pii q=*s.begin();
            s.erase(s.begin());
            int num=s.count(q);
            addedge(q.first,q.second,num>0);addedge(q.second,q.first,num>0);
            //除当前边外 还有连接该两点的 则重边标记状态应为true 不过仍只加1条边
            while(num--)s.erase(s.begin());
        }
        Tarjan(1,0,0);
    }
    return 0;
}
