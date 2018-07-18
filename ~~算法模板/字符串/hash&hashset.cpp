/*
M为要模的值
hashset 检验是否有相同（两个hash检验）（与set功能同 但有更好的复杂度？ 采用的方式与手写vector大致相同）
双哈希set：
*/
struct hashset{
    const static int seed=1e7+7;//模数 不能太大
    const static int maxn=2e6+7;//数组大小(总共结点个数）
    struct node{
        int x,y;
        int next;
        node(){};
        node(int _x,int _y,int n):x(_x),y(_y),next(n){};
    }T[maxn];//更好地空间局部性?(雾)
    int head[seed],size;
    void clear(){//初始化
        memset(head,-1,sizeof(head));
        size=0;
    }
    void insert(int x,int y){//插入
        int& h=head[x%seed];
        for (int i=h;~i;i=T[i].next)
            if (T[i].x==x&&T[i].y==y) return;
        T[size]=node(x,y,h);h=size++;
    }
    bool count(int x,int y){//是否存在
        for (int i=head[x%seed];~i;i=T[i].next)
            if (T[i].x==x&&T[i].y==y) return 1;
        return 0;
    }
}have;

/*
单哈希set，单独看着很蠢。可以按需要修改为所需的功能
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
    hash操作函数
*/
struct hash{
    int px[maxn],val[maxn],p;//px存p的i次方  val存字符串的前缀hash值  p为hash使用的质数
    void setp(int P,int n=2000000){//设置hash采用的p并进行预处理
        int i;px[0]=1;p=P;
        for(int i=1;i<=n;i++) px[i]=(ll)px[i-1]*p%M;
    }
    void set(char a[],int n){//对长度为n的字符串hash
        int i;val[0]=0;
        for(int i=1;i<=n;i++) val[i]=((ll)val[i-1]*p+a[i-1])%M;
    }
    int get(int l,int r){//获得[l,r]区间的hash值 注意这里l从1开始 即原字符串的起始位置0在此为[1,……]
        int ret=val[r]-(ll)val[l-1]*px[r-l+1]%M;
        (ret<0)&&(ret+=M);return ret;
    }
};


/*
    使用举例
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
