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

int n,m,cnt,qcnt;
int lo[MAX],id[MAX],val[MAX];
ll ans[MAX];
inline int lowbit(int x){return x&(-x);}
void add_suf(int lo,int v){
    while(lo<=n)val[lo]+=v,lo+=lowbit(lo);
}
void add_pre(int lo,int v){
    while(lo)val[lo]+=v,lo-=lowbit(lo);
}
int query_pre(int lo){
    --lo;int re=0;
    while(lo)re+=val[lo],lo-=lowbit(lo);
    return re;
}
int query_suf(int lo){
    ++lo;int re=0;
    while(lo<=n)re+=val[lo],lo+=lowbit(lo);
    return re;
}
void clear_suf(int lo){
    while(lo<=n&&val[lo])val[lo]=0,lo+=lowbit(lo);
}
void clear_pre(int lo){
    while(lo&&val[lo])val[lo]=0,lo-=lowbit(lo);
}
struct Query{
    int t,x,y,opt;
    bool operator<(const Query &q)const{
        return x<q.x;
    }
}qs[MAX],tmp[MAX];
bool cmp(const Query &a,const Query &b){
    return a.t<b.t;
}
void addq(int t,int x,int y,int opt){
    qs[++qcnt]=Query{t,x,y,opt};
}
void cdq(int l,int r){
    if(l==r)return;
    int mid=(l+r)/2;
    cdq(l,mid);cdq(mid+1,r);
    int lp=l,rp=mid+1,tp=l;
    while(lp<=mid&&rp<=r){
        if(qs[lp]<qs[rp]){
            add_pre(qs[lp].y,1);
            tmp[tp++]=qs[lp++];
        }
        else{
            if(qs[rp].opt)
                ans[qs[rp].opt]+=query_suf(qs[rp].y);
            tmp[tp++]=qs[rp++];
        }
    }

    while(lp<=mid)tmp[tp++]=qs[lp++];
    while(rp<=r){
        if(qs[rp].opt)ans[qs[rp].opt]+=query_suf(qs[rp].y);
        tmp[tp++]=qs[rp++];
    }
    for(int i=l;i<=r;i++)clear_pre(tmp[i].y);
    for(int i=r;i>=l;i--){
        if(tmp[i].t<=mid)
            add_suf(tmp[i].y,1);
        else if(tmp[i].opt)
            ans[tmp[i].opt]+=query_pre(tmp[i].y);
    }
    for(int i=l;i<=r;i++)qs[i]=tmp[i],clear_suf(tmp[i].y);

}
int main(){
    read(n);read(m);
    for(int u,i=1;i<=n;i++)read(u),lo[u]=i;
    for(int u,i=0;i<m;i++)read(u),id[u]=n-i;
    for(int i=1;i<=n;i++){
        int temt=id[i];if(!temt)temt=++cnt;
        addq(temt,lo[i],i,id[i]?id[i]:0);
    }
    sort(qs+1,qs+1+qcnt,cmp);
    ll tot=0;
    for(int i=1;i<=n-m;i++)
        tmp[i]=qs[i];
    sort(tmp+1,tmp+1+n-m);
    for(int i=1;i<=n-m;i++)
    {
        tot+=query_suf(tmp[i].y);
        add_pre(tmp[i].y,1);
    }
    for(int i=1;i<=n-m;i++)clear_pre(qs[i].y);
    cdq(1,qcnt);
    ans[n-m]=tot;
    for(int i=n-m+1;i<=n;i++)ans[i]+=ans[i-1];
    for(int i=n;i>n-m;i--)printf("%lld\n",ans[i]);
    return 0;
}
/*
5 1
5
4
3
2
1
5

*/
