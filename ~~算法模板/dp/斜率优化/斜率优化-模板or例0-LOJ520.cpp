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
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=1e5+5;
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


inline ll sqr(const int x){return (ll)x*x;}
int n;
int w[MAX];
ll dp[MAX],sum;
struct convex_hull{
    typedef pll point;
#define x first
#define y second
    point p[MAX];
    int top;
    convex_hull():top(0){}
    inline ll cross(point &p,point &q,point &r){
        return (q.x-p.x)*(r.y-p.y)-(q.y-p.y)*(r.x-p.x);
    }
    inline void insert(ll x,ll y){
        point q(x,y);
        while(top>=2&&cross(p[top-2],p[top-1],q)<=0)--top;
        p[top++]=q;
    }
    inline ll eval(point &p,ll slope){return p.y-p.x*slope;}
    inline ll query(ll slope){
        int lo=0,hi=top-1,mid;
        while(lo<hi-1){
            mid=(lo+hi)>>1;
            if(eval(p[mid],slope)>eval(p[mid+1],slope))
                lo=mid;
            else hi=mid;
        }
        return eval(p[hi],slope);
    }
#undef x
#undef y
}hull;
int main(){
    read(n);
    for(int i=0;i<n;i++)read(w[i]);
    sort(w,w+n);
    dp[0]=sqr(w[1]-w[0]);
    hull.insert(w[0],dp[0]+sqr(w[0]));

    for(int i=2;i<n;i++){
        dp[i-1]=hull.query(w[i]*2)+sum+sqr(w[i]);
        sum+=sqr(w[i]-w[i-1]);
        dp[i-1]-=sum;
        hull.insert(w[i-1],dp[i-1]+sqr(w[i-1]));
    }
    ll ans=INFF;
    for(int i=0;i<n-1;i++)ans=min(ans,dp[i]+sqr(w[n-1]-w[i]));
    printf("%lld\n",ans+sum);
    return 0;
}
/*

4
1 2 3 4
*/
