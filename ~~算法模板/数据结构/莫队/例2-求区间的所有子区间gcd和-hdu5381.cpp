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
const int MAX=1e4+10;
//const int M=(1<<20)+5;
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
    while (b){
        if (b&1LL) ret=ret*a%M;
        b>>=1LL;
        a=a*a%M;
    }
    return ret;
}

ll mul(ll a , ll b,ll Q){
    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
}

//const long double eps=-1.0;
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);
void open()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
}
//#define debug
int rgcd[MAX][15],a[MAX];
vector<pii>vr[MAX],vl[MAX];
int t,n,m;
ll an[MAX];
struct node
{
    int al,ar,bel,id;
    bool operator <(const node &t)const
    {
        if(bel==t.bel)return ar<t.ar;
        else return bel<t.bel;
    }
}qs[MAX];
void init()
{
    for(int i=1;i<=n;i++)rgcd[i][0]=a[i];
    for(int i=1;(1<<i)<=n;i++)
        for(int j=1;j<=n;j++)
            if(j+(1<<i)-1<=n)rgcd[j][i]=gcd(rgcd[j][i-1],rgcd[j+(1<<i-1)][i-1]);
}
int query(int l,int r)
{
    int k=(int)log2(r-l+1);
    return gcd(rgcd[l][k],rgcd[r-(1<<k)+1][k]);
}
//s作为右端点 搜索向左gcd为t的最远位置
int Rsearch(int s,int l,int r,int t){
    int re,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(query(mid,s)==t){
            re=mid;r=mid-1;
        }
        else l=mid+1;
    }
    return re;
}
int Lsearch(int s,int l,int r,int t){
    int re,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(query(s,mid)==t){
            re=mid;l=mid+1;
        }
        else r=mid-1;
    }
    return re;
}
//计算s为右端点的贡献 t为当前区间的左端点
ll rcal(int s,int t)
{
    ll re=0;
    int lo=s;
    for(int i=0;i<vr[s].size();i++){
        re+=1LL*(lo-max(t,vr[s][i].second)+1)*(vr[s][i].first);
        lo=vr[s][i].second-1;
        if(lo<t)break;
    }
    return re;
}
ll lcal(int s,int t)
{
    ll re=0;
    int lo=s;
    for(int i=0;i<vl[s].size();i++){
        re+=1LL*(min(t,vl[s][i].second)-lo+1)*vl[s][i].first;
        lo=vl[s][i].second+1;
        if(lo>t)break;
    }
    return re;
}
int main()
{
    read(t);
    while(t--){
        read(n);int siz=sqrt(n);
        for(int i=1;i<=n;i++)read(a[i]);
        init();
        for(int i=1;i<=n;i++){
            int r=i;
            vl[i].clear();
            while(r<=n){
                int who=query(i,r);
                r=Lsearch(i,r,n,who);
                vl[i].pb(mp(who,r));
                ++r;
            }
        }
        for(int i=n;i>=1;i--)
        {
            int l=i;
            vr[i].clear();
            while(l>=1){
                int who=query(l,i);
                l=Rsearch(i,1,l,who);
                vr[i].pb(mp(who,l));--l;
            }
        }
        read(m);ll sum=0;
        for(int i=0;i<m;i++){
            read(qs[i].al);read(qs[i].ar);qs[i].id=i;
            qs[i].bel=(qs[i].al-1)/siz;
        }
        sort(qs,qs+m);
        int lol=1,lor=0;
        for(int i=0;i<m;i++){
            while(lol>qs[i].al)--lol,sum+=lcal(lol,lor);
            while(lor<qs[i].ar)++lor,sum+=rcal(lor,lol);
            while(lol<qs[i].al)sum-=lcal(lol,lor),++lol;
            while(lor>qs[i].ar)sum-=rcal(lor,lol),--lor;
            an[qs[i].id]=sum;
        }
        for(int i=0;i<m;i++)
            printf("%lld\n",an[i]);
    }
    return 0;
}
/*
1 3 1 3
2 3 2 5
*/
