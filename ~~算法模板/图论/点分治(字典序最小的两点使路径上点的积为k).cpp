/*

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
//#define mp make_pair
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
const int MOD=1e6+3;
//const ll MOD=1e9+7;
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
}edg[MAX<<2];
int inv[M],a[MAX],h[MAX],f[MAX],siz[MAX],id[MAX],temd[MAX],d[MAX],mp[M];
int n,k,ecnt,rt,tot,an1,an2,dcnt;
bool vi[MAX];
void add_edge(int u,int v)
{
    edg[++ecnt]=node{v,h[u]};
    h[u]=ecnt;
}
void getrt(int now,int fa)
{
    f[now]=0;siz[now]=1;
    for(int i=h[now];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(!vi[to]&&to!=fa){
            getrt(to,now);siz[now]+=siz[to];f[now]=max(f[now],siz[to]);
        }
    }
    f[now]=max(f[now],tot-siz[now]);
    if(f[now]<f[rt])rt=now;
}
void dfs(int now,int fa)
{
    temd[++dcnt]=d[now];id[dcnt]=now;
    for(int i=h[now];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(!vi[to]&&to!=fa)
        {
            d[to]=(1LL*d[now]*a[to])%MOD;
            dfs(to,now);
        }
    }
}
void query(int x,int ID)
{
    x=1LL*inv[x]*k%MOD;
    int y=mp[x];
    if(!y)return;
    if(y>ID)swap(y,ID);
    if(y<an1||(y==an1&&ID<an2))
        an1=y,an2=ID;
}
void solve(int now)
{
    vi[now]=1;mp[a[now]]=now;
    for(int i=h[now];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(!vi[to])
        {
            dcnt=0;d[to]=a[to];
            dfs(to,now);
            for(int j=1;j<=dcnt;j++)
                query(temd[j],id[j]);
            dcnt=0;d[to]=(1LL*a[now]*a[to])%MOD;
            dfs(to,now);
            for(int j=1;j<=dcnt;j++)
            {
                int now=mp[temd[j]];
                if(!now||now>id[j])mp[temd[j]]=id[j];
            }
        }
    }
    //Çå¿Õmap
    mp[a[now]]=0;
    for(int i=h[now];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(!vi[to])
        {
            dcnt=0;d[to]=(1LL*a[now]*a[to])%MOD;
            dfs(to,now);
            for(int j=1;j<=dcnt;j++)mp[temd[j]]=0;
        }
    }
    for(int i=h[now];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(!vi[to])
        {
            rt=0;tot=siz[to];
            getrt(to,0);
            solve(rt);
        }
    }

}
int main()
{
    inv[1]=1;
    for(int i=2;i<1000009;i++)
        inv[i]=1LL*(MOD-inv[MOD%i])*(MOD/i)%MOD;
    while(~scanf("%d%d",&n,&k))
    {
        memset(h,0,sizeof(h));ecnt=0;an1=an2=INF;
        memset(vi,0,sizeof(vi));
        for(int i=1;i<=n;i++)read(a[i]);
        for(int u,v,i=1;i<n;i++)
        {
            read(u);read(v);add_edge(u,v);add_edge(v,u);
        }
        rt=0;f[0]=n+1;tot=n;
        getrt(1,0);solve(rt);
        if(an1==INF)printf("No solution\n");
        else printf("%d %d\n",an1,an2);
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
