ll mod_pow(ll x,ll n,ll mod)
{
    ll re=1;
    while(n>0)
    {
        if(n&1)/*������������λΪ1�������x^(2^i) */
            re=re*x%mod;
        x=x*x%mod;/*��xƽ�� */
        n>>=1;
    }
    return re;
}


