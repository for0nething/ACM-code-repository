/*
    HDU 4348
*/

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
//#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp

//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;
//const double INF=1e20;
const int INF=0x3f3f3f3f;
//const int INF= 0x7fffffff;
//const ll INF=0x3f3f3f3f3f3f3f3fll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=1e5+7;
//const int M=2500007;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const int MOD=1e9+7;
//const ull MOD=1e7+7;
//const ll MOD=998244353;
//const long double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-6;
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
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
//const long double eps=-1.0;
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);
void open()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
}
int n,m,tot,TM;
int T[MAX<<2],lson[MAX*40],rson[MAX*40];
ll lazy[MAX*40],sum[MAX*40];
char opt[10];
int build(int l,int r)
{
    int re=tot++;lazy[re]=sum[re]=0;
    if(l==r){
        scanf("%lld",&sum[re]);return re;
    }
    int mid=(l+r)/2;
    lson[re]=build(l,mid);rson[re]=build(mid+1,r);
    sum[re]=sum[lson[re]]+sum[rson[re]];
    return re;
}
void pushup(int rt,int l,int r)
{
    int mid=(l+r)/2;
    sum[rt]=sum[lson[rt]]+sum[rson[rt]]+(1LL*mid-l+1)*lazy[lson[rt]]+(1LL*r-mid)*lazy[rson[rt]];
    return ;
}
int Insert(int rt,int il,int ir,int l,int r,ll d)
{
    int ntr=tot++;lazy[ntr]=lazy[rt];
    if(l>=il&&r<=ir){
        lazy[ntr]=lazy[rt]+d;sum[ntr]=sum[rt];lson[ntr]=lson[rt];rson[ntr]=rson[rt];return ntr;
    }
    int mid=(l+r)/2;
    if(il<=mid)
        lson[ntr]=Insert(lson[rt],il,ir,l,mid,d);
    else lson[ntr]=lson[rt];
    if(ir>mid)
        rson[ntr]=Insert(rson[rt],il,ir,mid+1,r,d);
    else rson[ntr]=rson[rt];
    pushup(ntr,l,r);
    return ntr;
}
ll query(int rt,int ql,int qr,int l,int r,ll add)
{
    if(l>=ql&&r<=qr){
        return (add+lazy[rt])*(r-l+1LL)+sum[rt];
    }
    int mid=(l+r)/2;
    ll re=0;
    if(ql<=mid)re+=query(lson[rt],ql,qr,l,mid,add+lazy[rt]);
    if(qr>mid)re+=query(rson[rt],ql,qr,mid+1,r,add+lazy[rt]);
    return re;
}
bool st;
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        if(st)printf("\n");st=1;
        tot=TM=0;
        T[0]=build(1,n);
        while(m--){
            scanf("%s",opt);
            if(opt[0]=='C'){
                int l,r;ll d;scanf("%d%d%lld",&l,&r,&d);T[TM+1]=Insert(T[TM],l,r,1,n,d);++TM;
            }
            else if(opt[0]=='Q'){
                int l,r;scanf("%d%d",&l,&r);printf("%lld\n",query(T[TM],l,r,1,n,0));
            }
            else if(opt[0]=='H'){
                int l,r,t;scanf("%d%d%d",&l,&r,&t);printf("%lld\n",query(T[t],l,r,1,n,0));
            }
            else{
                int t;scanf("%d",&t);TM=t;tot=T[TM+1];
            }

        }
    }
    return 0;
}
/*
7 5
1 1 3 2 3 4 3
1 3
1 4
3 7
1 7
6 6

*/
