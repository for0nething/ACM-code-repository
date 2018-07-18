/*
MΪҪģ��ֵ
hashset �����Ƿ�����ͬ������hash���飩����set����ͬ ���и��õĸ��Ӷȣ� ���õķ�ʽ����дvector������ͬ��
˫��ϣset��
*/
struct hashset{
    const static int seed=1e7+7;//ģ�� ����̫��
    const static int maxn=2e6+7;//�����С(�ܹ���������
    struct node{
        int x,y;
        int next;
        node(){};
        node(int _x,int _y,int n):x(_x),y(_y),next(n){};
    }T[maxn];//���õؿռ�ֲ���?(��)
    int head[seed],size;
    void clear(){//��ʼ��
        memset(head,-1,sizeof(head));
        size=0;
    }
    void insert(int x,int y){//����
        int& h=head[x%seed];
        for (int i=h;~i;i=T[i].next)
            if (T[i].x==x&&T[i].y==y) return;
        T[size]=node(x,y,h);h=size++;
    }
    bool count(int x,int y){//�Ƿ����
        for (int i=head[x%seed];~i;i=T[i].next)
            if (T[i].x==x&&T[i].y==y) return 1;
        return 0;
    }
}have;

/*
����ϣset���������źܴ������԰���Ҫ�޸�Ϊ����Ĺ���
*/
struct hashset{
    const static int seed=1e7+7;
    const static int maxn=2e6+7;
    struct node{
        int x,next;
        node(){};
        node(int _x,int _n):x(_x),next(_n){};
    }T[maxn];
    int head[seed],size;
    void clear()
    {
        memset(head,-1,sizeof(head));
        size=0;
    }
    void insert(int x)
    {
        int &h=head[x%seed];
        for(int i=h;~i;i=T[i].next)
            if(T[i].x==x)return ;
        T[size]=node(x,h);h=size++;
    }
    bool count(int x)
    {
        for(int i=head[x%seed];~i;i=T[i].next)
            if(T[i].x==x)return 1;
        return 0;
    }
}have;
/*
    hash��������
*/
struct hash{
    int px[maxn],val[maxn],p;//px��p��i�η�  val���ַ�����ǰ׺hashֵ  pΪhashʹ�õ�����
    void setp(int P,int n=2000000){//����hash���õ�p������Ԥ����
        int i;px[0]=1;p=P;
        for(int i=1;i<=n;i++) px[i]=(ll)px[i-1]*p%M;
    }
    void set(char a[],int n){//�Գ���Ϊn���ַ���hash
        int i;val[0]=0;
        for(int i=1;i<=n;i++) val[i]=((ll)val[i-1]*p+a[i-1])%M;
    }
    int get(int l,int r){//���[l,r]�����hashֵ ע������l��1��ʼ ��ԭ�ַ�������ʼλ��0�ڴ�Ϊ[1,����]
        int ret=val[r]-(ll)val[l-1]*px[r-l+1]%M;
        (ret<0)&&(ret+=M);return ret;
    }
};


/*
    ʹ�þ���
*/
hash HA,HB;
char a[maxn],b[maxn];
int i,n,m;
int main(){
    scanf("%s",a);
    int n=strlen(a);
    REP(i,n) a[i+n]=a[i];
    HA.setp(27);HB.setp(29);
    HA.set(a,n+n);HB.set(a,n+n);
    have.clear();
    FOR(i,1,n) have.insert(HA.get(i,i+n-1),HB.get(i,i+n-1));
    scanf("%d",&m);
    REP(i,m){
        int i,ans=0;
        scanf("%s",b);
        int m=strlen(b);
        HA.set(b,m);HB.set(b,m);
        FOR(i,1,m-n+1) if (have.count(HA.get(i,i+n-1),HB.get(i,i+n-1))) ans++;
        printf("%d\n",ans);
    }
    return 0;
}
