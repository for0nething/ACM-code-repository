/*
    完整版插头DP模版
    URAL1519
    题目简意：
    给你一个m * n的棋盘，有的格子是障碍，问共有多少条回路使得经过每个非障碍格子恰好一次．m, n ≤ 12。
*/
const int HASH=30007;
const int STATE=1000010;
const int MAXD=15;
int N,M,ex,ey;//ex\ey非必需
int code[MAXD],maze[MAXD][MAXD];
int ch[MAXD];
struct HASHMAP
{
    int head[HASH],next[STATE],size;//链表形式 head通过取模进行了一种索引 提高查询效率
    long long f[STATE],state[STATE];//到某状态的个数
    void init()
    {
        size=0;memset(head,-1,sizeof(head));
    }
    void push(long long st,long long ans)//达到第i种状态的方式加ans个
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
void decode(int *code,int m,long long st)
{
    int i;
    for(i=m;i>=0;i--)
    {
        code[i]=st&7;
        st>>=3;
    }
}
/*
    将当前的长度为m的code数组进行编码
*/
long long encode(int *code,int m)
{
    int i;
    int cnt=1;
    memset(ch,-1,sizeof(ch));
    ch[0]=0;
    ll st=0;
    for(i=0;i<=m;i++)
    {
        if(ch[code[i]]==-1)ch[code[i]]=cnt++;
        code[i]=ch[code[i]];
        st<<=3;
        st|=code[i];
    }
    return st;
}
/*
    可作为通用的读入函数
    注意需要在右侧、下策边界设一圈代表不可“到达”的数
*/
char lin[20];
/*
    读入数据，将状态图记录在maze中
*/
void init()
{
    ex=ey=0;
    memset(maze,0,sizeof(maze));
    for(int i=1;i<=N;i++)
    {
        scanf("%s",lin);
        for(int j=0;j<M;j++)
            if(lin[j]=='.'){maze[i][j+1]=1;ex=i;ey=j+1;}
    }
}
/*
    换行的时候移位
    不想改变code数组 可以采用 encode(code,j==M?M-1:M);的方式
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
        left=code[j-1];//左侧是否有连 及其连通编号
        up=code[j];//上侧是否有连 及其连通编号
        if(left&&up)//11 -> 00
        {
            if(left==up)//左、上已经连通
            {
                if(i==ex&&j==ey)
                {
                    code[j-1]=code[j]=0;
                    if(j==M)shift(code,M);
                    hm[cur^1].push(encode(code,M),hm[cur].f[k]);
                }
            }
            else//左、上并未连通 则合并
            {
                code[j-1]=code[j]=0;
                for(int s=0;s<=M;s++)
                    if(code[s]==up)code[s]=left;
                if(j==M)shift(code,M);
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
        }
        else if(left||up)//01 或 10
        {
            int t=left?left:up;
            if(maze[i][j+1])//可以向右侧连 并且并不涉及换行 无需shift
            {
                code[j-1]=0;code[j]=t;
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
            if(maze[i+1][j])
            {
                code[j-1]=t;code[j]=0;
                if(j==M)shift(code,M);
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
        }
        else//00 -> 11 必须两个都可以连
        {
            if(maze[i][j+1]&&maze[i+1][j])
            {
                code[j]=code[j-1]=13;
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
    printf("%I64d\n",ans);
}
int main()
{
    while(~scanf("%d%d",&N,&M))
    {
        init();
        if(!ex)
            printf("0\n");
        else solve();
    }
    return 0;
}

/*

*/
