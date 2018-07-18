#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int MAXN=110;

int dp[MAXN];
int value[MAXN];//每袋的价格
int weight[MAXN];//每袋的重量
int bag[MAXN];//袋数
int nValue,nKind;

//0-1背包，代价为cost,获得的价值为weight
void ZeroOnePack(int cost,int weight)
{
    for(int i=nValue;i>=cost;i--)
      dp[i]=max(dp[i],dp[i-cost]+weight);
}

//完全背包，代价为cost,获得的价值为weight 每种无穷多
void CompletePack(int cost,int weight)
{
    for(int i=cost;i<=nValue;i++)
      dp[i]=max(dp[i],dp[i-cost]+weight);
}

//多重背包
void MultiplePack(int cost,int weight,int amount)
{
    if(cost*amount>=nValue) CompletePack(cost,weight);
    else
    {
        int k=1;
        while(k<amount)
        {
            ZeroOnePack(k*cost,k*weight);
            amount-=k;
            k<<=1;
        }
        ZeroOnePack(amount*cost,amount*weight);//这个不要忘记了，经常掉了
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        //这个dp的初始化一定不要忘记，可以不装满则初始化为0，
        //否则dp[0]=0,其余的为-INF
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&nValue,&nKind);
        for(int i=0;i<nKind;i++)
          scanf("%d%d%d",&value[i],&weight[i],&bag[i]);
        for(int i=0;i<nKind;i++)
          MultiplePack(value[i],weight[i],bag[i]);
        printf("%d\n",dp[nValue]);
    }
    return 0;
}
