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
const int MAX=4e5+5;
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
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){x+=y;if(x>=MOD)x%=MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
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
int lcnt;
int id[MAX];
struct matrix{
    int e[3][3];
    matrix(){
        memset(e,0,sizeof(e));
    };
    matrix operator * (const matrix &tem)const{
        matrix ret;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)ret.e[i][j]=0;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                    addi(ret.e[i][j],mul(e[i][k],tem.e[k][j]));
        return ret;
    }
}val[MAX<<2],change[MAX][23],res;
int lazy[MAX<<2];
void pushup(int k){
    val[k]=val[k<<1]*val[k<<1|1];
}
void pushdown(int k,int l,int r){
    if(lazy[k]==-1)return;
    lazy[k<<1]=lazy[k<<1|1]=lazy[k];
    lazy[k]=-1;
    int mid=(l+r)/2,len=mid-l+1;
//    assert(__builtin_popcount(len)==1);
    int mi=id[len];
    val[k<<1]=change[lazy[k<<1]][mi];
    val[k<<1|1]=change[lazy[k<<1|1]][mi];

}
void build(int k,int l,int r){
    lazy[k]=-1;
    if(l==r){
        if(l>n){
            for(int i=0;i<3;i++)val[k].e[i][i]=1;
            return;
        }
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)read(val[k].e[i][j]);
        return;
    }
    int mid=(l+r)/2;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    pushup(k);
}
void update(int k,int l,int r,int ul,int ur,int who){
    if(ul<=l&&r<=ur){
        lazy[k]=who;
        int len=r-l+1,mi=id[len];
        val[k]=change[who][mi];
        return;
    }
    int mid=(l+r)/2;
    pushdown(k,l,r);
    if(ul<=mid)update(k<<1,l,mid,ul,ur,who);
    if(ur>mid)update(k<<1|1,mid+1,r,ul,ur,who);
    pushup(k);
}
matrix query(int k,int l,int r,int ql,int qr){
    if(ql<=l&&qr>=r){
        return val[k];
    }
    int mid=(l+r)/2;
    pushdown(k,l,r);
    if(qr<=mid)return query(k<<1,l,mid,ql,qr);
    else if(ql>mid)return query(k<<1|1,mid+1,r,ql,qr);
    else return query(k<<1,l,mid,ql,qr)*query(k<<1|1,mid+1,r,ql,qr);
}
int main(){
    read(n);read(m);--n;
    tot=1;
    int ans;
    while(tot<n)tot<<=1;
    build(1,1,tot);
    for(int i=1;i<=18;i++)id[1<<i]=i;
    for(int i=0;i<m;i++){
        int u,v,w;
        read(u);read(v);read(w);
        if(u==1){
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)read(change[i][0].e[j][k]);
            for(int j=1;j<18;j++)
                change[i][j]=change[i][j-1]*change[i][j-1];
            update(1,1,tot,v,w,i);
        }
        else{
            ans=0;
            res=query(1,1,tot,v,w-1);
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)addi(ans,res.e[j][k]);
            printf("%d\n",ans);
        }
    }
    return 0;
}

/*
3 4
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
2 1 2
2 1 3
2 2 3
*/
