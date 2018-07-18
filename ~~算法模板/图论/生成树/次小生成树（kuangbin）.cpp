/*
* 次小生成树
* 求最小生成树时，用数组Max[i][j]来表示MST中i到j最大边权
* 求完后，直接枚举所有不在MST中的边，替换掉最大边权的边，更新答案
* 点的编号从0开始
* cost数组需初始化为INFF
*/
const int MAXN=110;//点数
const int INF=0x3f3f3f3f;
bool vis[MAXN];
int lowc[MAXN];
int pre[MAXN];
int Max[MAXN][MAXN];//Max[i][j]表示在最小生成树中从i到j的路径中的最大边权
bool used[MAXN][MAXN];//i到j的边是否出现在最小生成树中（未直接相连的两点必为false）
int Prim(int cost[][MAXN],int n)
{
    int ans=0;
    memset(vis,false,sizeof(vis));
    memset(Max,0,sizeof(Max));
    memset(used,false,sizeof(used));
    vis[0]=true;
    pre[0]=-1;
    for(int i=1;i<n;i++)
    {
        lowc[i]=cost[0][i]; pre[i]=0;
    }
    lowc[0]=0;
    for(int i=1;i<n;i++)
    {
        int minc=INF;
        int p=-1;
        for(int j=0;j<n;j++)
            if(!vis[j]&&minc>lowc[j])
            {
                minc=lowc[j]; p=j;
            }
        if(minc==INF)return -1;
        ans+=minc;
        vis[p]=true;
        used[p][pre[p]]=used[pre[p]][p]=true;
        for(int j=0;j<n;j++)
        {
            if(vis[j]&&j!=p)Max[j][p]=Max[p][j]=max(Max[j][pre[p]],lowc[p]);//更新树上j到p的路径上的最大边权值
            if(!vis[j]&&lowc[j]>cost[p][j])
            {
                lowc[j]=cost[p][j]; pre[j]=p;
            }
        }
    }
    return ans;
}
