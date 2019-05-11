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
const int MOD=1e9+7;
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
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
//inline int mul(int x,int y){return 1LL*x*y%MOD;}
inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void muli(int &x,int y){x=1LL*x*y%MOD;}
inline int sub(int x,int y){int res=x-y;if(res<0)res+=MOD;return res;}
inline void subi(int &x,int y){x-=y;if(x<0)x+=MOD;}
inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,m,tot;
int cnt[1<<14|5];
ll dis[20][20];
ll dp[20][1<<14|5];
int main(){
//    int now=1;
//    for(int i=0;i<14;i++)now*=3;
//    printf("%d\n",now*14*14);
    read(n);read(m);
    tot=(1<<n);
    for(int i=1;i<tot;i++)cnt[i]=cnt[i>>1]+(i&1);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)dis[i][j]=-INFF;
    for(int u,v,w,i=1;i<=m;i++){
        read(u);read(v);read(w);
        dis[u-1][v-1]=dis[v-1][u-1]=w;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<tot;j++)dp[i][j]=-INFF;
    for(int i=0;i<n;i++)dp[i][(1<<i)]=0;
    for(int i=0;i<tot;i++)//枚举子集
    {
        if(cnt[i]<=1)continue;
        for(int j=0;j<n;j++)//枚举树根
            if(i&(1<<j)){
                int now=i^(1<<j);//该子树除了根节点以外的部分的状态
                for(int k=0;k<n;k++)//枚举子树的根 由该子树向其转移
                    if((now&(1<<k))&&dis[j][k]>0){
                        int tmp=now^(1<<k);//该子树的除了子树根节点状态
                        for(;;tmp=now&(tmp-1)){//枚举子树除了选定的根以外的部分
                            int st=tmp|(1<<k);//该子树的实际状态
//                            cout<<"!!"<<endl;
                            dp[j][i]=max(dp[j][i],dp[j][i^st]+dp[k][st]+cnt[st]*(n-cnt[st])*dis[j][k]);
                            if(tmp==0)break;
                        }
                    }
            }
    }

    printf("%lld\n",dp[0][tot-1]);
    return 0;
}

/*
5
-5 0 5 0 0 0 3
-1 0 1 0 0 0 1

-1 0 1 0 0 -1 1
*/
