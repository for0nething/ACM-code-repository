/*
    kruskal��С�������㷨
    ���ձߵ�Ȩֵ��˳���С����һ�飬���������Ȧ���ر�Ҳ�������ڣ�
    �Ͱѵ�ǰ�����߼��뵽��������
    �Ƿ����Ȧֻ�迴����֮ǰ�Ƿ���ͬһ��ͨ������
    ʹ�ò��鼯�ж��Ƿ�����ͬһ����ͨ����
*/
#define rank rankk  //������ĳ����������ͬ��������define
/*
���鼯
���Ӷ�Ϊ�����������ķ���������O(log(n))����
*/

int par[MAX];//����
int rank[MAX];//���ĸ߶�
//��ʼ��n��Ԫ��
void init(int n)
{
    for(int i=0;i<=n;i++)
    {
        par[i]=i;
        rank[i]=0;
    }
}
//��ѯ���ĸ����ڼ������·��ѹ��
int find(int x)
{
    if(par[x]==x)
        return x;
    else
        return par[x]=find(par[x]);
}
//�ϲ�x��y�����ļ���
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y)
        return ;
    if(rank[x]<rank[y])
        par[x]=y;
    else
    {
        par[y]=x;
        if(rank[x]==rank[y])
            rank[x]++;
    }
}
//�ж�x��y�Ƿ�����ͬһ������
bool same(int x,int y)
{
    return find(x)==find(y);
}
/*
�����ṹ���¼��
*/
struct edge
{
    int u,v,cost;
};
/*����ߵ�����*/
edge es[MAX];
int V,E;//������������
bool cmp(const edge &e1,const edge &e2)
{
    return e1.cost<e2.cost;
}
ll kruskal(edge *e,int edge_num,int vertice_num)//eΪ�洢�ߵ����飬�±��0��ʼ
{
    sort(e,e+edge_num,cmp);//����edge.cost˳���С��������
    init(vertice_num);//��ʼ�����鼯
    ll re=0;
    for(int i=0;i<edge_num;i++)
    {
        edge tem=e[i];
        if(!same(tem.u,tem.v))
        {
            unite(tem.u,tem.v);
            re+=(ll)tem.cost;
        }
    }
    return re;
}
