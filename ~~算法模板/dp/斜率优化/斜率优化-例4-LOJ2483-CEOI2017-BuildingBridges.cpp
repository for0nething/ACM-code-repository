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

int n;

inline ll sqr(ll x){return x*x;}
//inline ll getY(int i){
//    return dp[i]-pre[i]+h[i]*h[i];
//}

struct node{
    ll h,w,pre,dp,id,y;
    bool operator <(const node & z)const{
        if(h!=z.h)
            return h<z.h;
        return id<z.id;
    }
    ll getY(){
        return dp-pre+h*h;
    }
}a[MAX],tmp[MAX];
struct convex_hull{
    typedef pll point;
#define x first
#define y second
    point p[MAX];
    int head,tail;
    convex_hull():head(0),tail(0){}
    inline void init(){
        head=tail=0;
    }
    inline ll cross(point &p,point &q,point &r){
        return (q.x-p.x)*(r.y-p.y)-(q.y-p.y)*(r.x-p.x);
    }
    inline void insert(ll x,ll y){
        point q(x,y);
        while(head>tail+1&&cross(p[head-1],p[head],q)<=0)--head;
        p[++head]=q;
    }
    inline void update(ll x){
        while(head>tail+1&&(p[tail+2].y-p[tail+1].y)<=2*x*(p[tail+2].x-p[tail+1].x ) )
            ++tail;
    }
#undef x
#undef y

}hull;

void CDQ(int l,int r){
    if(l==r){
        a[l].y=a[l].getY();
        return ;
    }
    int mid=(l+r)/2;
    int stl=l,str=mid+1;
    for(int i=l;i<=r;i++){
        if(a[i].id<=mid)tmp[stl++]=a[i];
        else tmp[str++]=a[i];
    }
    for(int i=l;i<=r;i++)a[i]=tmp[i];
    CDQ(l,mid);
    hull.init();
    for(int i=l;i<=mid;i++)
        hull.insert(a[i].h,a[i].y);
    for(int i=mid+1;i<=r;i++){
        hull.update(a[i].h);
        ll X=hull.p[hull.tail+1].fi,Y=hull.p[hull.tail+1].se;
        a[i].y=Y-2*a[i].h*(X-a[i].h)-a[i].w;
        a[i].dp=min(a[i].dp,a[i].y+a[i].pre-sqr(a[i].h));
    }
    CDQ(mid+1,r);
    stl=l,str=mid+1;
    int lo=l;
    while(stl<=mid&&str<=r){
        if(a[stl].h==a[str].h){
            if(a[stl].y<a[str].y)tmp[lo++]=a[stl++];
            else tmp[lo++]=a[str++];
        }
        else{
            if(a[stl].h<a[str].h)
                tmp[lo++]=a[stl++];
            else tmp[lo++]=a[str++];
        }
    }
    while(stl<=mid)tmp[lo++]=a[stl++];
    while(str<=r)tmp[lo++]=a[str++];
    for(int i=l;i<=r;i++)
        a[i]=tmp[i];

}
int main(){
    read(n);
    for(int i=1;i<=n;i++)
        read(a[i].h);
    for(int i=1;i<=n;i++){
        read(a[i].w);a[i].pre=a[i-1].pre+a[i].w;a[i].id=i;
        a[i].dp=INFF/2LL;
    }
    a[1].dp=0;
    sort(a+1,a+1+n);
    CDQ(1,n);
    for(int i=1;i<=n;i++)
        if(a[i].id==n)printf("%lld\n",a[i].dp);

    return 0;
}
/*
9 5
440 546 398 3132 3121 2939 3139 1476 3075

13040944
*/
