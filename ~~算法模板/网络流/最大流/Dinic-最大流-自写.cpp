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
