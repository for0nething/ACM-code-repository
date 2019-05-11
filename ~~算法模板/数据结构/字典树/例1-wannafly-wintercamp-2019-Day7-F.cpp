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
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;


const int INF=0x3f3f3f3f;
//const ll INFF=1200000000000000000ll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=8e6+5;
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
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){x+=y;if(x>=MOD)x%=MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
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

int n,m;
int dcnt,ans;//字典树结点个数
int cnt[MAX<<1],dp[105][2],nxt[MAX][2];//字典树
int mcnt[100][2];//小于等于m的数中二进制下第i位为j的数的个数
void insert(int k){
    int lo=0;//字典树的位置
    for(int i=31;i>=0;i--){
        int val=(k>>i)&1;
        if(!nxt[lo][val])nxt[lo][val]=++dcnt;
        addi(dp[i][val],cnt[nxt[lo][!val]]);
        lo=nxt[lo][val];++cnt[lo];
    }
}
inline ll cal_1(ll x){//小于等于x的奇数个数
    return (x+1)/2;
}
void get_mcnt(ll val){//对于val计算mcnt
    for(int i=0;i<=31;i++){
        ll ge=(val>>i);//数位dp无lim的部分(包含0)
        if(ge==0)break;
        ll num=cal_1(ge-1);//无lim部分该位置为1的个数
        addi(mcnt[i][1],(num<<i)%MOD);
        addi(mcnt[i][0],((ge-num)<<i)%MOD);
        ll limcnt=(val-(ge<<i)+1)%MOD;//有lim的数的个数
        if(val&(1<<i))addi(mcnt[i][1],limcnt);
        else addi(mcnt[i][0],limcnt);
        sub(mcnt[i][0],1);
    }
}
int main(){
    read(n);read(m);
    for(int i=1;i<=n;i++){
        int k;read(k);insert(k);
    }
    get_mcnt(m);
    for(int i=0;i<=31;i++)
        addi(ans,add(mul(m-mcnt[i][1],dp[i][0]),mul(dp[i][1],mcnt[i][1]) ));
    printf("%d\n",ans);
    return 0;
}

/*
3 1000000000
1 2 3

1 10
1

3 4
0 1 2
*/
