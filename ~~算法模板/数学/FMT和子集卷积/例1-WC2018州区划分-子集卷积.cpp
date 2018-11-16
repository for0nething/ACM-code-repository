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
const int MAX=1<<21|5;
const int MOD=998244353;
//const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
//const double eps=1e-6;
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
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
//inline int mul(int x,int y){return 1LL*x*y%MOD;}
inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void muli(int &x,int y){x=1LL*x*y%MOD;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,m,p,tot,ecnt;
int h[MAX],val[MAX],fa[MAX],deg[MAX],w[MAX],inv[MAX],ge[MAX];
int dp[22][MAX],gp[22][MAX];
bool ava[MAX];
struct node{
    int to,nxt;
    node(){}
    node(int _to,int _nxt):to(_to),nxt(_nxt){}
}edg[MAX<<1];
inline void add_edge(int u,int v){
    edg[++ecnt]=node(v,h[u]);
    h[u]=ecnt;
}
inline int find(int x){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
inline bool check(int x){
    int cnt=0;
    for(int i=0;i<n;i++)
        if(x&(1<<i))fa[i]=i,++cnt,deg[i]=0,w[x]+=val[i];
    ge[x]=cnt;
    for(int i=0;i<n;i++){
        if((x>>i)&1){
            for(int j=h[i];j;j=edg[j].nxt){
                int to=edg[j].to;
                if(!((x>>to)&1))continue;
                ++deg[to];++deg[i];
                int u=find(to),v=find(i);
                if(u!=v)fa[v]=u,--cnt;
            }
        }
    }
    if(cnt>1)return 1;
    cnt=0;
    for(int i=0;i<n;i++)
        if(((x>>i)&1)&& (deg[i]&1))++cnt;
    return cnt>0;
}

inline void FMT(int *a){
    for(int i=1;i<tot;i<<=1)
        for(int j=0;j<tot;j++)
            if(i&j)addi(a[j],a[j^i]);
}
inline void IFMT(int *a){
    for(int i=1;i<tot;i<<=1)
        for(int j=0;j<tot;j++)
            if(i&j)addi(a[j],(MOD-a[j^i])%MOD);
}
int main(){
    read(n);read(m);read(p);tot=(1<<n);
    for(int u,v,i=1;i<=m;i++){
        read(u);read(v);--u;--v;add_edge(u,v);
    }
    for(int i=0;i<n;i++)read(val[i]);
    for(int i=0;i<tot;i++)ava[i]=check(i);
    for(int i=0;i<tot;i++){
        if(p==0)w[i]=1;
        else if(p==2)w[i]=mul(w[i],w[i]);
        inv[i]=powMM(w[i],MOD-2,MOD);
        if(ava[i])gp[ge[i]][i]=w[i];
    }
    dp[0][0]=1;FMT(dp[0]);
    for(int i=0;i<=n;i++)FMT(gp[i]);
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++)
            for(int k=0;k<tot;k++)
                addi(dp[i][k],mul(dp[j][k],gp[i-j][k]));
        IFMT(dp[i]);
        for(int k=1;k<tot;k++)muli(dp[i][k],inv[k]);
        if(i==n)break;
        FMT(dp[i]);
    }
    printf("%d\n",dp[n][tot-1]);
    return 0;
}
/*
1
30
3
6
##.#..
7
.#.#.#.
5
##.##
*/
