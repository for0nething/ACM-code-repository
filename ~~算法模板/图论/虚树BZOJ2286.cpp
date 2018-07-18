/*
    bzoj 2286
    题意：
    给定一棵树，每条边都有一定权值。若干次询问，每次给出m个点，要求去掉权值和最小的一些边，使得1与这些点不连通
*/

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
const int MAX=5e5+5;
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
struct node
{
    node(){};
    node(int _to,int _dis,int _nxt):to(_to),dis(_dis),nxt(_nxt){};
    node(int _to,int _nxt):to(_to),nxt(_nxt){};
    int to,dis,nxt;
}edg[MAX<<1];
int n,ecnt,c,m,tot,top;
int x,y,z;
int h[MAX],hd[MAX];//val:根节点到某点路径上最短的边长
int dep[MAX],fa[MAX][20],dfn[MAX],que[MAX],stk[MAX];
ll f[MAX],val[MAX];
void add_edge(int u,int v,int cost)//原树的图
{
    edg[++ecnt]=node(v,cost,h[u]);
    h[u]=ecnt;
}
void dfs(int now,int pre)
{
    fa[now][0]=pre;dfn[now]=++ecnt;
    for(int i=1;i<=18;i++)fa[now][i]=fa[fa[now][i-1]][i-1];
    for(int i=h[now];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(to==pre)continue;
        val[to]=min(val[now],1LL*edg[i].dis);dep[to]=dep[now]+1;
        dfs(to,now);
    }
}
bool cmp(int a,int b){return dfn[a]<dfn[b];}
inline int lca(int x,int y)
{
    if(dep[x]<dep[y])swap(x,y);
    int cha=dep[x]-dep[y];
    for(int i=18;i>=0;i--)
        if(cha&(1<<i))x=fa[x][i];
    if(x==y)return x;
    for(int i=18;i>=0;i--)
        if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return x==y?x:fa[x][0];
}
inline void add(int u,int v){if(u==v)return ;edg[++ecnt]=node(v,hd[u]);hd[u]=ecnt;}
inline void dp(int x)
{
    ll tem=0;f[x]=val[x];
    for(int i=hd[x];i;i=edg[i].nxt){
        dp(edg[i].to);
        tem+=f[edg[i].to];
    }
    hd[x]=0;//退出时顺便清空
    if(!tem)f[x]=val[x];//叶子节点 val[x]就是将该点去掉的最小花费
    else if(tem<f[x])f[x]=tem;
}
void solve()//断绝根节点到1的路径？？
{
    read(m);
    for(int i=1;i<=m;i++)read(que[i]);
    sort(que+1,que+1+m,cmp);//按dfs序排序
    tot=0;que[++tot]=que[1];
    for(int i=2;i<=m;i++)if(lca(que[i],que[tot])!=que[tot])que[++tot]=que[i];
    //在下面的肯定不用计算 只要切断上部的即可
    top=0;stk[++top]=1;
    ecnt=0;//清空图
    int grand;//LCA
    for(int i=1;i<=tot;i++){
        grand=lca(stk[top],que[i]);
        while(1){
            if(dep[stk[top-1]]<=dep[grand]){
                add(grand,stk[top]);top--;
                if(stk[top]!=grand)stk[++top]=grand;
                break;
            }
            add(stk[top-1],stk[top]);--top;
        }
        if(stk[top]!=que[i])stk[++top]=que[i];//在同一子树
    }
    --top;
    while(top)add(stk[top],stk[top+1]),--top;//剩余的记得连上
    dp(1);
    printf("%lld\n",f[1]);
}
int main()
{
    read(n);
    for(int i=1;i<n;i++){
        read(x);read(y);read(z);
        add_edge(x,y,z);add_edge(y,x,z);
    }
    val[1]=INFF;ecnt=0;dep[1]=0;
    dfs(1,0);
    read(c);
    while(c--)solve();
    return 0;
}
/*
2 1
1 100
100 1
2 2
1 100
100 1


*/
