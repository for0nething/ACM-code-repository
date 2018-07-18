/*
    题意：给定树 每次问(u,v)路径上的点权值与x异或中的最大值
    做法就是按dfs序插点就好了
*/
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
//#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp

//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;
//const double INF=1e20;
const int INF=0x3f3f3f3f;
//const int INF= 0x7fffffff;
//const ll INF=0x3f3f3f3f3f3f3f3fll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=1e5+10;
//const int M=(1<<20)+5;
//const int M=2500007;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const int MOD=1e9+7;
//const ull MOD=1e7+7;
//const ll MOD=998244353;
//const long double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-6;
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
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
    while (b){
        if (b&1LL) ret=ret*a%M;
        b>>=1LL;
        a=a*a%M;
    }
    return ret;
}

ll mul(ll a , ll b,ll Q){
    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
}

//const long double eps=-1.0;
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);
void open()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
}
//#define debug
struct node
{
    int to,nxt;
}edg[MAX<<2];
int n,m,ecnt;
int a[MAX],bin[25];
int fa[MAX][20],dep[MAX],rt[MAX];
int h[MAX];
void add_edge(int u,int v)
{
    edg[++ecnt]=node{v,h[u]};
    h[u]=ecnt;
}
struct trie{
    int cnt;
    int ch[MAX*20][2],sum[MAX*20];
    int insert(int pre,int val){
        int re,now;re=now=++cnt;
        for(int i=18;i>=0;i--){
            ch[now][0]=ch[pre][0];ch[now][1]=ch[pre][1];
            sum[now]=sum[pre]+1;
            int t=val&bin[i];t>>=i;
            pre=ch[pre][t];
            ch[now][t]=++cnt;
            now=ch[now][t];
        }
        sum[now]=sum[pre]+1;
        return re;
    }
    int query(int u,int v,int anc,int w,int val){
        int re=0;
        for(int i=18;i>=0;i--){
            int t=val&bin[i];t>>=i;
            if(sum[ch[u][t^1]]+sum[ch[v][t^1]]-sum[ch[anc][!t]]-sum[ch[w][!t]]>0){
                re+=bin[i];u=ch[u][!t];v=ch[v][!t];w=ch[w][!t];anc=ch[anc][!t];
            }
            else{
                u=ch[u][t];v=ch[v][t];anc=ch[anc][t];w=ch[w][t];
            }
        }
        return re;
    }
}trie;
void dfs(int u,int pre)
{
    fa[u][0]=pre;
    rt[u]=trie.insert(rt[pre],a[u]);
    for(int i=1;i<=18;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=h[u];i;i=edg[i].nxt){
        int to=edg[i].to;
        if(to==pre)continue;
        dep[to]=dep[u]+1;
        dfs(to,u);
    }
}
int lca(int u,int v)
{
    if(dep[u]<dep[v])swap(u,v);
    int cha=dep[u]-dep[v];
    for(int i=18;i>=0;i--)if(cha&(1<<i))u=fa[u][i];
    if(u==v)return u;
    for(int i=18;i>=0;i--)
        if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
int main()
{
    bin[0]=1;for(int i=1;i<=20;i++)bin[i]=bin[i-1]<<1;
    while(~scanf("%d%d",&n,&m))
    {
        trie.cnt=0;
        ecnt=0;memset(h,0,sizeof(h));
        for(int i=1;i<=n;i++)read(a[i]);
        for(int u,v,i=1;i<n;i++){
            read(u);read(v);add_edge(u,v);add_edge(v,u);
        }
        dfs(1,0);
        for(int u,v,x,i=1;i<=m;i++){
            read(u);read(v);read(x);
            int c=lca(u,v),anc=fa[c][0];
            printf("%d\n",trie.query(rt[u],rt[v],rt[c],rt[anc],x));
        }
    }
    return 0;
}
/*
1 3 1 3
2 3 2 5
*/
