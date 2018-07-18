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
#include <unordered_map>
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
const int MAX=1e5+5;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const int MOD=1e9+7;
//const ull MOD=1e7+7;
//const ll MOD=998244353;
//const long double pi=acos(-1.0);
//const double eps=0.00000001;
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

int n,m;
int bin[20],fa[MAX][20],bel[MAX],a[MAX],cnt[MAX],edg_cnt,root,dep[MAX];
int dfn[MAX],dfs_id;
int sum;
int siz,block_cnt;
int stk[MAX],top;
bool vi[MAX];
struct node
{
    int to,nxt;
}edg[MAX<<1];
int head[MAX];
void add(int u,int v)
{
    edg[++edg_cnt]=node{v,head[u]};
    head[u]=edg_cnt;
}
void dfs(int now,int bot)
{
    dfn[now]=++dfs_id;
//    printf("now=%d\n",now);
//    system("pause");
    for(int i=1;i<=16&&dep[now]>=bin[i];i++)fa[now][i]=fa[fa[now][i-1]][i-1];
    for(int i=head[now];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(to!=fa[now][0])
        {
            dep[to]=dep[now]+1;
            fa[to][0]=now;
            dfs(to,top);
            if(top-bot>=siz)
            {
                ++block_cnt;
                while(top!=bot)
                {
                    bel[stk[top--]]=block_cnt;
                }
            }
        }
    }
    stk[++top]=now;
}
int lca(int u,int v)
{
    if(dep[u]>dep[v])swap(u,v);
    int dif=dep[v]-dep[u];
    for(int i=0;bin[i]<=dif;i++)
        if(dif&bin[i])v=fa[v][i];
    for(int i=16;i>=0;i--)
        if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
    if(u!=v)return fa[v][0];
    return v;
}
int reverse(int u)
{
    if(!vi[u])vi[u]=1,++cnt[a[u]],sum+=(cnt[a[u]]==1);
    else vi[u]=0,--cnt[a[u]],sum-=(!cnt[a[u]]);
}
void solve(int u,int v)
{
    while(u!=v)
    {
//        printf("%d %d %d %d\n",u,v,dep[u],dep[v]);
        if(dep[u]>dep[v])reverse(u),u=fa[u][0];
        else reverse(v),v=fa[v][0];
    }
}
struct nod
{
    int u,v,a,b,id;
    bool operator<(const nod& z)const
    {
        if(bel[u]!=bel[z.u])return bel[u]<bel[z.u];
        else return dfn[v]<dfn[z.v];
    }
}qs[MAX];
int an[MAX];
/*
    BZOJ3757 求路径上不同颜色点个数  （a被视为b 除了a=b=0）
*/
int main()
{
//    freopen("6.in","r",stdin);
//    freopen("out.txt","w",stdout);
    bin[0]=1;
    for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
    scanf("%d%d",&n,&m);
    siz=sqrt(n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        int u,v;scanf("%d%d",&u,&v);if(u&&v){add(u,v);add(v,u);}else {if(!u)root=v;if(!v)root=u;}
    }
//    printf("root=%d\n",root);
//    system("pause");
    dfs(root,0);
//    printf("??\n");
    ++block_cnt;
    while(top)
        bel[stk[top--]]=block_cnt;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&qs[i].u,&qs[i].v,&qs[i].a,&qs[i].b),qs[i].id=i;
        if(dfn[qs[i].u]>dfn[qs[i].v])swap(qs[i].u,qs[i].v);
    }
    sort(qs+1,qs+1+m);
    int t=lca(qs[1].u,qs[1].v);
//    printf("??\n");
    solve(qs[1].u,qs[1].v);
    reverse(t);
    an[qs[1].id]=sum-(cnt[qs[1].a]&&cnt[qs[1].b]&&qs[1].a!=qs[1].b);
    reverse(t);
    for(int i=2;i<=m;i++)
    {
//        printf("i=%d\n",i);
        solve(qs[i-1].u,qs[i].u);
        solve(qs[i-1].v,qs[i].v);
        t=lca(qs[i].u,qs[i].v);
        reverse(t);
        an[qs[i].id]=sum-(cnt[qs[i].a]&&cnt[qs[i].b]&&qs[i].a!=qs[i].b);
        reverse(t);
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",an[i]);

}
/*
5 3
1 1 3 3 2
0 1
1 2
1 3
2 4
3 5
1 4 0 0
1 4 1 3
1 4 1 2
*/
