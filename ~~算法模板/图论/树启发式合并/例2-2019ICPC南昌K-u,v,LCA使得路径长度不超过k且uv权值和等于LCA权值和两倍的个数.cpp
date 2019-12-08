#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
typedef pair<ll,ll>pll;
#define pb push_back
#define rank rankk
#define right riight
#define mp make_pair
const int maxn=2e6+5;;
const int MAX=1e9+7;

/*
    题意：给定一棵树，每个点有权值val，求这样的u,v个数
    (1)u\v不同且互不为祖先
    (2)u\v路径长度<=k
    (3)val_u+val_v=2*val_LCA(u,v)
    做法:
    启发式合并，动态开点线段树维护某个val的不同深度出现的次数
    需要注意的是，启发式合并处理轻边要算答案时，先单独递归算答案，再插进去
    不然轻边之间也会有影响
*/
int n,m,k;

int DEP,VAL;
ll ans;
int rt[maxn];
int val[maxn];
int siz[maxn],son[maxn],maxs[maxn],dep[maxn];
vector<int>edg[maxn];
struct seg_tree{
    int tot;
    int cnt[maxn<<2],ls[maxn<<2],rs[maxn<<2];
    void update(int &k,int l,int r,int lo,int val){
        if(!k){
            k=++tot;cnt[tot]=ls[tot]=rs[tot]=0;
        }
        cnt[k]+=val;
        if(l==r)return;
        int mid=(l+r)/2;
        if(lo<=mid)update(ls[k],l,mid,lo,val);
        else update(rs[k],mid+1,r,lo,val);
    }
    int query(int k,int l,int r,int lim){
        if(!k)return 0;
        if(r<=lim)return cnt[k];
        int mid=(l+r)/2,re=0;
        if(ls[k])re+=query(ls[k],l,mid,lim);
        if(lim>mid && rs[k])re+=query(rs[k],mid+1,r,lim);
        return re;
    }
}T;
void dfs(int now){
    siz[now]=1;m=max(m,dep[now]);
    for(int u:edg[now]){
        dep[u]=dep[now]+1;
        dfs(u);
        siz[now]+=siz[u];
        if(siz[u]>maxs[now])maxs[now]=siz[u],son[now]=u;
    }
}
void clear(int now){
    T.update(rt[val[now]],1,m,dep[now],-1);
    for(int u:edg[now])clear(u);
}
void addans(int now){
    if(k+DEP-dep[now]>0 && VAL-val[now]>=0 && VAL-val[now]<=n){
        ans+=T.query(rt[VAL-val[now]],1,m,k+DEP-dep[now]);
    }
    for(int u:edg[now])addans(u);
}
void insert(int now){
    for(int u:edg[now])insert(u);
    T.update(rt[val[now]],1,m,dep[now],1);
}
void dfs2(int now){
    for(int u:edg[now]){
        if(u!=son[now]){
            dfs2(u);
            clear(u);
        }
    }
    if(son[now])dfs2(son[now]);
    DEP=2*dep[now];VAL=2*val[now];
    for(int u:edg[now])
        if(u!=son[now]){addans(u);insert(u);}
    T.update(rt[val[now]],1,m,dep[now],1);
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&val[i]);
    for(int u,i=2;i<=n;i++)scanf("%d",&u),edg[u].pb(i);
    T.tot=0;
    dep[1]=1;dfs(1);
    dfs2(1);
    printf("%lld\n",ans*2);
}
/*
*/
