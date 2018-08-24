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
const int MAX=5e5+10;
const int MOD=998244353;
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
inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,s;
ll t[MAX],f[MAX],dp[MAX],T[MAX],F[MAX];
struct node{
    ll k,x,y,pos,pd;//pd??
    node(ll pos=0):pos(pos){
        k=T[pos];
    }
    void get(){
        x=F[pos];y=dp[pos]-F[n]*T[pos]+F[pos]*T[pos]-s*F[pos];
    }
    bool operator <(const node&rhs)const{
        return k<rhs.k;
    }
}q[MAX],now[MAX],sta[MAX];
bool cmp(const node &lhs,const node &rhs){
    return lhs.x<rhs.x||(lhs.x==rhs.x&&lhs.y<rhs.y);
}
ll dy(const node &a,const node &b){
    return a.y-b.y;
}
ll dx(const node &a,const node &b){
    return a.x-b.x;
}
void solve(int l,int r){
    if(l==r){
        q[l].get();return;
    }
    int mid=(l+r)/2,l1=l,l2=mid+1;
    for(int i=l;i<=r;i++)
        if(q[i].pos<=mid)now[l1++]=q[i];
        else now[l2++]=q[i];
    for(int i=l;i<=r;i++)q[i]=now[i];
    solve(l,mid);
    solve(mid+1,r);
    int top=0;
    for(int i=l;i<=mid;i++){//k is increasing  维护左侧点的下凸包
        while(top>=2&&dy(q[i],sta[top])*dx(sta[top],sta[top-1])<dy(sta[top],sta[top-1])*dx(q[i],sta[top]))--top;
        sta[++top]=q[i];
    }
    int j=1;
    for(int i=mid+1;i<=r;i++){
        while(j<top&&q[i].k*dx(sta[j],sta[j+1])<dy(sta[j],sta[j+1]))++j;
        dp[q[i].pos]=min(dp[q[i].pos],sta[j].y-sta[j].x*q[i].k+F[n]*(T[q[i].pos]+s));
    }

    l1=l,l2=mid+1;
    for(int i=l;i<=r;i++)
        if((cmp(q[l1],q[l2])||(l2>r))&&l1<=mid)now[i]=q[l1++];
        else now[i]=q[l2++];
    for(int i=l;i<=r;i++)q[i]=now[i];
}
int main()
{
    read(n);read(s);
    for(int i=1;i<=n;i++)
        read(t[i]),read(f[i]),dp[i]=INFF;
    for(int i=1;i<=n;i++)T[i]=T[i-1]+t[i],F[i]=F[i-1]+f[i];
    for(int i=0;i<=n;i++)q[i]=node(i);
    sort(q,q+n+1);
    solve(0,n);
    printf("%lld\n",dp[n]);
    return 0;
}
/*
5
3 2 3 5
2500 200 9 0 27
4 2
3 5
2 5
4 1

*/
