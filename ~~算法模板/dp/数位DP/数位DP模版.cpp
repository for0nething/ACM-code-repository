/*
    以不出现49的个数为例
*/
ll dp[30][2];//第几位 上一位是不是4
int dig[30];//最大范围的每一位数 下标从1开始 下标为1表示个位的数
ll DP(int wei,bool si,bool lim)//第几位  上一位是否为4   是否仍在边界限制（e.g. 范围568 到此时前两位为56 即有限制）
{
    if(!wei)return 1;//此为到0位不需要特别判断的直接返回1（个数）
    if(!lim&&dp[wei][si]!=-1)return dp[wei][si];//之前计算过直接返回
    int da=9;//该位最大的数值
    ll re=0;
    if(lim)da=dig[wei];//若有边界限制 上界取为边界
    for(int i=0;i<=da;i++)
    {
        if(si&&i==9)continue;//不能出现49
        re+=DP(wei-1,i==4,lim&&(i==da));
    }
    if(!lim)dp[wei][si]=re;//若无边界限制 可以更新该位的值 （若有限制的话 此值随数的变化而变 无需记忆）
    return re;
}
ll cal(ll x)
{
    int wei=0;
    while(x)//求出每一位的数码
    {
        dig[++wei]=x%10;x/=10;
    }
    return DP(wei,0,1);
}
int t;
ll n;
int main()
{
    memset(dp,-1,sizeof(dp));//dp数组初始化为-1
    scanf("%d",&t);
    while(t--)
    {
        cin>>n;
        cout<<(n-cal(n)+1LL)<<"\n";
    }
    return 0;
}
