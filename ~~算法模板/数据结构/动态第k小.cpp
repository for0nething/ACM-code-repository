/*
    ZOJ 2112
    ¶¯Ì¬µÚkÐ¡
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
const int MAX=6e4+7;
const int M=2500007;
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
struct node
{
    int kind,x,y,z;
}query[MAX];
int ts,n,q,m,tot;
int a[MAX],od[MAX],t[MAX];
int T[MAX],lson[M],rson[M],s[M],bs[MAX];
int use[MAX];
char opt[10];
inline int lowbit(int x)
{
    return x&(-x);
}
int build(int l,int r)
{
    int rt=tot++;
    s[rt]=0;
    if(l!=r){
        int mid=(l+r)/2;
        //原本下一行没有lson\rson的赋值 感觉不对？
        lson[rt]=build(l,mid);rson[rt]=build(mid+1,r);
    }
    return rt;
}
int Insert(int rt,int pos,int val)
{
    int re=tot++,l=0,r=m-1,newrt=re;s[newrt]=s[rt]+val;
    while(l<r)
    {
        int mid=(l+r)/2;
        if(pos<=mid){
            lson[newrt]=tot++;rson[newrt]=rson[rt];
            newrt=lson[newrt];rt=lson[rt];r=mid;
        }
        else{
            lson[newrt]=lson[rt];rson[newrt]=tot++;
            newrt=rson[newrt];rt=rson[rt];l=mid+1;
        }
        s[newrt]=s[rt]+val;
    }
    return re;
}
int sum(int x)
{
    int re=0;
    for(int i=x;i>0;i-=lowbit(i))
    {
        re+=s[lson[use[i]]];
    }
    return re;
}
int Query(int ql,int qr,int k)
{
    int l=0,r=m-1,mid,rtl=T[ql-1],rtr=T[qr];
    for(int i=ql-1;i>0;i-=lowbit(i))use[i]=bs[i];
    for(int i=qr;i>0;i-=lowbit(i))use[i]=bs[i];
    while(l<r)
    {
        int mid=(l+r)/2;
        int tem=sum(qr)-sum(ql-1)+s[lson[rtr]]-s[lson[rtl]];
        if(tem>=k){
            for(int i=ql-1;i>0;i-=lowbit(i))use[i]=lson[use[i]];
            for(int i=qr;i>0;i-=lowbit(i))use[i]=lson[use[i]];
            rtl=lson[rtl];rtr=lson[rtr];
            r=mid;
        }
        else{
            k-=tem;
            for(int i=ql-1;i>0;i-=lowbit(i))use[i]=rson[use[i]];
            for(int i=qr;i>0;i-=lowbit(i))use[i]=rson[use[i]];
            rtl=rson[rtl];rtr=rson[rtr];l=mid+1;
        }
    }
    return l;
}
void upd(int x,int who,int d)
{
    while(x<=n)
    {
        bs[x]=Insert(bs[x],who,d);
        x+=lowbit(x);
    }
}
inline int lo(int x){return lower_bound(t,t+m,x)-t;}
int main()
{
    scanf("%d",&ts);
    while(ts--)
    {
        scanf("%d%d",&n,&q);m=tot=0;
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),t[m++]=a[i];
        for(int i=1;i<=q;i++)
        {
            scanf("%s",opt);
            if(opt[0]=='Q'){
                query[i].kind=1;scanf("%d%d%d",&query[i].x,&query[i].y,&query[i].z);
            }
            else{
                query[i].kind=0;scanf("%d%d",&query[i].x,&query[i].y);t[m++]=query[i].y;
            }
        }
        sort(t,t+m);m=unique(t,t+m)-t;
        T[0]=build(0,m-1);
        for(int i=1;i<=n;i++){
            T[i]=Insert(T[i-1],lo(a[i]),1);
        }
        for(int i=1;i<=n;i++)bs[i]=T[0];
        for(int i=1;i<=q;i++)
        {
            if(query[i].kind)printf("%d\n",t[Query(query[i].x,query[i].y,query[i].z)]);
            else{
                upd(query[i].x,lo(a[query[i].x]),-1);
                upd(query[i].x,lo(query[i].y),1);
                a[query[i].x]=query[i].y;
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
