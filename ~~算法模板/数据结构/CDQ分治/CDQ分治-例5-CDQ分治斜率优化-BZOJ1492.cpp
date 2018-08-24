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
const int MAX=1e6+10;
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
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline int addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;}
inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

const int N=1e5+10;
const double inf=1e20;
//const double eps=1e-8;
struct Pt{
    double x,y,a,b,k,r;
    int id;
    bool operator <(const Pt &rhs)const{
        return k>rhs.k;
    }
}p[N],t[N];
double f[N];
int n,top,st[N];
double slop(int a,int b){
    if(!b)return -inf;
    if(fabs(p[a].x-p[b].x)<eps)return inf;
    return (p[b].y-p[a].y)/(p[b].x-p[a].x);
}
void solve(int l,int r){
    if(l==r){
        f[l]=max(f[l],f[l-1]);
        p[l].y=f[l]/(p[l].a*p[l].r+p[l].b);
        p[l].x=p[l].y*p[l].r;
        return ;
    }
    int mid=(l+r)>>1,j=1,l1=l,l2=mid+1;
    for(int i=l;i<=r;i++){
        if(p[i].id<=mid)t[l1++]=p[i];
        else t[l2++]=p[i];
    }
    for(int i=l;i<=r;i++)p[i]=t[i];
    solve(l,mid);
    top=0;
    for(int i=l;i<=mid;i++){
        while(top>1&&slop(st[top-1],st[top])<slop(st[top-1],i)+eps)--top;
        st[++top]=i;
    }
    st[++top]=0;
    for(int i=mid+1;i<=r;i++){
        while(j<top&&slop(st[j],st[j+1])+eps>p[i].k)++j;
        f[p[i].id]=max(f[p[i].id],p[st[j]].x*p[i].a+p[st[j]].y*p[i].b);
    }
    solve(mid+1,r);
    l1=l,l2=mid+1;
    for(int i=l;i<=r;i++){
        if((((p[l1].x<p[l2].x)||(fabs(p[l1].x-p[l2].x)<eps&&p[l1].y<p[l2].y ))||l2>r )&&l1<=mid)
            t[i]=p[l1++];
        else t[i]=p[l2++];
    }
    for(int i=l;i<=r;i++)p[i]=t[i];
}
int main()
{
    scanf("%d%lf",&n,&f[0]);
    for(int i=1;i<=n;i++){
        scanf("%lf%lf%lf",&p[i].a,&p[i].b,&p[i].r);
        p[i].k=-p[i].a/p[i].b;p[i].id=i;
    }
    sort(p+1,p+n+1);
    solve(1,n);
    printf("%.3f",f[n]);
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
