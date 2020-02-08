#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
typedef pair<ll,ll>pll;
#define pb push_back
#define rank rankk
#define right riight
#define mp make_pair
const int maxn=1e5+5;;
const int MAX=1e9+7;
const int MOD=1e9+7;

/*
    题意:有一棵树，每个结点有一个灯（初始均是关着的）。每个灯能对该位置和相邻结点贡献1的亮度。现有两种操作：

    （1）将一条链上的灯状态翻转，开变关、关变开；

    （2）查询一个结点的亮度。

    数据规模：1≤n,q≤105

    做法:
    对于这种题，很容易想到任意指定一个根转化为有根树，每个结点维护值ai表示它的所有儿子的贡献之和，
    这样再加上自己以及父亲的贡献就能回答一个询问了。
    然而经过一波思考发现问题在于链修改时根本没法维护ai。因此需要用链修改时的常规操作——树链剖分理论来解决本题了。
    对于树链剖分，每一条链被剖分成了O(logn)条重链，下面考虑修改每条重链(s,t)，
    不妨设depth[s]<depth[t]。可以发现修改后只会改变(father[s],father[t])这条链上的ai，
    但是注意到链(s,father[t])上每个结点都是它父亲的重儿子，如果我们ai不维护重儿子，
    让ai表示它的所有轻儿子的贡献之和，那么每条重链只需暴力修改一个afather[s]。
    这样对于每个修改，更新a数组的时间复杂度为O(logn)；同时当然还需要更新链上灯的状态，
    即进行链异或1的操作，如果采用树链剖分加树状数组可达到O(log^2)的时间复杂度。
    对于每个询问x，只需要查询ax（对应轻儿子），以及father[x],x,son[x]（分别对应父亲、重儿子、自身）的状态即可
    （这里son[x]表示x的重儿子），查询时间复杂度O(logn)。

    总时间复杂度O(n+qlog2n)

    除此以外，若使用欧拉序而非树剖的DFS序来做的话，修改的复杂度也可以降到一个log

*/
int n,m,dcnt,treeLen;
vector<int>edg[maxn];
int dep[maxn],fa[maxn],top[maxn],id[maxn],son[maxn],light[maxn];
bool tree[maxn];
int dfs1(int now,int father){
    fa[now]=father;
    dep[now]=dep[father]+1;
    son[now]=0;
    int ret=0,maxSize=0;
    for(int t:edg[now]){
        if(t==father)continue;
        int siz=dfs1(t,now);
        ret+=siz;
        if(siz>maxSize){
            maxSize=siz;son[now]=t;
        }
    }
    return ret+1;
}
void dfs2(int now,int tp){
    top[now]=tp;
    id[now]=++dcnt;
    if(son[now])dfs2(son[now],tp);
    for(int t:edg[now]){
        if(t==fa[now]||t==son[now])continue;
        dfs2(t,t);
    }
}
void init(){
    dcnt=0;dep[0]=0;
    dfs1(1,0);dfs2(1,1);
}
int sum(int now){
    int ret=0;
    while(now)ret^=tree[now],now-=now&-now;
    return ret;
}
void flip(int lo){
    while(lo<=treeLen)tree[lo]^=1,lo+=lo&-lo;
}
void modify(int s,int t){
    int top1=top[s],top2=top[t];
    while(top1!=top2){
        if(dep[top1]>=dep[top2]){
            swap(top1,top2);swap(s,t);
        }
        flip(id[top2]);flip(id[t]+1);
        t=fa[top2];
    }
    if(dep[s]>dep[t])swap(s,t);
    flip(id[s]);flip(id[t]+1);
    if(son[fa[s]]!=s)light[fa[s]]+=sum(id[s])?1:-1;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int u,v,i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        edg[u].pb(v);edg[v].pb(u);
    }
    init();treeLen=n;
    while(m--){
        int opt;
        scanf("%d",&opt);
        if(opt==1){
            int u,v;scanf("%d%d",&u,&v);
            modify(u,v);
        }
        else{
            int u;scanf("%d",&u);
            int ans=fa[u]?sum(id[fa[u]]):0;
            if(son[u])ans+=sum(id[son[u]]);
            ans+=sum(id[u])+light[u];
            printf("%d\n",ans);
        }

    }
    return 0;
}
/*
*/
