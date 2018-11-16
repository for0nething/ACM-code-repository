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

const int MAX1=1e6+5;
int tot,inv2;
bool check[MAX1+5];
int val[MAX+5],p[MAX1+5],prime[MAX1+5];
ll id[MAX];
ll n;
int haash(ll x){
    int t=x%MAX;
    while(id[t]&&id[t]!=x){t=t+1;if(t>=MAX)t-=MAX;}
    return t;
}
int cal(ll n){
    if(n<MAX1)return p[n];
    ll x=n%MOD;
    int re=mul(mul(x,x+1),inv2),lo=haash(n);
    ll i=2,j;
    if(id[lo])return val[lo];
    while(i<=n){
        j=n/(n/i);
//        cout<<i<<" "<<j<<" "<<n<<endl;
        addi(re,mul(MOD-1,mul((j-i+1)%MOD,cal(n/i))));
        i=j+1;
    }
    re=(re%MOD+MOD)%MOD;
    id[lo]=n;val[lo]=re;
    return re;
}
int main(){
    inv2=powMM(2,MOD-2,MOD);
    p[1]=1;
    for(int i=2;i<MAX1;i++){
        if(!check[i]){
            prime[++tot]=i;p[i]=i-1;
        }
        for(int j=1;j<=tot;j++){
            if(1LL*i*prime[j]>=MAX1)break;
            check[i*prime[j]]=1;
            if(i%prime[j]==0){
                p[i*prime[j]]=p[i]*prime[j];break;
            }
            p[i*prime[j]]=p[i]*p[prime[j]];
        }
    }
    for(int i=1;i<MAX1;i++)addi(p[i],p[i-1]);
    scanf("%lld",&n);
    printf("%d\n",cal(n));
    return 0;
}
/*
10000000000
*/
