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
const int MAX=5e6+5;
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
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
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

/*
    BZOJ 4337
    求树的同构
*/
int n,t,mx,ecnt;
int h[MAX],nxt[MAX],ts[MAX],siz[MAX],dp[MAX];
string qs[MAX],q[MAX],val[MAX];
/*
    加边
*/
void add_edge(int u,int v){
    nxt[++ecnt]=h[u];ts[ecnt]=v;
    h[u]=ecnt;
}
/*
    找树的重心
*/
void findrt(int now,int fa){
    siz[now]=1;dp[now]=0;
    for(int i=h[now];i;i=nxt[i]){
        int to=ts[i];
        if(to!=fa){
            findrt(to,now);
            siz[now]+=siz[to];
            if(siz[to]>dp[now])dp[now]=siz[to];
        }
    }
    if(n-siz[now]>dp[now])dp[now]=n-siz[now];
    if(dp[now]<mx)mx=dp[now];
}
/*
    从重心开始dfs得出整个树的括号表示 （即单个叶子节点用一对括号表示）
    其中每个结点的一对括号里面各子树的顺序为由字典序小到大
*/
void dfs(int now,int fa){
    qs[now]="(";
    for(int i=h[now];i;i=nxt[i]){
        int to=ts[i];
        if(to!=fa)dfs(to,now);
    }
    int lo=0;
    for(int i=h[now];i;i=nxt[i]){
        int to=ts[i];
        if(to!=fa)q[lo++]=qs[to];
    }
    if(lo>1)sort(q,q+lo);
    for(int i=0;i<lo;i++)qs[now]+=q[i];
    qs[now]+=")";
}
/*
    读入并hash一棵树
*/
string solve(){
    string re="";
    read(n);
    mx=n;for(int i=1;i<=n;i++)h[i]=0;
    for(int i=1;i<=n;i++){
        int fa;read(fa);
        if(fa)add_edge(i,fa),add_edge(fa,i);
    }
    findrt(1,0);
    for(int i=1;i<=n;i++){
        if(dp[i]==mx){
            dfs(i,0);
            if(qs[i]>re)re=qs[i];
        }
    }
    return re;
}
int main(){
    read(t);
    for(int i=1;i<=t;i++)val[i]=solve();
    for(int i=1;i<=t;i++)
    {
        int j,k;
        for(j=k=i;j;j--)
            if(val[j]==val[i])k=j;
        printf("%d\n",k);
    }
    return 0;
}
/*
10000000
*/
