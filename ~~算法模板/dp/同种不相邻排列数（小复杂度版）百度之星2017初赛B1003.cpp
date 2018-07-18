#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include<bitset>
#include <utility>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define xo(a,b) ((b)&1?(a):0)
//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll M=1e9+7;
//const ll maxn=2e5+7;
//const int MAXN=1005;
const int MAX=5010;
const int MAX_N=MAX;
//const int N=55;
const ll MOD=998244353;
//const double eps=0.00000001;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<class T> inline
void read(T& num) {
    bool start=false,neg=false;
    char c;
    num=0;
    while((c=getchar())!=EOF) {
        if(c=='-') start=neg=true;
        else if(c>='0' && c<='9') {
            start=true;
            num=num*10+c-'0';
        } else if(start) break;
    }
    if(neg) num=-num;
}
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
void open()
{
    freopen("1004.in","r",stdin);
    freopen("out.txt","w",stdout);
}
ll fi[MAX],inv[MAX];
ll quick(ll a,ll b)
{
    ll an=1LL;
    while(b)
    {
        if(b&1)
        {
            an=an*a%MOD;
        }
        a=a*a%MOD;
        b/=2;
    }
    return an%MOD;
}
ll C(ll a,ll b)
{
    if(a<0||b<0||b>a)
        return 0LL;
    return (fi[a]*inv[b]%MOD)*inv[a-b]%MOD;
}
int a[MAX];
ll dp[2][MAX],an;//总共分成j组的分法数
int t,sum,now;
int main()
{
    for(ll i=0;i<=4005;i++)
    {
        fi[i]=i?(fi[i-1]*i%MOD):1;
    }
    inv[4005]=quick(fi[4005],MOD-2);
    for(ll i=4004;i>=0;i--)
        inv[i]=(i+1)*inv[i+1]%MOD;
    while(~scanf("%d%d%d%d",&a[1],&a[2],&a[3],&a[4]))
    {
        memset(dp,0,sizeof(dp));
        now^=1;sum=0;dp[now][0]=1;
        an=0;
        for(int i=1;i<=4;i++)
        {
            if(a[i])
            {
                for(int j=0;j<=sum;j++)//已分成的组数
                {
                    for(int s=1;s<=a[i];s++)//当前种类分成的组数
                    {
                        dp[now^1][j+s]=(dp[now^1][j+s]+dp[now][j]*C(a[i]-1,s-1)%MOD*inv[s]%MOD)%MOD;
                    }
                }
                sum+=a[i];memset(dp[now],0,sizeof(dp[now]));now^=1;
            }
        }
        if(!sum)
        {
            printf("0\n");continue;
        }
        for(int i=0;i<=sum;i++)
        {
            ll tem=dp[now][sum-i];
            if(i&1)
                tem=MOD-tem;
            an=(an+tem*fi[sum-i]%MOD)%MOD;
        }
        printf("%lld\n",an);
    }
    return 0;
}
