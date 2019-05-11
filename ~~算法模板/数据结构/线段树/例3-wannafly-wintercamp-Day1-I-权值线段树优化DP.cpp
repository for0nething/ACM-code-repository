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
#define fi first
#define se second
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;


const int INF=0x3f3f3f3f;
//const ll INFF=1200000000000000000ll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=1e5+5;
const ll MOD=1e9+7;
//int MOD;
//const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
//const long double eps=1e-13;
//const double pi=acos(-1);
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
namespace{
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
template<class T> inline T add(T x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(T &x,T y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){x+=y;if(x>=MOD)x%=MOD;}
template<class T> inline T mul(T x,T y){return 1LL*x*y%MOD;}
//inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
template<class T> inline void muli(T &x,T y){x=1LL*x*y%MOD;}
template<class T> inline T sub(T x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(T &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline T half(T x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,ans;
int a[MAX];
int dp[MAX<<2],lazy[MAX<<2],cnt[MAX<<2];
inline void change(int k,int val){
    addi(lazy[k],val);
    addi(dp[k],mul(cnt[k],val));
}
inline void pushup(int k){
    cnt[k]=add(cnt[k<<1],cnt[k<<1|1]);
    dp[k]=add(dp[k<<1],dp[k<<1|1]);
}
inline void pushdown(int k){
    if(lazy[k]){
        change(k<<1,lazy[k]);
        change(k<<1|1,lazy[k]);
        lazy[k]=0;
    }
}
void updatecnt(int k,int ul,int ur,int l,int r){
    if(ul<=l&&r<=ur){
        change(k,1);return;
    }
    int mid=(l+r)/2;
    pushdown(k);
    if(ul<=mid)updatecnt(k<<1,ul,ur,l,mid);
    if(ur>mid)updatecnt(k<<1|1,ul,ur,mid+1,r);
    pushup(k);
}
void updatedp(int k,int lo,int val,int l,int r){
    if(l==r){
        addi(cnt[k],val);return;
    }
    int mid=(l+r)/2;
    pushdown(k);
    if(lo<=mid)updatedp(k<<1,lo,val,l,mid);
    else updatedp(k<<1|1,lo,val,mid+1,r);
    pushup(k);
}
int query(int k,int ql,int qr,int l,int r){
    if(ql<=l&&r<=qr)return dp[k];
    int mid=(l+r)/2,re=0;
    pushdown(k);
    if(ql<=mid)addi(re,query(k<<1,ql,qr,l,mid));
    if(qr>mid)addi(re,query(k<<1|1,ql,qr,mid+1,r));
    pushup(k);
    return re;
}
int main(){
    read(n);
    for(int i=1;i<=n;i++)read(a[i]);
    for(int i=n;i>=1;i--){
        int sum=0;
        if(a[i]!=1)sum=query(1,1,a[i]-1,1,n);
        addi(ans,sum);
        if(a[i]!=n)updatecnt(1,a[i]+1,n,1,n);
        updatedp(1,a[i],sum+1>=MOD?sum+1-MOD:sum+1,1,n);
    }
    printf("%d",ans);
    return 0;

}

/*

*/
