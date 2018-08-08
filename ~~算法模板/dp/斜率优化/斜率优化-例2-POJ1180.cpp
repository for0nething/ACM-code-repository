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

int n,s,st,en;
int que[MAX],f[MAX],t[MAX];
ll sumt[MAX],sumf[MAX],dp[MAX];
int main()
{
    while(~scanf("%d%d",&n,&s)){
        for(int i=1;i<=n;++i){read(t[i]);read(f[i]);}
        sumt[n+1]=sumf[n+1]=dp[n+1]=0;
        for(int i=n;i>=1;--i){
            sumt[i]=sumt[i+1]+t[i];
            sumf[i]=sumf[i+1]+f[i];
        }
        st=1,en=1;que[st]=n+1;
        for(int i=n;i>=1;--i){
            while(st<en&& (dp[que[st+1]]-dp[que[st]])<=sumf[i]*(sumt[que[st+1]]-sumt[que[st]]))
                ++st;
            int j=que[st];
            dp[i]=dp[j]+(s+sumt[i]-sumt[j])*sumf[i];
            while(st<en&& (dp[i]-dp[que[en]])*(sumt[que[en]]-sumt[que[en-1]])<=(dp[que[en]]-dp[que[en-1]])*(sumt[i]-sumt[que[en]]))
                --en;
            que[++en]=i;
        }
        printf("%lld\n",dp[1]);

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
