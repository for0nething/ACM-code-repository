#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int MAXN=110;

int dp[MAXN];
int value[MAXN];//ÿ���ļ۸�
int weight[MAXN];//ÿ��������
int bag[MAXN];//����
int nValue,nKind;

//0-1����������Ϊcost,��õļ�ֵΪweight
void ZeroOnePack(int cost,int weight)
{
    for(int i=nValue;i>=cost;i--)
      dp[i]=max(dp[i],dp[i-cost]+weight);
}

//��ȫ����������Ϊcost,��õļ�ֵΪweight ÿ�������
void CompletePack(int cost,int weight)
{
    for(int i=cost;i<=nValue;i++)
      dp[i]=max(dp[i],dp[i-cost]+weight);
}

//���ر���
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
        ZeroOnePack(amount*cost,amount*weight);//�����Ҫ�����ˣ���������
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        //���dp�ĳ�ʼ��һ����Ҫ���ǣ����Բ�װ�����ʼ��Ϊ0��
        //����dp[0]=0,�����Ϊ-INF
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
