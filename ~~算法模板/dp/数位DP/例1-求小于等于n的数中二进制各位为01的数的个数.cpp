
inline ll cal_1(ll x){//С�ڵ���x����������
    return (x+1)/2;
}
void get_mcnt(ll val){//����val����mcnt
    for(int i=0;i<=31;i++){
        ll ge=(val>>i);//��λdp��lim�Ĳ���(����0)
        if(ge==0)break;
        ll num=cal_1(ge-1);//��lim���ָ�λ��Ϊ1�ĸ���
        addi(mcnt[i][1],(num<<i)%MOD);
        addi(mcnt[i][0],((ge-num)<<i)%MOD);
        ll limcnt=(val-(ge<<i)+1)%MOD;//��lim�����ĸ���
        if(val&(1<<i))addi(mcnt[i][1],limcnt);
        else addi(mcnt[i][0],limcnt);
        sub(mcnt[i][0],1);
    }
}

