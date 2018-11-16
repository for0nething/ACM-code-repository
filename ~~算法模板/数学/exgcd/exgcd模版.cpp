/*
    ����gcd(a,b) =gcd (b,a%b)

    x1*a+y1*b=gcd(a,b)=gcd(b,a%b)= x2*b+y2*(a%b)=x2*b+y2*(a-a/b*b)
   =y2*a+(x2-a/b*y2)*b

   �ݹ���� �ݹ鵽��gcd(q,0)ʱ���� ��ʱx2=1 y2=0 ��㷵��
   ����x1=y2  y1=x2-a/b*y2 �������ת��

   ����gcd(a,b)  x��yΪax+by=gcd(a,b)�Ľ�
*/
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1;y=0;return a;
    }
    ll re=exgcd(b,a%b,x,y);
    ll t=x;
    x=y;y=t-a/b*y;
    return re;
}

