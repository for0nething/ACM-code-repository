
ll multmod(ll a,ll b){
    a%=MOD;b%=MOD;
    if(b<0)b+=MOD;
    if(a<0)a+=MOD;
    ll re=0;
    while(b){
        if(b&1LL){
            re+=a;if(re>=MOD)re-=MOD;
        }
        a=a<<1;
        if(a>=MOD)a-=MOD;
        b=b>>1;
    }
    return re;
}

