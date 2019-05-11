/*
    以下的各个模板中 dwt中的/2 结合具体情况转化为2的逆元
    也可以不在过程中除以2  转为在求完之后直接除以数组长度 (2^k)
    并且有一个trick为 过程中取模就直接以 (2^k*MOD) 为模
    这样最后就可以直接除以2^k了
    不过这样乘法取模过程中可能会溢出ll 需要使用常用模板文件夹下的防溢出乘法

*/

/*
    最速版 非递归 速度远超其他 DWT只需加一个除2操作 这里FWT展示的是不取模的 DWT展示的是取模的
    使用是 for(int i=0;i<n;i++)a[i]=a[i]*b[i] 这里也可以加取模操作 在模意义下不影响结果
*/
template<typename T>void FWT(T* a,int len)
{
    for (int hl = 1, l = 2; l <= len; hl = l, l <<= 1)
        for (T i = 0; i < len; i += l)
        for (register T t, j = 0, *x = a + i, *y = x + hl; j < hl; ++j, ++x, ++y)
            t = *x + *y, *y = *x - *y, *x = t; return;
}


template<typename T>void DWT(T* a,int len,int inv)
{
    for (int hl = 1, l = 2; l <= len; hl = l, l <<= 1)
        for (T i = 0; i < len; i += l)
        for (register T t, j = 0, *x = a + i, *y = x + hl; j < hl; ++j, ++x, ++y)
            t = mul(add(*x , *y),inv), *y = mul(inv,add(*x,MOD - *y)), *x = t; return;
}
/*
    不通过DWT 直接O(n)获取 某一下标的 DWT后的结果 cnt[i]表示i的二进制1的个数 可以预处理出来
    addi(int &x,int y) 修改x的值 （模意义下）
    模可能会产生问题（毕竟是模意义的hash处理 但概率很小）可以多hash解决
*/
int cnt[MAX];
int get(int* a,int len,int pos){
    int re=0;
    for(int i=0;i<len;i++)
        if(cnt[i&pos]&1)addi(re,MOD-a[i]);
        else addi(re,a[i]);
    return re;
}

/*
    递归 n稍大一点就很慢了
*/
template<typename T> void fwt(T *a,int l,int r)
{
    if(l==r)return;
    int n=(r-l+1)/2,mid=l+n-1;
    fwt(a,l,mid);fwt(a,mid+1,r);
    for(int i=1;i<=mid;i++)
    {
        T x=a[i],y=a[i+n];
        a[i]=x+y;a[i+n]=x-y;
    }
}
template<typename T> void dwt(T *a,int l,int r)
{
    if(l==r)return;
    int n=(r-l+1)/2,mid=l+n-1;
    dwt(a,l,mid);dwt(a,mid+1,r);
    for(int i=1;i<=mid;i++)
    {
        T x=a[i],y=a[i+n];
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
