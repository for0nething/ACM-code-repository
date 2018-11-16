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
const int MOD=1e9+7;
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

struct kd{
    int ls,rs,min[2],max[2],v[2];
    ll sum,s;
    kd(int a,int b,int c){ls=rs=0;min[0]=max[0]=v[0]=a;min[1]=max[1]=v[1]=b;s=sum=c;}
    kd(){}
}t[MAX];
int n,m,D,root,a,b,c;
ll A,B,C;
bool cmp(kd a,kd b){
    return (a.v[D]==b.v[D])?(a.v[D^1]<b.v[D^1]):(a.v[D]<b.v[D]);
}
void pushup(int x,int y){
    for(int i=0;i<=1;i++){
        t[x].max[i]=max(t[x].max[i],t[y].max[i]);
        t[x].min[i]=min(t[x].min[i],t[y].min[i]);
    }
    t[x].sum+=t[y].sum;
}
int build(int l,int r,int d){
    if(l>r)return 0;
    int mid=(l+r)>>1;
    D=d;
    nth_element(t+l,t+mid,t+r,cmp);
    t[mid].ls=build(l,mid-1,d^1);t[mid].rs=build(mid+1,r,d^1);
    if(t[mid].ls)pushup(mid,t[mid].ls);
    if(t[mid].rs)pushup(mid,t[mid].rs);
    return mid;
}
int check(int x){
    int re=0;
    re+=(A*t[x].min[0]+B*t[x].min[1]<C);
    re+=(A*t[x].min[0]+B*t[x].max[1]<C);
    re+=(A*t[x].max[0]+B*t[x].min[1]<C);
    re+=(A*t[x].max[0]+B*t[x].max[1]<C);
    return re;
}
ll query(int x){
    if(!x||!check(x))return 0;
    if(check(x)==4)return t[x].sum;
    ll re=0;
    if(A*t[x].v[0]+B*t[x].v[1]<C)re+=t[x].s;
    re+=query(t[x].ls)+query(t[x].rs);
    return re;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a,&b,&c);
        t[i]=kd(a,b,c);
    }
    root=build(1,n,0);
    for(int i=1;i<=m;i++){
        scanf("%lld%lld%lld",&A,&B,&C);
        printf("%lld\n",query(root));
    }
    return 0;
}
/*
4 4
*/
