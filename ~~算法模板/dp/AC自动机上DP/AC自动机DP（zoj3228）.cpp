/*
    ZOJ 3228
    ��Ŀ���⣺���ȸ���һ��ĸ�������Ȳ�����10^5��Ȼ���� N��10^5�� �β�ѯ��
    ÿ�β�ѯ���������0����1��Ȼ���һ���Ӵ���ѯ��ĸ�������ж��ٸ��Ӵ���
    0��ʾ�����ظ���1��ʾ�������ظ���

*/
int cnt[MAX][2];
int las[MAX];
const int SIGMA_SIZE=26;
const int MAXNODE=610000;
struct AhoCorasickAutomata
{
    int ch[MAXNODE][SIGMA_SIZE];//Trie��
    int f[MAXNODE];//fail����
    int val[MAXNODE];//ÿ���ַ����Ľ�β��㶼�з�0��val
    int last[MAXNODE];//����������һ�����ʽ��
    int dep[MAXNODE];
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
    int insert(char *s,int& v)
    {
        int u=0,n=strlen(s);
        for(int i=0;i<n;i++)
        {
            int c=idx(s[i]);
            if(ch[u][c]==-1)
            {
                memset(ch[num],-1,sizeof(ch[num]));
                val[num]=0;
                dep[num]=dep[u]+1;
                ch[u][c]=num++;
            }
            u=ch[u][c];
        }
        if(!val[u])
        val[u]=++v;
        return val[u];
    }
    //�ݹ��ӡ�Խ��j��β�������ַ���
    void print(int j,int pos)
    {
        if(j)
        {
            cnt[val[j]][0]++;
            if(las[val[j]]==-1||las[val[j]]+dep[j]<=pos)
            {
                las[val[j]]=pos;
                cnt[val[j]][1]++;
            }
            print(last[j],pos);
        }
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
                f[u]=0;que.push(u);last[u]=0;
            }
            else
                ch[0][c]=0;
        }
        while(!que.empty())
        {
            int r=que.front();que.pop();
//            if(val[f[r]]&&)val[r]
            for(int c=0;c<SIGMA_SIZE;c++)
            {
                int u=ch[r][c];
//                if(u==-1)continue;
                if(u==-1){ch[r][c]=ch[f[r]][c];continue;}
                que.push(u);
                int v=f[r];
                while(v&&!ch[v][c])//����kmp�Ĺ���
                    v=f[v];
                f[u]=ch[v][c];
                last[u]=val[f[u]]?f[u]:last[f[u]];
            }
        }
    }
    //��T����ģ��
    int find(char *T)
    {
        int n=strlen(T);
        int u=0;//��ǰ�����,��ʼΪ�����
        for(int i=0;i<n;i++)//�ı�����ǰָ��
        {
            int c=idx(T[i]);
//            while(u&&!ch[u][c])u=f[u];//˳��ʧ��ָ���ߣ�ֱ������ƥ���ص����ڵ�
            u=ch[u][c];
            if(val[u])
                print(u,i);
            else if(last[u])//������ �����ǰǡΪĳ��ĩβ ��ֱ��print���俪ʼ ��Ȼ�ӵ�ǰ��׺��Ϊĳ����λ�ÿ�ʼprint
                print(last[u],i);
        }
    }
}AC;

char a[MAX];
int n,num;
int kind[MAX],id[MAX],Case;
char tem[30];
int main()
{
    while(~scanf("%s",a))
    {
        AC.init();
        num=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&kind[i]);
            scanf("%s",tem);
            id[i]=AC.insert(tem,num);
        }
        AC.getFail();
        for(int i=0;i<=num;i++)
            las[i]=-1;
        for(int i=0;i<=num;i++)
            for(int j=0;j<=1;j++)cnt[i][j]=0;
        AC.find(a);
        printf("Case %d\n",++Case);
        for(int i=1;i<=n;i++)
            printf("%d\n",cnt[id[i]][kind[i]]);
        printf("\n");
    }
}
