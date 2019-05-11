#include<cstdio>
#include<vector>
#include<set>
#include<cmath>
#include<algorithm>
#include<assert.h>
#include<iostream>
using namespace std;
#define eb emplace_back
#define mp make_pair
typedef long long ll;
typedef pair<int,int> pii;
const int MAX=2e5+5;
const int MOD=1e9+7;
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
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
vector<pii>tem[MAX],edg[MAX];
int t,n,m,dcnt,len,top,rt,tot;
int a[MAX],id[MAX],aux[MAX],dep[MAX],dfn[MAX],qs[MAX];
int st[MAX][20],wd[MAX],ans[MAX],dwho[MAX],stk[MAX],siz[MAX];
vector<int>pts[MAX],fac[MAX],lin;
bool used[MAX],vi[MAX];
void dfs(int now,int fa){
    aux[++len]=now;dfn[now]=++dcnt;dwho[dcnt]=now;id[now]=len;
    for(pii u:tem[now]){
        if(u.first!=fa){
            dep[u.first]=dep[now]+1;
            wd[u.first]=add(wd[now],u.second);
            dfs(u.first,now);
            aux[++len]=now;
        }
    }
}
void initst(){
    for(int i=1;i<=len;i++)st[i][0]=aux[i];
    for(int i=1;i<=17;i++)
        for(int j=1;j+(1<<(i-1))<=len;j++)
            st[j][i]=dep[st[j][i-1]]<dep[st[j+(1<<(i-1))][i-1]]?st[j][i-1]:st[j+(1<<(i-1))][i-1];
}
inline int lca(int x,int y){
    x=id[x],y=id[y];
    if(x>y)swap(x,y);
    int len=log2(y-x+1);
    return dep[st[x][len]]<dep[st[y-(1<<len)+1][len]]?st[x][len]:st[y-(1<<len)+1][len];

}
inline void addedge(int x,int y,int w=0){
    if(y==x)return;
    w=wd[y]-wd[x];if(w<0)w+=MOD;edg[x].eb(mp(y,w));
}
void dfs2(int now,int bel,int fa){
    siz[now]=used[now];
    for(pii u:edg[now]){
        int x=u.first,dis=u.second;
        if(x==fa||x==now)continue;
        dfs2(x,bel,now);
        addi(ans[bel],mul(dis,mul(tot-siz[x],siz[x])));
        siz[now]+=siz[x];
    }
}
void solve(int x){
    int lim=pts[x].size();lin.clear();
    top=0;
    for(int i=0;i<lim;i++){
        int who=pts[x][i];used[who]=1;
        if(!top){stk[++top]=who;lin.eb(who);continue;}
        int LCA=lca(stk[top],who);
        while(1){
            if(dep[stk[top-1]]<=dep[LCA]){
                addedge(LCA,stk[top]);--top;
                if(stk[top]!=LCA)stk[++top]=LCA,lin.eb(LCA);
                break;
            }
            addedge(stk[top-1],stk[top]);--top;
        }

        if(stk[top]!=who)stk[++top]=who,lin.eb(who);
    }
    rt=stk[top];--top;
    while(top)rt=stk[top],addedge(stk[top],stk[top+1]),--top;
    tot=lim;dfs2(rt,x,0);
    for(int u:pts[x])used[u]=0;
    for(int u:lin)edg[u].clear();
}
int main(){
    read(t);
    while(t--){
        read(n);
        for(int i=1;i<=n;i++)read(a[i]);
        for(int u,v,w,i=1;i<n;i++){
            read(u);read(v);read(w);if(w>=MOD)w-=MOD;tem[a[u]].eb(mp(a[v],w));tem[a[v]].eb(mp(a[u],w));
        }
        len=dcnt=0;
        dfs(1,1);initst();
        read(m);
        for(int i=1;i<=m;i++)read(qs[i]),vi[qs[i]]=1;
        for(int i=1;i<=n;i++)if(vi[i])for(int j=i;j<=n;j+=i)fac[j].eb(i);
        for(int i=1;i<=dcnt;i++){
            int x=dwho[i];
            for(int u:fac[x])pts[u].eb(x);
        }
        for(int i=1;i<=n;i++)if(vi[i])solve(i),vi[i]=0;
        for(int i=1;i<=m;i++)printf("%d\n",ans[qs[i]]);
        for(int i=1;i<=n;i++)tem[i].clear(),pts[i].clear(),fac[i].clear();
        for(int i=1;i<=n;i++)ans[i]=0;
    }
    return 0;
}
