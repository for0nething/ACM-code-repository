#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <bitset>
#include <utility>
#include <complex>
#include <assert.h>
#include <limits.h>
#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;


const int INF=0x3f3f3f3f;
//const ll INFF=1200000000000000000ll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=1e6+5;
const int MOD=1e9+7;
const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-6;
//#define double long double
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
//#define double long double
template<class T> inline
void read(T& num) {
    bool start=false,neg=false;
    char c;
    num=0;
    while((c=getchar())!=EOF) {
        if(c=='-') start=neg=true;
        else if(c>='0' && c<='9') {
            start=true;
            num=num*10+c-'0';
        } else if(start) break;
    }
    if(neg) num=-num;
}
inline int powMM(int a,int b,int M){
    int ret=1;
    a%=M;
    while (b){
        if (b&1) ret=1LL*ret*a%M;
        b>>=1;
        a=1LL*a*a%M;
    }
    return ret;
}
inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
//inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

/*
    最小费用最大流，求最大费用只需要取相反数，结果取相反数即可。 点的总数为 N，点的编号 0~N-1
*/
const int MAXN = 10000;
const int MAXM = 100000;
//const int INF = 0x3f3f3f3f;
struct Edge
{
    int to,next,cap,flow,cost;
}edge[MAXM];
int head[MAXN],tol;
int pre[MAXN],dis[MAXN];
bool vis[MAXN];
int N;//节点总个数，节点编号从0~N-1
void init(int n)
{
    N = n;
    tol = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int cap,int cost)
{
    edge[tol].to = v;
    edge[tol].cap = cap;
    edge[tol].cost = cost;
    edge[tol].flow = 0;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = 0;
    edge[tol].cost = -cost;
    edge[tol].flow = 0;
    edge[tol].next = head[v];
    head[v] = tol++;
}
bool spfa(int s,int t)
{
    queue<int>q;
    for(int i = 0;i < N;i++)
    {
        dis[i] = INF; vis[i] = false; pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1;i = edge[i].next)
        {
            int v = edge[i].to;


            if(edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost )
            {
                dis[v] = dis[u] + edge[i].cost; pre[v] = i;
                if(!vis[v])
                {
                    vis[v] = true; q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1)return false; else return true;
}
//返回的是最大流，cost存的是最小费用
int minCostMaxflow(int s,int t,int &cost)
{
    int flow = 0; cost = 0; while(spfa(s,t))
    {
        int Min = INF;
        for(int i = pre[t];i != -1;i = pre[edge[i^1].to])
        {
            if(Min > edge[i].cap - edge[i].flow) Min = edge[i].cap - edge[i].flow;
        }
        for(int i = pre[t];i != -1;i = pre[edge[i^1].to])
        {
            edge[i].flow += Min; edge[i^1].flow -= Min;
            cost += edge[i].cost * Min;
        }
        flow += Min;
    }
    return flow;
}
int t,n,cnt,S,T=401,tot,sum;
int deg[205],ci[205],lim[205][2];
char a[205];
int main()
{
    read(t);
    while(t--){
        read(n);cnt=0;
        tot=n*(n-1)*(n-2)*(n-3);
        memset(deg,0,sizeof(deg));memset(ci,0,sizeof(ci));
        for(int i=1;i<=n;i++){
            scanf("%s",a+1);
            for(int j=1;j<=n;j++){
                if(a[j]=='1')++deg[i];
                else if(a[j]=='2'&&j>i)++ci[i],++ci[j],lim[cnt][0]=i,lim[cnt][1]=j,++cnt;
            }
        }
        init(T+1);
        for(int i=0;i<cnt;i++){
            int x=lim[i][0],y=lim[i][1];
            addedge(S,i+1,1,0);
            addedge(i+1,200+x,1,0);
            addedge(i+1,200+y,1,0);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=ci[i];j++)
                addedge(200+i,T,1,deg[i]+j-1);
        }
        minCostMaxflow(S,T,sum);
        for(int i=1;i<=n;i++)sum+=deg[i]*(deg[i]-1)/2;
        printf("%d\n",tot-sum*(n-3)*8);
    }
    return 0;
}
/*

*/
