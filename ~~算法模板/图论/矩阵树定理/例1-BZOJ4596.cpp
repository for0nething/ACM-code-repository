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
const int MAX=1e6+5;
const int MOD=1e9+7;
//int MOD;
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

int a[20][20];
int det(int n){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)if(a[i][j]<0)a[i][j]+=MOD;
//    for(int i=1;i<=n;i++,printf("\n"))
//            for(int j=1;j<=n;j++)printf("%10d ",a[i][j]);
    int res=1;
    for(int i=2;i<=n;i++){
        for(int j=i;j<=n;j++)
            if(a[j][i]!=0){
                if(i!=j){
                    res=(MOD-res)%MOD;
                    for(int k=i;k<=n;k++)swap(a[i][k],a[j][k]);
                }
                break;
            }
            if(a[i][i]==0){
//                cout<<"??"<<endl;
                res=0;break;
            }
            int inv=powMM(a[i][i],MOD-2,MOD);
            for(int j=i+1;j<=n;j++){
                int mut=mul(a[j][i],inv);
                for(int k=i;k<=n;k++)
                    subi(a[j][k],mul(a[i][k],mut));
            }
            muli(res,a[i][i]);
    }
//    cout<<"res="<<res<<endl;
    return res;
}
int n,ans;
int cnt[20],eu[20][400],ev[20][400];
bool ava[20];
void dfs(int dep,int sig){
//    cout<<dep<<" "<<sig<<endl;
    if(dep==n){
        memset(a,0,sizeof(a));
        for(int i=1;i<n;i++){
            if(ava[i]){
                for(int j=1;j<=cnt[i];j++)
                    ++a[eu[i][j]][eu[i][j]],++a[ev[i][j]][ev[i][j]],--a[eu[i][j]][ev[i][j]],--a[ev[i][j]][eu[i][j]];
            }
        }
        addi(ans,mul(sig,det(n)));
        return;
    }
    ava[dep]=1;dfs(dep+1,sig);
    ava[dep]=0;dfs(dep+1,MOD-sig);

}
int main(){
    read(n);
    for(int i=1;i<n;i++){
        read(cnt[i]);
        for(int j=1;j<=cnt[i];j++)read(eu[i][j]),read(ev[i][j]);
    }
    dfs(1,1);
    printf("%d\n",ans);
    return 0;
}

/*
10000000000

9
9999999997
*/
