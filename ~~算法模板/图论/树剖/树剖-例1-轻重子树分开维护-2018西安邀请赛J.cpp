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
    ����:��һ������ÿ�������һ���ƣ���ʼ���ǹ��ŵģ���ÿ�����ܶԸ�λ�ú����ڽ�㹱��1�����ȡ��������ֲ�����

    ��1����һ�����ϵĵ�״̬��ת������ء��ر俪��

    ��2����ѯһ���������ȡ�

    ���ݹ�ģ��1��n,q��105

    ����:
    ���������⣬�������뵽����ָ��һ����ת��Ϊ�и�����ÿ�����ά��ֵai��ʾ�������ж��ӵĹ���֮�ͣ�
    �����ټ����Լ��Լ����׵Ĺ��׾��ܻش�һ��ѯ���ˡ�
    Ȼ������һ��˼�����������������޸�ʱ����û��ά��ai�������Ҫ�����޸�ʱ�ĳ���������������ʷ���������������ˡ�
    ���������ʷ֣�ÿһ�������ʷֳ���O(logn)�����������濼���޸�ÿ������(s,t)��
    ������depth[s]<depth[t]�����Է����޸ĺ�ֻ��ı�(father[s],father[t])�������ϵ�ai��
    ����ע�⵽��(s,father[t])��ÿ����㶼�������׵��ض��ӣ��������ai��ά���ض��ӣ�
    ��ai��ʾ������������ӵĹ���֮�ͣ���ôÿ������ֻ�豩���޸�һ��afather[s]��
    ��������ÿ���޸ģ�����a�����ʱ�临�Ӷ�ΪO(logn)��ͬʱ��Ȼ����Ҫ�������ϵƵ�״̬��
    �����������1�Ĳ�����������������ʷּ���״����ɴﵽO(log^2)��ʱ�临�Ӷȡ�
    ����ÿ��ѯ��x��ֻ��Ҫ��ѯax����Ӧ����ӣ����Լ�father[x],x,son[x]���ֱ��Ӧ���ס��ض��ӡ�������״̬����
    ������son[x]��ʾx���ض��ӣ�����ѯʱ�临�Ӷ�O(logn)��

    ��ʱ�临�Ӷ�O(n+qlog2n)

    �������⣬��ʹ��ŷ����������ʵ�DFS�������Ļ����޸ĵĸ��Ӷ�Ҳ���Խ���һ��log

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
