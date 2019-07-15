//#pragma comment(linker, "/STACK:1024000000,1024000000")
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
//#include <bitset>
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
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=1e5+5;
const ll MOD=1e9+7;
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

//vector<int>G[MAX];
int pre[MAX][52],lowlink[MAX][52],sccno[MAX][52],dfn,scc_cnt;
pii S[MAX*52];
int dp[MAX*52];
bool ava[MAX][52],have[MAX];
int n,m,d,ecnt;
struct node{
    int nxt,to;
}edg[MAX<<1];
int head[MAX];
int top;
vector<int>tm;
bool vi[MAX][55];
void dfs(int u,int day){
    pre[u][day]=lowlink[u][day]=++dfn;
    S[++top]=mp(u,day);assert(top<51*MAX);
    vi[u][day]=1;
    int nxt_day=(day+1)%d;
    for(int i=head[u];i;i=edg[i].nxt){
        int v=edg[i].to;
        if(!pre[v][nxt_day]){
            dfs(v,nxt_day);
            lowlink[u][day]=min(lowlink[u][day],lowlink[v][nxt_day]);
        }
        else if(vi[v][nxt_day])lowlink[u][day]=min(lowlink[u][day],pre[v][nxt_day]);
    }
    if(lowlink[u][day]==pre[u][day]){
        ++scc_cnt;
        int mor=0,nowans=0;
        tm.clear();
        for(;;){
            int x=S[top].first,y=S[top].second;--top;
            int nxt=(y+1)%d;
            for(int i=head[x];i;i=edg[i].nxt){
                int v=edg[i].to;
                mor=max(mor,dp[sccno[v][nxt]]);
            }
            if(ava[x][y]){
                nowans+=1-have[x];
                if(!have[x])tm.eb(x);have[x]=1;
            }
            vi[x][y]=0;
            sccno[x][y]=scc_cnt;
            if(x==u&&day==y)break;
        }
        for(int u:tm)have[u]=0;
        tm.clear();
        dp[scc_cnt]=nowans+mor;
    }
}
inline void add_edge(int u,int v){
    edg[++ecnt].nxt=head[u];
    edg[ecnt].to=v;
    head[u]=ecnt;
}
char a[55];
bool used[MAX];
int ans;
int main(){
    scanf("%d%d%d",&n,&m,&d);
    for(int u,v,i=1;i<=m;i++){
        scanf("%d%d",&u,&v);add_edge(u,v);
    }
    for(int i=1;i<=n;i++){
        scanf("%s",a);
        for(int j=0;j<d;j++)ava[i][j]=a[j]-'0';
    }
    dfs(1,0);
    printf("%d\n",dp[sccno[1][0]]);
    return 0;
}
