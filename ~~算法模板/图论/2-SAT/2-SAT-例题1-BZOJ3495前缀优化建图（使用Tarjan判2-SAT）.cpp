/*
有 n 个点， m 条边和 K 个国家（国家里的点已知）。
每个国家只能选一个点作为首都，并且要保证最后所有边的两端至少有一个点是首都，问是否存在方案。

做法：
每个点是首都或不是首都，只有两个状态，所以是2-SAT问题。m 条边的限制很容易转化，就是每个国家只能选一个点为首都比较奇怪。
其实这是典型的前后缀优化建图，这里以前缀优化建图为例：
首先我们先增加 n 个点，令 i 的新增节点为 i+n 。然后对于一个国家，
假设有 w 个点，那么该国家中的第 i 个点（设为 A[i] ）的新增点 A[i]+n
表示该国家中1~ i 的点是否有被选的节点，即代表前缀 i 中是否有被选的节点。
那么我们可以得到以下关系式：
1. A[i−1]+n 选了， A[i]+n 必定选了； A[i]+n 没选， A[i−1]+n 必定没选（前缀之间的关系）。
2. A[i] 选了， A[i−1]+n 必定没选； A[i−1]+n 选了， A[i] 必定没选（一个国家只能有一个首都）。

后缀优化建图原理是一样的，只不过这道题并不需要后缀优化。
最后刷2-SAT判断是否存在解即可。
*/
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
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=5e6+10;
const int MOD=1e9+7;
//const long double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-6;
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
inline int add(int x,int y){return (x+y)%MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);
struct node{
    int to,nxt;
}edg[MAX<<1];

int n,m,k,dcnt,ecnt,top,scc_cnt;
int dfn[MAX],h[MAX],low[MAX],scc[MAX],stk[MAX];
bool instk[MAX];
void add_edge(int u,int v){
    edg[++ecnt]=node{v,h[u]};
    h[u]=ecnt;
}
void Tarjan(int x){
    dfn[x]=low[x]=++dcnt;stk[++top]=x;instk[x]=1;
    for(int i=h[x];i;i=edg[i].nxt){
        int to=edg[i].to;
        if(!dfn[to])Tarjan(to),low[x]=min(low[x],low[to]);
        else if(instk[to])low[x]=min(low[x],dfn[to]);
    }
    if(dfn[x]==low[x]){
        ++scc_cnt;int y;
        do y=stk[top--],instk[y]=0,scc[y]=scc_cnt;while(y!=x);
    }
}
bool Two_SAT(){
    for(int i=0;i<4*n;i++)if(!dfn[i])Tarjan(i);
    for(int i=0;i<4*n;i+=2)
        if(scc[i]==scc[i^1])return false;
}
int main()
{
    read(n);read(m);read(k);
    for(int x,y,i=1;i<=m;i++){
        read(x);read(y);--x;--y;
        add_edge(x<<1,y<<1^1);add_edge(y<<1,x<<1^1);
    }
    for(int i=0;i<n;i++)
        add_edge(i<<1^1,i+n<<1^1),add_edge(i+n<<1,i<<1);
    for(int i=1;i<=k;i++){
        int w,x,lst;read(w);
        for(int j=0;j<w;j++,lst=x){
            read(x);--x;
            if(j){
                add_edge(x+n<<1,lst+n<<1);
                add_edge(lst+n<<1^1,x+n<<1^1);
                add_edge(x<<1^1,lst+n<<1);
                add_edge(lst+n<<1^1,x<<1);
            }
        }
    }
    if(Two_SAT())printf("TAK\n");
    else printf("NIE\n");
    return 0;
}
/*
*/
