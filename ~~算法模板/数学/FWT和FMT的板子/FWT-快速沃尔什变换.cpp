/*
    ���µĸ���ģ���� dwt�е�/2 ��Ͼ������ת��Ϊ2����Ԫ
    Ҳ���Բ��ڹ����г���2  תΪ������֮��ֱ�ӳ������鳤�� (2^k)
    ������һ��trickΪ ������ȡģ��ֱ���� (2^k*MOD) Ϊģ
    �������Ϳ���ֱ�ӳ���2^k��
    ���������˷�ȡģ�����п��ܻ����ll ��Ҫʹ�ó���ģ���ļ����µķ�����˷�

*/

/*
    ���ٰ� �ǵݹ� �ٶ�Զ������ DWTֻ���һ����2���� ����FWTչʾ���ǲ�ȡģ�� DWTչʾ����ȡģ��
    ʹ���� for(int i=0;i<n;i++)a[i]=a[i]*b[i] ����Ҳ���Լ�ȡģ���� ��ģ�����²�Ӱ����
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
    ��ͨ��DWT ֱ��O(n)��ȡ ĳһ�±�� DWT��Ľ�� cnt[i]��ʾi�Ķ�����1�ĸ��� ����Ԥ�������
    addi(int &x,int y) �޸�x��ֵ ��ģ�����£�
    ģ���ܻ�������⣨�Ͼ���ģ�����hash���� �����ʺ�С�����Զ�hash���
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
    �ݹ� n�Դ�һ��ͺ�����
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
    ����Ϊ^����

    &���㣺 fwt(a)=(fwt(a0+a1), fwt(a1) )
            dwt(a)=(dwt(a0-a1), dwt(a1) )

    or����  fwt(a)=(fwt(a0), fwt(a0+a1) )
            dwt(a)=(dwt(a0), dwt(a1-a0) )

*/


/*
    �ǵݹ��
    ����UFWT��������a^k ���� ������ǵĻ���Ҫ��һ��
    ֻ��Ҫ��inv��� 2^(MOD-2)���� ��2����Ԫ
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
    �ǵݹ� ������� ע���������������ҿ��ģ�
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
