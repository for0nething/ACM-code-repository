/*
BIT
�����߶�����ʵ�ָ��򵥣��ٶȸ���
i-=i&-i���д�� i=i&(i-1)
*/
//[1,n]
int bit[MAX_N+1];
int sum(int i)//[1,i]ǰ׺��
{
    int s=0;
    while(i>0)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int n,int x)//�Ը�����a[i],ִ��a[i]+=x
{
    while(i<=n)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}

/*
struct ��
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
