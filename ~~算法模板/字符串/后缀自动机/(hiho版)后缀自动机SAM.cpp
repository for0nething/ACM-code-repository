/*
    ģ�沿��
*/
const int MAXL=2000005;
const int MAXCH=26;
char s[MAXL];
char CH='a';
int tot=0;//totΪ�ܽ����
int maxlen[MAXL],minlen[MAXL],trans[MAXL][MAXCH],slink[MAXL];
/*
    һЩ�Ǳ�Ҫ�Ĺ�������
    ��ȥ�� �����ں������޸�
*/
int ind[MAXL];//�����ӽڵ����
int edpts[MAXL];//����endpos����
bool pre[MAXL];//�Ƿ�Ϊǰ׺���ڽ��
/*
    �����½��ĺ��� δ֪��ֵ�� ֵ����-1���� δ֪��ֵ������ ����NULL����
*/
int new_state(int _maxlen,int _minlen,int *_trans,int _slink)
{
    maxlen[tot]=_maxlen;
    minlen[tot]=_minlen;
    for(int i=0;i<MAXCH;i++)
    {
        if(_trans==NULL)
            trans[tot][i]=-1;
        else trans[tot][i]=_trans[i];
    }
    slink[tot]=_slink;
    return tot++;
}
/*
    ��u��������ַ�ch
*/
int add_char(char ch,int u)
{
    int c=ch-CH;
    /*
    �������Զ���������һ������ �ص�root��0��
    ֮����������һ�в����޸�
    ����� (2018.8.3UPD:��ȫ���ü���仰��)
    if(trans[u][c]!=-1&&maxlen[trans[u][c]]==maxlen[u]+1)return trans[u][c];
    ��û��if�ɹ��������������
    ��������֮ǰ�Ĵ�����ʶ�����˸о������жϻ��һЩ ��Ȼ�����maxlen<minlen����ֵĵ㣨e.g. ��������"a"���������
    */
    int z=new_state(maxlen[u]+1,-1,NULL,-1);
    pre[z]=true;//�ý���Ϊ����ԭ��ǰ׺�Ľ��
    int v=u;
    while(v!=-1&&trans[v][c]==-1)
    {
        trans[v][c]=z;
        v=slink[v];
    }
    if(v==-1)//��򵥵������suffix-path(u->s)�϶�û�ж�Ӧ�ַ�ch��ת��
    {
        minlen[z]=1;
        slink[z]=0;
        ++ind[0];
        return z;
    }
    int x=trans[v][c];
    if(maxlen[v]+1==maxlen[x])//�ϼ򵥵���������ò��x
    {
        minlen[z]=maxlen[x]+1;
        slink[z]=x;
        ++ind[x];
        return z;
    }
    int y=new_state(maxlen[v]+1,-1,trans[x],slink[x]);//��ӵ���������x
    slink[y]=slink[x];
    ind[y]+=2;
    minlen[x]=maxlen[y]+1;
    slink[x]=y;
    minlen[z]=maxlen[y]+1;
    slink[z]=y;
    int w=v;
    while(w!=-1&&trans[w][c]==x)//�ò����ַ�������Խ��Խ�� һ������Ҫת�Ƶ�y�� ��Ϊy��������xԭ���϶̵Ĳ���
    {
        trans[w][c]=y;
        w=slink[w];
    }
    minlen[y]=maxlen[slink[y]]+1;
    return z;
}
/*
    ��������
    ���ÿ������endpos����
    ����topsort�Ǵ�Ҷ�ӽ�����ϵ����� �����дӸ��ڵ����µ�����
*/
void getEndPtCount() {
    queue<int> q;
    for(int i=1;i<tot;i++)
    if(!ind[i])
        q.push(i);
    while( !q.empty() ) {
        int u = q.front();
        q.pop();
        if(pre[u])edpts[u]++;
        edpts[ slink[u]] += edpts[u];
        if( !--ind[slink[u]] ) q.push(slink[u]);
    }
}
/*
    ��һ��toposort
*/
void toposort()
{
    for(int i=0;i<=n;i++)cnt[i]=0;
    for(int i=1;i<tot;i++)
        ++cnt[maxlen[i]];
    for(int i=1;i<=n;i++)
        cnt[i]+=cnt[i-1];
    for(int i=tot-1;i>0;--i)
        lo[cnt[maxlen[i]]--]=i;
}
/*
    ʹ��ʾ����
    ����ַ��������в�ͬ�Ӵ�����  hihocoder 1445
    & ����ַ�����ÿ�������Ӵ��������Ĵ��� hihocoder 1449
*/
int anlen[MAXL];
int n;
ll an;
int main()
{
    /*
        ��ʼ������
    */
    int pres=new_state(0,0,NULL,-1);
//    memset(trans,-1,sizeof(trans));
//    memset(slink,-1,sizeof(slink));
    /*
        ͨ�ù��̴��벿��
    */
    scanf("%s",s);
//    tot=1;//tot=0�ı�ʾ�մ��Ľ�� ��������tot=1 ʹ���½���1��ʼ���
    n=strlen(s);
    for(int i=0;i<n;i++)
        pres=add_char(s[i],pres);//���������

    /*
        ����ַ��������в�ͬ�Ӵ�����
    */
    for(int i=1;i<tot;i++)//���н���±귶ΧΪ [0,tot) 0Ϊ�մ���� �ʴ�1��ʼ����
        an+=1LL*maxlen[i]-minlen[i]+1;
    printf("%lld\n",an);

    /*
        ����ַ�����ÿ�������Ӵ��������Ĵ���
    */
    getEndPtCount();
    for(int i=1;i<tot;i++)//���н���±귶ΧΪ [0,tot) 0Ϊ�մ���� �ʴ�1��ʼ����
        anlen[maxlen[i]]=max(anlen[maxlen[i]],edpts[i]);
    for(int i=n;i>=1;i--)
        anlen[i]=max(anlen[i],anlen[i+1]);
    for(int i=1;i<=n;i++)
        printf("%d\n",anlen[i]);
}






/*
    ���ڵ�����topsort������
    hihocoder 1457
*/
const int MAXL=2000005;
const int MAXCH=11;
string s,tem;
char CH='0';
int tot=0;//totΪ�ܽ����
int maxlen[MAXL],minlen[MAXL],trans[MAXL][MAXCH],slink[MAXL];
/*
    һЩ�Ǳ�Ҫ�Ĺ�������
    ��ȥ�� �����ں������޸�
*/
int ind[MAXL];//�����ӽڵ����
int edpts[MAXL];//����endpos����
bool pre[MAXL];//�Ƿ�Ϊǰ׺���ڽ��
/*
    �����½��ĺ��� δ֪��ֵ�� ֵ����-1���� δ֪��ֵ������ ����NULL����
*/
int new_state(int _maxlen,int _minlen,int *_trans,int _slink)
{
    maxlen[tot]=_maxlen;
    minlen[tot]=_minlen;
    for(int i=0;i<MAXCH;i++)
    {
        if(_trans==NULL)
            trans[tot][i]=-1;
        else trans[tot][i]=_trans[i];
    }
    slink[tot]=_slink;
    return tot++;
}
/*
    ��u��������ַ�ch
*/
int add_char(char ch,int u)
{
    int c=ch-CH;
    int z=new_state(maxlen[u]+1,-1,NULL,-1);
    pre[z]=true;//�ý���Ϊ����ԭ��ǰ׺�Ľ��
    int v=u;
    while(v!=-1&&trans[v][c]==-1)
    {
        trans[v][c]=z;
        v=slink[v];
    }
    if(v==-1)//��򵥵������suffix-path(u->s)�϶�û�ж�Ӧ�ַ�ch��ת��
    {
        minlen[z]=1;
        slink[z]=0;
        ++ind[0];
        return z;
    }
    int x=trans[v][c];
    if(maxlen[v]+1==maxlen[x])//�ϼ򵥵���������ò��x
    {
        minlen[z]=maxlen[x]+1;
        slink[z]=x;
        ++ind[x];
        return z;
    }
    int y=new_state(maxlen[v]+1,-1,trans[x],slink[x]);//��ӵ���������x
    slink[y]=slink[x];
    ind[y]+=2;
    minlen[x]=maxlen[y]+1;
    slink[x]=y;
    minlen[z]=maxlen[y]+1;
    slink[z]=y;
    int w=v;
    while(w!=-1&&trans[w][c]==x)//�ò����ַ�������Խ��Խ�� һ������Ҫת�Ƶ�y�� ��Ϊy��������xԭ���϶̵Ĳ���
    {
        trans[w][c]=y;
        w=slink[w];
    }
    minlen[y]=maxlen[slink[y]]+1;
    return z;
}
/*
    ��������
    ���ÿ������endpos����
*/
void getEndPtCount() {
    queue<int> q;
    for(int i=1;i<tot;i++)
    if(!ind[i])
        q.push(i);
    while( !q.empty() ) {
        int u = q.front();
        q.pop();
        if(pre[u])edpts[u]++;
        edpts[ slink[u]] += edpts[u];
        if( !--ind[slink[u]] ) q.push(slink[u]);
    }
}
/*
    ʹ��ʾ����
    ����ַ��������в�ͬ�Ӵ�����
    & ����ַ�����ÿ�������Ӵ��������Ĵ���
*/

int cnt[MAXL];
ll val_num[MAXL];//��ÿ�����valid�ĸ���
ll sum[MAXL];//ÿ�����ĺ�
void init_dag()
{
    for(int i=0;i<=tot;i++)
        for(int j=0;j<11;j++)
            if(trans[i][j]>0)
                ++cnt[trans[i][j]];
}
void topsort()
{
    queue<int>q;
    for(int i=0;i<tot;i++)
    {
        if(cnt[i]==0)
        {
            q.push(i);
            val_num[i]=1;
            sum[i]=0;
        }
    }
    while(!q.empty())
    {
        int now=q.front();
        q.pop();

        for(int k=0;k<11;k++)
        {
            if(trans[now][k]>0)
            {
                int j=trans[now][k];
                if(k<10)
                {
                    val_num[j]=(val_num[j]+val_num[now])%MOD;
                    sum[j]=(sum[j]+sum[now]*10LL%MOD+k*val_num[now]%MOD)%MOD;
                }
                --cnt[j];
                if(!cnt[j])q.push(j);
            }
        }
    }
}
int n;
ll an;
int main()
{
    /*
        ��ʼ������
    */
    int pres=new_state(0,0,NULL,-1);
    /*
        ͨ�ù��̴��벿��
    */
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>tem;
        if(i)s+=":";
        s+=tem;
    }
    n=s.length();

    for(int i=0;i<n;i++)
        pres=add_char(s[i],pres);//���������
    init_dag();
    topsort();

    /*
        ����ַ��������в�ͬ�Ӵ�����
    */
    for(int i=1;i<tot;i++)
        an=(an+sum[i])%MOD;
    printf("%lld\n",an);

}
/*
*/

