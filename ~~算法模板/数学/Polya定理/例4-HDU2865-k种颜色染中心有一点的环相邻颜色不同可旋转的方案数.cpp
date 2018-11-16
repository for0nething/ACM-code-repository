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
const int MAX=1e5+5;
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

int n,k,f1,f2,f3,prime[MAX],phi[MAX],p[MAX];
void init(){
    phi[1]=1;
    for(int i=2;i<=100000;i++){
        if(!p[i]){
            prime[++prime[0]]=i;phi[i]=i-1;
        }
        for(int j=1;j<=prime[0]&&i*prime[j]<=100000;j++){
            p[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];break;
            }
            else phi[i*prime[j]]=phi[i]*phi[prime[j]];
        }
    }
}
ll getphi(int x){
    if(x<=100000)return phi[x];
    ll re=x;
    for(int i=1;x>1&&i<=prime[0]&&prime[i]*prime[i]<=x;++i)
        if(x%prime[i]==0){
            re=re*(prime[i]-1)/prime[i];
            while(x%prime[i]==0)x/=prime[i];
        }
    if(x>1)re=re*(x-1)/x;
    return re%MOD;
}
const int m_num=10;
struct matrix{
    int e[m_num][m_num];
    int row,col;
    matrix(){}
    matrix(int _r,int _c):row(_r),col(_c){memset(e,0,sizeof(e));}
    matrix operator * (const matrix &tem)const{
        matrix ret=matrix(row,tem.col);
        for(int i=1;i<=ret.row;i++)
            for(int j=1;j<=ret.col;j++)
                for(int k=1;k<=ret.col;k++)
                    addi(ret.e[i][j],mul(e[i][k],tem.e[k][j]));
        return ret;
    }
    void getE(){
        for(int i=1;i<=row;i++)
            for(int j=1;j<=col;j++)e[i][j]=(i==j);
    }
}xi,an;
matrix m_qpow(matrix tem,int x){
    matrix ret=matrix(tem.row,tem.row);
    ret.getE();
    while(x){
        if(x&1)ret=ret*tem;
        x>>=1;tem=tem*tem;
    }
    return ret;
}
int getf(int d){
    if(d==1)return f1;
    else if(d==2)return f2;
    else if(d==3)return f3;
    else return (an*m_qpow(xi,d-3)).e[1][1];
}
int main(){
    init();
    xi.col=2;xi.row=2;
    an.col=2;an.row=1;
    while(~scanf("%d%d",&n,&k)){
        int ans=0;
        xi.e[1][1]=k-3;xi.e[1][2]=1;
        xi.e[2][1]=k-2;xi.e[2][2]=0;
        f2=mul(k-1,k-2);
        f1=k-1LL;
        f3=mul(f2,k-3);
        an.e[1][1]=f3;an.e[1][2]=f2;
        for(int i=1;i*i<=n;i++){
            if(n%i==0){
                addi(ans,mul(getphi(n/i),getf(i) ) );
                if(i*i!=n)
                    addi(ans,mul(getphi(i),getf(n/i)));
            }
        }
        addi(ans,MOD-mul(getphi(n),k-1) );
        muli(ans,mul(k,powMM(n,MOD-2,MOD ) ));
        printf("%d\n",ans);
    }
    return 0;
}
/*

*/
