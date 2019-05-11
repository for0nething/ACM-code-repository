#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <bitset>
#include <utility>
#include <complex>
#include <assert.h>
#include <limits.h>
#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;


#define rank rankk
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define xo(a,b) ((b)&1?(a):0)
#define fi first
#define se second
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;


const int INF=0x3f3f3f3f;
//const ll INFF=1200000000000000000ll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=2e5+5;
const ll MOD=998244353;
//int MOD;
//const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
//const long double eps=1e-13;
//const double pi=acos(-1);
//#define double long double
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
//#define double long double
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
inline int powMM(int a,int b,int M){
    int ret=1;
    a%=M;
    while (b){
        if (b&1) ret=1LL*ret*a%M;
        b>>=1;
        a=1LL*a*a%M;
    }
    return ret;
}
namespace{
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
template<class T> inline T add(T x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(T &x,T y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){x+=y;if(x>=MOD)x%=MOD;}
template<class T> inline T mul(T x,T y){return 1LL*x*y%MOD;}
//inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
template<class T> inline void muli(T &x,T y){x=1LL*x*y%MOD;}
template<class T> inline T sub(T x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(T &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline T half(T x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);


namespace seives{
//使用以下define以及一个ui数组在欧拉筛过程中即可快速判断是否是质数
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
    const int MAXP=6666666;//欧拉筛的大小 固定为n的上限的 2/3次方
    const int MAX=20000010;
    int mu[MAX],phi[MAX];
    int p[MAXP],tot;
    ui ar[(MAX>>6)+7]={0};
    void init(){
        setbit(ar,0);setbit(ar,1);
        tot=0;
        mu[1]=phi[1]=1;
        for(int i=2;i<MAX;i++){
            if(isprime(i))p[tot++]=i,mu[i]=-1,phi[i]=i-1;
            for(int j=0;j<tot;j++){
                if(i*p[j]>=MAX)break;
                if((i*p[j])&1)setbit(ar,i*p[j]);
                if(i%p[j]==0){
                    mu[i*p[j]]=0;
                    phi[i*p[j]]=phi[i]*p[j];
                    break;
                }
                else{
                    phi[i*p[j]]=phi[i]*(p[j]-1);
                    mu[i*p[j]]=-mu[i];
                }
            }
        }
        for(int i=2;i<MAX;i++){addi(phi[i],phi[i-1]),addi(mu[i],mu[i-1]);if(mu[i]<0)mu[i]%=MOD,mu[i]+=MOD;}
    }
    ll get2(ll x){
        x%=MOD;return x*(x+1)%MOD*499122177%MOD;
    }
    map<ll,int>HASHmu;//使用map多一个log
    ll sum_mu(ll x){
        if(x<MAX)return mu[x];
        if(HASHmu.count(x))return HASHmu[x];
        ll ret=1,l;
        for(l=2;l<=x;l++){
            ll t=x/l,r=x/t;
            addi(ret,mul(MOD-(r-l+1)%MOD,sum_mu(t)%MOD));
            l=r;
        }
        return HASHmu[x]=ret;
    }
    ll sum_F(ll x){//直接利用∑的形式求前缀和（也可以利用其=2*phi-1的特性求phi的前缀和再求）
        if(x<MAX)return (phi[x]*2-1)%MOD;
        ll l,ret=0;
        for(l=1;l<=x;l++){
            ll t=x/l,r=x/t;ll _t=t%MOD;
            addi(ret,(sum_mu(r)-sum_mu(l-1)+MOD)%MOD*_t%MOD*_t%MOD);
            l=r;
        }
        return ret;
    }
}
ll n;
int main(){
    seives::init();
    read(n);
    ll l=1,ans=0;
    for(l=1;l<=n;l++){//可以证明n^2/3的杜教筛外套一个分块不影响复杂度
        ll t=n/l,r=n/t;
        addi(ans,mul(sub(seives::sum_mu(r),seives::sum_mu(l-1) ),seives::sum_F(t) ));
        l=r;
    }
    ans%=MOD;ans+=MOD;ans%=MOD;
    printf("%lld\n",ans);
    return 0;
}

/*

*/
