ll mod_pow(ll x,ll n,ll mod)
{
    ll re=1;
    while(n>0)
    {
        if(n&1)/*如果二进制最低位为1，则乘上x^(2^i) */
            re=re*x%mod;
        x=x*x%mod;/*将x平方 */
        n>>=1;
    }
    return re;
}


