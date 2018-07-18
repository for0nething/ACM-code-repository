/*
    HDU 3966
    题意：给一棵树，并给定各个点权的值，然后有3种操作：

    I C1 C2 K: 把C1与C2的路径上的所有点权值加上K

    D C1 C2 K：把C1与C2的路径上的所有点权值减去K

    Q C：查询节点编号为C的权值

    线段树维护即可
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
const int MAX=2e5+5;
//const int M=2500007;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const ll MOD=1e9+7;
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
    int to,nxt;
}edg[MAX<<1];
int n,m,p,ecnt,dcnt;
int h[MAX],a[MAX],top[MAX],dep[MAX],son[MAX],fa[MAX],sz[MAX],dfn[MAX],who[MAX];
void add_edge(int u,int v)
{
    edg[++ecnt]=node{v,h[u]};
    h[u]=ecnt;
}
void dfs1(int u,int pre)
{
    fa[u]=pre;son[u]=0;sz[u]=1;
    for(int i=h[u];i;i=edg[i].nxt){
        int to=edg[i].to;if(to==pre)continue;
        dep[to]=dep[u]+1;
        dfs1(to,u);
        sz[u]+=sz[to];
        if(sz[to]>sz[son[u]])
            son[u]=to;
    }
}
void dfs2(int u,int anc){
    top[u]=anc;dfn[u]=++dcnt;who[dcnt]=u;
    if(son[u])dfs2(son[u],anc);
    for(int i=h[u];i;i=edg[i].nxt){
        int to=edg[i].to;
        if(to==fa[u]||to==son[u])continue;
        dfs2(to,to);
    }
}
int sum[MAX*4],lazy[MAX<<2];
void pushup(int x){
    sum[x]=sum[x<<1]+sum[x<<1|1];
}
void build(int x,int l,int r){
    lazy[x]=0;
	if (l==r){
        sum[x]=a[who[l]];
		return;
	}int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void pushdown(int k,int l,int r)
{
    int mid=(l+r)/2;
    sum[k<<1]+=lazy[k]*(mid-l+1);sum[k<<1|1]+=lazy[k]*(r-mid);
    lazy[k<<1]+=lazy[k];lazy[k<<1|1]+=lazy[k];
    lazy[k]=0;
}
void update(int x,int l,int r,int L,int R,int val){//negative
	if (l<=L&&R<=r){
        sum[x]+=val*(R-L+1);
        lazy[x]+=val;
		return;
	}
	if(lazy[x])pushdown(x,L,R);
	int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,L,mid,val);
	if (r>mid) update(x<<1|1,l,r,mid+1,R,val);
	pushup(x);
}
//int query(int x,int l,int r,int L,int R){
//    if (!sum[x]) return 0;
//	if (l<=L&&R<=r) return sum[x];
//	int mid=(L+R)/2,ret=0;
//	if (mid>=l) ret+=query(x<<1,l,r,L,mid);
//	if (r>mid) ret+=query(x<<1|1,l,r,mid+1,R);
//	pushup(x);
//	return ret;
//}
int query(int x,int lo,int l,int r)
{
    if(l==r)return sum[x];
    if(lazy[x])pushdown(x,l,r);
    int mid=(l+r)/2,re;
    if(lo<=mid)re=query(x<<1,lo,l,mid);
    else re=query(x<<1|1,lo,mid+1,r);
    pushup(x);
    return re;
}
char opt[15];
int main()
{
    while(~scanf("%d%d%d",&n,&m,&p))
    {
        ecnt=dcnt=0;
        memset(h,0,sizeof(h));
        for(int i=1;i<=n;i++)read(a[i]);
        for(int u,v,i=1;i<n;i++){
            read(u);read(v);add_edge(u,v);add_edge(v,u);
        }
        dfs1(1,0);dfs2(1,1);
        build(1,1,n);
        while(p--){
            scanf("%s",opt);
            if(opt[0]=='Q'){
                int w;read(w);w=dfn[w];
                printf("%d\n",query(1,w,1,n));
            }
            else{
                int u,v,val;
                read(u);read(v);read(val);
                if(opt[0]=='D')val=-val;
                while(top[u]!=top[v])
                {
                    if(dep[top[u]]<dep[top[v]])swap(u,v);
                    update(1,dfn[top[u]],dfn[u],1,n,val);
                    u=fa[top[u]];
                }
                if(dep[u]>dep[v])swap(u,v);
                update(1,dfn[u],dfn[v],1,n,val);
            }
        }
    }
    return 0;
}
/*


*/
