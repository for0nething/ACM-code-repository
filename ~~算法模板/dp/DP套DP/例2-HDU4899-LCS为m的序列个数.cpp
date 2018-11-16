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
const int MAX=2e4+5;
const int MOD=1e9+7;
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

int n,m,t;
char a[20],c[10]="AGCT";
int trans[(1<<15)|5][4],cnt[1<<15|5],dp[2][1<<15|5],ans[20],d[20],pre[20];

void init(){
    for(int i=0;i<(1<<n);i++){
        if(i)cnt[i]=cnt[i^(i&-i)]+1;
        for(int j=0;j<n;j++)d[j+1]=d[j]+(bool)(i&(1<<j));
        for(int k=0;k<4;k++){
            for(int j=1;j<=n;j++){
                pre[j]=max(pre[j-1],d[j]);
                if(c[k]==a[j])pre[j]=max(pre[j],d[j-1]+1);
            }
            trans[i][k]=0;
            for(int j=0;j<n;j++)if(pre[j+1]-pre[j])trans[i][k]|=(1<<j);
        }
    }
}
int main(){
    read(t);
    while(t--){
        scanf("%s",a+1);n=strlen(a+1);
        init();
        read(m);
        memset(ans,0,sizeof(ans));memset(dp,0,sizeof(dp));
        dp[0][0]=1;int p=0;
        for(int i=1;i<=m;i++,p^=1){
            memset(dp[p^1],0,sizeof(dp[p^1]));
            for(int j=0;j<(1<<n);j++)
                for(int k=0;k<4;k++)
                    addi(dp[p^1][trans[j][k]],dp[p][j]);
        }
        for(int i=0;i<(1<<n);i++)
            addi(ans[cnt[i]],dp[p][i]);
        for(int i=0;i<=n;i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}
/*
4 4
*/
