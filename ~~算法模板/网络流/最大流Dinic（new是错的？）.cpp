const int maxn=1e5+5;
const int inf=1e7;
int head[maxn],cnt,S,T,q[maxn],h[maxn];
struct node{int to,next,v;}e[maxn];//记录边 终点、容量、反向边 e数组存边
void add(int u,int v,int w){e[++cnt].to=v;e[cnt].next=head[u];head[u]=cnt;e[cnt].v=w;}
void ins(int u,int v,int w){add(u,v,w),add(v,u,0);}//加边用此 1次共加4条
inline bool bfs()
{
	memset(h,-1,sizeof(h));
	q[0]=S,h[S]=0;
	int t=0,w=1;
	while(t!=w)
	{
		int x=q[t++];
		for(int i=head[x];i;i=e[i].next)
			if(h[e[i].to]==-1&&e[i].v>0)
                            h[e[i].to]=h[x]+1,q[w++]=e[i].to;
	}return h[T]!=-1;
}
inline int dfs(int x,int flow)
{
	if(x==T)return flow;
	int used=0,w=0;
	for(int i=head[x];i;i=e[i].next)
	{
	    if(h[e[i].to]==h[x]+1&&e[i].v>0)
	    {
		    w=dfs(e[i].to,min(flow-used,e[i].v));
		    e[i].v-=w,e[i^1].v+=w;used+=w;
		    if(used==flow)return flow;
	    }
	}
	if(!used)h[x]=-1;
	return used;
}
int dinic(){int ans=0;while(bfs())ans+=dfs(S,inf);return ans;}
