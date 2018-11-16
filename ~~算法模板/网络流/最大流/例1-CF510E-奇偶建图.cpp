/*
1、CF510E
给出n个人(n<=300)， 以及每个人的值， 要求他们坐在一些桌子上面， 每个桌子如果有人坐， 就必须做3个人以上。　并且相邻的两个人的值加起来必须是素数。每个人的值都>=2.输出一种可行方案。
由大于等于2这个条件， 可以知道素数都是奇数， 那么很明显就需要一奇一偶相邻这样做， 那么一个桌子上必定有偶数个人。 一个奇数旁边有两个偶数， 一个偶数旁边有两个奇数。
所以可以先判断n是否为偶数， 如果是奇数直接输出不可能。
然后开始奇偶建边， 源点和奇数建边， 权值为2， 因为一个奇数需要和两个偶数匹配； 偶数和汇点建边， 同理权值也为2。
然后， 如果一个奇数和一个偶数相加得到的数是素数， 那么奇数向偶数连一条边， 权值为1。
这样跑一遍网络流， 看结果是否等于n， 如果不相等， 说明不可能。如果可能， dfs一下就可以求出几个桌子， 每个桌子上面几个人了。
*/

//最坏复杂度 n*n*m
namespace Maxflow{
    typedef int type;//默认类型为int
    const type INF=0x3f3f3f3f;//INT类型的INF设置
    const int maxn=4e4;
    struct node{
        int to;type cap;int nxt;
        node(int _to=0,type _cap=0,int _nxt=0):to(_to),cap(_cap),nxt(_nxt){};
    }edg[maxn*50];
    int head[maxn],tot;
    void addedge(int from,int to,type cap,type rcap=0){
        edg[tot]=node(to,cap,head[from]);head[from]=tot++;//边的标号必须从0开始 不然i^1不能表示反向边
        edg[tot]=node(from,rcap,head[to]);head[to]=tot++;
    }
    int dep[maxn],cur[maxn];//当前弧优化
    //bfs分层
    bool bfs(int s,int t,int n){//源点 汇点 点数（用于初始化）下标从1开始
        static int Q[maxn],ST,ED;//模拟队列
        memset(dep+1,0,sizeof(int)*n);//下标从1开始
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
    //dfs寻找增广路
    type dfs(int x,const int &t,type flow=INF){//当前点 目标点 当前流量
        if(x==t||flow==0)return flow;
        type ret=0;
        for(int i=cur[x];~i;i=edg[i].nxt){
            if(dep[x]+1==dep[edg[i].to]&&edg[i].cap){
                type f=dfs(edg[i].to,t,min(flow,edg[i].cap));
                edg[i].cap-=f;edg[i^1].cap+=f;
                ret+=f;flow-=f;cur[x]=i;
                if(flow==0)break;
            }
        }
        if(!ret)dep[x]=0;
        return ret;
    }
    //源点 汇点 点数 下标从1开始
    type maxflow(int s,int t,int n){
        type ret=0;
        while(bfs(s,t,n)){//仍能分层
            type f;
            memcpy(cur+1,head+1,n*sizeof(int));
            while((f=dfs(s,t))>0)ret+=f;//可以找到增广路
        }
        return ret;
    }
    void init(int n){
        memset(head+1,-1,sizeof(int)*n);tot=0;
    }
}
using namespace Maxflow;
int pcnt,n,S,T,vcnt;
bool check[MAX],vis[MAX];
int a[MAX],prime[MAX];
vector<int>v[MAX];
//dfs得到每个桌子的人
void dfsv(int now,int id){
    vis[now]=1;
    v[id].eb(now);
    for(int i=head[now];~i;i=edg[i].nxt){
        int to=edg[i].to;
        if(to==S||to==T||vis[to])continue;
        if(i%2==0&&!edg[i].cap){
            dfsv(to,id);
        }
        if(i%2==1&&!edg[i^1].cap){
            dfsv(to,id);
        }
    }
}
int main(){
    read(n);
    for(int i=1;i<=n;i++)read(a[i]);
    if(n&1)return 0*printf("Impossible\n");
    for(int i=2;i<MAX;i++){
        if(!check[i]){
            prime[pcnt++]=i;
        }
        for(int j=0;j<pcnt;j++){
            if(prime[j]*i>=MAX)break;
            check[i*prime[j]]=1;
            if(i%prime[j]==0)break;
        }
    }
    init(n+2);
    S=n+1;T=n+2;
    for(int i=1;i<=n;i++){
        if(a[i]&1)addedge(S,i,2,0);
        else addedge(i,T,2,0);
        for(int j=i+1;j<=n;j++){
            int sum=a[i]+a[j];
            if(a[i]%2==a[j]%2)continue;
            if(!check[sum]){
                if(a[i]&1)addedge(i,j,1,0);
                else addedge(j,i,1,0);
            }
        }
    }
    int mf=maxflow(S,T,n+2);
    if(mf!=n)return 0*printf("Impossible\n");
    else{
        for(int i=1;i<=n;i++)
            if(!vis[i])dfsv(i,vcnt++);
    }
    printf("%d\n",vcnt);
    for(int i=0;i<vcnt;i++){
        printf("%d",v[i].size());
        for(int u:v[i])printf(" %d",u);
        printf("\n");
    }
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
