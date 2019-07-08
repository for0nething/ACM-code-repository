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

int n,m;
bool ava[20][20];
char e[20][20],ecnt[20];
char a[20],acnt;
ll dp[20][20];
ll ans,sum;
void dfs(int now,int fa){
    for(char i=0;i<acnt;i++)dp[now][a[i]]=1;
    for(int i=0;i<ecnt[now];i++){
        int to=e[now][i];
        if(to==fa)continue;
        dfs(to,now);
        for(int j=0;j<acnt;j++){//当前节点颜色
            ll tot=0;
            for(int k=0;k<acnt;k++)tot+=dp[to][a[k]]*ava[a[j]][a[k]];
            dp[now][a[j]]*=tot;
        }
    }
}
int main(){
    read(n);read(m);
    for(char u,v,i=1;i<=m;i++){
        read(u);read(v);--u;--v;
        ava[u][v]=ava[v][u]=1;
    }
    for(char u,v,i=1;i<n;i++){
        read(u);read(v);--u;--v;
        e[u][ecnt[u]++]=v;
        e[v][ecnt[v]++]=u;
    }
    int tot=1<<n;
    for(int i=1;i<tot;i++){
        acnt=0;
        int now=i;
        int ge=n;
        for(char j=0;j<n;j++)
            if((now>>j)&1)
                a[acnt++]=j,--ge;
        sum=0;
        dfs(0,-1);
        for(char i=0;i<acnt;i++)sum+=dp[0][a[i]];
        if(ge&1)ans-=sum;
        else ans+=sum;
    }
    printf("%lld\n",ans);
    return 0;
}
/*


*/
