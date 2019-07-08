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
//#include <utility>
//#include <complex>
#include <assert.h>
//#include <limits.h>
//#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;

#define rank rankk
#define mp make_pair
#define pb push_back
#define eb push_back
//#define eb emplace_back
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
typedef pair<double,int> pdi;
typedef long double ld;
const int INF=0x3f3f3f3f;
const ll INFF=1e16;
//const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=2e5+5;
const ll MOD=998244353;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
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
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,m,now,pre;
ll p[MAX];
int dp[2][MAX];
ll getY(int id){
    return dp[pre][id]+p[id]*p[id];
}
struct convex_hull{
    typedef pll point;
#define x first
#define y second
    point p[MAX];
    int head,tail;///у╬ве
    convex_hull():head(0),tail(0){}
    inline void init(){
        head=tail=0;
    }
    inline ll cross(point &p,point &q,point &r){
        return (q.x-p.x)*(r.y-p.y)-(q.y-p.y)*(r.x-p.x);
    }
    inline void insert(ll x,ll y){
        point q(x,y);
        while(head>tail+1&&cross(p[head-1],p[head],q)<0)--head;
        p[++head]=q;
    }
    inline void update(ll x){
        while(head>tail+1&&(p[tail+2].y-p[tail+1].y)<2*x*(p[tail+2].x-p[tail+1].x) )++tail;
    }
}hull;
int main(){
    read(n);read(m);
    pre=1;
    for(int i=1;i<=n;i++){
        read(p[i]);p[i]+=p[i-1];
    }
    for(int i=1;i<=n;i++)
        dp[now][i]=p[i]*p[i];
    for(int j=2;j<=m;j++){

        swap(now,pre);
        memset(dp[now],0x3f,sizeof(dp[now]));
        hull.init();
        ll tem=getY(j-1);
//        dp[now][j-1]=tem;
        hull.insert(p[j-1],tem);
        for(int i=j;i<=n;i++){
            hull.update(p[i]);
            ll px=hull.p[hull.tail+1].x,dpval=hull.p[hull.tail+1].y-px*px;
            dp[now][i]=dpval+(p[i]-px)*(p[i]-px);
            hull.insert(p[i],getY(i));
        }
    }
//    printf("%lld\n",dp[now][n]);
    printf("%lld\n",m*dp[now][n]-p[n]*p[n]);

    return 0;
}
/*
9 5
440 546 398 3132 3121 2939 3139 1476 3075

13040944
*/
