/*
�򵥵�01����
*/
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

const int MAXN=3500;
int dp[13000];
int value[MAXN];//ÿ���ļ۸�
int weight[MAXN];//ÿ��������

int nValue,nKind;

//0-1����������Ϊcost,��õļ�ֵΪweight
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
