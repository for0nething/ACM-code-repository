/*
    kuangbin���й�ʣ�ඨ��
*/
//����d=gcd(a,b);�Ͷ�Ӧ�ڵ�ʽax+by=d�е�x,y
long long extend_gcd(long long a,long long b,long long &x,long long &y)
{
    if(a == 0 && b == 0)return -1;
    if(b ==0 ){x = 1; y = 0;return a;}
    long long d = extend_gcd(b,a%b,y,x);
    y -= a/b*x;
    return d;
}
long long m[10],a[10];//ģ��Ϊm,����Ϊa, X % m = a
bool solve(long long &m0,long long &a0,long long m,long long a)
{
    long long y,x;
    long long g = extend_gcd(m0,m,x,y);
    if( abs(a - a0)%g )return false;
    x *= (a - a0)/g;
    x %= m/g;
    a0 = (x*m0 + a0);
    m0 *= m/g;
    a0 %= m0;
    if( a0 < 0 )a0 += m0;
    return true;
}
/*
* �޽ⷵ��false,�нⷵ��true;
* �����ʽ���Ϊ a0 + m0 * t (0<=a0<m0)
*/
bool MLES(long long &m0 ,long long &a0,long long n)//��Ϊ  X = a0 + m0 * k
{
    bool flag = true; m0 = 1;
    a0 = 0;
    for(long long i = 0;i < n;i++)
    if( !solve(m0,a0,m[i],a[i]) )
    {
        flag = false; break;
    }
    return flag;
}
