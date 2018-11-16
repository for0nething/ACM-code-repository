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
const int MAX=(1<<18)+5;
const int MOD=313;
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
//inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

struct node{
    int x,y,tim;
}a[MAX];
struct Query{
    int num,c[5];
}qs[MAX];

int tcnt,tp;
bool ans[MAX];
int fa[MAX],stk1[MAX<<2],stk2[MAX<<2];
int find(int x){
    if(fa[x]!=x){
        int y=fa[x];
        stk1[++tp]=x;stk2[tp]=y;
        fa[x]=find(fa[x]);
    }
    return fa[x];
}
void solve(int l,int r){
    int now=tp;
    if(l==r){
        bool re=1;
        for(int i=1;i<=qs[l].num;i++)
            if(find(a[qs[l].c[i]].x)!=find(a[qs[l].c[i]].y)){re=0;break;}
        ans[l]=re;
        while(tp!=now)fa[stk1[tp]]=stk2[tp],--tp;
        return;
    }
    int mid=(l+r)>>1;
    ++tcnt;
    for(int i=l;i<=mid;i++)
        for(int j=1;j<=qs[i].num;j++)
            a[qs[i].c[j]].tim=tcnt;
    for(int i=mid+1;i<=r;i++)
        for(int j=1;j<=qs[i].num;j++)
            if(a[qs[i].c[j]].tim!=tcnt){
                int f1=find(a[qs[i].c[j]].x),f2=find(a[qs[i].c[j]].y);
                if(f1!=f2){
                    stk1[++tp]=f1;stk2[tp]=fa[f1];
                    fa[f1]=f2;
                }
            }
    solve(l,mid);
    while(tp!=now)fa[stk1[tp]]=stk2[tp],tp--;
    tcnt++;
    for(int i=mid+1;i<=r;i++)
        for(int j=1;j<=qs[i].num;j++)
            a[qs[i].c[j]].tim=tcnt;
    for(int i=l;i<=mid;i++)
        for(int j=1;j<=qs[i].num;j++)
            if(a[qs[i].c[j]].tim!=tcnt){
                int f1=find(a[qs[i].c[j]].x),f2=find(a[qs[i].c[j]].y);
                if(f1!=f2){
                    stk1[++tp]=f1;stk2[tp]=fa[f1];
                    fa[f1]=f2;
                }
            }
    solve(mid+1,r);
}
int main()
{
    int n,m,k;
    read(n);read(m);
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){read(a[i].x);read(a[i].y);a[i].tim=0;}
    read(k);
    tcnt=1,tp=0;
    for(int i=1;i<=k;i++){
        read(qs[i].num);
        for(int j=1;j<=qs[i].num;j++){
            read(qs[i].c[j]);
            a[qs[i].c[j]].tim=tcnt;
        }
    }
    for(int i=1;i<=m;i++)
        if(a[i].tim!=tcnt){
            int f1=find(a[i].x),f2=find(a[i].y);
            if(f1!=f2)fa[f1]=f2;
        }
    solve(1,k);
    for(int i=1;i<=k;i++)
        puts(ans[i]?"Connected":"Disconnected");
    return 0;
}
/*
3  10
1 1
2 0
3 1

3  10
1 1
2 1
3 0
*/
