/*
    以下的各个模板中 dwt中的/2 结合具体情况转化为2的逆元
    也可以不在过程中除以2  转为在求完之后直接除以数组长度 (2^k)
    并且有一个trick为 过程中取模就直接以 (2^k*MOD) 为模
    这样最后就可以直接除以2^k了
    不过这样乘法取模过程中可能会溢出ll 需要使用常用模板文件夹下的防溢出乘法

*/

void fwt(int *a,int l,int r)
{
    if(l==r)return;
    int n=(r-l+1)/2,mid=l+n-1;
    fwt(a,l,mid);fwt(a,mid+1,r);
    for(int i=1;i<=mid;i++)
    {
        int x=a[i],y=a[i+n];
        a[i]=x+y;a[i+n]=x-y;
    }
}
void dwt(int *a,int l,int r)
{
    if(l==r)return;
    int n=(r-l+1)/2,mid=l+n-1;
    dwt(a,l,mid);dwt(a,mid+1,r);
    for(int i=1;i<=mid;i++)
    {
        int x=a[i],y=a[i+n];
        a[i]=(x+y)/2;a[i+n]=(x-y)/2;
    }
}
/*
    以上为^运算

    &运算： fwt(a)=(fwt(a0+a1), fwt(a1) )
            dwt(a)=(dwt(a0-a1), dwt(a1) )

    or运算  fwt(a)=(fwt(a0), fwt(a0+a1) )
            dwt(a)=(dwt(a0), dwt(a1-a0) )

*/


/*
    非递归版
    其中UFWT仅适用于a^k 这种 如果不是的话需要改一下
    只需要把inv设成 2^(MOD-2)即可 即2的逆元
*/
void FWT()
{
    for(int d=1;d<len;d<<=1)
        for(int i=0;i<len;i+=(d<<1))
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)%p,a[i+j+d]=(x-y+p)%p;
            }
}

void UFWT()
{
    for(int d=1;d<len;d<<=1)
        for(int i=0;i<len;i+=(d<<1))
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=1ll*(x+y)*inv%p,a[i+j+d]=(1ll*(x-y)*inv%p+p)%p;
            }
}



/*
    非递归 传数组版 注意这个区间是左闭右开的！
*/
void Transform(int l, int r, LL a[]) // [l, r)
{
    if(l == r - 1) return ;
    int len = (r - l) >> 1;
    int m = l + len;
    Transform(l, m, a);
    Transform(m, r, a);
    for(int i = l; i < m; i ++)
    {
        LL x1 = a[i], x2 = a[i + len];
        a[i] = (x1 - x2 + MOD) % MOD;
        a[i + len] = (x1 + x2) % MOD;
    }
}

void ReTranform(int l, int r, LL a[])
{
    if(l == r - 1) return ;
    int len = (r - l) >> 1;
    int m = l + len;
    for(int i = l; i < m; i ++)
    {
        LL y1 = a[i], y2 = a[i + len];
        a[i] = (y1 + y2) * Inv2 % MOD;
        a[i + len] = (y2 - y1 + MOD) * Inv2 % MOD;
    }
    ReTranform(l, m, a);
    ReTranform(m, r, a);
}
