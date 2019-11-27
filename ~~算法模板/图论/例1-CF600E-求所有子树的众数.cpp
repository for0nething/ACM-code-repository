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
const int MAX=1e5+5;
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

//求每个子树众数的和(出现次数相同就都算)

int n;
vector<int>edg[MAX];
int fa[MAX],a[MAX],siz[MAX],son[MAX],maxs[MAX];
int cnt[MAX],da[MAX];///某数出现次数，某子树众数
int LIM;///当前最多出现的树出现的次数
ll sum;
ll an[MAX];///某子树的众数之和
void dfs(int now,int f){///树剖
    siz[now]=1;
    for(int u:edg[now]){
        if(u==f)continue;
        fa[u]=now;
        dfs(u,now);
        siz[now]+=siz[u];
        if(siz[u]>maxs[now])maxs[now]=siz[u],son[now]=u;
    }
}
void clear(int now){
    --cnt[a[now]];
//    if(cnt[a[now]]==LIM-1)
//    --cnt[a[now]];
    for(int u:edg[now]){
        if(u==fa[now])continue;
        clear(u);
    }
}
void insert(int now){
    ++cnt[a[now]];
    if(LIM==cnt[a[now]])sum+=a[now];
    else if(LIM<cnt[a[now]])sum=a[now],LIM=cnt[a[now]];
    for(int u:edg[now]){
        if(u==fa[now])continue;
        insert(u);
    }
}
void dfs2(int now){///计算众数
    for(int u:edg[now]){
        if(u==fa[now]||u==son[now])continue;
        dfs2(u);
        clear(u);///去除轻子树的影响
        LIM=0;sum=0;
    }
    if(son[now])dfs2(son[now]);
    for(int u:edg[now]){
        if(u==fa[now]||u==son[now])continue;
        insert(u);///加上轻子树的影响
    }
    ++cnt[a[now]];
    if(LIM==cnt[a[now]])sum+=a[now];
    else if(LIM<cnt[a[now]])sum=a[now],LIM=cnt[a[now]];
    an[now]=sum;
//    da[now]=LIM=max(LIM,++cnt[a[now]]);
    //da[now]=max(da[now])
}
void dfs3(int now){
    an[now]+=da[now];
    for(int u:edg[now]){
        if(u==fa[now])continue;
        dfs3(u);
        an[now]+=an[u];
    }
}
int main(){
    read(n);
    for(int i=1;i<=n;i++)read(a[i]);
    for(int u,v,i=1;i<n;i++){
        read(u);read(v);
        edg[u].pb(v);
        edg[v].pb(u);
    }
    dfs(1,0);
    dfs2(1);
    for(int i=1;i<=n;i++)
        printf("%lld ",an[i]);
    return 0;
}
/*
3 20
5 4 11
9 1 1
output:
2
9 18

5 40
5 10 5 10 5
3 4 5 9 4
output:
2
21 30
*/
