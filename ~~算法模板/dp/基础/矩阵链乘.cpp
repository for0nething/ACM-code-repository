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
//const ll INF=0x3f3f3f3f3f3f3f3fll;
const ll INFF=0x3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=1e5+5;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const int MOD=1e9+7;
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
ll lo[305][305];//当前拆分区间为[i,j]时中间选择的位置
ll dp[305][305];//拆分区间为[i,j]时的最小花费
ll a[305];//a[i]是第i个数的列数 a[i-1]是第i个数的行数
int n;
void print(int l,int r)
{
    if(l==r)
        printf("A%d",l);
    else
    {
        printf("(");
        print(l,lo[l][r]-1);
        print(lo[l][r],r);
        printf(")");
    }
}
int main()
{
    while(~scanf("%d",&n))
    {
//        memset(dp,0x3f,sizeof(dp));

        memset(lo,0,sizeof(lo));
        for(int i=0;i<=n;i++)
            scanf("%lld",&a[i]);
        for(int i=2;i<=n;i++)//区间长度
            for(int st=1;st<=n-i+1;st++)//区间起始位置
            {
                int en=st+i-1;//区间结束位置
                dp[st][en]=INFF;
                for(int t=st+1;t<=en;t++)//划分位置 后一个区间的起始
                {
                    int zhi=dp[st][t-1]+dp[t][en]+a[st-1]*a[en]*a[t-1];
                    if(zhi<=dp[st][en])
                    {
                        dp[st][en]=zhi;
                        lo[st][en]=t;
                    }
                }
            }
        print(1,n);
        printf("\n");
    }
}
/*
3
1 2 3

*/
