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
#include <bitset>
#include <utility>
#include <assert.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp

//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<ll,ll> pll;
//const int INF=0x3f3f3f3f;
//const int INF= 0x7fffffff;
const ll INF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=0x3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=1e6+5;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const ll MOD=1e9+7;
//const long double pi=acos(-1.0);
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
//    freopen("1009.in","r",stdin);
    freopen("out.txt","w",stdout);
}
int n,m;
char a[1005],b[1005];
int dp[505][505];//a到i b到j的最长子序列
int main()
{
    while(~scanf("%s",a))
    {
        scanf("%s",b);
        n=strlen(a);m=strlen(b);
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<=n;i++)dp[i][0]=0;
        for(int j=0;j<=m;j++)dp[0][j]=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
                dp[i][j]=max(dp[i-1][j-1]+(a[i-1]==b[j-1]),dp[i][j]);
            }
        printf("%d\n",dp[n][m]);
    }
}
/*
3
1 2 3

*/


/*

*/
