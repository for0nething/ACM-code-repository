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
const int MAX=2e5+5;
const ll MOD=998244353;
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
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n;
ll dp[2][20][MAX];//0 不能入  1 要进入
ll a[MAX];
vector<int>vec;
ll dis[MAX];
ll ans;
void dfs(int id,int dep,vector<int>& v){
    if(id>n)return;
    if(2*id>n){//是叶子节点
        v.eb(id);
        dp[0][dep][id]=dp[1][dep][id]=0;
        return;
    }
    vector<int>ls,rs;
    dfs(id<<1,dep+1,ls);
    dfs(id<<1|1,dep+1,rs);
    for(int u:ls)v.eb(u);
    for(int u:rs)v.eb(u);
    if(rs.empty()){//只有左子树 可能为新的出去的点
        v.eb(id);
        for(int u:ls){
            dp[1][dep][u]=dp[0][dep][u]=dp[1][dep+1][u]+(dis[id<<1]-dis[id])*a[id<<1];//从id入到这里 或要出去 当前节点为起始点
            dp[0][dep][id]=min(dp[0][dep][id],dp[0][dep+1][u]+(dis[u]-dis[id])*a[id]);//要从该节点出去
        }
    }
    else{//两侧均非空 出去的点不包含该节点
        ll disr=(dis[id<<1|1]-dis[id])*a[id<<1|1],  ///从根走到右儿子
           disl=(dis[id<<1]-dis[id])*a[id<<1];      ///从根走到左儿子
        ll MINu1,MINu2,MINv1,MINv2;
        MINu1=MINu2=MINv1=MINv2=INFF;
        for(int u:ls)MINu1=min(MINu1,dp[1][dep+1][u]+dis[u]*a[id<<1|1]),
                     MINu2=min(MINu2,dp[0][dep+1][u]+dis[u]*a[id]);
        for(int v:rs)MINv1=min(MINv1,dp[1][dep+1][v]+dis[v]*a[id<<1]),
                     MINv2=min(MINv2,dp[0][dep+1][v]+dis[v]*a[id]);
        for(int u:ls){
            ll base1=dp[1][dep+1][u]+disr+(dis[id<<1]-2*dis[id])*a[id<<1],
               base3=dp[1][dep+1][u]+disl-dis[id]*a[id];
            dp[1][dep][u]=min(dp[1][dep][u],base1+MINv1);//先走到右边再走回来
            dp[0][dep][u]=min(dp[0][dep][u],base3+MINv2);

            dp[0][dep][u]=min(dp[0][dep][u],dp[1][dep][u]);///看代码时将这些变量拆开看式子
        }
        for(int v:rs){
            ll base2=dp[1][dep+1][v]+disl+(dis[id<<1|1]-2*dis[id])*a[id<<1|1],
               base4=dp[1][dep+1][v]+disr-dis[id]*a[id];
            dp[1][dep][v]=min(dp[1][dep][v],base2+MINu1);
            dp[0][dep][v]=min(dp[0][dep][v],base4+MINu2);
            dp[0][dep][v]=min(dp[0][dep][v],dp[1][dep][v]);
        }

    }
}
int main(){
    read(n);
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;i++)read(a[i]);
    for(int u,i=1;i<n;i++){
        read(u);dis[i+1]=dis[(i+1)/2]+u;
    }
    dfs(1,0,vec);
    ans=INFF;
    for(int u:vec)///所有可能的终点
        ans=min(ans,min(dp[1][0][u],dp[0][0][u]));
    printf("%lld\n",ans);
    return 0;
}
/*


*/
