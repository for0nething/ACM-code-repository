
inline ll cal_1(ll x){//小于等于x的奇数个数
    return (x+1)/2;
}
void get_mcnt(ll val){//对于val计算mcnt
    for(int i=0;i<=31;i++){
        ll ge=(val>>i);//数位dp无lim的部分(包含0)
        if(ge==0)break;
        ll num=cal_1(ge-1);//无lim部分该位置为1的个数
        addi(mcnt[i][1],(num<<i)%MOD);
        addi(mcnt[i][0],((ge-num)<<i)%MOD);
        ll limcnt=(val-(ge<<i)+1)%MOD;//有lim的数的个数
        if(val&(1<<i))addi(mcnt[i][1],limcnt);
        else addi(mcnt[i][0],limcnt);
        sub(mcnt[i][0],1);
    }
}

