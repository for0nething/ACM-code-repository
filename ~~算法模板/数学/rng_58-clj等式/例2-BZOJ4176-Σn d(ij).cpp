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
const int MAX=2e6+5;
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
//inline int mul(int x,int y){return 1LL*x*y%MOD;}
inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
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
杜教筛求μ的前缀和 f(x)表示Σi [x/i]  答案即为 Σg=1,n μ(g)f(n/g)^2
分块求即可 (杜教筛一次计算f(n)即可把 f(n/g)的sqrt(n)种取值计算出来 复杂度 O（n^2/3 *log）因为用了map
*/
bool check[MAX];
int prime[MAX],mu[MAX],pre[MAX];
map<ll,ll>res;
int tot,n;
int lim=1e6;
inline int cal(int x){
    if(x<=lim)return pre[x];
    if(res[x])return res[x];
    int re=1;
    for(int i=2,j;i<=x;i=j+1){
        int tem=x/i;
        j=x/tem;
        int del=mul(j-i+1,cal(tem));
        if(del)del=MOD-del;
        addi(re,del);
    }
    return res[x]=re;
}
inline int cal2(int x){
    ll re=0;
    for(int i=1,j;i<=x;i=j+1){
        int tem=x/i;
        j=x/tem;
        re+=(j-i+1LL)*tem;
    }
    return re%MOD;
}
int main(){
    mu[1]=pre[1]=1;
    for(int i=2;i<=lim;i++){
        if(!check[i])mu[i]=-1,prime[tot++]=i;
        for(int j=0;j<tot;j++){
            if(i*prime[j]>lim)break;
            check[i*prime[j]]=1;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;break;
            }
            else mu[i*prime[j]]=-mu[i];
        }
        pre[i]=pre[i-1]+mu[i];
    }
    read(n);
    int re=0;
    for(int i=1,j;i<=n;i=j+1){
        j=n/(n/i);
        int tem=cal(j)-cal(i-1);
        if(tem<0)tem=(tem%MOD+MOD)%MOD;
        int mi=cal2(n/i);
        tem=mul(tem,mul(mi,mi));
        addi(re,tem);
    }
    printf("%d\n",re);
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
