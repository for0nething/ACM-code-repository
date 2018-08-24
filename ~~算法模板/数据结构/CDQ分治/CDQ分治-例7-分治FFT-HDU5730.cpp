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
//const ll INFF=1200000000000000000ll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=(1<<18)+5;
const int MOD=313;
const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-6;
//#define double long double
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
inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
//inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

struct cpx {
    double x,y;
    cpx(double a=0,double b=0):x(a),y(b) {}
};

cpx operator + (cpx a,cpx b) {return cpx(a.x+b.x,a.y+b.y);}
cpx operator - (cpx a,cpx b) {return cpx(a.x-b.x,a.y-b.y);}
cpx operator * (cpx a,cpx b) {return cpx(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}

const int maxn=500005;

char buf[maxn];
int n;
cpx A[maxn],B[maxn];
int dp[MAX],cnt[MAX];
ll num[maxn];

void DFT(cpx* a,int n,int d=1) {
    for(int i=(n>>1),j=1;j<n;j++) {
        if(i<j) swap(a[i],a[j]);
        int k;for(k=(n>>1);i&k;i^=k,k>>=1);
        i^=k;
    }
    for(int m=2;m<=n;m<<=1) {
        cpx w=cpx(cos(pi*2/m*d),sin(pi*2/m*d));
        for(int i=0;i<n;i+=m) {
            cpx s=cpx(1,0);
            for(int j=i;j<(i+(m>>1));j++) {
                cpx u=a[j],v=s*a[j+(m>>1)];
                a[j]=u+v;a[j+(m>>1)]=u-v;
                s=s*w;
            }
        }
    }
    if(d==-1) for(int i=0;i<n;i++) a[i].x=a[i].x/n;
}
void cdq(int l,int r){
    if(l==r)return;
    int mid=(l+r)/2;
    cdq(l,mid);
    int n=1;while(n<r-l+1)n<<=1;
    for(int i=0;i<n;i++)A[i]=B[i]=cpx();
    for(int i=l;i<=mid;i++)A[i-l].x=dp[i];
    for(int i=0;i<=r-l;i++)B[i].x=cnt[i];
    DFT(A,n);DFT(B,n);
    for(int i=0;i<n;i++)A[i]=A[i]*B[i];
    DFT(A,n,-1);
    for(int i=mid+1;i<=r;i++)
        addi(dp[i],(int)trunc(A[i-l].x+0.5));
    cdq(mid+1,r);
}
int main()
{
    while(scanf("%d",&n)&&n){
        for(int i=1;i<=n;i++)read(cnt[i]),cnt[i]%=MOD,dp[i]=cnt[i];
        cdq(1,n);
        printf("%d\n",dp[n]%MOD);
    }
    return 0;
}
/*
3  10
1 1
2 0
3 1

3  10
1 1
2 1
3 0
*/
