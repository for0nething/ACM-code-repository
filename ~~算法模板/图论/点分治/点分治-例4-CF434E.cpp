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
//const int MOD=1e9+7;
int MOD;
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
namespace{
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
//inline int mul(int x,int y){return 1LL*x*y%MOD;}
inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void muli(int &x,int y){x=1LL*x*y%MOD;}
inline int sub(int x,int y){int res=x-y;if(res<0)res+=MOD;return res;}
inline void subi(int &x,int y){x-=y;if(x<0)x+=MOD;}
inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,y,k,x,nk,ecnt,rt,lim,tot;
int mi[MAX],inv[MAX],siz[MAX],val[MAX],head[MAX],nxt[MAX],gto[MAX];
int in0[MAX],in1[MAX],out0[MAX],out1[MAX];
bool vis[MAX];
pii downs[MAX],ups[MAX];
void addedge(int u,int v){
    nxt[ecnt]=head[u];gto[ecnt]=v;head[u]=ecnt++;
}
//找重心
void findrt(int now,int fa){
    siz[now]=1;
    int tem=0;
    for(int i=head[now];~i;i=nxt[i]){
        int to=gto[i];
        if(to==fa||vis[to])continue;
        findrt(to,now);
        tem=max(tem,siz[to]);
        siz[now]+=siz[to];
    }
    tem=max(tem,tot-siz[now]);
    if(tem<lim){
        lim=tem;rt=now;
    }
}
void addp(int now,int fa,int dep,int down,int up){
    up=add(val[now],mul(up,k));
    addi(down,mul(mi[dep-1],val[now]));
    downs[tot]=mp(down,now);ups[tot++]=mp(mul(sub(x,up),inv[dep+1]),now);
    for(int i=head[now];~i;i=nxt[i]){
        int to=gto[i];
        if(!vis[to]&&to!=fa)addp(to,now,dep+1,down,up);
    }
}
//计算此时以now为根的树的值（flag为1加 为-1减）减的时候初始把原本更大一层的树的根放到down中
//因为计算较大一层时，在计算的down和up都在其某一子树时会出错 要减去
void calc(int now,int flag,int dep,int down,int up){
    tot=0;
    up=add(val[now],mul(up,k));
    if(dep)addi(down,mul(mi[dep-1],val[now]));
    downs[tot]=mp(down,now);ups[tot++]=mp(mul(sub(x,up),inv[dep+1]),now);
    for(int i=head[now];~i;i=nxt[i]){
        int to=gto[i];
        if(!vis[to])addp(to,now,dep+1,down,up);
    }
    sort(downs,downs+tot);sort(ups,ups+tot);
    for(int cnt=0,j=0,i=0;i<tot;i++){
        if(i&&downs[i].first!=downs[i-1].first)cnt=0;
        for(;j<tot&&ups[j].first<=downs[i].first;j++){
            if(ups[j].first==downs[i].first)++cnt;
        }
        in1[downs[i].second]+=cnt*flag;
    }
    for(int cnt=0,j=0,i=0;i<tot;i++){
        if(i&&ups[i].first!=ups[i-1].first)cnt=0;
        for(;j<tot&&downs[j].first<=ups[i].first;j++){
            if(downs[j].first==ups[i].first)++cnt;
        }
        out1[ups[i].second]+=cnt*flag;
    }

}
void dfs(int now){
    vis[now]=1;
    calc(now,1,0,0,0);
    for(int i=head[now];~i;i=nxt[i]){
        int to=gto[i];
        if(!vis[to]){
            calc(to,-1,1,0,val[now]);
            lim=INF;tot=siz[to];
            findrt(to,now);
            dfs(rt);
        }
    }
}
int main(){
    read(n);read(MOD);read(k);read(x);
    mi[0]=inv[0]=1;nk=powMM(k,MOD-2,MOD);
    for(int i=1;i<=n;i++)mi[i]=mul(mi[i-1],k),inv[i]=mul(inv[i-1],nk);
    for(int i=1;i<=n;i++)read(val[i]);
    memset(head,-1,sizeof(head));
    for(int u,v,i=1;i<n;i++){
        read(u);read(v);
        addedge(u,v);addedge(v,u);
    }
    lim=INF;
    tot=n;findrt(1,0);
    dfs(rt);
    ll ans=1LL*n*n*n;
    ll sum=0;
    for(int i=1;i<=n;i++){
        in0[i]=n-in1[i];out0[i]=n-out1[i];
        sum+=(2LL*in0[i]*in1[i]+2LL*out0[i]*out1[i]+1LL*in0[i]*out1[i]+1LL*in1[i]*out0[i]);
    }
    ans-=sum/2LL;
    printf("%I64d\n",ans);
    return 0;
}

/*
1
30
3
6
##.#..
7
.#.#.#.
5
##.##
*/
