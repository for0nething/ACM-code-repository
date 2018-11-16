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
const int MAX=3e5+5;
const int MOD=1e9+7;
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
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);


/*
给定n,k 求 sigma( divcnt(i^k))  (结果模2^64 即ull)
n<=1e10
*/
int t,S;
ll n,k;
ull g[MAX];
int prime[MAX],tot;
void getg(){
    S=sqrt(n);tot=0;
    ull *l=g+S,*s=g;
    for(int i=1;i<=S;i++)s[i]=i,l[i]=n/i;
    for(int p=2;p<=S;p++){
        if(s[p]==s[p-1])continue;
        ll r=p*(ll)p;
        ull v=s[p-1];
        int ed1=S/p,ed2=min(n/r,1LL*S);
        for(int i=1;i<=ed1;i++)l[i]-=l[i*p]-v;
        ll m=n/p;
        for(int i=ed1+1;i<=ed2;i++)l[i]-=s[m/i]-v;
        for(int i=S;i>=r;i--)s[i]-=s[i/p]-v;
        prime[++tot]=p;
    }
    prime[++tot]=S+1;
    for(int i=1;i<=S;i++)s[i]=s[i]*(k+1),l[i]=l[i]*(k+1);
}
ull F(ll x,int y){
    if(prime[y]>x)return 0;
    ull res=g[x<=S?x:S+n/x]-g[prime[y]-1],st;
    for(int i=y;i<=tot;i++){
        st=prime[i];
        if(st*prime[i]>x)break;
        for(int j=1;;j++){
            if(st*prime[i]>x)break;
            res+=F(x/st,i+1)*(1ULL*j*k+1ULL)+(1ULL*(j+1)*k+1);
            st*=prime[i];
        }
    }
    return res;
}
int main(){
    read(t);
    while(t--){
        read(n);read(k);
        getg();
        printf("%llu\n",F(n,1)+1);
    }
    return 0;
}
/*
3
6
##.#..
7
.#.#.#.
5
##.##
*/
