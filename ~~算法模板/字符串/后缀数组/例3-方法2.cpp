#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
#define pb push_back
#define rank rankk
#define mp make_pair
const int MAX=2e5+5;

/*
做法：
按height从大到小排序，使用并查集进行合并。
每次更新当前插的height的答案对应的(i,j)的最小值
判断串是否为字典序最小,首先在排序的时候按字典序排，并与固定长度后缀比较
*/
int n,k,q,ge;
char a[MAX];
int sa[MAX*3],fa[MAX],MIN[MAX];

vector<pii>v;


const int MAXN = 2e5+5;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int wa[MAXN*3],wb[MAXN*3],wv[MAXN*3],wss[MAXN*3];
int c0(int *r,int a,int b)
{
    return r[a] == r[b] && r[a+1] == r[b+1] && r[a+2] == r[b+2];
}
int c12(int k,int *r,int a,int b)
{
    if(k == 2)
    return r[a] < r[b] || ( r[a] == r[b] && c12(1,r,a+1,b+1) );
    else return r[a] < r[b] || ( r[a] == r[b] && wv[a+1] < wv[b+1] );
}
void sort(int *r,int *a,int *b,int n,int m)
{
    int i;
    for(i = 0;i < n;i++)wv[i] = r[a[i]]; for(i = 0;i < m;i++)wss[i] = 0; for(i = 0;i < n;i++)wss[wv[i]]++;
    for(i = 1;i < m;i++)wss[i] += wss[i-1];
    for(i = n-1;i >= 0;i--)
    b[--wss[wv[i]]] = a[i];
}
void dc3(int *r,int *sa,int n,int m)
{
    int i, j, *rn = r + n;
    int *san = sa + n, ta = 0, tb = (n+1)/3, tbc = 0, p; r[n] = r[n+1] = 0;
    for(i = 0;i < n;i++)if(i %3 != 0)wa[tbc++] = i; sort(r + 2, wa, wb, tbc, m);
    sort(r + 1, wb, wa, tbc, m);
    sort(r, wa, wb, tbc, m);
    for(p = 1, rn[F(wb[0])] = 0, i = 1;i < tbc;i++) rn[F(wb[i])] = c0(r, wb[i-1], wb[i]) ? p - 1 : p++;
    if(p < tbc)dc3(rn,san,tbc,p);
    else for(i = 0;i < tbc;i++)san[rn[i]] = i;
    for(i = 0;i < tbc;i++) if(san[i] < tb)wb[ta++] = san[i] * 3;
    if(n % 3 == 1)wb[ta++] = n - 1; sort(r, wb, wa, ta, m);
    for(i = 0;i < tbc;i++)wv[wb[i] = G(san[i])] = i;
    for(i = 0, j = 0, p = 0;i < ta && j < tbc;p++)
    sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for(;i < ta;p++)sa[p] = wa[i++];
    for(;j < tbc;p++)sa[p] = wb[j++];
}
//str和sa也要三倍
void da(int str[],int sa[],int rank[],int height[],int n,int m)
{
    for(int i = n;i < n*3;i++) str[i] = 0;
    dc3(str, sa, n+1, m);
    int i,j,k = 0;
    for(i = 0;i <= n;i++)rank[sa[i]] = i;
    for(i = 0;i < n; i++)
    {
        if(k) k--;
        j = sa[rank[i]-1]; while(str[i+k] == str[j+k]) k++; height[rank[i]] = k;
    }
}
int rank[MAXN*3],height[MAXN*3],last[MAX];


pii ans[MAX];
int RMQ[MAX];
int mm[MAX];//mm[i] : 满足2^x<=i的x的最大值（初始化mm[0]=-1）


int best[20][MAXN];

//init RMQ(int n) 之前需要 for(int i=1;i<=n;i++)RMQ[i]=height[i]; initRMQ(n);
void initRMQ(int n)
{
    mm[0]=-1;
    for(int i=1;i<=n;i++)
        mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
    for(int i=1;i<=n;i++)best[0][i]=i;
    for(int i=1;i<=mm[n];i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
        {
            int a=best[i-1][j];
            int b=best[i-1][j+(1<<(i-1))];
            if(RMQ[a]<RMQ[b])best[i][j]=a; else best[i][j]=b;
        }
}
int askRMQ(int a,int b)
{
    int t; t=mm[b-a+1];
    b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}
int lcp(int a,int b)
{
    a=rank[a];b=rank[b];
    if(a>b)swap(a,b);
    return height[askRMQ(a+1,b)];
}

inline int find(int x){if(x==fa[x])return x;return fa[x]=find(fa[x]);}
void unite(int x,int y,int z){
    int tx=x,ty=y;
    x=find(x),y=find(y);
    if(x!=y){///从两个里分别取最小的更新答案
        fa[x]=y;
        if(!z||rank[n-z]>=ty||lcp(n-z,sa[ty])==z){///比最后的串强
            if(last[z]==-1||lcp(sa[ty],last[z])>=z)ans[z]=min(ans[z],mp(min(MIN[x],MIN[y]),max(MIN[x],MIN[y])));
            if(last[z]==-1)last[z]=sa[ty];
        }
        MIN[y]=min(MIN[x],MIN[y]);
    }
}
char ss[MAX];
int sss[MAX];

int main(){
    scanf("%s",ss);
    n=strlen(ss);
    scanf("%d",&q);
    for(int i=0;i<n;i++)sss[i]=ss[i]-'a'+1;
    da(sss,sa,rank,height,n,28);
    for(int i=1;i<=n;i++)RMQ[i]=height[i];
    initRMQ(n);
//    printf("%d\n",lcp(1,1));
    ans[0]=mp(MAX,MAX);last[0]=-1;
    for(int i=1;i<=n;i++)fa[i]=i,MIN[i]=sa[i],v.pb(mp(height[i],-i)),ans[i]=mp(n-i,n-i),last[i]=-1;
//    for(int i=0;i<=n;i++)
//        printf("%2d %2d %2d %s\n",sa[i],height[i],i,ss+sa[i]);
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());

    for(pii tem:v){///大小为n 按height从更高到低合并

        int h=tem.first,pr=-tem.second,pl=pr-1;
        if(pl==0)continue;
//        printf("unite  h=%2d pl= %2d lo= %d %20s pr= %d lo= %d %20s\n",h,pl,sa[pl],ss+sa[pl],pr,sa[pr],ss+sa[pr]);
        unite(pl,pr,h);
    }
    while(q--){
        int u;
        scanf("%d",&u);
        if(u<0||u>n)return 0;
        printf("%d %d\n",ans[u].first==MAX?-1:ans[u].first+1,ans[u].second==MAX?-1:ans[u].second+1);
    }
    return 0;
}
/*
*/
