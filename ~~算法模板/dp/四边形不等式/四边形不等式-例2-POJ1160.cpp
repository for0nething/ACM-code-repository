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
//const double INF=1e20;
const int INF=0x3f3f3f3f;
//const int INF= 0x7fffffff;
//const ll INF=0x3f3f3f3f3f3f3f3fll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=1e5+10;
//const int M=(1<<20)+5;
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

ll mul(ll a , ll b,ll Q){
    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
}

//const long double eps=-1.0;
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);
void open()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
}
//#define debug
int n,m;
int dp[32][303];
int a[305];
int w[303][303];
int s[32][303];
int getw(int i,int j){
    if(i>=j)return 0;
    if(w[i][j])return w[i][j];
    return w[i][j]=a[j]-a[i]+getw(i+1,j-1);
}
int main()
{
    while(~scanf("%d%d",&n,&m)){
        for(int i=1;i<=n;i++)read(a[i]);
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++)
            dp[1][i]=getw(1,i),s[1][i]=1;//此s实际不是最后位置 而是用于循环中确定范围
        for(int i=2;i<=m;++i){
            s[i][n+1]=n;//尽管无意义 但因为循环中出现s[i][j+1] 为划定范围 加上此
            for(int j=n;j>i;--j){
                for(int k=s[i-1][j];k<=s[i][j+1];++k)
                {
                    if(dp[i-1][k]+getw(k+1,j)<dp[i][j]){
                        dp[i][j]=dp[i-1][k]+getw(k+1,j);
                        s[i][j]=k;
                    }
                }
            }
        }
        printf("%d\n",dp[m][n]);
    }

    return 0;
}
/*
4 1 0
1 2

4 1 1
1 2
3 4
*/
