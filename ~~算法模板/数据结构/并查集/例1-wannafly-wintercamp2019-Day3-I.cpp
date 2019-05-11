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
const int MAX=2e5+5;
const ll MOD=998244353;
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

int fa[MAX];
int val[MAX];
inline int getfa(int x){
    if(fa[x]==x)return x;
    int y=getfa(fa[x]);
    if(fa[x]!=y)
        muli(val[x],val[fa[x]]);
    fa[x]=y;
    return y;
}
int n,m,mi;
int v1_3,v2_3;
int main(){
    read(n);read(m);
    mi=powMM(3,n,MOD);
    v1_3=powMM(3,MOD-2,MOD);
    v2_3=mul(2,powMM(3,MOD-2,MOD));
    for(int i=1;i<=n;i++)fa[i]=i,val[i]=1;
    while(m--){
        int opt;
        read(opt);
        if(opt==1){
            int x,y;
            read(x);read(y);
            muli(val[x],v2_3);muli(val[y],v1_3);
            muli(val[y],powMM(val[x],MOD-2,MOD));
            fa[y]=x;
        }
        else{
            int x;read(x);
            int rt=getfa(x);
            int ans=mul(val[x],mi);
            if(x!=rt)muli(ans,val[rt]);
            printf("%d\n",ans);
        }
    }
    return 0;
}

/*

*/
