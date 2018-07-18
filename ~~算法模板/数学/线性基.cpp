const int MAXBIT=MAXBIT;

/*
    非化成绝对对角线型版（对角线某一列为1 其上侧可以有1）
    位数默认31（int范围 下标0——30）
*/

struct LB//Linear basis
{
    int a[35];
    void clear()
    {
        memset(a,0,sizeof(a));
    }
    int XORMAX()
    {
        int re=0;
        for(int i=MAXBIT;i>=0;i--)
        {
            if((re^a[i])>re)
                re^=a[i];
        }
        return re;
    }
    void insert(int x)
    {
        for(int i=MAXBIT;i>=0&&x;i--)
        {
            if(x&(1<<i))
            {
                if(!a[i])
                    a[i]=x;
                x^=a[i];
            }
        }
    }
    void merge(LB x)
    {
        for(int i=MAXBIT;i>=0;i--)
        {
            if(x.a[i])
                insert(x.a[i]);
        }
    }
}lb[MAX];


/*
    化成绝对对角线型版（对角线某一列为1 其上侧无1）
    位数默认31（int范围 下标0——30）
*/
struct LB//Linear basis
{
    int a[35];
    void clear()
    {
        memset(a,0,sizeof(a));
    }
    int XORMAX()
    {
        int re=0;
        for(int i=MAXBIT;i>=0;i--)
        {
            if((re^a[i])>re)
                re^=a[i];
        }
        return re;
    }
    void insert(int x)
    {
        for(int i=MAXBIT;i>=0&&x;i--)
        {
            if(x&(1<<i))
            {
                if(!a[i])
                {
                    a[i]=x;
                    for(int j=i-1;j>=0;j--)
                    {
                        if(a[j]&&(a[i]&(1<<j)))
                            a[i]^=a[j];
                    }
                    for(int j=i+1;j<=MAXBIT;j++)
                    {
                        if(a[j]&&(a[j]&(1<<i)))
                            a[j]^=a[i];
                    }
                }
                x^=a[i];
            }
        }
    }
    void merge(LB x)
    {
        for(int i=MAXBIT;i>=0;i--)
        {
            if(x.a[i])
                insert(x.a[i]);
        }
    }
}lb[MAX];
