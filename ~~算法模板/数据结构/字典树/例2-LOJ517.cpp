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
//#include <utility>
//#include <complex>
#include <assert.h>
//#include <limits.h>
//#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;

#define rank rankk
#define mp make_pair
#define pb push_back
#define eb push_back
//#define eb emplace_back
#define xo(a,b) ((b)&1?(a):0)
#define fi first
#define se second
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;
typedef pair<double,int> pdi;
typedef long double ld;
const int INF=0x3f3f3f3f;
const ll INFF=4e11;
//const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=3e6+5;
const ll MOD=998244353;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
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
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

const int MAXN=2e5+5;
int n,m,k,sort_val,tot_val;
int tcnt,rt,pcnt;
int opt;
int cnt[MAX][31],pre[MAXN][31],sum[31],bval[MAXN];
vector<int>pts;
struct Trie{
    int ls,rs,ncnt;
    Trie(int _ls=0,int _rs=0,int _ncnt=0):ls(_ls),rs(_rs),ncnt(_ncnt){}
}t[MAX];
inline void insert(int dep,int val,int& lo){
    if(!lo){
        lo=++tcnt;t[lo]=Trie(0,0,0);
    }
    ++t[lo].ncnt;
    for(register int i=0;i<31;i++)
        if(val&(1<<i))++cnt[lo][i];
    if(dep==-1)
        return;
    if(val&(1<<dep))
        insert(dep-1,val,t[lo].rs);
    else insert(dep-1,val,t[lo].ls);
}
inline ll query_pre(int x){
    ll re=0;
    for(register int i=0;i<31;i++){
        if(tot_val&(1<<i))re+=(1LL*(x-pre[x][i])<<(1LL*i));
        else re+=1LL*pre[x][i]<<(1LL*i);
    }
    return re;
}
inline ll query_pts(){
    for(int u:pts)
        for(register int i=0;i<31;i++)sum[i]+=cnt[u][i];
    ll re=0;
    for(register int i=0;i<31;i++){
        if(tot_val&(1<<i))re+=(1LL*(k-sum[i]))<<i;
        else re+=1LL*sum[i]<<i;
    }
    return re;
}
void dfs(int dep,int lo,int qcnt){
    if(qcnt<=0)return ;
    if(qcnt==t[lo].ncnt){
        pts.pb(lo);return;
    }
    if(dep==-1){
        for(int i=0;i<31;i++){
            sum[i]+=qcnt*(cnt[lo][i]?1:0);
        }
        return;
    }
    if(sort_val&(1<<dep))swap(t[lo].ls,t[lo].rs);
    if(t[lo].ls){
        int ls=t[lo].ls;
        if(t[ls].ncnt<qcnt){pts.eb(ls);dfs(dep-1,t[lo].rs,qcnt-t[ls].ncnt);}
        else dfs(dep-1,t[lo].ls,qcnt);
    }
    else dfs(dep-1,t[lo].rs,qcnt);
    if(sort_val&(1<<dep))swap(t[lo].ls,t[lo].rs);
}
inline ll get_pre(int x){
    memset(sum,0,sizeof(sum));
    if(!x)return 0LL;
    k=x;
    pts.clear();
    ll re=0;
    if(x>t[rt].ncnt){
        if(rt)
        pts.pb(rt);
        k=t[rt].ncnt;
        re+=query_pre(x-t[rt].ncnt);
    }
    else dfs(30,rt,x);
    re+=query_pts();
    return re;
}
int main(){
    read(n);
    for(int u,j=1;j<=n;j++){
        read(u);
        bval[++pcnt]=u;
        for(register int i=0;i<31;i++)
            pre[pcnt][i]=pre[pcnt-1][i]+((u>>i)&1);
    }
    read(m);
    while(m--){
        read(opt);
        if(opt==1){
            int u;read(u);
            bval[++pcnt]=(u^=tot_val);
            for(register int i=0;i<31;i++)
                pre[pcnt][i]=pre[pcnt-1][i]+((u>>i)&1);
        }
        else if(opt==2){
            int u,v;read(v);read(u);
            printf("%lld\n",get_pre(u)-get_pre(v-1));
        }
        else if(opt==3){
            int u;read(u);tot_val^=u;
        }
        else if(opt==4){
            sort_val=tot_val;
            while(pcnt)
                insert(30,bval[pcnt--],rt);
        }
    }
    return 0;
}
/*

10 6 9 6
4 6 3 5 7 4
*/
