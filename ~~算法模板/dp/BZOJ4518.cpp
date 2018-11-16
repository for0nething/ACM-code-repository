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
const int MAX=1e6+5;
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
inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
//inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
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


ll A[MAX],dp[MAX];
int pre[MAX];
int n,m;
inline int getY(int id){
    return dp[id]+A[id]*A[id];
}
inline int getX(int id){
    return A[id];
}
int solve_slope(ll w){
    static int Q[MAX],head,tail;
    int i,qi,qj,qk;
    head=tail=0;
    dp[0]=0;Q[tail++]=0;
    for(int i=1;i<=n;i++){
        while(head+1<tail){
            qi=Q[head],qj=Q[head+1];
            if(getY(qj)-getY(qi)<=2*A[i]*(getX(qj)-getX(qi)))head++;
            else break;
        }
        qi=Q[head];pre[i]=qi;
        dp[i]=dp[qi]+(A[i]-A[qi])*(A[i]-A[qi])+w;
        while(head+1<tail){
            qi=Q[tail-2];qj=Q[tail-1];qk=i;
            ll y1=getY(qj)-getY(qi),x1=getX(qj)-getX(qi);
            ll y2=getY(qk)-getY(qj),x2=getX(qk)-getX(qj);
            if(y2*x1<=y1*x2)tail--;
            else break;
        }
        Q[tail++]=i;
    }
    int ret=0;
    for(int x=n;x;x=pre[x])ret++;
    return ret;
}
ll solve(){
    ll l=-1000000000,r=1000000000;
    while(l+1<r){
        ll mid=l+(r-l)/2;
        for(int i=1;i<=n;i++)dp[i]=0;
        if(solve_slope(mid)<=m)r=mid;
        else l=mid;
    }
    solve_slope(l);
    // 这里的意义: 假设每次的答案都是最后一次的斜率
	// 然后, 二分这个斜率, 找到答案后减去每次的贡献
    return dp[n]-l*m;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld",&A[i]),A[i]+=A[i-1];
    printf("%lld\n",solve()*m-A[n]*A[n]);
    return 0;
}
/*
3 2
1 2 3

3 3
3 3 3

2 1
4 7
*/
