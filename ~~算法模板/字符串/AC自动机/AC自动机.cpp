const int SIGMA_SIZE=26;
const int MAXNODE=11000;
/*
    ����ʧ����̱Ƚϸ��ӣ�Ҫ��������ʧ����ߣ�
    ��ʵ���г�����������Զ�������һ�£������в����ڵıߡ����ϡ�
    ���Ѽ���ʧ�亯���е����if(!u)continue;�ĳ�
    if(!u){ch[r][c]=ch[f[r]][c];continue;}
    ��
    P.S.
        ������һֱ��last[u]=����֮ǰΪ
        if(!u){ch[r][c]=ch[f[r]][c];continue;}
        else
        {
            que.push(u);
            int v=f[r];
            while(v&&!ch[v][c])//����kmp�Ĺ���
                v=f[v];
            f[u]=ch[v][c];
        }

        ��Ϊͼ�����о��㲻���ڵı�Ҳ��������
        ������������������в����ڵı�
        ������BFSǰ �� while(!que.empty()) ǰforѭ����ӦΪ
            if(u)
            {
                f[u]=0;que.push(u);last[u]=0;
            }
            else
                ch[0][c]=0;
        ����������
            ���ϴ��벢����ȷ ��Ϊ�����б�ʱch��ʼ��ӦΪ-1  u���жϴ���ע�⣨ԭ����0���������壩
        ��
    ��
    ����������ȫ����Ҫʧ�亯�������Ƕ�����ת��һ��ͬ��
    ��find�����е�while(j&&!ch[j][c])j=f[j] ����ֱ��ɾ��

*/
struct AhoCorasickAutomata
{
    int ch[MAXNODE][SIGMA_SIZE];//Trie��
    int f[MAXNODE];//fail����
    int val[MAXNODE];//ÿ���ַ����Ľ�β��㶼�з�0��val
    int last[MAXNODE];//����������һ�����ʽ��
    int num;//trie����ţ���Ϊ���������ĵ�ǰsize��
    //��ʼ��
    void init()
    {
        num=1;
        memset(ch[0],0,sizeof(ch[0]));
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
            if(!ch[u][c])
            {
                memset(ch[num],0,sizeof(ch[num]));
                val[num]=0;
                ch[u][c]=num++;
            }
            u=ch[u][c];
        }
        val[u]=v;
    }
    //�ݹ��ӡ�Խ��j��β�������ַ���
    void print(int j)
    {
        if(j)
        {
            printf("%d %d\n",j,val[j]);
            print(last[j]);
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
            if(u)
            {
                f[u]=0;que.push(u);last[u]=0;
            }
        }
        while(!que.empty())
        {
            int r=que.front();que.pop();
            for(int c=0;c<SIGMA_SIZE;c++)
            {
                int u=ch[r][c];
                if(!u)
                    continue;
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
            while(u&&!ch[u][c])u=f[u];//˳��ʧ��ָ���ߣ�ֱ������ƥ���ص����ڵ�
            u=ch[u][c];
            if(val[u])
                print(u);
            else if(last[u])//������ �����ǰǡΪĳ��ĩβ ��ֱ��print���俪ʼ ��Ȼ�ӵ�ǰ��׺��Ϊĳ����λ�ÿ�ʼprint
                print(last[u]);
        }
    }
};



/*
΢���� ��������ͼ AC�Զ���
*/
const int SIGMA_SIZE=2;
const int MAXNODE=2505;
struct AhoCorasickAutomata
{
    int ch[MAXNODE][SIGMA_SIZE];//Trie��
    int f[MAXNODE];//fail����
    int val[MAXNODE];//ÿ���ַ����Ľ�β��㶼�з�0��val
    int last[MAXNODE];//����������һ�����ʽ��
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
        return c=='R'?0:1;
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
        val[u]=v;
    }
    //�ݹ��ӡ�Խ��j��β�������ַ���
    void print(int j)
    {
        if(j)
        {
            printf("%d %d\n",j,val[j]);
            print(last[j]);
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
            if(val[f[r]])val[r]+=val[f[r]];
            for(int c=0;c<SIGMA_SIZE;c++)
            {
                int u=ch[r][c];
                if(u==-1){ch[r][c]=ch[f[r]][c];continue;}
                que.push(u);
                f[u]=ch[f[r]][c];
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
            while(u&&!ch[u][c])u=f[u];//˳��ʧ��ָ���ߣ�ֱ������ƥ���ص����ڵ�
            u=ch[u][c];
            if(val[u])
                print(u);
            else if(last[u])//������ �����ǰǡΪĳ��ĩβ ��ֱ��print���俪ʼ ��Ȼ�ӵ�ǰ��׺��Ϊĳ����λ�ÿ�ʼprint
                print(last[u]);
        }
    }
}AC;
