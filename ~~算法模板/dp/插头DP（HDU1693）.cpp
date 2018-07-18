/*
    HDU 1693
    题意：在n*m的矩阵中，有些格子有树，没有树的格子不能到达，
    找一条或多条回路，吃完所有的树，求有多少中方法。
*/

const int HASH=10007;
const int STATE=1000010;
const int MAXD=15;
int N,M;
int code[MAXD],maze[MAXD][MAXD];
struct HASHMAP
{
    int head[HASH],next[STATE],state[STATE],size;//链表形式 head通过取模进行了一种索引 提高查询效率
    long long f[STATE];//到某状态的个数
    void init()
    {
        size=0;memset(head,-1,sizeof(head));
    }
    void push(int st,long long ans)//达到第i种状态的方式加ans个
    {
        int i,h=st%HASH;//h为哈希过后的编码 作为索引
        for(i=head[h];i!=-1;i=next[i])
            if(st==state[i])//若成功找到
            {
                f[i]+=ans;
                return;
            }
        //未找到，需自己创建
        f[size]=ans;//达到该状态的方法数即为ans
        state[size]=st;//其具体编码
        next[size]=head[h];
        head[h]=size++;
    }
}hm[2];//滚动数组，节省空间
/*
    对st进行解码，将结果保存在code数组中，其长度为m
*/
void decode(int *code,int m,int st)
{
    int i;
    for(i=m;i>=0;i--)
    {
        code[i]=st&1;
        st>>=1;
    }
}
/*
    将当前的长度为m的code数组进行编码
*/
int encode(int *code,int m)
{
    int i,st=0;
    for(i=0;i<=m;i++)
    {
        st<<=1;st|=code[i];
    }
    return st;
}
/*
    可作为通用的读入函数
    注意需要在右侧、下策边界设一圈代表不可“到达”的数
*/
void init()
{
    int i,j;
    scanf("%d%d",&N,&M);
    for(i=1;i<=N;i++)
        for(j=1;j<=M;j++)
            scanf("%d",&maze[i][j]);
    for(int i=1;i<=N;i++)maze[i][M+1]=0;
    for(int i=1;i<=M;i++)maze[N+1][i]=0;
}
/*
    换行的时候移位
*/
void shift(int *code,int m)
{
    int i;
    for(i=m;i>0;i--)code[i]=code[i-1];
    code[0]=0;
}
/*
    处理可以放的格子
    i行，j列，当前滚动数组的状态
*/
void dpblank(int i,int j,int cur)
{
    int k,left,up;
    for(k=0;k<hm[cur].size;k++)
    {
        decode(code,M,hm[cur].state[k]);
        left=code[j-1];//左侧是否有连
        up=code[j];//上侧是否有连
        if(left&&up)//11 -> 00
        {
            code[j-1]=code[j]=0;
            if(j==M)shift(code,M);
            hm[cur^1].push(encode(code,M),hm[cur].f[k]);
        }
        else if(left||up)//01 或 10
        {
            if(maze[i][j+1])//可以向右侧连 并且并不涉及换行 无需shift
            {
                code[j-1]=0;code[j]=1;
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
            if(maze[i+1][j])
            {
                code[j-1]=1;code[j]=0;
                if(j==M)shift(code,M);
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
        }
        else//00 -> 11 必须两个都可以连
        {
            if(maze[i][j+1]&&maze[i+1][j])
            {
                code[j]=code[j-1]=1;
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
        }
    }
}
/*
    不能放的格子
    i行，j列，当前滚动数组的状态
*/
void dpblock(int i,int j,int cur)
{
    int k;
    for(k=0;k<hm[cur].size;k++)
    {
        decode(code,M,hm[cur].state[k]);
        code[j-1]=code[j]=0;
        if(j==M)shift(code,M);
        hm[cur^1].push(encode(code,M),hm[cur].f[k]);
    }
}
void solve()
{
    int i,j,cur=0;
    long long ans=0;
    hm[cur].init();
    hm[cur].push(0,1);//dp前初始化 仅状态0的个数为1（即当下）
    for(i=1;i<=N;i++)
        for(j=1;j<=M;j++)
        {
            hm[cur^1].init();//滚动数组的初始化
            if(maze[i][j])dpblank(i,j,cur);
            else dpblock(i,j,cur);
            cur^=1;
        }
    for(i=0;i<hm[cur].size;i++)
        ans+=hm[cur].f[i];
    printf("There are %I64d ways to eat the trees.\n",ans);
}
int main()
{
    int T;
    int iCase=0;
    scanf("%d",&T);
    while(T--)
    {
        iCase++;
        printf("Case %d: ",iCase);
        init();
        solve();
    }
    return 0;
}

/*

*/
