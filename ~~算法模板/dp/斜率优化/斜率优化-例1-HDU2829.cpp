/*
    周源 浅谈数形结合思想在信息学竞赛中的应用 有介绍到斜率优化
*/
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
const int MAX=1e5+7;
//const int M=2500007;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const int MOD=1e9+7;
//const ull MOD=1e7+7;
//const ll MOD=998244353;
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
int n,m;
int a[MAX],dp[MAX][2],cost[MAX],sum[MAX],q[MAX],st,en;
int now;
int getx(int i){return sum[i];}
int gety(int i){return dp[i][now^1]-cost[i]+sum[i]*sum[i];}
int main()
{
    now=0;
    while(scanf("%d%d",&n,&m)&&n)
    {
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
        for(int i=1;i<=n;i++)cost[i]=cost[i-1]+sum[i-1]*a[i];
//        st=en=1;q[st]=0;
        for(int i=1;i<=n;i++)dp[i][now]=cost[i];
        for(int i=1;i<=m;i++)
        {
            now^=1;
            st=en=1;q[st]=0;
            for(int j=1;j<=n;j++)
            {
                while(st<en&&(gety(q[st+1])-gety(q[st]))<=sum[j]*(getx(q[st+1])-getx(q[st]) ))++st;
                dp[j][now]=dp[q[st]][now^1]+cost[j]-cost[q[st]]-sum[q[st]]*(sum[j]-sum[q[st]]);
//                printf("%d!\n",dp[j][now]);
                while(st<en&&( gety(j) -gety(q[en]) )*( getx(q[en])-getx(q[en-1]) )<=( gety(q[en])-gety(q[en-1]) ) *( getx(j)-getx(q[en])  ) )--en;
                q[++en]=j;
            }
        }
        printf("%d\n",dp[n][now]);
    }
    return 0;
}
/*
7 5
1 1 3 2 3 4 3
1 3
1 4
3 7
1 7
6 6

*/
