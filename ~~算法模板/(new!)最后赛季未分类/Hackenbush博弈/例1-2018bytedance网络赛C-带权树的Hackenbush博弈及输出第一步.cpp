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
//#include <utility>
//#include <complex>
#include <assert.h>
//#include <limits.h>
//#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;

#define rank rankk
#define mp make_pair
#define pb push_back
#define eb push_back
//#define eb emplace_back
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
typedef pair<double,int> pdi;
typedef long double ld;
const int INF=0x3f3f3f3f;
const ll INFF=1e16;
//const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=1e6+5;
const int MOD=1e9+7;
//const ll MOD=(ll)998244353;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
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
    while (b){
        if (b&1) ret=1LL*ret*a%M;
        b>>=1;
        a=1LL*a*a%M;
    }
    return ret;
}
namespace{
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;x%=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

/*
题意：
给定一棵 n 个节点的带权有根树，两人轮流操作，每次操作使某条边的边权减一，
若边权减至 0，则删去改边，并删去不含根的连通块，
判断先手是否必胜，并输出先手若要胜利，所有第一步可能的决策。

n,w <=1e6

做法:
考虑将题目转化为有根无向图删边游戏 (Hackenbush)，
每条树边的边权代表了无向图上两端点之间的边数量。
注意到对于边权大于1 时会形成环，按奇偶性缩环（无向图删边游戏的操作）即可。

在计算出 SG 值后，每一步操作会改动一条到根路径上的所有 SG 值，
自根向下确定每个子树如果修改那么需要修改得到的 SG 值是多少，即可检查某一种操作是否能使得先手必胜。

*/
vector<int>edg[MAX];
int fa[MAX],w[MAX],sg[MAX];
int T,n,cnt;
int an[MAX];
void dfs(int now){///算原图的sg
    sg[now]=0;
    for(int v:edg[now]){
        dfs(v);
        if(w[v]==1)sg[now]^=sg[v]+1;
        else{
            sg[now]^=sg[v];
            if(w[v]&1)sg[now]^=1;
        }
    }
}
void dfs(int now,int target){
    if(target<0)return;
    for(int v:edg[now]){
        if(w[v]==1){///1->0
            if((sg[now]^(sg[v]+1))==target)an[++cnt]=v;
        }
        else if(w[v]==2){///2->1
            if((sg[now]^(sg[v])^(sg[v]+1)) ==target)an[++cnt]=v;
        }
        else{/// ? ->  >1的状态
            if((sg[now]^1)==target)an[++cnt]=v;
        }
        ///去掉其余子树的影响更新target
        if(w[v]==1)dfs(v,(target^(sg[now]^(sg[v]+1))) -1);
        else dfs(v,target^(sg[now]^sg[v]));
    }

}
int main(){
    read(T);
    while(T--){
        read(n);
        for(int i=1;i<=n;i++)edg[i].clear();
        for(int u,i=2;i<=n;i++){
            read(u);read(w[i]);
            edg[u].pb(i);
        }
        dfs(1);
        if(!sg[1])puts("0\n");
        else{
            cnt=0;
            dfs(1,0);
            sort(an+1,an+1+cnt);
            printf("%d\n",cnt);
            for(int i=1;i<=cnt;i++)printf("%d%c",an[i]," \n"[i==cnt]);
        }
    }
    return 0;
}
/*

*/
