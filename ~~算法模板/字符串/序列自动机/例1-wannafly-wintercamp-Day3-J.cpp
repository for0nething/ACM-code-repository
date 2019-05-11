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
typedef unsigned int ui;
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
const ll MOD=998244353;
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
template<class T> inline T add(T x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(T &x,T y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){x+=y;if(x>=MOD)x%=MOD;}
template<class T> inline T mul(T x,T y){return 1LL*x*y%MOD;}
//inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
template<class T> inline void muli(T &x,T y){x=1LL*x*y%MOD;}
template<class T> inline T sub(T x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(T &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline T half(T x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);


//序列自动机: 假设y之后第一次出现位置为nxt[x][y]
//f[x]=f[x]+f[nxt[x][y]]; 所以只与head是几有关
//trans[head][last(nextvalue)]
//保存的是第一个head处的值
struct matrix{
    int trans[30][30];
    bool have[30];
    matrix(){memset(trans,0,sizeof(trans));memset(have,0,sizeof(have));}
};
matrix mul(matrix A,matrix B){
    matrix ret;
    for(int i=0;i<=26;i++){
        if(A.have[i]){
            for(int j=0;j<=26;j++){
                if(B.have[j])
                    for(int k=0;k<=26;k++)
                        addi(ret.trans[i][k],(int)mul(A.trans[i][j],B.trans[j][k]));
                else addi(ret.trans[i][j],A.trans[i][j]);

            }
        }
        else for(int j=0;j<=26;j++)addi(ret.trans[i][j],B.trans[i][j]);
    }
    for(int i=0;i<=26;i++)ret.have[i]=A.have[i]|B.have[i];
    return ret;
}
matrix getMat(int c){
    c-='a';
    matrix re;re.have[c]=1;
    for(int i=0;i<=26;i++)re.trans[c][i]=1;
    return re;
}
int n;
char a[2005];
int main(){
    read(n);
    scanf("%s",a);
    matrix ans=getMat(a[n-1]);
    int re=0;
    for(int i=n-2;i>=0;i--)ans=mul(ans,mul(getMat(a[i]),ans));
    for(int i=0;i<26;i++)addi(re,ans.trans[i][26]);
    printf("%d\n",re);
    return 0;
}

/*

*/
