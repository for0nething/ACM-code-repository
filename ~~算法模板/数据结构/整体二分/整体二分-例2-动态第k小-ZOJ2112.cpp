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
const int MAX=3e5+10;
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

int n,m,ecnt;
char op[20];
int ans[MAX],ar[MAX];
inline int lowbit(int x){return x&(-x);}
void adds(int lo,int v){
    while(lo<=n)ar[lo]+=v,lo+=lowbit(lo);
}
int sum(int lo){
    int re=0;
    while(lo)re+=ar[lo],lo-=lowbit(lo);
    return re;
}
//void clear(int lo){
//    while(lo<=n&&ar[lo])ar[lo]=0,lo+=lowbit(lo);
//}
struct Query{
    int x,y,k,id,opt;
}qs[MAX],ql[MAX],qr[MAX];
inline void addq(int x,int y,int k,int id,int opt){
    qs[++ecnt]=Query{x,y,k,id,opt};
}
void solve(int sl,int sr,int l,int r){
    if(sl>sr)return;
    if(l==r){
        for(int i=sl;i<=sr;i++)if(qs[i].opt)ans[qs[i].id]=l;
        return;
    }
    int mid=(l+r)>>1;
    int pl=0,pr=0;
    for(int i=sl;i<=sr;i++){
        if(!qs[i].opt){
            if(qs[i].x<=mid)adds(qs[i].id,qs[i].y),ql[pl++]=qs[i];
            else qr[pr++]=qs[i];
        }
        else{
            int cnt=sum(qs[i].y)-sum(qs[i].x-1);
            if(cnt>=qs[i].k)ql[pl++]=qs[i];
            else qs[i].k-=cnt,qr[pr++]=qs[i];
        }
    }
    for(int i=0;i<pl;i++)if(!ql[i].opt)adds(ql[i].id,-ql[i].y);
    for(int i=0;i<pl;i++)qs[sl+i]=ql[i];
    for(int i=0;i<pr;i++)qs[sl+pl+i]=qr[i];
    solve(sl,sl+pl-1,l,mid);solve(sl+pl,sr,mid+1,r);
}
int a[MAX];
int t,aidx;
int main(){
    read(t);
    while(t--)
    {
        ecnt=aidx=0;
        read(n);read(m);
        for(int i=1;i<=n;i++){
            read(a[i]);addq(a[i],1,-1,i,0);
        }
        for(int l,r,k,i=1;i<=m;i++){
            scanf("%s",op);
            if(op[0]=='Q')
            {
                read(l);read(r);read(k);
                addq(l,r,k,++aidx,1);
            }
            else{
                read(l);read(r);
                addq(a[l],-1,-1,l,0);
                a[l]=r;
                addq(a[l],1,-1,l,0);
            }
        }
        solve(1,ecnt,0,INF);
        for(int i=1;i<=aidx;i++)
            printf("%d\n",ans[i]);
    }
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
