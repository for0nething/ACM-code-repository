#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
#define pb push_back
#define rank rankk
#define right riight
#define mp make_pair
const int MAX=5e5+5;

/*
题意：给定字符串，求最长的 s1 -> s2 -> … sk
s_i是S的子串，按顺序无重叠的出现，且长度递减。 s_{i+1}是s_{i}的子串
做法：
贪心的想，长度变化一定是k-> k-1 ->…-> 1
dp[i]表示从i开始作为第一个字符串，最大的长度。
可以得出dp[i]-1<=dp[i+1] (dp[i+1]至少可以按dp[i]的方案，去掉第一个的来做)
转移时check i,k （看dp[i]是否可以达到k）
只需找 j满足
1、j>=i+k
2、dp[j]>=k-1
3、lcp(j,i)>=k-1 或 lcp(j,i+1)>=k-1
对于第一条，注意到从右往左扫，i+k单调递减，有需要时插入线段树即可。
这里线段树维护的是所有dp的最大值
对于第三条，分两次做，对于固定位置i，与其lcp>=k-1的可以二分出左右边界 （预处理后求LCP是O(1)的）
相当于在线段树查询这个[L,R]区间的dp最大值。
其中关于k，只需要使用dp[i]-1<=dp[i+1]，便可知从i+1到i，dp值最大加1，每次加1后开始暴力递减的check到可行为止即可。
这里由于相邻位置dp最大只能大1，故总共暴力的复杂度是O(n)的。
加上check的log，总共O(nlog)
*/
int n;

const int MAXN = 5e5+5;
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
int st[MAXN*3],sa[MAXN*3],rank[MAXN*3],height[MAXN*3];

int RMQ[MAXN];
int mm[MAXN];//mm[i] : 满足2^x<=i的x的最大值（初始化mm[0]=-1）


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

struct seg_tree{
    int val[MAX<<3];
    inline void change(int x,int v){
        val[x]=max(val[x],v);
    }
    void init(){
        memset(val,0,sizeof(val));
    }
    void update(int k,int l,int r,int v,int lo){
        if(l==r){change(k,v);return;}
        int mid=(l+r)/2;
        if(lo<=mid)update(k<<1,l,mid,v,lo);
        else update(k<<1|1,mid+1,r,v,lo);
        val[k]=max(val[k<<1],val[k<<1|1]);
    }
    int query(int k,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr)return val[k];
        int mid=(l+r)/2,re=0;
        if(ql<=mid)re=max(re,query(k<<1,l,mid,ql,qr));
        if(qr>mid)re=max(re,query(k<<1|1,mid+1,r,ql,qr));
        return re;
    }
}T;

int solvel(int l,int r,int pos,int v){
    int re=r+1,mid;
    while(l<=r){
        mid=(l+r)/2;
        if(lcp(sa[mid],sa[pos])>=v){
            re=mid;r=mid-1;
        }
        else l=mid+1;
    }
    return re;
}

int solver(int l,int r,int pos,int v){
    int re=l-1,mid;
    while(l<=r){
        mid=(l+r)/2;
        if(lcp(sa[mid],sa[pos])>=v){
            l=mid+1;re=mid;
        }
        else r=mid-1;
    }
    return re;
}
char str[MAXN];
int STR[MAXN],dp[MAXN];
int ans,right,k;
int main(){
    scanf("%d",&n);
    scanf("%s",str);
    for(int i=0;i<n;i++)STR[i]=str[i]-'a'+1;
    da(STR,sa,rank,height,n,26+2);
    for(int i=1;i<=n;i++)RMQ[i]=height[i];
    initRMQ(n);
    T.init();
    dp[n-1]=1;k=2;right=n-1;ans=1;
    for(int i=n-2;i>=0;i--,++k){
        bool flag=1;
        while(flag&&k>1){
            while(right>=i+k){
                T.update(1,1,n,dp[right],rank[right]),--right;///单点修改
            }
            int L=solvel(1,rank[i]-1,rank[i],k-1),R=solver(rank[i]+1,n,rank[i],k-1);
            int tem=T.query(1,1,n,L,R);
            assert(sa[L]==i||lcp(sa[L],i)>=k-1);
            assert(sa[R]==i||lcp(sa[R],i)>=k-1);
            if(tem>=k-1)flag=0;
            else{
                L=solvel(1,rank[i+1]-1,rank[i+1],k-1),R=solver(rank[i+1]+1,n,rank[i+1],k-1);
                tem=T.query(1,1,n,L,R);
                assert(sa[L]==i+1||lcp(sa[L],i+1)>=k-1);
                assert(sa[R]==i+1||lcp(sa[R],i+1)>=k-1);
                if(tem>=k-1)flag=0;
            }
            k-=flag;
        }
        dp[i]=k;
        ans=max(ans,k);
    }
    printf("%d\n",ans);
    return 0;
}
/*

100

a


*/
