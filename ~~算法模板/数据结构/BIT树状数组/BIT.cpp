/*
BIT
比起线段树，实现更简单，速度更快
i-=i&-i亦可写作 i=i&(i-1)
*/
//[1,n]
int bit[MAX_N+1];
int sum(int i)//[1,i]前缀和
{
    int s=0;
    while(i>0)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int n,int x)//对给定的a[i],执行a[i]+=x
{
    while(i<=n)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}

/*
struct 版
from quailty
*/
struct BIT
{
    int n,c[MAXN];
    void init(int _n)
    {
        n=_n;
        for(int i=1;i<=n;i++)c[i]=0;
    }
    void update(int p,int v)
    {
        for(int i=p;i<=n;i+=i&-i)c[i]+=v;
    }
    int query(int p)
    {
        int res=0;
        for(int i=p;i>0;i-=i&-i)res+=c[i];
        return res;
    }
}bit;
