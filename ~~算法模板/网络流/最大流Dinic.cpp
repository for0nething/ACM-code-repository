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
//用于表示边的结构体（终点、容量、反向边）
struct edge{int to,cap,rev;};
const int MAX_V=MAX;
vector <edge> G[MAX_V];//图的邻接表表示
int level[MAX_V];//顶点到源点的距离标号
int iter[MAX_V];//当前弧 在其之前的边已经没有用了
//向图中增加一条从from到to的容量为cap的边
void add_edge(int from,int to,int cap)
{
    G[from].push_back((edge){to,cap,G[to].size()});
    G[to].push_back((edge){from,0,G[from].size()-1});//反向边
}
//通过BFS计算从源点出发的距离标号
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int>que;
    level[s]=0;
    que.push(s);
    while(!que.empty())
    {
        int v=que.front();que.pop();
        for(int i=0;i<G[v].size();i++)
        {
            edge &e=G[v][i];
            if(e.cap>0&&level[e.to]<0)
            {
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}
//通过DFS寻找增广路
int dfs(int v,int t,int f)
{
    if(v==t)return f;
    for(int &i=iter[v];i<G[v].size();i++)
    {
        edge &e=G[v][i];
        if(e.cap>0&&level[v]<level[e.to])
        {
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0)
            {
                e.cap-=d;G[e.to][e.rev].cap+=d;//反向边增大
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
        bfs(s);
        if(level[t]<0)//已无能到t的增广路
            return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while((f=dfs(s,t,INF))>0)
            flow+=f;
    }
}
