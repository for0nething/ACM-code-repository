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
const int MAX=3e4+5;
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
//inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
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

int n,m,ans;
int a[2019][2019],sum[2019][2019];
int main(){
    read(n);read(m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)scanf("%1d",&a[i][j]);
    //左上
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(a[i][j]){
                addi(ans,mul(sum[i-1][j-1],(n-i+1)*(m-j+1)));
                addi(sum[i][j],i*j);
            }
            addi(sum[i][j],(sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+MOD)%MOD);
        }
    //右上
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--){
            if(a[i][j]){
                addi(ans,mul(sum[i-1][j+1],(n-i+1)*j));
                addi(sum[i][j],i*(m-j+1));
            }
            addi(sum[i][j],(sum[i-1][j]+sum[i][j+1]-sum[i-1][j+1]+MOD)%MOD);
        }
    //同一行不同列
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(a[i][j]){
                addi(ans,mul(sum[i][j-1],1LL*i*(n-i+1)*(m-j+1)%MOD));
                addi(sum[i][j],j);
            }
            addi(sum[i][j],sum[i][j-1]);
        }
    //同一列不同行
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(a[i][j]){
                addi(ans,mul(sum[i-1][j],1LL*j*(n-i+1)*(m-j+1)%MOD));
                addi(sum[i][j],i);
            }
            addi(sum[i][j],sum[i-1][j]);
        }
    addi(ans,ans);
    //同一个点
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j])
                addi(ans,1LL*i*(n-i+1)*j*(m-j+1)%MOD);
    printf("%d\n",ans);
    assert(ans>=0&&ans<MOD);
    return 0;
}

/*

*/
