/*
    �Բ�����49�ĸ���Ϊ��
*/
ll dp[30][2];//�ڼ�λ ��һλ�ǲ���4
int dig[30];//���Χ��ÿһλ�� �±��1��ʼ �±�Ϊ1��ʾ��λ����
ll DP(int wei,bool si,bool lim)//�ڼ�λ  ��һλ�Ƿ�Ϊ4   �Ƿ����ڱ߽����ƣ�e.g. ��Χ568 ����ʱǰ��λΪ56 �������ƣ�
{
    if(!wei)return 1;//��Ϊ��0λ����Ҫ�ر��жϵ�ֱ�ӷ���1��������
    if(!lim&&dp[wei][si]!=-1)return dp[wei][si];//֮ǰ�����ֱ�ӷ���
    int da=9;//��λ������ֵ
    ll re=0;
    if(lim)da=dig[wei];//���б߽����� �Ͻ�ȡΪ�߽�
    for(int i=0;i<=da;i++)
    {
        if(si&&i==9)continue;//���ܳ���49
        re+=DP(wei-1,i==4,lim&&(i==da));
    }
    if(!lim)dp[wei][si]=re;//���ޱ߽����� ���Ը��¸�λ��ֵ ���������ƵĻ� ��ֵ�����ı仯���� ������䣩
    return re;
}
ll cal(ll x)
{
    int wei=0;
    while(x)//���ÿһλ������
    {
        dig[++wei]=x%10;x/=10;
    }
    return DP(wei,0,1);
}
int t;
ll n;
int main()
{
    memset(dp,-1,sizeof(dp));//dp�����ʼ��Ϊ-1
    scanf("%d",&t);
    while(t--)
    {
        cin>>n;
        cout<<(n-cal(n)+1LL)<<"\n";
    }
    return 0;
}
