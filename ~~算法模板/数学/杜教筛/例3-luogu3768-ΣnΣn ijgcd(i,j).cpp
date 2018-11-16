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
const int MAX=1e7+5;
//const int MOD=1e9+7;
int MOD;
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

map<ll,int>res;
int phi[MAX],pref[MAX],prime[MAX];
bool check[MAX];
int inv4,inv6,pcnt;
ll n;
int cal2(ll n){n%=MOD;return mul(n,mul(mul(n+1,2*n+1),inv6));}
int cal3(ll n){n%=MOD;return mul(n,mul(n,mul(n+1,mul(n+1,inv4))));}
int getf(ll n){
    if(n<MAX)return pref[n];
    if(res.find(n)!=res.end())return res[n];
    int re=cal3(n);
    for(ll i=2,j;i<=n;i=j+1){
        j=n/(n/i);
        subi(re,mul(getf(n/i),sub(cal2(j),cal2(i-1))));
    }
    return res[n]=re;
}
int main(){
    read(MOD);read(n);
    phi[1]=1;
    for(int i=2;i<MAX;i++){
        if(!check[i])
            prime[pcnt++]=i,phi[i]=i-1;
        for(int j=0;j<pcnt;j++){
            if(prime[j]*i>=MAX)break;
            check[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]]=phi[i]*phi[prime[j]];
        }
    }
    for(int i=1;i<MAX;i++)pref[i]=add(pref[i-1],mul(mul(i,i),phi[i]));
    inv4=powMM(4,MOD-2,MOD);inv6=powMM(6,MOD-2,MOD);
    int ans=0;
    for(ll i=1,j;i<=n;i=j+1){

        j=n/(n/i);
        addi(ans,mul(cal3(n/i),sub(getf(j),getf(i-1) ) ) );
    }
    printf("%d\n",ans);
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
