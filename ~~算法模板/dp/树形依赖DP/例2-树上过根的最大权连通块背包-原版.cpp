#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
using namespace std;
//w=weight v=value
#define SZ 5004
int n,m,fa[SZ],w[SZ],v[SZ],fc[SZ],nc[SZ],siz[SZ],dp[SZ][SZ];
int st[SZ],t=0,dl[SZ];
void ass(int x) {int f=fa[x]; if(f) nc[x]=fc[f], fc[f]=x;}
void dfs(int p)
{
    siz[p]=1; st[p]=++t; dl[t]=p;
    for(int c=fc[p];c;c=nc[c])
    {
        dfs(c); siz[p]+=siz[c];
    }
}
#define FO(x) {freopen(#x".in","r",stdin); freopen(#x".out","w",stdout);}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d%d",fa+i,w+i,v+i), ass(i);
    dfs(1);
    for(int p=0;p<=m;p++) dp[n+1][p]=dp[n+2][p]=-1000000000;
    dp[n+1][0]=0; //原来这里忘了写
    for(int i=n;i>=1;i--)
    {
        int x=dl[i];
        for(int p=0;p<=m;p++)
        {
            if(p<w[x]) dp[i][p]=max(dp[i+siz[x]][p],0);
            else dp[i][p]=max(max(dp[i+siz[x]][p],dp[i+1][p-w[x]]+v[x]),0);
        }
    }
    printf("%d\n",dp[1][m]);
}
