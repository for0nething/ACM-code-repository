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
const int MAX=1e6+5;
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

namespace Maxflow{
    typedef int type;
    const int INF=0x3f3f3f3f;
    const int maxn=4e4+5;
    struct node{
        int to;type cap;int nxt,id;
        node(){}
        node(int _to,type _cap,int _nxt=0,int _id=0):to(_to),cap(_cap),nxt(_nxt),id(_id){}
    }edg[maxn*50];
    int head[maxn],tot;
    void add_edge(int from,int to,type cap,int _id=0,type rcap=0){
        edg[tot]=node(to,cap,head[from],_id);
        head[from]=tot++;
        edg[tot]=node(from,rcap,head[to]);head[to]=tot++;
    }
    int dep[maxn],cur[maxn];
    bool bfs(int s,int t,int n){
        static int Q[maxn],ST,ED;
        memset(dep+1,0,sizeof(int)*n);
        ST=0;ED=-1;
        Q[++ED]=s;dep[s]=1;
        while(ST<=ED){
            int u=Q[ST++];
            for(int i=head[u];~i;i=edg[i].nxt){
                int to=edg[i].to;
                if(!dep[to]&&edg[i].cap){
                    Q[++ED]=to;dep[to]=dep[u]+1;
                }
            }
        }
        return dep[t]!=0;
    }
    type dfs(int x,const int &t,type flow=INF){
        if(x==t||flow==0)return flow;
        type ret=0;
        for(int i=cur[x];~i;i=edg[i].nxt){
            int to=edg[i].to;
            if(dep[x]+1==dep[to]&&edg[i].cap){
                type f=dfs(to,t,min(flow,edg[i].cap));
                edg[i].cap-=f;edg[i^1].cap+=f;
                ret+=f;flow-=f;cur[x]=i;
                if(flow==0)break;
            }
        }
        if(!ret)dep[x]=0;
        return ret;
    }
    type maxflow(int s,int t,int n){
        type ret=0;
        while(bfs(s,t,n)){
            type f;
            memcpy(cur+1,head+1,n*sizeof(int));
            while((f=dfs(s,t))>0)ret+=f;
        }
        return ret;
    }
    void init(int n){
        memset(head+1,-1,sizeof(int)*n);tot=0;
    }
}

int ans[404][24],a[404],low[404][24],up[404][24],deg[404];
int n,m,t,k;
inline void op(int x,int y,char opt,int z){
    if(opt=='>')
        low[x][y]=std::max(low[x][y],z+1);
    else if (opt=='<')
        up[x][y]=std::min(up[x][y],z-1);
    else{
        low[x][y]=max(low[x][y],z);
        up[x][y]=min(up[x][y],z);
    }
}
char opt;
int main(){
    read(t);
    while(t--){
        read(n);read(m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)low[i][j]=0,up[i][j]=INF;
        for(int i=1;i<=n+m+2;i++)deg[i]=0;
        for(int i=1;i<=n+m;i++)read(a[i]);
        read(k);
        while(k--){
            int x,y,z;
            read(x);read(y);
            while(opt=getchar(),opt!='='&&opt!='<'&&opt!='>');
            read(z);
            if(!x&&!y)
                for(int i=1;i<=n;i++)
                    for(int j=1;j<=m;j++)op(i,j,opt,z);
            else if(!x)
                for(int i=1;i<=n;i++)op(i,y,opt,z);
            else if(!y)
                for(int i=1;i<=m;i++)op(x,i,opt,z);
            else op(x,y,opt,z);
        }
        bool an=1;
        for(int i=1;i<=n&&an;i++)
            for(int j=1;j<=m&&an;j++)
                if(low[i][j]>up[i][j])an=0;
        if(!an){
            puts("IMPOSSIBLE");
            if(t)puts("");
            continue;
        }
        int s=n+m+1,t=n+m+2;
        int ss=t+1,tt=ss+1;
        Maxflow::init(tt);
        Maxflow::add_edge(t,s,INF);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                int l=low[i][j],r=up[i][j];
                ans[i][j]=l;
                Maxflow::add_edge(i,j+n,r-l,i*400+j);
                deg[j+n]+=l;deg[i]-=l;
            }
        for(int i=1;i<=n;i++)deg[i]+=a[i],deg[s]-=a[i];
        for(int i=n+1;i<=n+m;i++)deg[i]-=a[i],deg[t]+=a[i];
        int sum_in=0,sum_out=0;
        for(int i=1;i<=t;i++){
            if(deg[i]>0){
                sum_in+=deg[i];Maxflow::add_edge(ss,i,deg[i]);
            }
            else if(deg[i]<0){
                sum_out-=deg[i];Maxflow::add_edge(i,tt,-deg[i]);
            }
        }
        if(sum_in!=sum_out||Maxflow::maxflow(ss,tt,tt)!=sum_in)
            puts("IMPOSSIBLE");
        else{
            for(int i=0;i<Maxflow::tot;i+=2){
                int id=Maxflow::edg[i].id;
                if(id){
                    int x=id/400,y=id%400;
                    ans[x][y]+=Maxflow::edg[i^1].cap;
                }
            }
            for(int i=1;i<=n;i++)
                for(int j=1;j<=m;j++)
                    printf("%d%c",ans[i][j],j==m?'\n':' ');
        }
        if(t)puts("");
    }
}

/*
10000000000

9
9999999997
*/
