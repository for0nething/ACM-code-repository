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
#include <unordered_map>
//#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp

//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;
//const double INF=1e20;
const int INF=0x3f3f3f3f;
//const int INF= 0x7fffffff;
//const ll INF=0x3f3f3f3f3f3f3f3fll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=2e3+5;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const int MOD=1e9+7;
//const ull MOD=1e7+7;
//const ll MOD=998244353;
//const long double pi=acos(-1.0);
//const double eps=0.00000001;
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
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
//const long double eps=-1.0;
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);
void open()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
}
/*
    树分块
    BZOJ 1086
    给出一棵树，求一种分块方案，使得每个块的大小size∈[B,3B]。
    每个块还要选一个省会，省会可以在块外，但是省会到块内任何一个点路径上的所有除了省会的点都必须属于这个块。n≤1000。
    注意：分完块以后每个块并不一定连通
*/

int n,b;
int tot;
struct node
{
    int to,nxt;
}edg[MAX];
int h[MAX],id[MAX],cap[MAX],cnt;
void add(int u,int v)
{
    edg[++tot]=node{v,h[u]};
    h[u]=tot;
}
int stk[MAX],top;
void dfs(int now,int fa,int bot)
{
    for(int i=h[now];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(to!=fa)
        {
            dfs(to,now,top);

            if(top-bot>=b)
            {
                cap[++cnt]=now;
                while(top!=bot)id[stk[top--]]=cnt;
            }
        }
    }
    stk[++top]=now;
}
int main()
{
    scanf("%d%d",&n,&b);
    if(n<b)return 0*printf("0\n");
    for(int i=1;i<n;i++)
    {
        int u,v;scanf("%d%d",&u,&v);add(u,v);add(v,u);
    }
    dfs(1,0,0);
    while(top)
        id[stk[top--]]=cnt;
    printf("%d\n",cnt);
    for(int i=1;i<=n;i++)printf("%d ",id[i]);printf("\n");
    for(int i=1;i<=cnt;i++)printf("%d ",cap[i]);
}
/*
10 4
1 5 2 9 1 3 4 2 1 7
2 4
3 8
7 10
1 9

17
82
23
210
*/
