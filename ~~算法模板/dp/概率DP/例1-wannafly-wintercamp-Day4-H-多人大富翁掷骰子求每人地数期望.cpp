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


double dp[7][505][505];//第i个人在第j轮之前没到过第k个位置的概率
double p[7][7];
int n;
double ans[7];
int main(){
    read(n);
    for(int i=1;i<=6;i++)
        for(int j=1;j<=6;j++)scanf("%lf",&p[i][j]);
    for(int i=1;i<=6;i++){//人
        for(int j=1;j<=n;j++)dp[i][0][j]=1;//第0轮没到过任何一个点
        dp[i][0][0]=0;//第0轮到过0
        for(int j=1;j<=500;j++){//轮数
            dp[i][j][0]=0;//全都到过0
            for(int k=1;k<=n;k++)//位置
                for(int t=1;t<=6;t++)//步数
                    dp[i][j][k]+=p[i][t]*dp[i][j-1][(k-t+n*6)%n];//n可能很小 t最大为6 所以6*n
        }
    }
    for(int i=1;i<=6;i++)//人
        for(int j=1;j<=500;j++)//轮
            for(int k=1;k<=n;k++){//位置
                double pos=1;
                for(int t=1;t<i;t++)pos*=dp[t][j][k];
                for(int t=i+1;t<=6;t++)pos*=dp[t][j-1][k];
                pos*=dp[i][j-1][k]-dp[i][j][k];
                ans[i]+=pos;
            }
    for(int i=1;i<=6;i++)printf("%.3f\n",ans[i]);
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
