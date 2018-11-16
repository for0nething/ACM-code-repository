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

int t,n,m,tot;
int id[(1<<18)|5],nxt[1008][8],val[1008],dp[207][207][78];//dp[i][j][k] 看到第i种牌时 已选j张,状态集为k
queue<int>que;
inline int encode(int n_2,int n_1,int have2){//start from n-2 / n-1 /if have a pair
    int re=0;
    re=re*3+n_2;
    re=re*3+n_1;
    re=re*2+have2;
    return re;
}
inline void decode(int v,int &n_2,int &n_1,int &have2){
    have2=v%2;v>>=1;
    n_1=v%3;v/=3;
    n_2=v;
}
int get_nxt_st(int st,int cnt){//得到 从st 该位选cnt个 能转移到的状态
    int nxt_st=0;
    int n_2,n_1,have2;
    int x_2,x_1,xave2;
    for(int n=0;n<18;n++){
        if(st&(1<<n)){
            decode(n,n_2,n_1,have2);
            x_2=n_1;x_1=cnt-n_2-n_1;xave2=have2;
            if(x_1>=0){
                int new_st=encode(x_2,x_1%3,xave2);
                nxt_st|=(1<<new_st);
                if(!have2&&x_1>=2){
                    new_st=encode(x_2,x_1-2,1);
                    nxt_st|=(1<<new_st);
                }
            }
        }
    }
    return nxt_st;
}
void initDP(){//初始化状态转移
    que.push(1);id[0]=++tot;
    while(!que.empty()){
        int st=que.front();que.pop();
        for(int cnt=0;cnt<=4;cnt++){
            int nxt_st=get_nxt_st(st,cnt);
            if(!id[nxt_st])id[nxt_st]=++tot,val[tot]=nxt_st,que.push(nxt_st);
            nxt[id[st]][cnt]=id[nxt_st];
        }
    }
}
int solve(){
    memset(dp,0,sizeof(dp));
    dp[0][0][1<<id[0]]=1;//0 0 0的状态encode结果就是0 所以id[0]
    for(int i=0;i<=n+2;i++){
        int lim=(i<n?4:0);//该位最多能取的数量
        for(int j=0;j<=m;j++)//已取的数量
            for(int t=1;t<=tot;t++)//所有的可能状态
                if(dp[i][j][t])
                    for(int k=0;k<=lim;k++)//枚举这一位具体取多少
                        addi(dp[i+1][j+k][nxt[t][k]],dp[i][j][t] );
    }
    int re=0;
    for(int i=1;i<=tot;i++)
        if(val[i]&2)//出现了对子
            addi(re,dp[n+3][m][i]);
    return re;
}
int main(){
    initDP();
//    cout<<tot<<endl;//总共只有68种状态
    read(t);
    for(int Case=1;Case<=t;Case++){
        read(n);read(m);
        printf("Case #%d: %d\n",Case,solve());
    }
    return 0;
}
/*
4 4
*/
