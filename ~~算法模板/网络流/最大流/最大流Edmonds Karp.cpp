#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <stack>
#define mp make_pair
//#define P make_pair
#define MIN(a,b) (a>b?b:a)
//#define MAX(a,b) (a>b?a:b)
typedef long long ll;
typedef unsigned long long ull;
const int MAX=1e3+5;
const int MAX_V=1e3+5;
const int INF=1e9+5;
const ll INF2=4e18+5;
const double M=4e18;
using namespace std;
const int MOD=1e9+7;
typedef pair<ll,int> pii;
const double eps=0.000000001;
#define rank rankk

/*
Edmonds-Karp算法
加入反向边 给for 反悔的机会
VE^2
*/
const int maxn=1e5+5;
struct Edge
{
    int from,to,cap,flow;
    Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};
struct EdmondsKarp
{
    int n,m;
    vector<Edge>edges;//边数的两倍
    vector<int> G[maxn];//邻接表，G[i][j]表示结点i的第j条边在edges数组中的序号
    int a[maxn];//当起点到i的可改进量 求完最大流后记录的是残余网络（最大流后整个图分为了2个部分，分别与原点、汇点联通） >0的为与原点相连的部分 =0的为与汇点相连的部分
    int p[maxn];//最短路树上p的入弧编号
    void init(int n)
    {
        for(int i=0;i<n;i++)
            G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,int cap)
    {
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));//反向弧
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    int Maxflow(int s,int t)
    {
        int flow=0;
        for(;;)
        {
            memset(a,0,sizeof(a));
            queue<int>que;
            que.push(s);
            a[s]=INF;
            while(!que.empty())
            {
                int x=que.front();que.pop();
                for(int i=0;i<G[x].size();i++)
                {
                    Edge &e=edges[G[x][i]];
                    if(!a[e.to]&&e.cap>e.flow)
                    {
                        p[e.to]=G[x][i];
                        a[e.to]=min(a[x],e.cap-e.flow);
                        que.push(e.to);
                    }
                }
                if(a[t])
                    break;
            }
            if(!a[t])//到汇点已无改进值
                break;
            for(int u=t;u!=s;u=edges[p[u]].from)
            {
                edges[p[u]].flow+=a[t];
                edges[p[u]^1].flow-=a[t];
            }
            flow+=a[t];
        }
        return flow;
    }
};

