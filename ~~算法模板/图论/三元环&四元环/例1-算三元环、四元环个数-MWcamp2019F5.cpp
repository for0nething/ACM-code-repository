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
typedef __int128 int128; 

const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=1e5+5;
const ll MOD=1e9+7;
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

vector<int>edg[MAX],hnxt[MAX];//原图 与rank比其大的点连的情况
int128 qua[MAX],tri[MAX],trisum[MAX];//每个点在四元环、三元环内的情况个数
bool vi[3][MAX];//走i步能否到j
int deg[MAX],rank[MAX],id[MAX];
int128 cnt[MAX];
int128 dp[MAX][5];//从i走j步的方案数（相邻两次方向不同）
set<int>tem;
int n,m;
bool cmp(int x,int y){
    return deg[x]<deg[y];
}
inline void print(int128 x){
	if(x==0){printf("0\n");return;}
	int now=(int)(x%10);
	x/=10;
	if(x)print(x);
	printf("%d",now);
}
int main(){
    read(n);read(m);
    for(int u,v,i=1;i<=m;i++){
        read(u);read(v);
        edg[u].eb(v);edg[v].eb(u);
        ++deg[u];++deg[v];
    } 
    for(int i=1;i<=n;i++)dp[i][1]=deg[i],dp[i][0]=1;
    for(int i=2;i<=4;i++){//步数 
        for(int j=1;j<=n;j++){
            for(int u:edg[j])
                dp[j][i]+=dp[u][i-1];
            dp[j][i]-=dp[j][i-2]*max(0,(i-2?deg[j]-1:deg[j]));//相邻两步不同 
        }
    }
    for(int i=1;i<=n;i++)id[i]=i;
    sort(id+1,id+1+n,cmp);//按deg由小到大排序
    for(int i=1;i<=n;i++)rank[id[i]]=i;//deg大的rank大
    for(int i=1;i<=n;i++){
        for(int u:edg[i])
            if(rank[i]<rank[u])hnxt[i].eb(u);//只保存deg比其大（rank高）的
    }
    for(int i=1;i<=n;i++){
        for(int u:edg[i])vi[1][u]=1;
        for(int u:edg[i]){
            for(int v:hnxt[u]){
                if(rank[v]>rank[i])
                    ++cnt[v];
            }
        }
        tem.clear();
        for(int u:edg[i]){
            for(int v:hnxt[u]){
            	if(rank[v]<=rank[i])continue;
                qua[u]+=cnt[v]-1;
                tem.insert(v);
                if(vi[1][v])++tri[u],++tri[v],++tri[i];
            }
        }
        for(int u:tem){
        	qua[i]+=cnt[u]*(cnt[u]-1)/2;
        	qua[u]+=cnt[u]*(cnt[u]-1)/2;
		}
		for(int v:tem)cnt[v]=0;
		tem.clear();
        for(int u:edg[i])vi[1][u]=0;
    }
    for(int i=1;i<=n;i++)tri[i]/=2;
    for(int i=1;i<=n;i++)trisum[i]=-2*tri[i];
    for(int i=1;i<=n;i++)
        for(int u:edg[i])
            trisum[i]+=tri[u];
    for(int i=1;i<=n;i++){ 
		int128 ans=dp[i][4]-2*(deg[i]-1)*tri[i]-2*trisum[i]-2*qua[i];
        print(ans);
        printf("\n");
    }
    return 0;
}
/*
6 8
1 2
2 3
5 2
1 5
3 4
5 3
5 6
5 4

6 15
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
4 5
4 6
5 6

8 11
3 6
7 8
8 5
4 5
2 1
2 6
3 2
4 3
5 3
6 5
7 6
*/

