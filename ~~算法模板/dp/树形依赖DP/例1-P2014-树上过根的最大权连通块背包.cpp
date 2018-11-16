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
const int MAX=2e5+5;
const int MOD=1e9+7;
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
inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
//inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

#define SZ 5004
int n,m,dcnt,ecnt;
int h[SZ],siz[SZ],dp[SZ][SZ],fa[SZ],w[SZ],v[SZ];
int dfn[SZ],dwho[SZ];//dfsÐòµÄ±àºÅ
struct node{
    int to,nxt;
    node(){};
    node(int _to,int _nxt):to(_to),nxt(_nxt){};
}edg[SZ<<1];
void add_edge(int who){
    int f=fa[who];
//    if(!f)return;
    edg[++ecnt]=node(who,h[f]);
    h[f]=ecnt;
}
void dfs(int now){
    siz[now]=1;dfn[now]=++dcnt;dwho[dcnt]=now;
    for(int i=h[now];i;i=edg[i].nxt){
        int to=edg[i].to;
        dfs(to);siz[now]+=siz[to];
    }
}
int main(){
    read(n);read(m);
    for(int i=1;i<=n;i++)read(fa[i]),read(v[i]),w[i]=1,add_edge(i);
    dfs(0);
    for(int i=0;i<=m;i++)dp[dcnt+1][i]=dp[dcnt+2][i]=-1000000000;
    dp[dcnt+1][0]=0;
    for(int i=dcnt;i>=1;i--){
        int lo=dwho[i];
        for(int j=0;j<=m;j++){
            if(j<w[lo])dp[i][j]=max(dp[i+siz[lo]][j],0);
            else dp[i][j]=max(max(dp[i+siz[lo]][j],dp[i+1][j-w[lo]]+v[lo]),0);
        }
    }
    printf("%d\n",dp[1][m]);
    return 0;
}
/*
4 4
*/
