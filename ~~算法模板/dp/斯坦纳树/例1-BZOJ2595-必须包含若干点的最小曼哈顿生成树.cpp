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
const int MAX=2e5+5;
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
int n,m,k;
int a[10][10],f[10][10][1<<10];
struct tup{
    int first,second,thd;
    tup(int _fst=0,int _sec=0,int _thd=0):first(_fst),second(_sec),thd(_thd){}
}pre[10][10][1<<10],zero;
queue<pii>que;
int vis[10][10];
void spfa(int sta){
    const static int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
    while(!que.empty()){
        pii u=que.front();que.pop();vis[u.first][u.second]=0;
        for(int k=0;k<4;k++){
            int x=dx[k]+u.first,y=dy[k]+u.second;
            if(x<0||y<0||x>=n||y>=m)continue;
            if(f[x][y][sta]>f[u.first][u.second][sta]+a[x][y]){
                f[x][y][sta]=f[u.first][u.second][sta]+a[x][y];
                pre[x][y][sta]=tup(u.first,u.second,sta);
                if(!vis[x][y])que.push(mp(x,y)),vis[x][y]=1;
            }
        }
    }
}
void dfs(int i,int j,int sta){
    if(i==INF||pre[i][j][sta].thd==0)return;
    vis[i][j]=1;tup tp=pre[i][j][sta];
    dfs(tp.first,tp.second,tp.thd);
    if(tp.first==i&&tp.second==j)dfs(i,j,sta-tp.thd);
}
int main(){
    read(n);read(m);
    memset(f,0x3f,sizeof(f));
//    fill(&f[0][0][0],&f[10][10][1<<10],INF);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            scanf("%d",&a[i][j]);
            if(!a[i][j])f[i][j][1<<(k++)]=0;
        }
    for(int sta=1;sta<(1<<k);sta++){
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                for(int s=sta&(sta-1);s;s=sta&(s-1)){
                    if(f[i][j][sta]>f[i][j][s]+f[i][j][sta-s]-a[i][j]){
                        f[i][j][sta]=f[i][j][s]+f[i][j][sta-s]-a[i][j];
                        pre[i][j][sta]=tup(i,j,s);
                    }
                }
                if(f[i][j][sta]!=INF){
                    que.push(mp(i,j));vis[i][j]=1;
                }
            }
            spfa(sta);
    }
    int x,y;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(!a[i][j]){x=i;y=j;break;}
    printf("%d\n",f[x][y][(1<<k)-1]);
    dfs(x,y,(1<<k)-1);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            if(!a[i][j])putchar('x');//景点
            else if(vis[i][j])putchar('o');//有人
            else putchar('_');
            if(j==m-1)puts("");
    }
    return 0;
}
/*
4 4
*/
