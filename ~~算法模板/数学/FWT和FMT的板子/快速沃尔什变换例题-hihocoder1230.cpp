/*
题意：有2*n+1个人，第一遍给每个人先发 [0,m]中任意值的钱，第二遍再给每个人发x元，
x的范围为[L,R]。问有多少种第一遍发钱的方法使得：存在x使得这些人的钱的异或值在第二遍发完之后为0。
解法：首先暴力打表发现如果某一方案可行，则第二遍发钱的值x一定唯一。（并不会证，但发现2*n+1为奇数时有该性质）
然后就可以转化为：先枚举x，然后求给每个人发[x, x+m]元钱，使得他们异或值为0的方案数。
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
const int MAX=1e5+10;
const int M=1e6+15;
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
    while (b){
        if (b&1LL) ret=ret*a%M;
        b>>=1LL;
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
//#define debug
ll inv;
int a[MAX];
void fwt(int *a,int l,int r)//左闭右闭
{
    if(l==r)return;
    int n=(r-l+1)/2,mid=l+n-1;
    fwt(a,l,mid);fwt(a,mid+1,r);
    for(int i=l;i<=mid;i++)
    {
        ll x=a[i],y=a[i+n];
        a[i]=(x+y)%MOD;a[i+n]=(x-y+MOD)%MOD;
    }
}
void dwt(int *a,int l,int r)
{
    if(l==r)return;
    int n=(r-l+1)/2,mid=l+n-1;
    dwt(a,l,mid);dwt(a,mid+1,r);
    for(int i=l;i<=mid;i++)
    {
        ll x=a[i],y=a[i+n];
        a[i]=(x+y)%MOD*inv%MOD;a[i+n]=(x-y+MOD)%MOD*inv%MOD;
    }
}
ll cal(int l,int r,int n)
{
    int N=1;
    while(N<=r)N<<=1;
    for(int i=0;i<N;i++)a[i]=(i<=r&&i>=l)?1:0;
    fwt(a,0,N-1);//左闭右闭 故需要-1
    for(int i=0;i<N;i++)a[i]=powMM(a[i],n,MOD);
    dwt(a,0,N-1);
    return (a[0]+MOD)%MOD;
}
int n,m,l,r;
int main()
{
    inv=powMM(2,MOD-2,MOD);
    while(~scanf("%d%d%d%d",&n,&m,&l,&r))
    {
        n=2*n+1;
        ll ans=0;
        for(int i=l;i<=r;i++)(ans+=cal(i,m+i,n))%=MOD;//枚举取的k
        printf("%lld\n",ans);
    }
    return 0;
}
/*
1 3 1 3
2 3 2 5
*/
