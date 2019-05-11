#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ull;
typedef long long ll;
//const int INF=0x3f3f3f3f;
const int INF=1e9;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const ll M=1e9+7;
const ll maxn=1e5+7;
const int MAXN=1005;
const int MAX=2e5+5;
const int MAX_N=MAX;
const ll MOD=1e9+7;
//const double eps=0.00000001;
//ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b){
    ll ret=1;
    a%=M;
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
/*
    二分图：
    无向图G为二分图的充分必要条件是，G至少有两个顶点，且其所有回路的长度均为偶数。
    二分图又称作二部图，是图论中的一种特殊模型。 设G=(V,E)是一个无向图，如果顶点V可分割为两个互不相交的子集(A,B)，
    并且图中的每条边（i，j）所关联的两个顶点i和j分别属于这两个不同的顶点集(i in A,j in B)，则称图G为一个二分图。
*/

/*
    性质
    1。一个二分图中的最大匹配数等于这个图中的最小点覆盖数  （König定理）
    2。最小路径覆盖＝｜G｜－最大匹配数
    3。二分图最大独立集=顶点数-二分图最大匹配

定义：
路径覆盖：
在一个ＰＸＰ的有向图中，路径覆盖就是在图中找一些路经，使之覆盖了图中的所有顶点，且任何一个顶点有且只有一条路径与之关联；

最小点覆盖
二分图中，选取最少的点数，使这些点和所有的边都有关联（把所有的边的覆盖），叫做最小点覆盖。

用最大匹配求解最小点覆盖的点：
 匈牙利算法需要我们从右边的某个没有匹配的点，走出一条使得“一条没被匹配、一条已经匹配过，
 再下一条又没匹配这样交替地出现”的路（交错轨，增广路）。但是，现在我们已经找到了最大匹配，已经不存在这样的路了。
 换句话说，我们能寻找到很多可能的增广路，但最后都以找不到“终点是还没有匹配过的点”而失败。
 我们给所有这样的点打上记号：从右边的所有没有匹配过的点出发，按照增广路的“交替出现”的要求可以走到的所有点（最后走出的路径是很多条不完整的增广路）。
 那么这些点组成了最小覆盖点集：右边所有没有打上记号的点，加上左边已经有记号的点。


最大独立（点）集
在一个二分图中,选择一些顶点,使得所选择的点集中任意两个顶点之间没有边相连

/*
判断是否为二分图
如果不确定图是否连通 for循环一遍，遇到color尚未赋值的 先赋该点初值为1，再bipartite
*/
int color[maxn];
bool bipartite(int u)
{
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(color[v]==color[u])return false;
        if(!color[v])
        {
            color[v]=3-color[u];
            if(!bipartite(v))return false;
        }
    }
    return true;
}



/*
    二分图匹配方法1：
    加点（分别连向所有 “电脑” 从所有“任务”连出）作为源点和汇点
    此时最大匹配（总点数）即为2*最大流

*/

//输入
int N,K;
bool can[MAX_N][MAX_K]; //can[i][j]=计算机i能够处理任务j
void solve()
{
    //0-N-1 计算机对应的顶点
    //N- N+K-1 任务对应的顶点
    int s=N+K,t=S+1;//自行添加源点、汇点
    //在源点和计算机之间连边
    for(int i=0;i<N;i++)
        add_edge(s,i,1);
    //在任务和汇点之间连边
    for(int i=0;i<K;i++)
        add_edge(N+i,t,1);
    //在计算机和任务之间连边
    for(int i=0;i<N;i++)
        for(int j=0;j<K;j++)
            if(can[i][j])
                add_edge(i,n+j,1);
    printf("%d\n",max_flow(s,t));
}

/*
算法二
利用所有边容量都是1以及二分图的性质
重复使用初始化时只需要将G clear
（匈牙利算法 DFS版）


//不清楚为何有向图使用此不行 使用邻接矩阵就可以
*/
const int MAX_V=1e5;
int V;//顶点数(二分图中左侧的顶点数）
vector<int> G[MAX_V];//图的邻接表表示
int match[MAX_V];//所匹配的顶点
bool used[MAX_V];//DFS中用到的访问标记
//向图中增加一条连接u和v的边（v应为>=V的值）
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
//通过DFS寻找增广路
bool dfs(int v)
{
    used[v]=true;
    for(int i=0;i<G[v].size();i++)
    {
        int u=G[v][i],w=match[u];
        if(w<0||(!used[w]&&dfs(w)))
        {
            match[v]=u;
            match[u]=v;
            return true;
        }
    }
    return false;
}
//求解二分图的最大匹配
int bipartite_matching()
{
    int res=0;
    memset(match,-1,sizeof(match));
    for(int v=0;v<V;v++)
    {
        if(match[v]<0)
        {
            memset(used,0,sizeof(used));
            if(dfs(v))
                ++res;
        }
    }
    return res;//返回的是总点数的一半 亦即二分图中的边数
}



/* ***********************************************************
//二分图匹配（匈牙利算法的DFS实现）(邻接矩阵形式)
//初始化：g[][]两边顶点的划分情况
//建立g[i][j]表示i->j的有向边就可以了，是左边向右边的匹配
//g没有边相连则初始化为0
//uN是匹配左边的顶点数，vN是匹配右边的顶点数
//调用：res=hungary();输出最大匹配数
//优点：适用于稠密图，DFS找增广路，实现简洁易于理解
//时间复杂度:O(VE)

//同样的 重复使用初始化只需要初始化g数组
//*************************************************************/
//顶点编号从0开始的(图左侧、右侧均从0开始）

const int MAXN = 510;
int uN,vN;//u,v的数目，使用前面必须赋值
int g[MAXN][MAXN];//邻接矩阵
int linker[MAXN];
bool used[MAXN];
bool dfs(int u)
{
    for(int v = 0; v < vN;v++)
    if(g[u][v] && !used[v])
    {
        used[v] = true;
        if(linker[v] == -1 || dfs(linker[v]))
        {
            linker[v] = u;
            return true;
        }
    }
    return false;
}
int hungary()
{
    int res = 0;
    memset(linker,-1,sizeof(linker));
    for(int u = 0;u < uN;u++)
    {
        memset(used,false,sizeof(used)); if(dfs(u))res++;
    }
    return res;
}



/* *******************************
*	二分图匹配（Hopcroft-Carp算法）
* 复杂度O(sqrt(n)*E) 由于匈牙利算法 点数比较多时用此
* 邻接表存图，vector实现
* vector先初始化，然后加入边
* uN 为左端的顶点数，使用前赋值(点编号0开始)
*/
const int MAXN = 3000;
const int INF = 0x3f3f3f3f;
vector<int>G[MAXN];
int uN;

int Mx[MAXN],My[MAXN];
int dx[MAXN],dy[MAXN];
int dis;
bool used[MAXN];
//向图中增加一条连接u和v的边（v应为>=V的值）
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
bool SearchP()
{
    queue<int>Q; dis = INF;
    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for(int i = 0 ; i < uN; i++)
        if(Mx[i] == -1)
        {
            Q.push(i);
            dx[i] = 0;
        }
    while(!Q.empty())
    {
        int u = Q.front(); Q.pop();
        if(dx[u]  >  dis)break; int sz = G[u].size(); for(int i = 0;i < sz;i++)
        {
            int v = G[u][i];
            if(dy[v] == -1)
            {
                dy[v] = dx[u] + 1;
                if(My[v] == -1)dis = dy[v];
                else
                {
                    dx[My[v]] = dy[v] + 1;
                    Q.push(My[v]);
                }
            }
        }
    }
    return dis != INF;
}
bool DFS(int u)
{
    int sz = G[u].size();
    for(int i = 0;i < sz;i++)
    {
        int v = G[u][i];
        if(!used[v] && dy[v] == dx[u] + 1)
        {
            used[v] = true;
            if(My[v] != -1 && dy[v] == dis)continue;
            if(My[v] == -1 || DFS(My[v]))
            {
                My[v] = u;
                Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}
int MaxMatch()
{
    int res = 0;
    memset(Mx,-1,sizeof(Mx));
    memset(My,-1,sizeof(My));
    while(SearchP())
    {
        memset(used,false,sizeof(used)); for(int i = 0;i < uN;i++)
        if(Mx[i] == -1 && DFS(i)) res++;
    }
    return res;
}

