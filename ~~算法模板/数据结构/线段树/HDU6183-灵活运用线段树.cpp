/*
    充分节省建多棵线段树的冗余空间
*/
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
const int MAX=1e6+10;
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
int rt[100],l[MAX],r[MAX],v[MAX];
int tot,y1,y2,X,opt;
bool flag;
void ins(int &t,int L,int R,int y,int x)
{
    if(!t){
        t=++tot;
        v[t]=x;
    }
    if(v[t]>x)v[t]=x;
    if(L==R)return;
    int mid=(L+R)/2;
    if(y<=mid)ins(l[t],L,mid,y,x);
    else ins(r[t],mid+1,R,y,x);
}
void ask(int t,int L,int R)
{
    if(flag||!t)return;
    if(y1<=L&&R<=y2){
        if(v[t]<=X)flag=1;
        return;
    }
    int mid=(L+R)/2;
    if(y1<=mid)ask(l[t],L,mid);
    if(y2>mid)ask(r[t],mid+1,R);
}
int main()
{
    while(~scanf("%d",&opt))
    {
        if(opt==3)return 0;
        else if(opt==0){
            for(int i=0;i<=50;i++)rt[i]=0;
            for(int i=1;i<=tot;i++)l[i]=r[i]=0;
            tot=0;
        }
        else if(opt==1){
            int x,y,v;
            read(x);read(y);read(v);ins(rt[v],1,1000000,y,x);
        }
        else if(opt==2){
            read(X);read(y1);read(y2);
            int ans=0;
            for(int i=0;i<=50;i++){
                flag=0;
                ask(rt[i],1,1000000);
                if(flag)++ans;
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
/*
1 3 1 3
2 3 2 5
*/
