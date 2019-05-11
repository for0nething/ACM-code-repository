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
#define fi first
#define se second
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef unsigned int ui;
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
const ll MOD=998244353;
//int MOD;
//const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
//const long double eps=1e-13;
//const double pi=acos(-1);
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
namespace{
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
template<class T> inline T add(T x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(T &x,T y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){x+=y;if(x>=MOD)x%=MOD;}
template<class T> inline T mul(T x,T y){return 1LL*x*y%MOD;}
//inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
template<class T> inline void muli(T &x,T y){x=1LL*x*y%MOD;}
template<class T> inline T sub(T x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(T &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline T half(T x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,m;
vector<int>edg[MAX];
int dp[MAX];//以i为根的子树取最大独立集 i选(1)or 不选(0)
int tp[MAX];//整棵树除了以i为根的子树的部分 i的父节点是否选
int cnt[MAX];//以i为根的子树中的各个儿子结点的子树的根选的个数
int rt[MAX];//以i为根的整棵树最大独立集中i是否选 1表示选了
int stans;//初始的树的最大独立集大小
void dfs_dp(int now,int fa){
    dp[now]=1;
    for(int u:edg[now]){//计算dp
        if(u==fa)continue;
        dfs_dp(u,now);
        if(dp[u])//有选的
            dp[now]=0,++cnt[now];
    }
    stans+=dp[now];
}
void dfs_tp(int now,int fa){
    cnt[now]+=tp[now];
    rt[now]=!cnt[now];
    for(int u:edg[now]){
        if(u==fa)continue;
        cnt[now]-=dp[u];
        tp[u]=!cnt[now];
        dfs_tp(u,now);
        cnt[now]+=dp[u];
    }
}
int ans;
int main(){
    read(n);read(m);
    for(int u,v,i=1;i<n;i++){
        read(u);read(v);
        edg[u].eb(v);edg[v].eb(u);
    }
    dfs_dp(1,0);
    dfs_tp(1,0);
    printf("%d\n",stans);ans=stans;
    bool rtst=rt[1];//根节点的状态
    for(int u,i=1;i<=m;i++){
        read(u);
        if(!rtst)//根节点未选
            muli(ans,n),addi(ans,stans),rtst=rt[u];
        else  muli(ans,n),rtst=0;//根节点已被选
        printf("%d\n",ans);
    }
    return 0;
}

/*

*/
