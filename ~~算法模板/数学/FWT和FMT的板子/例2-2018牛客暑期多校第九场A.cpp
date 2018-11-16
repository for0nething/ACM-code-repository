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
const int MAX=1e6+10;
const ll MOD=1e9+7;
//const int MOD=1e9+7;
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
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
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

template<typename T>void FWT(T* a,int len)
{
    for (int hl = 1, l = 2; l <= len; hl = l, l <<= 1)
        for (T i = 0; i < len; i += l)
        for (register T t, j = 0, *x = a + i, *y = x + hl; j < hl; ++j, ++x, ++y) t = add(*x , *y), *y = add(*x,MOD - *y), *x = t; return;
}
template<typename T>void DWT(T* a,int len,int inv)
{
    for (int hl = 1, l = 2; l <= len; hl = l, l <<= 1)
        for (T i = 0; i < len; i += l)
        for (register T t, j = 0, *x = a + i, *y = x + hl; j < hl; ++j, ++x, ++y) t = mul(add(*x , *y),inv), *y = mul(inv,add(*x,MOD - *y)), *x = t; return;
}
int a[MAX],b[MAX],inv,n;
int main()
{
    read(n);
    for(int i=0;i<n;i++)read(a[i]);
    for(int i=0;i<n;i++)read(b[i]);
    FWT(a,n);FWT(b,n);
    inv=powMM(2,MOD-2,MOD);
    for(int i=0;i<n;i++)a[i]=mul(powMM(a[i],MOD-2,MOD),b[i]);
    DWT(a,n,inv);
    for(int i=0;i<n;i++)printf("%d\n",a[i]);
    return 0;
}
/*
4
0 3 7 1
3 0 2 2
7 2 0 3
1 2 3 0

*/
