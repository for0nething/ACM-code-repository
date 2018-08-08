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

int n,L;
int l[MAX],stk[MAX],st,en;
ll a[MAX],sum[MAX],dp[MAX];
//由j点dp更新i点
ll turn(int j,int i){
    ll x=i-j+sum[i]-sum[j]-1;
    return dp[j]+(x-L)*(x-L);
}
//确定某点x应该在哪个决策区间中
int find(int x)
{
    int left=st,right=en,mid,re=1;
    while(left<=right){
        mid=(left+right)/2;
        if(l[stk[mid]]==x)return mid;
        if(l[stk[mid]]<x)re=mid,left=mid+1;
        else right=mid-1;
    }
    return re;
}
int main()
{
    read(n);read(L);
    for(int i=1;i<=n;i++)read(a[i]),sum[i]=sum[i-1]+a[i];
    st=en=1;l[1]=1;
    for(int i=1;i<=n;i++){
        dp[i]=turn(stk[find(i)],i);//由对应的决策点确定该点
        while(st<=en&& l[stk[en]]>i && turn(i,l[stk[en]])<turn(stk[en],l[stk[en]]) )--en;
//        if(!en)//栈中已没有确定的决策区间 整个区间均为此 可以去掉
//        {
//            stk[++en]=i;l[i]=i;continue;
//        }
        //不然二分最后一个决策 寻找更新的位置
        int left=max(i+1,l[stk[en]]),right=n;
        while(left<=right){
            int mid=(left+right)/2;
            if(turn(i,mid)>turn(stk[en],mid))left=mid+1;
            else right=mid-1;
        }
        //如果i整体比前一个决策差
        if(turn(i,left)>turn(stk[en],left))continue;
        stk[++en]=i,l[i]=left;
    }
    printf("%lld\n",dp[n]);
    return 0;
}
/*
4 1 0
1 2

4 1 1
1 2
3 4
*/
