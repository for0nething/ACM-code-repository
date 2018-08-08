/*
    2018 牛客多校2 K
    https://www.nowcoder.com/acm/contest/140#question
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
const ll magic=31;
int n,m,x,y,st,en;
char a[MAX];
int f[MAX];
ll c[MAX],maxh[MAX],maxl[MAX];
ll row[MAX],col[MAX],re[30],que[MAX],loq[MAX];
void getf(ll *z,int m){
    f[0]=f[1]=0;
    for(int i=2,j=0;i<=m;i++){
        while(j&&z[j+1]!=z[i])j=f[j];
        if(z[j+1]==z[i])++j;
        f[i]=j;
    }
}
#define id(x,y) ((x-1)*m+y)
/*
    二维单调队列
    n*m的矩阵中 处理每个w*l 的矩阵的最大值
*/
void getmax(int w,int l,ll *z){
    for(int i=1;i<=n;i++){
        st=1;en=0;
        for(int j=1;j<=m;j++){
            while(st<=en&&loq[st]+l-1<j)++st;
            while(st<=en&&que[en]<=z[id(i,j)])--en;
            que[++en]=z[id(i,j)];
            loq[en]=j;
            maxh[id(i,j)]=que[st];
        }
    }
    for(int i=1;i<=m;i++){
        st=1,en=0;
        for(int j=1;j<=n;j++){
            while(st<=en&&loq[st]+w-1<j)++st;
            while(st<=en&&que[en]<=maxh[id(j,i)])--en;
            que[++en]=maxh[id(j,i)];
            loq[en]=j;
            maxl[id(j,i)]=que[st];
        }
    }
}
int main()
{
    for(int i=0;i<=25;i++)re[i]=i+1;
    random_shuffle(re,re+26);
    read(n);read(m);
    for(int i=1;i<=n;i++){
        scanf("%s",a+1);
        for(int j=1;j<=m;j++){
            row[i]=(row[i]*magic%MOD+re[a[j]-'a'])%MOD;
            col[j]=(col[j]*magic%MOD+re[a[j]-'a'])%MOD;
        }
    }
    getf(row,n);x=n-f[n];//宽 （循环节的宽）
    getf(col,m);y=m-f[m];//长 （循环节的长）
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            read(c[id(i,j)]);
    getmax(x,y,c);
    ll an=INFF;
    for(int i=x;i<=n;i++)
        for(int j=y;j<=m;j++)an=min(an,maxl[id(i,j)]);
    printf("%lld\n",an*(x+1)*(y+1));
    return 0;
}
/*
4 1 0
1 2

4 1 1
1 2
3 4
*/
