//******************************
//����d=gcd(a,b);�Ͷ�Ӧ�ڵ�ʽax+by=d�е�x,y
int extend_gcd(int a,int b,int &x,int &y)
{
    if(a==0&&b==0) return -1;//�����Լ��
    if(b==0){x=1;y=0;return a;}
    int d=extend_gcd(b,a%b,y,x); y-=a/b*x;
    return d;
}
//*********����Ԫ��*******************
//ax = 1(mod n)
int mod_reverse(int a,int n)
{
    int x,y;
    int d=extend_gcd(a,n,x,y);
    if(d==1) return (x%n+n)%n;
    else return -1;
}




/* ��x=a[i] mod(m[i]) */

int CRT(int a[],int m[],int n)
{
    int M = 1;
    int ans = 0;
    for(int i=1; i<=n; i++)
        M *= m[i];
    for(int i=1; i<=n; i++)
    {
        int x, y;
        int Mi = M / m[i];
        extend_gcd(Mi, m[i], x, y);
        ans = (ans + Mi * x * a[i]) % M;
    }
    if(ans < 0) ans += M;
    return ans;
}
