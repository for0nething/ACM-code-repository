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
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=4e5+5;
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

int t,n,m;
int ecnt1,ecnt2,eid,dcnt;
int head1[MAX],head2[MAX],a[MAX];
int lev[MAX],cur[MAX];
int dfn[MAX],low[MAX],scc,bel[MAX];
ll dis[2][MAX];
struct node{
    int to,nxt,val;
    node(){}
    node(int _to,int _nxt,int _val):to(_to),nxt(_nxt),val(_val){}
}edg1[MAX],edg2[MAX];
inline void add_edge1(int u,int v,int w){
    edg1[++ecnt1]=node(v,head1[u],w);
    head1[u]=ecnt1;
}
inline void add_edge2(int u,int v,int w){
    edg2[++ecnt2]=node(v,head2[u],w);
    head2[u]=ecnt2;
    edg2[++ecnt2]=node(u,head2[v],0);
    head2[v]=ecnt2;
}
void dij(int st){
    priority_queue<pli,vector<pli>,greater<pli> >que;
    int id=(st==1?0:1);
    memset(dis[id],0x3f,sizeof(dis[id]));
    que.push(mp(0,st));dis[id][st]=0;
    while(!que.empty()){
        int who=que.top().se;
        ll d=que.top().fi;que.pop();
        if(dis[id][who]<d)continue;
        for(int i=head1[who];i;i=edg1[i].nxt){
            int to=edg1[i].to,val=edg1[i].val;
            if(dis[id][to]>dis[id][who]+val){
                dis[id][to]=dis[id][who]+val;
                que.push(mp(dis[id][to],to));
            }
        }
    }
}
inline bool bfs(){
    queue<int>que;
    memset(lev,0,sizeof(lev));
    lev[1]=1;que.push(1);
    while(!que.empty()){
        int x=que.front();que.pop();
        for(int i=head2[x];i;i=edg2[i].nxt){
            int to=edg2[i].to;
            if(lev[to]||!edg2[i].val)continue;
            lev[to]=lev[x]+1;
            if(to==n)return 1;
            que.push(to);
        }
    }
    return 0;
}
inline int dinic(int x,int low){
    if(x==n)return low;
    int tmp=low;
    for(int &i=cur[x];i;i=edg2[i].nxt){
        int to=edg2[i].to;
        if(lev[to]!=lev[x]+1||!edg2[i].val)continue;
        int res=dinic(to,min(tmp,edg2[i].val));
        if(!res)lev[to]=0;
        else tmp-=res,edg2[i].val-=res,edg2[i^1].val+=res;
        if(!tmp)return low;
    }
    return low-tmp;
}
stack<int>stk;
bool inq[MAX];
void tarjan(int x){
    dfn[x]=low[x]=++dcnt;
    stk.push(x);inq[x]=1;
    for(int i=head2[x];i;i=edg2[i].nxt){
        if(!edg2[i].val)continue;
        int to=edg2[i].to;
        if(!dfn[to])tarjan(to),low[x]=min(low[x],low[to]);
        else if(inq[to])low[x]=min(low[x],dfn[to]);
    }
    if(low[x]==dfn[x]){
        ++scc;
        while(1){
            int y=stk.top();stk.pop();
            inq[y]=0;bel[y]=scc;
            if(x==y)break;
        }
    }
}
int main(){
    read(t);
    while(t--){
        read(n);read(m);
        memset(head1,0,sizeof(head1));
        memset(head2,0,sizeof(head2));
        ecnt1=0;ecnt2=1;
        for(int i=1;i<n;i++)read(a[i]);
        a[n]=INFF;
        while(m--){
            int u,v,w;
            read(u);read(v);read(w);
            add_edge1(u,v,w);add_edge1(v,u,w);
        }
        dij(1);dij(n);eid=n;
        for(int i=1;i<n;i++)
            for(int j=head1[i];j;j=edg1[j].nxt){
                int to=edg1[j].to,val=edg1[j].val;
                if(dis[0][i]+val+dis[1][to]==dis[0][n]){
                    ++eid;
                    add_edge2(i,eid,a[i]);
                    add_edge2(eid,to,a[to]);
                }
            }
        ll ans=0;
        while(bfs()){memcpy(cur,head2,sizeof(head2));ans+=dinic(1,INF); }
        memset(dfn,0,sizeof(dfn));
        memset(inq,0,sizeof(inq));
        dcnt=scc=0;
        for(int i=1;i<=eid;i++)
            if(!dfn[i])tarjan(i);
        bool flag=0;
        for(int i=2;i<=ecnt2&&!flag;i+=2){
            if(edg2[i].val)continue;//Ã»ÓÐÂúÁ÷
            int x=edg2[i^1].to,y=edg2[i].to;
            if(bel[x]==bel[y])continue;
            if(bel[x]!=bel[1]||bel[y]!=bel[n])flag=1;
        }
        if(flag)printf("No %lld\n",ans);
        else printf("Yes %lld\n",ans);
    }
    return 0;
}
/*

*/
