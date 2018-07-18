#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
typedef long long LL;
const int MAX=1e5+5;//按理说取左侧点数即可
const int MAXM=6e6+5;//总边数
int head[MAX];//数组形式vector
int nxt[MAXM],val[MAXM];
int match[MAX<<1],check[MAX<<1],prv[MAX<<1];
int que[MAXM];//模拟队列
int st,en,cnt,numL;//numL需要初始化为左侧点数！
inline void add_edge(int u,int v)//加边 只需要加左到右的即可
{
    val[cnt]=v;nxt[cnt]=head[u];head[u]=cnt++;
}
//下标 0——numL-1
int Hungarian()
{
    int ans=0;
    memset(match,-1,sizeof(match));
    memset(check,-1,sizeof(check));
    for(int i=0;i<numL;i++)
    {
        if(match[i]==-1)
        {
            st=en=0;
            que[en++]=i;
            prv[i]=-1;
            bool sta=false;
            while(st!=en&&!sta)
            {
                int u=que[st];
                for(int t=head[u];t!=-1&&!sta;t=nxt[t])
                {
                    int v=val[t];
                    if(check[v]!=i)
                    {
                        check[v]=i;
                        que[en++]=match[v];
                        if(match[v]>=0)
                            prv[match[v]]=u;
                        else
                        {
                            sta=true;
                            int d=u,e=v;
                            while(d!=-1)
                            {
                                int q=match[d];
                                match[d]=e;
                                match[e]=d;
                                d=prv[d];
                                e=q;
                            }
                        }
                    }
                }
                ++st;
            }
            if(match[i]!=-1)++ans;
        }
    }
    return ans;
}
int n,a[MAX],hp[MAX],p[MAX],a2[MAX],hp2[MAX];
int main()
{
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;i++){read(a[i]);read(hp[i]);read(p[i]);}
//            scanf("%d%d%d",&a[i],&hp[i],&p[i]);
        for(int i=0;i<n;i++){read(a2[i]);read(hp2[i]);}
//            scanf("%d%d",&a2[i],&hp2[i]);
        memset(head,-1,sizeof(head));
        numL=n;
        for(int i=0;i<n;i++)
        {
            if(!p[i])
            {
                for(int j=0;j<n;j++)
                {
                    if(a[i]>=hp2[j]&&hp[i]>a2[j])add_edge(i,j+n);
                }
            }
            else if(p[i]==1)
            {
                for(int j=0;j<n;j++)
                    if(a[i]>=hp2[j])add_edge(i,j+n);
            }
            else if(p[i]==2)
            {
                for(int j=0;j<n;j++)
                    if(hp[i]>a2[j])add_edge(i,j+n);
            }
            else
            {
                for(int j=0;j<n;j++)
                    add_edge(i,j+n);
            }
        }
//        cout<<Hungarian()<<endl;
//        cout<<Hungarian()<<endl;
        if(Hungarian()==n)
            printf("YES\n");
        else printf("NO\n");
    }
}
