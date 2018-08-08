/*
    �������ͷDPģ��
    URAL1519
    ��Ŀ���⣺
    ����һ��m * n�����̣��еĸ������ϰ����ʹ��ж�������·ʹ�þ���ÿ�����ϰ�����ǡ��һ�Σ�m, n �� 12��
*/
const int HASH=30007;
const int STATE=1000010;
const int MAXD=15;
int N,M,ex,ey;//ex\ey�Ǳ���
int code[MAXD],maze[MAXD][MAXD];
int ch[MAXD];
struct HASHMAP
{
    int head[HASH],next[STATE],size;//������ʽ headͨ��ȡģ������һ������ ��߲�ѯЧ��
    long long f[STATE],state[STATE];//��ĳ״̬�ĸ���
    void init()
    {
        size=0;memset(head,-1,sizeof(head));
    }
    void push(long long st,long long ans)//�ﵽ��i��״̬�ķ�ʽ��ans��
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
    ����ǰ�ĳ���Ϊm��code������б���
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
    ����Ϊͨ�õĶ��뺯��
    ע����Ҫ���Ҳࡢ�²߽߱���һȦ�����ɡ��������
*/
char lin[20];
/*
    �������ݣ���״̬ͼ��¼��maze��
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
    ���е�ʱ����λ
    ����ı�code���� ���Բ��� encode(code,j==M?M-1:M);�ķ�ʽ
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
        left=code[j-1];//����Ƿ����� ������ͨ���
        up=code[j];//�ϲ��Ƿ����� ������ͨ���
        if(left&&up)//11 -> 00
        {
            if(left==up)//�����Ѿ���ͨ
            {
                if(i==ex&&j==ey)
                {
                    code[j-1]=code[j]=0;
                    if(j==M)shift(code,M);
                    hm[cur^1].push(encode(code,M),hm[cur].f[k]);
                }
            }
            else//���ϲ�δ��ͨ ��ϲ�
            {
                code[j-1]=code[j]=0;
                for(int s=0;s<=M;s++)
                    if(code[s]==up)code[s]=left;
                if(j==M)shift(code,M);
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
        }
        else if(left||up)//01 �� 10
        {
            int t=left?left:up;
            if(maze[i][j+1])//�������Ҳ��� ���Ҳ����漰���� ����shift
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
        else//00 -> 11 ����������������
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
