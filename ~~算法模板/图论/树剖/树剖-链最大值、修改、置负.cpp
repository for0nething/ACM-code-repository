/*
    POJ 3237
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
const int M=1e6+15;
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
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
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
    int to,nxt,val;
}edg[MAX<<1];

int t,ecnt,dcnt,n;
int h[MAX],top[MAX],dep[MAX],son[MAX],fa[MAX],sz[MAX],dfn[MAX],who[MAX];
int x[MAX],y[MAX],val[MAX],dis[MAX];
char opt[105];
void add_edge(int u,int v,int val)
{
    edg[++ecnt]=node{v,h[u],val};
    h[u]=ecnt;
}
void dfs1(int u,int pre)
{
    fa[u]=pre;son[u]=0;sz[u]=1;
    for(int i=h[u];i;i=edg[i].nxt)
    {
        int to=edg[i].to;if(to==pre)continue;
        dep[to]=dep[u]+1;
        dis[to]=edg[i].val;
        dfs1(to,u);
        sz[u]+=sz[to];
        if(sz[to]>sz[son[u]])
            son[u]=to;
    }
}
void dfs2(int u,int anc)
{
    top[u]=anc;dfn[u]=++dcnt;who[dcnt]=u;
    if(son[u])dfs2(son[u],anc);
    for(int i=h[u];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(to==fa[u]||to==son[u])continue;
        dfs2(to,to);
    }
}
inline int lca(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        u=fa[top[u]];
    }
    return dep[u]<dep[v]?u:v;
}
int Max[MAX<<2],Min[MAX<<2],lazy[MAX<<2];
void push(int k)
{
    if(!lazy[k])return;
    lazy[k<<1]^=1;lazy[k<<1|1]^=1;lazy[k]=0;
    int da=Max[k<<1],xiao=Min[k<<1];
    Max[k<<1]=-xiao;Min[k<<1]=-da;
    da=Max[k<<1|1],xiao=Min[k<<1|1];
    Max[k<<1|1]=-xiao,Min[k<<1|1]=-da;
}
void build(int k,int l,int r)
{
    if(l==r){Max[k]=Min[k]=dis[who[l]];lazy[k]=0;return;}
    int mid=(l+r)/2;
    lazy[k]=0;
    build(k<<1,l,mid);build(k<<1|1,mid+1,r);
    Min[k]=min(Min[k<<1],Min[k<<1|1]);
    Max[k]=max(Max[k<<1],Max[k<<1|1]);
}
int query(int k,int l,int r,int ql,int qr)
{
    if(l>=ql&&r<=qr)return Max[k];
    int mid=(l+r)/2;
    int re=-INF;
    push(k);
    if(ql<=mid)re=max(re,query(k<<1,l,mid,ql,qr));
    if(qr>mid)re=max(re,query(k<<1|1,mid+1,r,ql,qr));
    return re;
}
int Query(int u,int v)
{
    int re=-INF;
    while(top[u]!=top[v])
    {
        re=max(re,query(1,2,n,dfn[top[u]],dfn[u]));
        u=fa[top[u]];
    }
    if(dfn[v]+1<=dfn[u])
        re=max(re,query(1,2,n,dfn[v]+1,dfn[u]));//同一条链上就是连续的!
    return re;
}
void change(int k,int lo,int l,int r)
{
    push(k);
    if(l==r){
        Max[k]=dis[who[l]];Min[k]=dis[who[l]];
        return;
    }
    int mid=(l+r)/2;
    if(lo<=mid)change(k<<1,lo,l,mid);
    else change(k<<1|1,lo,mid+1,r);
    Min[k]=min(Min[k<<1],Min[k<<1|1]);
    Max[k]=max(Max[k<<1],Max[k<<1|1]);
}
void update(int k,int l,int r,int ul,int ur)
{
    push(k);
    if(l>=ul&&r<=ur){
        lazy[k]^=1;
        int da=Max[k],xiao=Min[k];
        Max[k]=-xiao;Min[k]=-da;
        return ;
    }
    int mid=(l+r)/2;
    if(ul<=mid)update(k<<1,l,mid,ul,ur);
    if(ur>mid)update(k<<1|1,mid+1,r,ul,ur);
    Max[k]=max(Max[k<<1],Max[k<<1|1]);
    Min[k]=min(Min[k<<1],Min[k<<1|1]);
}
void Update(int u,int v)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        update(1,2,n,dfn[top[u]],dfn[u]);
        u=fa[top[u]];
    }
    if(dfn[u]<dfn[v])swap(u,v);
    if(dfn[v]+1<=dfn[u])
        update(1,2,n,dfn[v]+1,dfn[u]);
}
int main()
{
    #ifdef debug
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif // debug
    read(t);
    while(t--){
        memset(h,0,sizeof(h));
        ecnt=dcnt=0;
        read(n);
        for(int i=1;i<n;i++){
            read(x[i]);read(y[i]);read(val[i]);
            add_edge(x[i],y[i],val[i]);
            add_edge(y[i],x[i],val[i]);
        }
        dfs1(1,0);dfs2(1,1);
        build(1,2,n);
        while(scanf("%s",opt)&&opt[0]!='D')
        {
            int u,v,c;read(u);read(v);
            if(opt[0]=='Q'){
                c=lca(u,v);
                #ifdef debug
                    printf("c=%d\n",c);
                #endif // debug
                printf("%d\n",max(Query(u,c),Query(v,c)));
            }
            else if(opt[0]=='C'){
                u=(dfn[x[u]]>dfn[y[u]]?x[u]:y[u]);
                dis[u]=v;
                change(1,dfn[u],2,n);
            }
            else
                Update(u,v);

        }
    }
    return 0;
}
/*
5 10 4
1 2 1
2 3 3
3 4 3
4 5 7
0 1
0 5
*/
