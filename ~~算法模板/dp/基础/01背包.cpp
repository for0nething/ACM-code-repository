/*
简单的01背包
*/
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

const int MAXN=3500;
int dp[13000];
int value[MAXN];//每袋的价格
int weight[MAXN];//每袋的重量

int nValue,nKind;

//0-1背包，代价为cost,获得的价值为weight
void ZeroOnePack(int cost,int weight)
{
    for(int i=nValue;i>=cost;i--)
      dp[i]=max(dp[i],dp[i-cost]+weight);
}

int main()
{
    while(scanf("%d%d",&nKind,&nValue)!=EOF)
    {
        for(int i=0;i<nKind;i++)scanf("%d%d",&value[i],&weight[i]);
        memset(dp,0,sizeof(dp));
        for(int i=0;i<nKind;i++)
          ZeroOnePack(value[i],weight[i]);
        printf("%d\n",dp[nValue]);
    }
    return 0;
}
