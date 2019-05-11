//#pragma comment(linker, "/STACK:1024000000,1024000000")
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
//#include <bitset>
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
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=2e5+5;
const ll MOD=998244353;
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
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

const int B=318,Bcnt=318;
int n,k,ans;
int pre[MAX],dp[MAX],tag[Bcnt],las[MAX],sum[MAX];//pre[i] 下标i前一个出现该位置值的位置
int val[Bcnt][MAX];//某块i中只作为后缀的开始出现一次的数为j的位置的dp值之和
int bel(int x){return (x-1)/B+1;}//返回x在的块的ID

void Ins(int u,int v){
    int id=bel(u);
    sum[u]-=tag[id];
    addi(ans,v);
    addi(val[id][n+sum[u]],v);
}
void update(int pos,int v){//单点加val
    int id=bel(pos);
    if(sum[pos]+tag[id]<=k)//原本是<=k的
        subi(ans,dp[pos-1]);//修改原先对ans的影响
    subi(val[id][sum[pos]+n],dp[pos-1]);//修改原先对val的影响
    sum[pos]+=v;
    if(sum[pos]+tag[id]<=k)addi(ans,dp[pos-1]);
    addi(val[id][sum[pos]+n],dp[pos-1]);
}
void update_b(int L,int R,int v){//整个区间[L,R]进行更新
    if(L>R)return;
    int bl=bel(L),br=bel(R);
    if(bl+1>=br)//在同一个块中
        for(int i=L;i<=R;i++)update(i,v);
    else{
        for(int i=L;i<=bl*B;i++)update(i,v);//修改区间的头部非完整块
        for(int i=(br-1)*B+1;i<=R;i++)update(i,v);//修改区间的尾部非完整块
        for(int i=bl+1;i<br;i++){
            if(~v)subi(ans,val[i][k-tag[i]+n]);
            else addi(ans,val[i][k-tag[i]+1+n]);
            tag[i]+=v;
        }
    }
}
int main(){
    read(n);read(k);
    for(int u,i=1;i<=n;i++){
        read(u);pre[i]=las[u];las[u]=i;
    }
    dp[0]=1;//从1转移
    Ins(1,1);
    for(int i=1;i<=n;i++){
        update_b(pre[i]+1,i,1);
        update_b(pre[pre[i]]+1,pre[i],-1);
        Ins(i+1,dp[i]=ans);
    }
    printf("%d\n",dp[n]);
    return 0;
}
/*

*/
