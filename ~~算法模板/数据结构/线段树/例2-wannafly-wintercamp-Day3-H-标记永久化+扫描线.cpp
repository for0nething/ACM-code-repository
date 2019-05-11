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

int n,m,q,ans,tcnt,inv2,inv6,rt;
int l[MAX],r[MAX];
vector<pair<pii,int> >events[MAX];
struct node{
    int sum[3],lazy,l,r;
}T[MAX*100];
inline int getsum(int lo,int ci){
    if(ci==0)return lo;
    else if(ci==1)return mul(lo,mul(lo+1,inv2));
    else return 1LL*lo*(lo+1)%MOD*(2*lo+1)%MOD*inv6%MOD;
}
//将X、Y两个结点合并到ret
inline void merge(node &ret,node X,node Y){
    for(int i=0;i<3;i++)ret.sum[i]=add(X.sum[i],Y.sum[i]);
}
//修改k结点（对应区间[l,r]add val）
inline void change(int k,int val,int l,int r){
    T[k].lazy+=val;
    if(T[k].lazy==0)merge(T[k],T[T[k].l],T[T[k].r]);
    else for(int i=0;i<3;i++)T[k].sum[i]=(getsum(r,i)-getsum(l-1,i)+MOD)%MOD;
}
void update(int &k,int ul,int ur,int val,int l,int r){
    if(!k)k=++tcnt;
    if(ul<=l&&r<=ur){
        change(k,val,l,r);return;
    }
    int mid=(l+r)/2;
    if(ul<=mid)update(T[k].l,ul,ur,val,l,mid);
    if(ur>mid)update(T[k].r,ul,ur,val,mid+1,r);
    change(k,0,l,r);
}
node query(int k,int ql,int qr,int l,int r,int upper){
    if(ql<=l&&r<=qr){
        node ret=T[k];
        if(upper)
            for(int i=0;i<3;i++)ret.sum[i]=(getsum(r,i)-getsum(l-1,i)+MOD)%MOD;
        return ret;
    }
    node ret=node();
    int mid=(l+r)/2;
    if(ql<=mid)merge(ret,ret,query(T[k].l,ql,qr,l,mid,upper+T[k].lazy));
    if(mid<qr)merge(ret,ret,query(T[k].r,ql,qr,mid+1,r,upper+T[k].lazy));
    return ret;
}
int main(){
    read(n);read(m);read(q);
    inv2=powMM(2,MOD-2,MOD);
    inv6=powMM(6,MOD-2,MOD);
    for(int i=1;i<=n;i++)read(l[i]),read(r[i]);
    for(int i=1;i<=q;i++){
        int lx,ly,rx,ry;
        read(lx);read(ly);read(rx);read(ry);
        events[lx].eb(mp(mp(ly,ry),1));
        events[rx+1].eb(mp(mp(ly,ry),-1));
    }
    for(int i=1;i<=n;i++){
        for(auto now:events[i])
            update(rt,now.fi.fi,now.fi.se,now.se,1,m);
        node ret=query(1,l[i],r[i],1,m,0);
        for(int k=0;k<3;k++)
            ret.sum[k]=(((ll)getsum(r[i],k)-getsum(l[i]-1,k)+MOD-ret.sum[k]+MOD))%MOD;
        ll all=(ll)(MOD-ret.sum[2]+(ll)(r[i]+l[i])*ret.sum[1]+(ll)ret.sum[0]*(r[i]+1)%MOD*(MOD+1-l[i]))%MOD;
        muli(all,(ll)powMM(mul(r[i]-l[i]+2,r[i]-l[i]+1),MOD-2,MOD));
        addi(all,all);
        addi(ans,(int)all);
    }
    printf("%d\n",ans);
    return 0;
}

/*

*/
