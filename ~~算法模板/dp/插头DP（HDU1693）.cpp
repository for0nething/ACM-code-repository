/*
    HDU 1693
    ���⣺��n*m�ľ����У���Щ����������û�����ĸ��Ӳ��ܵ��
    ��һ���������·���������е��������ж����з�����
*/

const int HASH=10007;
const int STATE=1000010;
const int MAXD=15;
int N,M;
int code[MAXD],maze[MAXD][MAXD];
struct HASHMAP
{
    int head[HASH],next[STATE],state[STATE],size;//������ʽ headͨ��ȡģ������һ������ ��߲�ѯЧ��
    long long f[STATE];//��ĳ״̬�ĸ���
    void init()
    {
        size=0;memset(head,-1,sizeof(head));
    }
    void push(int st,long long ans)//�ﵽ��i��״̬�ķ�ʽ��ans��
    {
        int i,h=st%HASH;//hΪ��ϣ����ı��� ��Ϊ����
        for(i=head[h];i!=-1;i=next[i])
            if(st==state[i])//���ɹ��ҵ�
            {
                f[i]+=ans;
                return;
            }
        //δ�ҵ������Լ�����
        f[size]=ans;//�ﵽ��״̬�ķ�������Ϊans
        state[size]=st;//��������
        next[size]=head[h];
        head[h]=size++;
    }
}hm[2];//�������飬��ʡ�ռ�
/*
    ��st���н��룬�����������code�����У��䳤��Ϊm
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
    ����ǰ�ĳ���Ϊm��code������б���
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
    ����Ϊͨ�õĶ��뺯��
    ע����Ҫ���Ҳࡢ�²߽߱���һȦ�����ɡ��������
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
    ���е�ʱ����λ
*/
void shift(int *code,int m)
{
    int i;
    for(i=m;i>0;i--)code[i]=code[i-1];
    code[0]=0;
}
/*
    ������Էŵĸ���
    i�У�j�У���ǰ���������״̬
*/
void dpblank(int i,int j,int cur)
{
    int k,left,up;
    for(k=0;k<hm[cur].size;k++)
    {
        decode(code,M,hm[cur].state[k]);
        left=code[j-1];//����Ƿ�����
        up=code[j];//�ϲ��Ƿ�����
        if(left&&up)//11 -> 00
        {
            code[j-1]=code[j]=0;
            if(j==M)shift(code,M);
            hm[cur^1].push(encode(code,M),hm[cur].f[k]);
        }
        else if(left||up)//01 �� 10
        {
            if(maze[i][j+1])//�������Ҳ��� ���Ҳ����漰���� ����shift
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
        else//00 -> 11 ����������������
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
    ���ܷŵĸ���
    i�У�j�У���ǰ���������״̬
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
    hm[cur].push(0,1);//dpǰ��ʼ�� ��״̬0�ĸ���Ϊ1�������£�
    for(i=1;i<=N;i++)
        for(j=1;j<=M;j++)
        {
            hm[cur^1].init();//��������ĳ�ʼ��
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
