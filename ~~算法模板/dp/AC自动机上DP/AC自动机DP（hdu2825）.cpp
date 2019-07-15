/*
    HDU 2825
    题意：
    给 m 个单词构成的集合，统计所有长度为 n 的串中，包含至少 k 个单词的方案数。
*/


const int SIGMA_SIZE=26;
const int MAXNODE=110;
struct AhoCorasickAutomata
{
    int ch[MAXNODE][SIGMA_SIZE];//Trie树
    int f[MAXNODE];//fail函数
    int val[MAXNODE];//每个字符串的结尾结点都有非0的val
    int num;//trie树编号（亦为包含根结点的当前size）
    //初始化
    void init()
    {
        num=1;
        memset(ch[0],-1,sizeof(ch[0]));
    }
    //返回字符对应编号
    int idx(char c)
    {
        return c-'a';
    }
    //插入权值为v的字符串
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
    //计算fail函数
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
//                while(v&&ch[v][c]==-1)//类似kmp的过程
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
        for(int i=0;i<n;i++)//步数
            for(int j=0;j<AC.num;j++)//当前位置
                for(int s=0;s<tot;s++)//当前状态
                {
                    if(!dp[i][j][s])continue;//无当前状态
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
