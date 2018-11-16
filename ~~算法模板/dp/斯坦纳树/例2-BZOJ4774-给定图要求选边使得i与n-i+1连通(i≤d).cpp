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
const int MAX=2e4+5;
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

struct node{
    int to,nxt,weight;
    node(){};
    node(int _to,int _nxt,int _weight):to(_to),nxt(_nxt),weight(_weight){};
}edg[MAX<<1];
int n,m,d,ecnt,tot;
int h[MAX],dp[257][MAX],tp[20];
void add_edge(int u,int v,int w){
    edg[++ecnt]=node(v,h[u],w);
    h[u]=ecnt;
}
struct qs{
    int lo,val;
    qs(){};
    qs(int _lo,int _val):lo(_lo),val(_val){}
    bool operator<(const qs& z)const{return val>z.val;}
};
priority_queue<qs>que;
int main(){
    read(n);read(m);read(d);
    for(int u,v,w,i=1;i<=m;i++){
        read(u);read(v);read(w);
        add_edge(u,v,w);add_edge(v,u,w);
    }
    tot=(1<<d);
    memset(dp,0x3f,sizeof(dp));
    memset(tp,0x3f,sizeof(tp));
    for(int i=1;i<=d;i++)
        dp[1<<i-1][i]=dp[1<<i-1+d][n+1-i]=0;
    for(int i=1;i<tot*tot;i++){
        int *tem=dp[i];
        for(int j=(i-1)&i;j>(i^j);j=(j-1)&i){//中间的条件永远取不到等号
            for(int k=1,*l1=dp[j],*l2=dp[i^j];k<=n;++k)
                tem[k]=min(tem[k],l1[k]+l2[k]);
        }
        for(int k=1;k<=n;k++)
            if(tem[k]<INF)que.push(qs(k,tem[k]));
        while(!que.empty()){
            qs now=que.top();que.pop();
            int pos=now.lo;
            if(now.val>tem[pos])continue;
            for(int j=h[pos];j;j=edg[j].nxt){
                int to=edg[j].to,td=tem[pos]+edg[j].weight;
                if(tem[to]>td)tem[to]=td,que.push(qs(to,tem[to]));
            }
        }
        if((i&(tot-1))==(i>>d)){
            int lin=INF;
            for(int j=1;j<=n;j++)lin=min(lin,tem[j]);
            tp[i>>d]=lin;
        }
    }
    for(int i=1;i<tot;i++)
        for(int j=(i-1)&i;j>(i^j);j=(j-1)&i)
            tp[i]=min(tp[i],tp[j]+tp[i^j]);
    printf("%d\n",tp[tot-1]!=INF?tp[tot-1]:-1);
    return 0;
}
/*
4 4
*/
