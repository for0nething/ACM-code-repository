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
const int MAX=1<<(20)|5;
const int MOD=998244353;
//const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
//const double eps=1e-6;
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
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
//inline int mul(int x,int y){return 1LL*x*y%MOD;}
inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void muli(int &x,int y){x=1LL*x*y%MOD;}
inline int sub(int x,int y){int res=x-y;if(res<0)res+=MOD;return res;}
inline void subi(int &x,int y){x-=y;if(x<0)x+=MOD;}
inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,lim,da,inv4;
int cnt[MAX],dp[MAX];
inline void FWTxor(int *x){
    for(int i=1;i<lim;i<<=1)
        for(int j=0;j<lim;j+=(i<<1))
            for(int k=0;k<i;++k){
                int y=x[j+k],z=x[j+k+i];
                x[j+k]=add(y,z);x[j+k+i]=sub(y,z);
            }
}
inline void IFWTxor(int *x){
    for(int i=1;i<lim;i<<=1)
        for(int j=0;j<lim;j+=(i<<1))
            for(int k=0;k<i;++k){
                int y=x[j+k],z=x[j+k+i];
                x[j+k]=half(add(y,z)),x[j+k+i]=half(sub(y,z));
            }
}
int main(){
    read(n);
    cnt[0]=n;
    inv4=powMM(4,MOD-2,MOD);
    for(int i=1,x;i<=n;i++){
        read(x);cnt[x]+=2;da=max(da,x);
    }
    lim=1;while(lim<=da)lim<<=1;
    FWTxor(cnt);
    for(int i=0;i<lim;i++){
        int x=mul(inv4,add(n,cnt[i]));
        int y=(n-x+MOD)%MOD;
        if(y&1)dp[i]=mul(powMM(3,x,MOD),MOD-1);
        else dp[i]=powMM(3,x,MOD);
    }
    IFWTxor(dp);
    printf("%d\n",sub(dp[0],1));
    return 0;
}

/*
1
30
3
6
##.#..
7
.#.#.#.
5
##.##
*/
