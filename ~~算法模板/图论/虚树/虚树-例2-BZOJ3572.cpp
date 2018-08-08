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
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=3e5+10;
const int MOD=1e9+7;
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
inline int add(int x,int y){return (x+y)%MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);
struct node{
    int to,nxt;
}edg[MAX<<1],vtg[MAX<<1];
int n,q,ecnt,vcnt,dcnt,ccnt,top,tot,LCA;
int h[MAX],f[MAX],fa[MAX][20],siz[MAX],dfn[MAX],dep[MAX];
int bel[MAX],stk[MAX],a[MAX],b[MAX],g[MAX],c[MAX],ans[MAX];
void add_edge(int u,int v){//原树加边
    if(u==0||v==0||u==v)return;
    edg[++ecnt]=node{v,h[u]};
    h[u]=ecnt;
}
void addedge(int u,int v){//虚树加边
    if(u==0||v==0||u==v)return;
    vtg[++vcnt]=node{v,f[u]};
    f[u]=vcnt;
}
void dfs(int now,int pre){
    siz[now]=1;dfn[now]=++dcnt;
    for(int i=1;i<=18;i++)fa[now][i]=fa[fa[now][i-1]][i-1];
    for(int i=h[now];i;i=edg[i].nxt){
        int to=edg[i].to;
        if(to==pre)continue;
        fa[to][0]=now;dep[to]=dep[now]+1;
        dfs(to,now);siz[now]+=siz[to];
    }
}
inline int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    int cha=dep[u]-dep[v];
    for(int i=18;i>=0;i--)if(cha&(1<<i))u=fa[u][i];
    if(u==v)return u;
    for(int i=18;i>=0;i--)
        if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
inline int getdis(int x,int y){return dep[x]+dep[y]-2*dep[lca(x,y)]; }
//使用子树更新该点
void dfs1(int now,int pre){
    int d1,d2;g[now]=siz[now];
    c[++ccnt]=now;
    for(int i=f[now];i;i=vtg[i].nxt){
        int to=vtg[i].to;
        if(to==pre)continue;
        dfs1(to,now);
        if(bel[to]==0)continue;
        if(bel[now]==0){bel[now]=bel[to];continue;}
        d1=getdis(bel[to],now);d2=getdis(bel[now],now);
        if(d1<d2||(d1==d2&&bel[to]<bel[now]))bel[now]=bel[to];
    }
}
//使用父节点更新该点
void dfs2(int now,int pre){
    int d1,d2;
    for(int i=f[now];i;i=vtg[i].nxt){
        int to=vtg[i].to;
        if(to==pre)continue;
        if(bel[to]==0){bel[to]=bel[now];}
        else{
            d1=getdis(bel[to],to);d2=getdis(bel[now],to);
            if(d1>d2||(d1==d2&&bel[to]>bel[now]))
                bel[to]=bel[now];
        }
        dfs2(to,now);
    }
}
//处理每一条边
void solve(int pre,int now){
    int son=now,mid=now,d1,d2,nex;
    for(int i=18;i>=0;i--)
        if(dep[fa[son][i]]>dep[pre])son=fa[son][i];
    g[pre]-=siz[son];
    if(bel[pre]==bel[now]){
        ans[bel[pre]]+=siz[son]-siz[now];
        return;
    }
    for(int i=18;i>=0;i--){
        nex=fa[mid][i];
        if(dep[nex]<=dep[pre])continue;
        d1=getdis(nex,bel[pre]);d2=getdis(nex,bel[now]);
        if(d1>d2||(d1==d2&&bel[now]<bel[pre]))
            mid=nex;
    }
    ans[bel[pre]]+=siz[son]-siz[mid];
    ans[bel[now]]+=siz[mid]-siz[now];
}
bool cmp(int x,int y){
    return dfn[x]<dfn[y];
}
//建虚树 前几行读入关键点
void build(){
    read(tot);
    for(int i=1;i<=tot;i++)read(a[i]),b[i]=a[i];
    for(int i=1;i<=tot;i++)bel[a[i]]=a[i];
    sort(a+1,a+1+tot,cmp);
    top=vcnt=0;
    if(bel[1]!=1)stk[++top]=1;
    for(int i=1;i<=tot;i++){
        if(top==0){stk[++top]=a[i];continue;}
        LCA=lca(stk[top],a[i]);
        while(1){
            if(dep[stk[top-1]]<=dep[LCA]){
                addedge(LCA,stk[top]);--top;
                if(stk[top]!=LCA)stk[++top]=LCA;
                break;
            }
            addedge(stk[top-1],stk[top]);--top;
        }
        if(stk[top]!=a[i])stk[++top]=a[i];
    }
    while(top>1)addedge(stk[top-1],stk[top]),--top;
    top=ccnt=0;
    dfs1(1,0);dfs2(1,0);
    for(int i=1;i<=ccnt;i++)
        for(int j=f[c[i]];j;j=vtg[j].nxt)
            solve(c[i],vtg[j].to);
    for(int i=1;i<=ccnt;i++)
        ans[bel[c[i]]]+=g[c[i]];
    for(int i=1;i<=tot;i++)printf("%d ",ans[b[i]]);
    printf("\n");
    for(int i=1;i<=ccnt;i++)
        ans[c[i]]=f[c[i]]=g[c[i]]=bel[c[i]]=0;
}
int main()
{
    read(n);
    for(int u,v,i=1;i<n;++i){
        read(u);read(v);add_edge(u,v);add_edge(v,u);
    }
    dfs(1,0);
    read(q);
    while(q--)build();
    return 0;
}
/*
10
2 1
3 2
4 3
5 4
6 1
7 3
8 3
9 4
10 1
5
2
6 1
5
2 7 3 6 9
1
8
4
8 7 10 3
5
2 9 3 5 8
*/
