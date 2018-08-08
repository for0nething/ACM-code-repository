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
const int MAX=1e6+10;
//const int M=(1<<20)+5;
//const int M=2500007;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const ll MOD=1e9+7;
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
    while (b){
        if (b&1LL) ret=ret*a%M;
        b>>=1LL;
        a=a*a%M;
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
int n,m,k;
int x[1005][1005];
int maxh[1005][1005],maxl[1005][1005];
int que[1005],st,en;
void getmax(int len,int z[1005][1005])//连续长度为len的区间
{
    for(int i=1;i<=n;i++){
        st=1,en=0;
        for(int j=1;j<=m;j++){
            while( st<=en&& que[st]+len-1<j ) ++st;
            while( st<=en&& que[en]<=z[i][j] ) --en;
            que[++en]=z[i][j];
            maxh[i][j]=que[st];
        }
    }
    for(int i=1;i<=m;i++){
        st=1,en=0;
        for(int j=1;j<=n;j++){
            while( st<=en&& que[st]+len-1<j ) ++st;
            while( st<=en&& que[en]<=maxh[j][i] )--en;
            que[++en]=maxh[j][i];
            maxl[j][i]=que[st];
        }
    }
}
int main()
{
    read(n);read(m);read(k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)read(x[i][j]);
    getmax(k,x);
    int an=0;
    for(int i=k;i<=n;i++)
        for(int j=k;j<=n;j++)an=max(an,maxl[i][j]);
    printf("%d\n",an);
    return 0;
}
/*
4 1 0
1 2

4 1 1
1 2
3 4
*/
