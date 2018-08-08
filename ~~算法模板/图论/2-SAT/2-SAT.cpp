/*
    2-SAT�����������ģ���n����������xi,����m����Ҫ�����������ÿ����������ʽ����
    ��xiΪ��/�ٻ���xjΪ��/�١������硰x1Ϊ�����x3Ϊ�١�����x7Ϊ�ٻ���x2Ϊ�١����ǺϷ���������
    �����ָ������������������һ������ȷ��
*/
const int maxn=1e5+5;
struct TwoSAT
{
    int n;
    vector<int>G[maxn*2];
    bool mark[maxn*2];
    int S[maxn*2],c;//s����洢��ǰ����ǵĵ�
    bool dfs(int x)
    {
        if(mark[x^1])return false;//���ͬʱ����ǣ��߼�ì��
        if(mark[x])return true;//���仯
        mark[x]=1;
        S[c++]=x;
        for(int i=0;i<G[x].size();i++)
            if(!dfs(G[x][i]))return false;//ͬһ��ǿ��ͨ����Ӧ��ͬһ����ɫ
        return true;
    }
    void init(int n)
    {
        this->n=n;
        for(int i=0;i<n*2;i++)G[i].clear();
        memset(mark,0,sizeof(mark));
    }
    //x=xval or y=yval
    /*
        xΪxval ���� yΪyval��Ҫ��һ������
    */
    void add_clause(int x,int xval,int y,int yval)
    {
        x=x*2+xval;y=y*2+yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }
    bool solve()
    {
        for(int i=0;i<n*2;i+=2)
        {
            if(!mark[i]&&!mark[i+1])//��ٶ�û��� ����Ҫdfs
            {
                c=0;//����
                if(!dfs(i))//���Ա��Ϊtrue
                {
                    while(c>0)mark[S[--c]]=false;
                    if(!dfs(i+1))return false;//���Ա��Ϊfalse
                }
            }
        }
        return true;
    }
};
int main()
{


}
/*

*/
