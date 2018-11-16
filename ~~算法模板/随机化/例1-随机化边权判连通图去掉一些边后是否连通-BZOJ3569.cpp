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
const int MAX=1e6+5;
const int MOD=1e9+7;
const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-6;
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
inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int ecnt,n,m,q,k,cnt;
int dp[MAX],h[MAX],fa[MAX],eval[MAX],a[50];
bool v_vi[MAX],e_vi[MAX];//点是否使用过 边是否使用过
struct node{
    int to,nxt,val;
}edg[MAX<<1];
void add_edge(int u,int v){
    edg[++ecnt]=node{v,h[u],0};
    h[u]=ecnt;
}
void dfs(int now,int pre){
    v_vi[now]=1;
    for(int i=h[now];i;i=edg[i].nxt){
        int to=edg[i].to;
        if(to==pre||v_vi[to])continue;
        fa[to]=now;e_vi[i>>1]=1;
        dfs(to,now);
    }
}
void dfs2(int now){
    for(int i=h[now];i;i=edg[i].nxt){
        int to=edg[i].to;
        if(fa[to]!=now)continue;
        dfs2(to);
        eval[i>>1]^=dp[to];
        dp[now]^=dp[to];
    }
}
int main()
{
    read(n);read(m);
    ecnt=1;
    for(int u,v,i=1;i<=m;i++){
        read(u);read(v);add_edge(u,v);add_edge(v,u);
    }
    dfs(1,0);
    srand(19260817);
    for(int i=1;i<=m;i++){
        if(e_vi[i])continue;
        eval[i]=rand()%MOD+1;
        dp[edg[i<<1].to]^=eval[i];
        dp[edg[i<<1|1].to]^=eval[i];
    }
    dfs2(1);
    read(q);
    while(q--){
        read(k);
        bool ans=1;
        memset(a,0,sizeof(a));
        for(int u,i=1;i<=k;i++){
            read(u);u^=cnt;u=eval[u];
            for(int j=31;j>=0;j--){
                if(!(u&(1<<j)))continue;
                if(!a[j]){a[j]=u;break;}
                u^=a[j];
            }
            ans&=(u!=0);
        }
        cnt+=ans;
        puts(ans?"Connected":"Disconnected");
    }
    return 0;
}
/*

*/
﻿
