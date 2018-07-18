#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=2e6+5;


/*
    模版部分开始：
*/

const ll MOD=998244353;
const ll g=3;//模MOD的原根
inline ll mul(ll x,ll y,ll mod=MOD){return x*y%mod;}
inline ll poww(ll a,ll b,ll mod=MOD)
{
    a%=mod;
    ll ret=1;
    for(;b;b>>=1LL,a=mul(a,a,mod))
        if(b&1)ret=mul(ret,a,mod);
    return ret;
}
void ntt(ll *A,int len,int inv=1)//A下标0开始 inv=1 DFT inv=-1 IDFT   想改成vector只需要ll *A 改成vector<ll>&A
{
    int k;
    for(int i=1,j=len/2;i<len-1;i++)
    {
        if(i<j)swap(A[i],A[j]);
        k=len/2;
        while(j>=k)
        {
            j-=k;k/=2;
        }
        if(j<k)j+=k;
    }
    for(int i=2;i<=len;i<<=1)
    {
        ll wn=poww(g,(MOD-1)/i);
        if(inv==-1)wn=poww(wn,MOD-2);
        for(int j=0;j<len;j+=i)
        {
            ll w=1;
            for(k=j;k<(j+i/2);k++)
            {
                ll a=A[k],b=mul(w,A[k+i/2]);
                A[k]=(a+b)%MOD;
                A[k+i/2]=(a-b+MOD)%MOD;
                w=mul(w,wn);
            }
        }
    }
    if(inv==-1){
        ll vn=poww(len,MOD-2);
        for(int i=0;i<len;i++)A[i]=mul(A[i],vn);
    }
}

/*
    模版部分结束
    以下为使用示例 忽略对x的处理即为  (1+x)^n的系数异或和
*/


char a[MAX];
int k;
ll ans,A[MAX],n;
int main()
{
    scanf("%s%d",a,&k);
    int len=strlen(a);
    for(int i=0;i<len;i++)
        n=(n*10+a[i]-'0')%(MOD-1);
    A[0]=A[1]=1;
    ntt(A,k,1);
    for(int i=0;i<k;i++)A[i]=poww(A[i],n);
    ntt(A,k,-1);
    for(int i=0;i<k;i++)
        ans^=A[i];
    printf("%lld\n",ans);
    return 0;
}

/*
    int数组&wn预处理版
    速度更快 尤其是多次NTT、INTT时
*/
#include<bits/stdc++.h>
using namespace std;
const int MAX=3e5+7;
typedef long long ll;
const int MOD=998244353;
const int g=3;//模MOD的原根
inline int mul(int x,int y) {
    return (ll)x*y%MOD;
}
int poww(int a,int b){
    int ret=1;
    for (;b;b>>=1,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}

int wx[20][MAX];
void initwn(int len,int inv){
    for(int i=2,ix=1;i<=len;i<<=1,ix++){
        wx[ix][0]=1;int wn=poww(g,(MOD-1)/i);
        if (inv==-1) wn=poww(wn,MOD-2);
        for (int k=1;k<i/2;k++)
            wx[ix][k]=mul(wx[ix][k-1],wn);
    }
}
void ntt(int *A,int len,int inv=1){
    int i,j,k;
    for (i=1,j=len/2;i<len-1;i++){
        if (i<j) swap(A[i],A[j]);
        k=len/2;
        while(j>=k){
            j-=k;
            k/=2;
        }if (j<k) j+=k;
    }
    for(int ix=1,i=2;i<=len;i<<=1,ix++){
        for (j=0;j<len;j+=i){
            for (k=j;k<(j+i/2);k++){
                int a=A[k],b=mul(wx[ix][k-j],A[k+i/2]);
                A[k]=a+b;(A[k]>MOD)&&(A[k]-=MOD);
                A[k+i/2]=a-b;(A[k+i/2]<0)&&(A[k+i/2]+=MOD);
            }
        }
    }
    if (inv==-1){
        int vn=poww(len,MOD-2);
        for(int i=0;i<len;i++) A[i]=mul(A[i],vn);
    }
}
char a[MAX],b[MAX];
int c[7][MAX],d[7][MAX];
ll st[MAX];
int n,m;
int A[MAX];
int fa[10];
int getfa(int x)
{
    while(fa[x]!=x)x=fa[x]=fa[fa[x]];
    return x;
}
int main()
{
    scanf("%s%s",a,b);
    n=strlen(a);m=strlen(b);
    int len=1;
    while(len<n+m)len<<=1;
    for(int i=0;i<n;i++)c[a[i]-'a'][i]=1;
    for(int i=0;i<m;i++)d[b[i]-'a'][m-1-i]=1;
    initwn(len,1);
    for(int i=0;i<6;i++){ntt(c[i],len,1);ntt(d[i],len,1);}
    initwn(len,-1);
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<len;k++)
                A[k]=1LL*c[i][k]*d[j][k]%MOD;
            ntt(A,len,-1);
            for(int k=0;k<len;k++)if(A[k])st[k]|=1LL<<(6*i+j);
        }
    for(int i=m-1;i<=n-1;i++)
    {
        for(int t=0;t<7;t++)fa[t]=t;
        int an=0;
        for(int k=0;k<36;k++)
            if((st[i]>>k)&1LL)
            {
                int x=getfa(k/6),y=getfa(k%6);
                if(x!=y){fa[x]=y;++an;}
            }
        printf("%d ",an);
    }
    printf("\n");

}

