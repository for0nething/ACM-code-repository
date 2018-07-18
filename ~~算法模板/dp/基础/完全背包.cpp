#include<bits/stdc++.h>
using namespace std;
const int maxn=555;
int dp[111111];
int weight[maxn],value[maxn];
int n,m;
int main()
{
	int i,j,k;
	while(~scanf("%d %d",&n,&m))
	{
		memset(dp,0,sizeof(dp));
		for(i=1;i<=n;i++)
			scanf("%d %d",&weight[i],&value[i]);
		for(i=1;i<=n;i++)
		{
			for(j=weight[i];j<=m;j++)
			{
				if(j>=weight[i])
				  dp[j]=max(dp[j],dp[j-weight[i]]+value[i]);
				}
		}
		printf("%d\n",dp[m]);
	}
	return 0;
}
