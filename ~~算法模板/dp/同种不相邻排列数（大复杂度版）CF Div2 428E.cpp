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
const int MAX=305;
const int MAX_N=MAX;
//const int N=55;
const ll MOD=1e9+7;
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
bool check(ll x,ll y)
{
    ll ji=x*y;
    ll sq=(ll)sqrt(ji);
    if(sq*sq==ji)
        return true;
    return false;
}
int n;
int a[MAX];
bool vi[MAX];
ll per;
queue<int>que;
ll dp[305][305];
int main()
{
    for(ll i=0;i<=300;i++)
    {
        fi[i]=i?(fi[i-1]*i%MOD):1;
    }
    inv[300]=quick(fi[300],MOD-2);
    for(ll i=299;i>=0;i--)
        inv[i]=(i+1)*inv[i+1]%MOD;
    scanf("%d",&n);per=1;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        if(vi[i])
            continue;
        int cnt=1;
        for(int j=i+1;j<=n;j++)
        {
            if(check(a[i],a[j]))
            {
                ++cnt;vi[j]=true;
            }
        }
        per=per*fi[cnt]%MOD;
        que.push(cnt);
    }
    int tot=que.size();
    int num=que.front();que.pop();
    int lin=num-1,id=1;
    dp[1][num-1]=1;
    while(!que.empty())
    {
        num=que.front();que.pop();++id;
        for(int i=0;i<=lin;i++)//原本有i个不合法空隙
        {
            for(int j=1;j<=num;j++)//将这种数分成几块
            {
//                dp[id][]
                for(int s=0;s<=i&&s<=j;s++)//破坏多少个原本的空隙
                    dp[id][i-s+num-j]=(dp[id][i-s+num-j]+dp[id-1][i]*C(num-1,j-1)%MOD*C(i,s)%MOD*C(id+lin-i,j-s)%MOD)%MOD;
            }
        }
        lin+=num-1;
    }
    printf("%I64d\n",dp[tot][0]*per%MOD);
}
