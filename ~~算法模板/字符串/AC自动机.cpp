const int SIGMA_SIZE=26;
const int MAXNODE=11000;
/*
    由于失配过程比较复杂，要反复沿着失配边走，
    在实践中常常会把下述自动机改造一下，把所有不存在的边“补上”
    即把计算失配函数中的语句if(!u)continue;改成
    if(!u){ch[r][c]=ch[f[r]][c];continue;}
    （
    P.S.
        完整的一直到last[u]=……之前为
        if(!u){ch[r][c]=ch[f[r]][c];continue;}
        else
        {
            que.push(u);
            int v=f[r];
            while(v&&!ch[v][c])//类似kmp的过程
                v=f[v];
            f[u]=ch[v][c];
        }

        因为图中所有就算不存在的边也都连上了
        ！！并且如果补上所有不存在的边
        在真正BFS前 即 while(!que.empty()) 前for循环中应为
            if(u)
            {
                f[u]=0;que.push(u);last[u]=0;
            }
            else
                ch[0][c]=0;
        （！！！！
            以上代码并不正确 因为连所有边时ch初始化应为-1  u的判断处需注意（原点编号0，避免歧义）
        ）
    ）
    这样，就完全不需要失配函数，而是对所有转移一视同仁
    即find函数中的while(j&&!ch[j][c])j=f[j] 可以直接删除

*/
struct AhoCorasickAutomata
{
    int ch[MAXNODE][SIGMA_SIZE];//Trie树
    int f[MAXNODE];//fail函数
    int val[MAXNODE];//每个字符串的结尾结点都有非0的val
    int last[MAXNODE];//输出链表的下一个单词结点
    int num;//trie树编号（亦为包含根结点的当前size）
    //初始化
    void init()
    {
        num=1;
        memset(ch[0],0,sizeof(ch[0]));
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
    //递归打印以结点j结尾的所有字符串
    void print(int j)
    {
        if(j)
        {
            printf("%d %d\n",j,val[j]);
            print(last[j]);
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
            while(u&&!ch[u][c])u=f[u];//顺着失配指针走，直到可以匹配或回到根节点
            u=ch[u][c];
            if(val[u])
                print(u);
            else if(last[u])//明白了 如果当前恰为某串末尾 则直接print从其开始 不然从当前后缀作为某串的位置开始print
                print(last[u]);
        }
    }
};



/*
微调版 完整有向图 AC自动机
*/
const int SIGMA_SIZE=2;
const int MAXNODE=2505;
struct AhoCorasickAutomata
{
    int ch[MAXNODE][SIGMA_SIZE];//Trie树
    int f[MAXNODE];//fail函数
    int val[MAXNODE];//每个字符串的结尾结点都有非0的val
    int last[MAXNODE];//输出链表的下一个单词结点
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
        return c=='R'?0:1;
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
        val[u]=v;
    }
    //递归打印以结点j结尾的所有字符串
    void print(int j)
    {
        if(j)
        {
            printf("%d %d\n",j,val[j]);
            print(last[j]);
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
    //在T中中模板
    int find(char *T)
    {
        int n=strlen(T);
        int u=0;//当前结点编号,初始为根结点
        for(int i=0;i<n;i++)//文本串当前指针
        {
            int c=idx(T[i]);
            while(u&&!ch[u][c])u=f[u];//顺着失配指针走，直到可以匹配或回到根节点
            u=ch[u][c];
            if(val[u])
                print(u);
            else if(last[u])//明白了 如果当前恰为某串末尾 则直接print从其开始 不然从当前后缀作为某串的位置开始print
                print(last[u]);
        }
    }
}AC;
