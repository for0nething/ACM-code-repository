/*
    ����һ����ͨͼ����������������ٴ����������㲻�ظ�����·������˵���ͼ�ǵ�-˫��ͬ�ģ�һ����˫��ͨ��biconnected��
    ��Ҫ��ȼ������������߶���ͬһ���򵥻��У����ڲ��޸
    ��������������ٴ����������߲��ظ�����·������˵���ͼ�ǡ���-˫��ͨ����
    ��Ҫ��ֻ��Ҫ ÿ���߶�������һ���򵥻��У������б߶�������

    ����һ����ͼ����-˫��ͨ�ļ�����ͼ��Ϊ˫��ͨ�������
    ÿ����ǡ����һ��˫��ͨ����  ������ ����⣩   ����ͬ˫��ͨ�������ܻ��й�����
    ����֤����ͬ˫��ͨ�������ֻ��һ�������㣬����һ���Ǹ��
    ��һ���棬������������������ͬ˫��ͬ�����Ĺ�����

    ͬ����-˫��ͨ�����ļ�����ͼ��Ϊ��-˫��ͨ����
    �����Ų������κα�-��ͨ����֮�⣬����ÿ����ǡ������һ����-˫��ͨ����
    �Ұ�������ɾ��֮��ÿ����ͨ������Ӧԭͼ�е�һ����-˫��ͨ����

    ����Ϊ ���� ��-˫��ͨ���� ���㷨
    ���㷨��һ��ջS��������ǰBCC�еı�
    ��������㷨һ�� �����dfs fa��Ҫ����ֵ
    ��ʼ��G��ԭͼ����Ҫ��ʼ��
    Ĭ��ͼ������0��ʼ �����Ҫ1��ʼ����ֱ�Ӹ���
*/
//���bccno������
const int maxn=1e5+5;
struct Edge{int u,v;};
int pre[maxn],iscut[maxn],bccno[maxn],dfs_clock,bcc_cnt;//bccno��¼ÿһ��������BCC�ı��
vector<int> G[maxn],bcc[maxn];//bcc����洢ĳһBCC�����еĵ�  G��ԭͼ
stack<Edge>S;
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    int child=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        Edge e=(Edge){u,v};
        if(!pre[v])//δ���ʹ�v
        {
            S.push(e);child++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);//�ú����low���������Լ�
            if(lowv>=pre[u])
            {
                iscut[u]=true;//�Ǹ
                bcc_cnt++;//˫��ͨ��������++
                bcc[bcc_cnt].clear();//ע�⣡bcc��1��ʼ���
                for(;;)
                {
                    Edge x=S.top();S.pop();
                    if(bccno[x.u]!=bcc_cnt){bcc[bcc_cnt].push_back(x.u);bccno[x.u]=bcc_cnt;}
                    if(bccno[x.v]!=bcc_cnt){bcc[bcc_cnt].push_back(x.v);bccno[x.v]=bcc_cnt;}
                    if(x.u==u&&x.v==v)break;//���˵�ǰ��ı�
                }
            }
        }
        else if(pre[v]<pre[u]&&v!=fa)
        {
            S.push(e);lowu=min(lowu,pre[v]);//�÷���߸����Լ�
        }
    }
    if(fa<0&&child==1)iscut[u]=0;
    return lowu;
}
void find_bcc(int n)
{
    //���ý�����S��֤Ϊ�� ���Բ������
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    dfs_clock=bcc_cnt=0;
    for(int i=0;i<n;i++)//Ĭ��ͼ������0��ʼ �����Ҫ1��ʼ����ֱ�Ӹ���
        if(!pre[i])dfs(i,-1);
}

/*
    ��-˫��ͨ���������ø��򵥵ķ������
    ��������dfs��ǳ����е��ţ�����һ��dfs�ҳ���-˫��ͨ����
    ��Ϊ��-˫��ͨ�������޹������ģ�����ֻҪ�ڵڶ���dfs��ʱ��֤�������ż���

*/
