/*
1��CF510E
����n����(n<=300)�� �Լ�ÿ���˵�ֵ�� Ҫ����������һЩ�������棬 ÿ����������������� �ͱ�����3�������ϡ����������ڵ������˵�ֵ������������������ÿ���˵�ֵ��>=2.���һ�ֿ��з�����
�ɴ��ڵ���2��������� ����֪���������������� ��ô�����Ծ���Ҫһ��һż������������ ��ôһ�������ϱض���ż�����ˡ� һ�������Ա�������ż���� һ��ż���Ա�������������
���Կ������ж�n�Ƿ�Ϊż���� ���������ֱ����������ܡ�
Ȼ��ʼ��ż���ߣ� Դ����������ߣ� ȨֵΪ2�� ��Ϊһ��������Ҫ������ż��ƥ�䣻 ż���ͻ�㽨�ߣ� ͬ��ȨֵҲΪ2��
Ȼ�� ���һ��������һ��ż����ӵõ������������� ��ô������ż����һ���ߣ� ȨֵΪ1��
������һ���������� ������Ƿ����n�� �������ȣ� ˵�������ܡ�������ܣ� dfsһ�¾Ϳ�������������ӣ� ÿ���������漸�����ˡ�
*/

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
using namespace Maxflow;
int pcnt,n,S,T,vcnt;
bool check[MAX],vis[MAX];
int a[MAX],prime[MAX];
vector<int>v[MAX];
//dfs�õ�ÿ�����ӵ���
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
