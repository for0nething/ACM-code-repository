//����Ӷ� n*n*m
namespace Maxflow{
    typedef int type;//Ĭ������Ϊint
    const type INF=0x3f3f3f3f;//INT���͵�INF����
    const int maxn=4e4;
    struct node{
        int to;type cap;int nxt;
        node(int _to=0,type _cap=0,int _nxt=0):to(_to),cap(_cap),nxt(_nxt){};
    }edg[maxn*50];
    int head[maxn],tot;
    void addedge(int from,int to,type cap,type rcap=0){
        edg[tot]=node(to,cap,head[from]);head[from]=tot++;//�ߵı�ű����0��ʼ ��Ȼi^1���ܱ�ʾ�����
        edg[tot]=node(from,rcap,head[to]);head[to]=tot++;
    }
    int dep[maxn],cur[maxn];//��ǰ���Ż�
    //bfs�ֲ�
    bool bfs(int s,int t,int n){//Դ�� ��� ���������ڳ�ʼ�����±��1��ʼ
        static int Q[maxn],ST,ED;//ģ�����
        memset(dep+1,0,sizeof(int)*n);//�±��1��ʼ
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
    //dfsѰ������·
    type dfs(int x,const int &t,type flow=INF){//��ǰ�� Ŀ��� ��ǰ����
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
    //Դ�� ��� ���� �±��1��ʼ
    type maxflow(int s,int t,int n){
        type ret=0;
        while(bfs(s,t,n)){//���ֲܷ�
            type f;
            memcpy(cur+1,head+1,n*sizeof(int));
            while((f=dfs(s,t))>0)ret+=f;//�����ҵ�����·
        }
        return ret;
    }
    void init(int n){
        memset(head+1,-1,sizeof(int)*n);tot=0;
    }
}
