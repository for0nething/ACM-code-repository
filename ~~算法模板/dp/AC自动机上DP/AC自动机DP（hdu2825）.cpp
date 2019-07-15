/*
    HDU 2825
    ���⣺
    �� m �����ʹ��ɵļ��ϣ�ͳ�����г���Ϊ n �Ĵ��У��������� k �����ʵķ�������
*/


const int SIGMA_SIZE=26;
const int MAXNODE=110;
struct AhoCorasickAutomata
{
    int ch[MAXNODE][SIGMA_SIZE];//Trie��
    int f[MAXNODE];//fail����
    int val[MAXNODE];//ÿ���ַ����Ľ�β��㶼�з�0��val
    int num;//trie����ţ���Ϊ���������ĵ�ǰsize��
    //��ʼ��
    void init()
    {
        num=1;
        memset(ch[0],-1,sizeof(ch[0]));
    }
    //�����ַ���Ӧ���
    int idx(char c)
    {
        return c-'a';
    }
    //����ȨֵΪv���ַ���
    void insert(char *s,int v)
    {
        int u=0,n=strlen(s);
        for(int i=0;i<n;i++)
        {
            int c=idx(s[i]);
            if(ch[u][c]==-1)
            {
                memset(ch[num],-1,sizeof(ch[num]));
                val[num]=0;
                ch[u][c]=num++;
            }
            u=ch[u][c];
        }
        val[u]|=v;
    }
    //����fail����
    void getFail()
    {
        queue <int> que;
        f[0]=0;
        for(int c=0;c<SIGMA_SIZE;c++)
        {
            int u=ch[0][c];
            if(u!=-1)
            {
                f[u]=0;que.push(u);
            }
            else ch[0][c]=0;
        }
        while(!que.empty())
        {
            int r=que.front();que.pop();
            if(val[f[r]])
                val[r]|=val[f[r]];
            for(int c=0;c<SIGMA_SIZE;c++)
            {
                int u=ch[r][c];
                if(u==-1){ch[r][c]=ch[f[r]][c];continue;}
                que.push(u);
                int v=f[r];
//                while(v&&ch[v][c]==-1)//����kmp�Ĺ���
//                    v=f[v];
                f[u]=ch[v][c];
            }
        }
    }
}AC;
int n,m,k;
char tem[20];
ll dp[26][105][1024];
ll num[1024],an;
int main()
{
    num[0]=0;
    for(int i=1;i<1024;i++)num[i]=num[i>>1]+(i&1);
    while(scanf("%d%d%d",&n,&m,&k)&&n)
    {
        int tot=(1<<m);
        AC.init();
        an=0;
        for(int i=1;i<=m;i++){scanf("%s",tem);AC.insert(tem,1<<(i-1));}
        AC.getFail();
        for(int i=0;i<=n;i++)
            for(int j=0;j<=AC.num;j++)
                for(int s=0;s<=tot;s++)dp[i][j][s]=0;
        dp[0][0][0]=1;
        for(int i=0;i<n;i++)//����
            for(int j=0;j<AC.num;j++)//��ǰλ��
                for(int s=0;s<tot;s++)//��ǰ״̬
                {
                    if(!dp[i][j][s])continue;//�޵�ǰ״̬
                    for(int k=0;k<26;k++)
                    {
                        dp[i+1][AC.ch[j][k]][s|AC.val[AC.ch[j][k]]]+=dp[i][j][s];
                        dp[i+1][AC.ch[j][k]][s|AC.val[AC.ch[j][k]]]%=MOD;
                    }
                }
        for(int s=0;s<tot;s++)
        {
            if(num[s]<k)continue;
            for(int i=0;i<AC.num;i++)
                an=(an+dp[n][i][s])%MOD;
        }
        printf("%lld\n",an);
    }
    return 0;
}
