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
//#include <utility>
//#include <complex>
#include <assert.h>
//#include <limits.h>
//#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;

#define rank rankk
#define mp make_pair
#define pb push_back
#define eb push_back
//#define eb emplace_back
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
typedef pair<double,int> pdi;
typedef long double ld;
const int INF=0x3f3f3f3f;
const ll INFF=1e16;
//const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=1e5+5;
const int MOD=1e9+7;
//const ll MOD=(ll)998244353;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
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
    while (b){
        if (b&1) ret=1LL*ret*a%M;
        b>>=1;
        a=1LL*a*a%M;
    }
    return ret;
}
namespace{
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;x%=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);
/*
题意：
n点m边有向图，不能走者负。
A偏好:平局>赢>输
B偏好:赢>输>平局
分两行，分别输出n个位置A/B先走时,先手按上述偏好最终的结果

做法：
1、按此通用模版，初始全是平局，从deg为0的开始转移。按上述偏好顺序转移即可。
2、A能必平局一定平，B能必赢一定赢。A不能必定平局时，B一定阻止其平，因为是其最坏结果。
B不能必赢，A一定阻止其赢，亦然。
故A不能必平局，则必赢。B不能必赢，则必输。
拓扑排序标记点。
*/

vector<int>edg[MAX];
const int lim=2e7;
int n,m,top,tail;
int dp[MAX][2],que[(int)2e7+5],deg[MAX],cnt[MAX][2][3];
inline int mk_st(int lo,int id,int pre_st,int now_st){
    return now_st|(pre_st<<2)|(id<<4)|(lo<<5);
}
inline void ad(int lo,int id,int st){
    int tem=dp[lo][id];
    if(tem!=st){
        ++top;
        if(top>lim)top=0;
        que[top]=mk_st(lo,id,tem,st);
        dp[lo][id]=st;
    }
}
int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    read(n);read(m);
    for(int i=1;i<=m;i++){
        int u,v;read(u);read(v);
        ++deg[u];edg[v].pb(u);
    }
    for(int i=1;i<=n;i++){
        dp[i][0]=dp[i][1]=1;
        cnt[i][0][1]=cnt[i][1][1]=deg[i];
    }
    for(int i=1;i<=n;i++)
        if(!deg[i])
            ad(i,0,2),ad(i,1,0);
    while(tail!=top){
        ++tail;
        if(tail>lim)tail=0;
        int tem=que[tail];
        int lo=tem>>5,id=(tem>>4)&1,pre_st=(tem>>2)&3,now_st=tem&3;
        int pid=id^1;///前一个人
        for(int u:edg[lo]){
            --cnt[u][pid][pre_st];
            ++cnt[u][pid][now_st];
            int val=0;
            if(pid==0){
                if(cnt[u][pid][0])val=0;
                else val=(cnt[u][pid][2]?2:0);
            }
            else{
                if(cnt[u][pid][1])val=1;
                else val=(cnt[u][pid][2]?2:0);
            }
            if(val!=dp[u][pid])ad(u,pid,val);
        }
    }
    for(int i=1;i<=n;i++)
        printf("%c",dp[i][1]==2?'W':(dp[i][1]==0?'L':'D'));
    puts("");
    for(int i=1;i<=n;i++)
        printf("%c",dp[i][0]==0?'W':(dp[i][0]==2?'L':'D'));
    return 0;
}
/*
6 7 1 2 2 1 2 3 1 4 4 1 4 5 5 6


WDLDWL
DWLLWL




*/
