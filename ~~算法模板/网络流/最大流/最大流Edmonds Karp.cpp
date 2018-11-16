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
Edmonds-Karp�㷨
���뷴��� ��for ���ڵĻ���
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
    vector<Edge>edges;//����������
    vector<int> G[maxn];//�ڽӱ�G[i][j]��ʾ���i�ĵ�j������edges�����е����
    int a[maxn];//����㵽i�ĿɸĽ��� ������������¼���ǲ������磨�����������ͼ��Ϊ��2�����֣��ֱ���ԭ�㡢�����ͨ�� >0��Ϊ��ԭ�������Ĳ��� =0��Ϊ���������Ĳ���
    int p[maxn];//���·����p���뻡���
    void init(int n)
    {
        for(int i=0;i<n;i++)
            G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,int cap)
    {
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));//����
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
            if(!a[t])//��������޸Ľ�ֵ
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

