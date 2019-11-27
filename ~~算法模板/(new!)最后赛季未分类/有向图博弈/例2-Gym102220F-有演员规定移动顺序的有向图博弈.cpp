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
两支队伍在一张n 个点m 条边的有向图上玩游戏，6 个人
轮流移动棋子行动一步，不能移动的人所属队伍输。
正常人希望赢，不能赢则希望平局；而演员希望输，不能输
则希望平局。
对于每个点计算棋子放在该点开始游戏时最后的游戏结果。

做法：
状态：fi;j 表示棋子位于i，目前轮到第j 个人行动时最终的
游戏结果。
定义-1 表示A 胜，0 表示平局，1 表示B 胜，则每个状
态的转移是min 或者max。
一开始假设所有状态的值都是0，并维护出cnt 数组表示每
个状态后继状态中有几个-1; 0; 1，用于O(1) 计算一个状态的值。
对于所有不能行动的状态，重新设定它的状态值，并加入队列。
用SPFA 的方式依次松弛每个值发生改变的状态的前驱状态，并更新cnt 数组。
每个状态的值只会在-1; 0; 1 之间切换常数次。
时间复杂度O(n + m)。
（实现中上述-1,0,1对应于 0,1,2）
*/
const double eps=1e-8;
const int lim=(1<<23);
int t,n,m,top,pos;
int deg[MAX],who[MAX],que[(int)2e7+5],bel[MAX];
vector<int>edg[MAX];
char a[20];
int dp[MAX][8],cnt[MAX][8][4];
inline int mk_st(int lo,int id,int tem,int st){
    return st|(tem<<2)|(id<<4)|(lo<<7);
}
inline void ad(int lo,int id,int st){
    int tem=dp[lo][id];///之前转移的状态
    if(st!=tem){
        ++top;
        if(top>lim)top=0;
        que[top]=mk_st(lo,id,tem,st);
        dp[lo][id]=st;
    }

}
int main(){
    read(t);
    while(t--){
        read(n);read(m);
        pos=top=0;
        for(int u,v,i=1;i<=m;i++){
            read(u);read(v);
            ++deg[u];
            edg[v].pb(u);
        }
        scanf("%s",a);///sequence
        for(int i=0;i<6;i++)
            who[i]=(a[i]=='A'),bel[i]=who[i];
        scanf("%s",a);///actor
        for(int i=0;i<6;i++)
            who[i]^=(a[i]=='1');
        for(int i=1;i<=n;i++){
            for(int j=0;j<6;j++){
                dp[i][j]=1;
                for(int k=0;k<3;k++)cnt[i][j][k]=0;
                cnt[i][j][1]=deg[i];
            }
        }
        for(int i=1;i<=n;i++)
            if(!deg[i])
                for(int j=0;j<6;j++)
                    ad(i,j,2*bel[j]);
        while(pos!=top){
            ++pos;if(pos>lim)pos=0;
            int st=que[pos];
            int lo=st>>7,id=(st>>4)&7,pre=(st>>2)&3,now=st&3;
            int pid=id-1;///前一个人
            if(pid<0)pid+=6;
            for(int u:edg[lo]){
                --cnt[u][pid][pre];
                ++cnt[u][pid][now];
                int val=0;
                if(who[pid]){///是A
                    if(cnt[u][pid][0])val=0;///能转移到0状态
                    else val=(cnt[u][pid][1]?1:2);
                }
                else{
                    if(cnt[u][pid][2])val=2;
                    else val=(cnt[u][pid][1]?1:0);
                }
                if(val!=dp[u][pid])
                    ad(u,pid,val);
            }
        }
        for(int i=1;i<=n;i++){
            char ans=(dp[i][0]==0?'A':(dp[i][0]==1?'D':'B'));
            printf("%c",ans);
        }
        puts("");
        for(int i=1;i<=n;i++){
            deg[i]=0;
            edg[i].clear();
        }
    }
    return 0;
}
/*

*/
