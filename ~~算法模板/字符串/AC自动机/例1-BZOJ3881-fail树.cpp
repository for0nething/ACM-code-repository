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
#define fi first
#define se second
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
const int MAX=2e6+5;
const int MOD=1e9+7;
//int MOD;
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
//inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
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

const int SIGMA_SIZ=26;
const int MAXNODE=2e6+5;
int pos[MAX];
struct AhoCorasickAutomata{
    int ch[MAXNODE][SIGMA_SIZ];
    int f[MAXNODE];
    int num=0;
    void init(){
        num=0;
        memset(ch[0],-1,sizeof(ch[0]));
    }
    void insert(char *s,int i){
        int n=strlen(s),u=0;
        for(int i=0;i<n;i++){
            int to=s[i]-'a';
            if(ch[u][to]==-1){
                ch[u][to]=++num;
                memset(ch[num],-1,sizeof(ch[num]));
            }
            u=ch[u][to];
        }
        pos[i]=u;
    }
    void getFail(){
        queue<int>que;
        for(int i=0;i<SIGMA_SIZ;i++){
            if(ch[0][i]==-1)ch[0][i]=0;
            else que.push(ch[0][i]),f[ch[0][i]]=0;
        }
        while(!que.empty()){
            int r=que.front();que.pop();
            for(int c=0;c<SIGMA_SIZ;c++){
                int u=ch[r][c];
                if(u==-1){
                    ch[r][c]=ch[f[r]][c];continue;
                }
                que.push(u);
                f[u]=ch[f[r]][c];
            }
        }
    }
}ac;
int ecnt,tcnt;
int h[MAX],nxt[MAX],to[MAX],fa[MAX][20],LOG[MAX],st[MAX],en[MAX],dep[MAX];
int va[MAX];
void add_edge(int u,int v){
    to[++ecnt]=v;nxt[ecnt]=h[u];h[u]=ecnt;
}
void dfs(int x){
    st[x]=++tcnt;
    for(int i=1;i<=LOG[dep[x]];i++)fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int i=h[x];i;i=nxt[i]){
        int ts=to[i];
        fa[ts][0]=x;dep[ts]=dep[x]+1;dfs(ts);
    }
    en[x]=tcnt;
}
inline int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    int dis=dep[u]-dep[v];
    for(int i=LOG[dis];i>=0;i--)
        if(dis&(1<<i))u=fa[u][i];
    if(u==v)return u;
    for(int i=LOG[dep[u]];i>=0;i--)
        if(dep[u]>=(1<<i)&&fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
int n,lim,m,opt;
char a[MAX];
inline void add(int x,int val){
    for(int i=x;i<=lim;i+=i&(-i))
    {
        va[i]+=val;
    }
}
inline int query(int x){
    int re=0;
    for(int i=x;i;i-=i&(-i))re+=va[i];
    return re;
}
bool cmp(int x,int y){
    return st[x]<st[y];
}
int tem[MAX],cnt;
int main(){
    read(n);
    ac.init();
    for(int i=1;i<=n;i++){
        scanf("%s",a);
        ac.insert(a,i);
    }
    ac.getFail();
    for(int i=1;i<=ac.num;i++){
        add_edge(ac.f[i],i);LOG[i]=LOG[i>>1]+1;
    }
    read(m);
    dfs(0);
    lim=tcnt;
    while(m--){
        read(opt);
        if(opt==1){
            scanf("%s",a);int lo=0;
            int len=strlen(a);cnt=0;
            for(int i=0;i<len;i++){
                lo=ac.ch[lo][a[i]-'a'];
                tem[cnt++]=lo;
            }
            sort(tem,tem+cnt,cmp);
            for(int i=0;i<cnt;i++){
                int who=tem[i];
                add(st[who],1);
            }

            for(int i=0;i<cnt-1;i++){
                int u=tem[i],v=tem[i+1];
                int LCA=lca(u,v);
                add(st[LCA],-1);
            }
        }
        else{

            int id;read(id);
            int lo=pos[id];
            printf("%d\n",query(en[lo])-query(st[lo]-1));
        }
    }
    return 0;
}

/*
10000000000

9
9999999997
*/
