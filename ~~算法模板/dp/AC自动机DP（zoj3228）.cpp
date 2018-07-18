/*
    ZOJ 3228
    题目大意：首先给你一下母串，长度不超过10^5，然后有 N（10^5） 次查询，
    每次查询有两种命令，0或者1，然后加一个子串，询问母串里面有多少个子串，
    0表示可以重复，1表示不可以重复。

*/
int cnt[MAX][2];
int las[MAX];
const int SIGMA_SIZE=26;
const int MAXNODE=610000;
struct AhoCorasickAutomata
{
    int ch[MAXNODE][SIGMA_SIZE];//Trie树
    int f[MAXNODE];//fail函数
    int val[MAXNODE];//每个字符串的结尾结点都有非0的val
    int last[MAXNODE];//输出链表的下一个单词结点
    int dep[MAXNODE];
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
    //递归打印以结点j结尾的所有字符串
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
                while(v&&!ch[v][c])//类似kmp的过程
                    v=f[v];
                f[u]=ch[v][c];
                last[u]=val[f[u]]?f[u]:last[f[u]];
            }
        }
    }
    //在T中中模板
    int find(char *T)
    {
        int n=strlen(T);
        int u=0;//当前结点编号,初始为根结点
        for(int i=0;i<n;i++)//文本串当前指针
        {
            int c=idx(T[i]);
//            while(u&&!ch[u][c])u=f[u];//顺着失配指针走，直到可以匹配或回到根节点
            u=ch[u][c];
            if(val[u])
                print(u,i);
            else if(last[u])//明白了 如果当前恰为某串末尾 则直接print从其开始 不然从当前后缀作为某串的位置开始print
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
