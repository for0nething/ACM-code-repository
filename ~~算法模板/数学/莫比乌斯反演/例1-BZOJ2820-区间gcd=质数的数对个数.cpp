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
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;


const int INF=0x3f3f3f3f;
//const ll INFF=1200000000000000000ll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=1e7+5;
const int MOD=998244353;
//const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
//const double eps=1e-6;
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
inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
//inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

/*
神犇YY虐完数论后给傻×kAc出了一题
给定N, M,求1<=x<=N, 1<=y<=M且gcd(x, y)为质数的(x, y)有多少对
kAc这种傻×必然不会了，于是向你来请教……
多组输入
T = 10000

N, M <= 10000000

*/
int mu[MAX],prime[MAX],sum[MAX];
bool check[MAX];
int t,x,y,tot;
void euler(){
    mu[1]=1;
    for(int i=2;i<=10000000;i++){
        if(!check[i]){
            prime[tot++]=i;mu[i]=-1;sum[i]=1;
        }
        for(int j=0;j<tot;j++){
            if(1LL*i*prime[j]>10000000LL)break;
            check[i*prime[j]]=1;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                sum[i*prime[j]]=mu[i];
                break;
            }
            else{
                mu[i*prime[j]]=-mu[i];
                sum[i*prime[j]]=mu[i]-sum[i];
            }
        }
    }
    for(int i=1;i<=10000000;i++)sum[i]=sum[i-1]+sum[i];
}
int main(){
    scanf("%d",&t);
    euler();
    while(t--){
        scanf("%d%d",&x,&y);
        if(x>y)swap(x,y);
        ll ans=0;
        for(int i=1,j;i<=x;i=j+1){
            j=min(x/(x/i),y/(y/i));
            ans+=1LL*(x/i)*(y/i)*(sum[j]-sum[i-1]);
//            cout<<"??"<<endl;

        printf("%lld\n",ans);
    }
    return 0;
}
/*
2
10 10
100 100
*/
