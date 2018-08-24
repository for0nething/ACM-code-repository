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
const int MAX=2e5+5;
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
int n,m;
int a[MAX];
/*
    记录莫队中的每一个查询的结构体
*/
struct node
{
    int al,ar,bel,id;
}qs[MAX];
/*
    对查询排序
*/
bool cmp(node x,node z)
{
    return x.bel==z.bel?x.ar<z.ar:x.bel<z.bel;
}
int cnt[MAX],sum[MAX];
int ans[MAX];
/*
    莫队示例：
    求数组区间mex
*/
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]>n)a[i]=n;
    }
    int siz=sqrt(n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&qs[i].al,&qs[i].ar);
        qs[i].bel=(qs[i].al-1)/siz;qs[i].id=i;
    }
    sort(qs+1,qs+1+m,cmp);
    /*
        对于下标从1开始的情况
        lol初始设置为1 lor初始设置为0
    */
    int lol=1,lor=0;siz=sqrt(n+1);
    /*
        每次莫队调整l和r的位置
    */
    for(int i=1;i<=m;i++)
    {
        while(lol>qs[i].al)--lol,sum[a[lol]/siz]+=(!cnt[a[lol]]),++cnt[a[lol]];
        while(lor<qs[i].ar)++lor,sum[a[lor]/siz]+=(!cnt[a[lor]]),++cnt[a[lor]];
        while(lol<qs[i].al)--cnt[a[lol]],sum[a[lol]/siz]-=(!cnt[a[lol]]),++lol;
        while(lor>qs[i].ar)--cnt[a[lor]],sum[a[lor]/siz]-=(!cnt[a[lor]]),--lor;
        int st=0;
        for(int i=0;i<=siz;i++,st+=siz)if(sum[i]<siz)break;
        while(cnt[st])++st;
        ans[qs[i].id]=st;
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
}
/*

*/
