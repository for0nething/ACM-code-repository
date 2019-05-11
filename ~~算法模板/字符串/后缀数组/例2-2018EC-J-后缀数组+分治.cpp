//164ms 27744KB
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=2e5+5;

int Log[N];
struct Suffix_Array
{
    int n,tm[N],sa[N],sa2[N],rk[N],ht[N],pos[N][18];
    char s[N];

    void Build()
    {
        scanf("%s",s+1), n=strlen(s+1);
//      memset(rk,0,std::min(N,n*2)<<2);//!
//      memset(sa2,0,std::min(N,n*2)<<2);

        int m=26,*x=rk,*y=sa2;
        for(int i=0; i<=m; ++i) tm[i]=0;
        for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]-'a'+1];
        for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
        for(int i=n; i; --i) sa[tm[x[i]]--]=i;
        for(int p=0,k=1; k<n; k<<=1,m=p,p=0)
        {
            for(int i=n-k+1; i<=n; ++i) y[++p]=i;
            for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;

            for(int i=0; i<=m; ++i) tm[i]=0;
            for(int i=1; i<=n; ++i) ++tm[x[i]];
            for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
            for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

            std::swap(x,y), x[sa[1]]=p=1;
            for(int i=2; i<=n; ++i)
                x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&sa[i]+k<=n&&sa[i-1]+k<=n&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;//如果不清空要这么写
//              x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
            if(p>=n) break;
        }
        for(int i=1; i<=n; ++i) rk[sa[i]]=i;
        ht[1]=0;
        for(int k=0,i=1,p; i<=n; ++i)
        {
            if(rk[i]==1) continue;
            if(k) --k;
            p=sa[rk[i]-1];
            while(i+k<=n && p+k<=n && s[i+k]==s[p+k]) ++k;
            ht[rk[i]]=k;
        }
    }
    inline int Min(int x,int y)
    {
        return ht[x]<ht[y]?x:y;
    }
    inline int QueryMin(int l,int r)
    {
        int k=Log[r-l+1];
        return Min(pos[l][k],pos[r-(1<<k)+1][k]);
    }
    void Init_ST(const int n)
    {
        for(int i=1; i<=n; ++i) pos[i][0]=i;
        for(int j=1; j<=Log[n]; ++j)
            for(int t=1<<j-1,i=n-t; i; --i)
                pos[i][j]=Min(pos[i][j-1],pos[i+t][j-1]);
    }
    double Solve(int l,int r)
    {
        if(l==r) return n-sa[l]+1;
        int p=QueryMin(l+1,r);
        double L=Solve(l,p-1),R=Solve(p,r),v=ht[p];
        return (L*R-v*v)/(L+R-2*v);
    }
    void Work()
    {
        Build(), Init_ST(n), printf("%.11lf\n",Solve(1,n));
    }
}sa;

int main()
{
//  freopen("bb.in","r",stdin);
//  freopen("bb.out","w",stdout);

    for(int i=2; i<N; ++i) Log[i]=Log[i>>1]+1;
    int T; scanf("%d",&T);
    while(T--) sa.Work();

    return 0;
}
