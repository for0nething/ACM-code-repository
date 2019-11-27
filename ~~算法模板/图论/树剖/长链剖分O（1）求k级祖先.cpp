#include<queue>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
int n,m;
int x,y;
int tot;
int ans;
int head[300300];
int nex[600600];
int to[600600];
int f[300300][20];
int son[300300];
int mx[300300];
int d[300300];
int top[300300];
int st[600600];
vector<int>s[300300];
vector<int>t[300300];
void add(int x,int y)
{
    tot++;
    nex[tot]=head[x];
    head[x]=tot;
    to[tot]=y;
}
void dfs(int x,int fa)
{
    d[x]=d[fa]+1;
    mx[x]=d[x];
    f[x][0]=fa;
    for(int i=1;i<=19;i++)
    {
        if(f[x][i-1])
        {
            f[x][i]=f[f[x][i-1]][i-1];
        }
        else
        {
            break;
        }
    }
    for(int i=head[x];i;i=nex[i])
    {
        if(to[i]!=fa)
        {
            dfs(to[i],x);
            if(mx[to[i]]>mx[son[x]])
            {
                son[x]=to[i];
                mx[x]=mx[to[i]];
            }
        }
    }
}
void dfs2(int x,int tp)
{
    top[x]=tp;
    if(son[x])
    {
        dfs2(son[x],tp);
    }
    for(int i=head[x];i;i=nex[i])
    {
        if(to[i]!=f[x][0]&&to[i]!=son[x])
        {
            dfs2(to[i],to[i]);
        }
    }
}
void find(int x)
{
    int rt=x;
    int len=mx[x]-d[x];
    x=f[rt][0];
    while(d[rt]-d[x]<=len&&x)
    {
        s[rt].push_back(x);
        x=f[x][0];
    }
    x=rt;
    while(son[x])
    {
        t[rt].push_back(son[x]);
        x=son[x];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    dfs(1,0);
    dfs2(1,1);
    st[1]=0;
    for(int i=2;i<=n;i++)
    {
        st[i]=st[i>>1]+1;
    }
    for(int i=1;i<=n;i++)
    {
        if(i==top[i])
        {
            find(i);
        }
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        x=x^ans;
        y=y^ans;
        if(y==0)
        {
            ans=x;
        }
        else if(y>=d[x])
        {
            ans=0;
        }
        else
        {
            x=f[x][st[y]];
            y-=(1<<st[y]);
            if(y==0)
            {
                ans=x;
            }
            else if(y<d[x]-d[top[x]])
            {
                ans=t[top[x]][d[x]-d[top[x]]-y-1];
            }
            else if(y==d[x]-d[top[x]])
            {
                ans=top[x];
            }
            else
            {
                ans=s[top[x]][y-d[x]+d[top[x]]-1];
            }
        }
        printf("%d\n",ans);
    }
}
