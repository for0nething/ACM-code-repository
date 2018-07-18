/*
13.2 SAP 邻接矩阵形式 2
保留原矩阵，可用于多次使用最大流
*/
/*
* SAP邻接矩阵形式
* 点的编号从0开始
* 增加个flow数组，保留原矩阵maze,可用于多次使用最大流
*/
const int MAXN=1100;
int maze[MAXN][MAXN];
int gap[MAXN],dis[MAXN],pre[MAXN],cur[MAXN];
int flow[MAXN][MAXN];//存最大流的容量
int sap(int start,int end,int nodenum)
{
    memset(cur,0,sizeof(cur));
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    memset(flow,0,sizeof(flow));
    int u=pre[start]=start,maxflow=0,aug=-1; gap[0]=nodenum;
    while(dis[start]<nodenum)
    {
        loop:
        for(int v=cur[u];v<nodenum;v++)
        if(maze[u][v]-flow[u][v] && dis[u]==dis[v]+1)
        {
            if(aug==-1 ||
            aug>maze[u][v]-flow[u][v])aug=maze[u][v]-flow[u][v]; pre[v]=u;
            u=cur[u]=v;
            if(v==end)
            {
                maxflow+=aug;
                for(u=pre[u];v!=start;v=u,u=pre[u])
                {
                    flow[u][v]+=aug;
                    flow[v][u]-=aug;
                }
                aug=-1;
            }
            goto loop;
        }
        int mindis=nodenum-1;
        for(int v=0;v<nodenum;v++)
        if(maze[u][v]-flow[u][v]&&mindis>dis[v])
        {
            cur[u]=v; mindis=dis[v];
        }
        if((--gap[dis[u]])==0)break;
        gap[dis[u]=mindis+1]++;
        u=pre[u];
    }
    return maxflow;
}








/*
    邻接表形式
*/
const int MAXN = 100010;//点数的最大值
const int MAXM = 400010;//边数的最大值
const int INF = 0x3f3f3f3f;
struct Edge
{
int to,next,cap,flow;
}edge[MAXM];//注意是MAXM
int tol;
int head[MAXN];
int gap[MAXN],dep[MAXN],pre[MAXN],cur[MAXN];
void init()
{
    tol = 0;
    memset(head,-1,sizeof(head));
}
//加边，单向图三个参数，双向图四个参数
void addedge(int u,int v,int w,int rw=0)
{
    edge[tol].to = v;edge[tol].cap = w;edge[tol].next = head[u]; edge[tol].flow = 0;head[u] = tol++;
    edge[tol].to = u;edge[tol].cap = rw;edge[tol].next = head[v]; edge[tol].flow = 0;head[v]=tol++;
}
//输入参数：起点、终点、点的总数
//点的编号没有影响，只要输入点的总数
int sap(int start,int end,int N)
{
    memset(gap,0,sizeof(gap)); memset(dep,0,sizeof(dep)); memcpy(cur,head,sizeof(head)); int u = start;
    pre[u] = -1;
    gap[0] = N;
    int ans = 0;
    while(dep[start] < N)
    {
        if(u == end)
        {
            int Min = INF;
            for(int i = pre[u];i != -1; i = pre[edge[i^1].to])
                if(Min > edge[i].cap - edge[i].flow) Min = edge[i].cap - edge[i].flow;
            for(int i = pre[u];i != -1; i = pre[edge[i^1].to])
            {
                edge[i].flow += Min; edge[i^1].flow -= Min;
            }
            u = start; ans += Min; continue;
        }
        bool flag = false; int v;
        for(int i = cur[u]; i != -1;i = edge[i].next)
        {
            v = edge[i].to;
            if(edge[i].cap - edge[i].flow && dep[v]+1 == dep[u])
            {
                flag = true;
                cur[u] = pre[v] = i;
                break;
            }
        }
        if(flag)
        {
            u = v;
            continue;
        }
        int Min = N;
        for(int i = head[u]; i != -1;i = edge[i].next)
        if(edge[i].cap - edge[i].flow && dep[edge[i].to] < Min)
        {
            Min = dep[edge[i].to]; cur[u] = i;
        }
        gap[dep[u]]--;
        if(!gap[dep[u]])return ans; dep[u] = Min+1; gap[dep[u]]++;
        if(u != start) u = edge[pre[u]^1].to;
    }
    return ans;
}





/*
ISAP+bfs 初始化+栈优化
*/
const int MAXN = 100010;//点数的最大值
const int MAXM = 400010;//边数的最大值
//const int INF = 0x3f3f3f3f;
struct Edge
{
    int to,next,cap,flow;
}edge[MAXM];//注意是MAXM
int tol;
int head[MAXN];
int gap[MAXN],dep[MAXN],cur[MAXN];
void init()
{
    tol = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w,int rw = 0)
{
    edge[tol].to = v; edge[tol].cap = w; edge[tol].flow = 0; edge[tol].next = head[u]; head[u] = tol++;
    edge[tol].to = u; edge[tol].cap = rw; edge[tol].flow = 0; edge[tol].next = head[v]; head[v] = tol++;
}
int Q[MAXN];
void BFS(int start,int end)
{
    memset(dep,-1,sizeof(dep)); memset(gap,0,sizeof(gap)); gap[0] = 1;
    int front = 0, rear = 0; dep[end] = 0;
    Q[rear++] = end;
    while(front != rear)
    {
    int u = Q[front++];
    for(int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to; if(dep[v] != -1)continue; Q[rear++] = v;
        dep[v] = dep[u] + 1;
        gap[dep[v]]++;
    }
    }
}
int S[MAXN];
int sap(int start,int end,int N)
{
    BFS(start,end);
    memcpy(cur,head,sizeof(head));
    int top = 0; int u = start; int ans = 0;
    while(dep[start] < N)
    {
        if(u == end)
        {
            int Min = INF;
            int inser;
            for(int i = 0;i < top;i++)
                if(Min > edge[S[i]].cap - edge[S[i]].flow)
                {
                    Min = edge[S[i]].cap - edge[S[i]].flow; inser = i;
                }
            for(int i = 0;i < top;i++)
            {
                edge[S[i]].flow += Min; edge[S[i]^1].flow -= Min;
            }
            ans += Min; top = inser;
            u = edge[S[top]^1].to;
            continue;
        }
        bool flag = false; int v;
        for(int i = cur[u]; i != -1; i = edge[i].next)
        {
            v = edge[i].to;
            if(edge[i].cap - edge[i].flow && dep[v]+1 == dep[u])
            {
                flag = true; cur[u] = i; break;
            }
        }
        if(flag)
        {
            S[top++] = cur[u]; u = v;
            continue;
        }
        int Min = N;
        for(int i = head[u]; i != -1; i = edge[i].next)
        if(edge[i].cap - edge[i].flow && dep[edge[i].to] < Min)
        {
            Min = dep[edge[i].to]; cur[u] = i;
        }
        gap[dep[u]]--;
        if(!gap[dep[u]])
            return ans;
        dep[u] = Min + 1; gap[dep[u]]++;
        if(u != start)u = edge[S[--top]^1].to;
    }
    return ans;
}
