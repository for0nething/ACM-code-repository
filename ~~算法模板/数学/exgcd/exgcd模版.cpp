/*
    利用gcd(a,b) =gcd (b,a%b)

    x1*a+y1*b=gcd(a,b)=gcd(b,a%b)= x2*b+y2*(a%b)=x2*b+y2*(a-a/b*b)
   =y2*a+(x2-a/b*y2)*b

   递归求解 递归到到gcd(q,0)时结束 此时x2=1 y2=0 逐层返回
   利用x1=y2  y1=x2-a/b*y2 逐层向上转移

   返回gcd(a,b)  x、y为ax+by=gcd(a,b)的解
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

