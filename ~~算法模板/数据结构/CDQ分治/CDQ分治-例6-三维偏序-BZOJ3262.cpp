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
const int MAX=2e6+10;
const int MOD=1e9+7;
//const int MOD=1e9+7;
const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-6;
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
inline int mul(int x,int y){x%=MOD;y%=MOD;return 1LL*x*y%MOD;}
inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,k,qcnt;
int ar[MAX];
inline int lowbit(int x){return x&(-x);}
void bit_add(int lo,int v){
    while(lo<=k)ar[lo]+=v,lo+=lowbit(lo);
}
int sum(int lo){
    int re=0;
    while(lo)re+=ar[lo],lo-=lowbit(lo);
    return re;
}
void clear(int lo){
    while(lo<=k&&ar[lo])ar[lo]=0,lo+=lowbit(lo);
}
struct Query{
    int x,y,z,opt;
    bool operator<(const Query& q)const{
//        if(x!=q.x)return x<q.x;
        if(y!=q.y)return y<q.y;
//        if(z!=q.z)return z<q.z;
        return opt<q.opt;
    }
}qs[MAX],tmp[MAX];
bool cmp(const Query &a,const Query &b){
        if(a.x!=b.x)return a.x<b.x;
        if(a.y!=b.y)return a.y<b.y;
        if(a.z!=b.z)return a.z<b.z;
        return a.opt<b.opt;
}
void addq(int x,int y,int z,int opt){
    qs[qcnt++]=Query{x,y,z,opt};
}
int ans[MAX],ax[MAX],ay[MAX],az[MAX];
void cdq(int l,int r){
    if(l==r)return;
    int mid=(l+r)/2;
    cdq(l,mid);cdq(mid+1,r);
    int lp=l,rp=mid+1,tp=l;
    while(lp<=mid&&rp<=r){
        if(qs[lp]<qs[rp]){
            if(!qs[lp].opt)bit_add(qs[lp].z,1);
            tmp[tp++]=qs[lp++];
        }
        else{
            if(qs[rp].opt)ans[qs[rp].opt]+=sum(qs[rp].z);
            tmp[tp++]=qs[rp++];
        }
    }
    while(lp<=mid){
        if(!qs[lp].opt)bit_add(qs[lp].z,1);
            tmp[tp++]=qs[lp++];
    }
    while(rp<=r){
        if(qs[rp].opt){
            ans[qs[rp].opt]+=sum(qs[rp].z);
        }
        tmp[tp++]=qs[rp++];
    }
    for(int i=l;i<=r;i++)qs[i]=tmp[i];
    for(int i=l;i<=r;i++)clear(qs[i].z);
}
int cnt[MAX];
int main(){
    read(n);read(k);
    for(int x,y,z,i=1;i<=n;i++){
        read(ax[i]);read(ay[i]);read(az[i]);
        addq(ax[i],ay[i],az[i],0);
    }
    for(int i=1;i<=n;i++)
        addq(ax[i],ay[i],az[i],i);
    sort(qs,qs+qcnt,cmp);cdq(0,qcnt-1);
    for(int i=1;i<=n;i++)++cnt[ans[i]];
    for(int i=0;i<n;i++)printf("%d\n",cnt[i+1]);
//        printf("%d\n",ans[i]);

    return 0;
}
/*
3
11011010

*/
