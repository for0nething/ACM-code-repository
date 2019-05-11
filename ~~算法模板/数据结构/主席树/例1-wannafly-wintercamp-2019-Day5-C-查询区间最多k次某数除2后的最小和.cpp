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


struct node{
    int l,r,cnt;
    ll sum;
}T[MAX*100];
int tcnt,lim;
int rt[MAX];
void insert(int &k,int lo,int l,int r){
    T[++tcnt]=T[k];k=tcnt;//可以避免初始化整个主席树结点池
    ++T[k].cnt;T[k].sum+=lo;
    if(l==r)return;
    int mid=(l+r)/2;
    if(lo<=mid)insert(T[k].l,lo,l,mid);
    else insert(T[k].r,lo,mid+1,r);
}
ll query(int rl,int rr,int &cnt,int l,int r){
    if(!cnt||rl==rr)return 0LL;
    if(T[rr].cnt-T[rl].cnt<=cnt){
        cnt-=T[rr].cnt-T[rl].cnt;
        return T[rr].sum-T[rl].sum;
    }
    if(l==r){
        int ge=min(cnt,T[rr].cnt-T[rl].cnt);
        cnt-=ge;
        return 1LL*ge*l;
    }
    int cnt_r=T[T[rr].r].cnt-T[T[rl].r].cnt;
    int mid=(l+r)/2;
    ll re=query(T[rl].r,T[rr].r,cnt,mid+1,r);
    re+=query(T[rl].l,T[rr].l,cnt,l,mid);
    return re;
}
int n,q;
ll pre[MAX];//前缀和
int ql[MAX*5],qr[MAX*5],qk[MAX*5];
ll ans[MAX*5];
int a[MAX];
int main(){
    read(n);read(q);
    for(int i=1;i<=n;i++)
        read(a[i]),pre[i]=pre[i-1]+a[i];
    for(int i=1;i<=q;i++)read(ql[i]),read(qr[i]),read(qk[i]),ans[i]=pre[qr[i]]-pre[ql[i]-1];
    for(int i=30;i>=0;i--){
        tcnt=0;lim=1<<(i+1);
        int minlim=1<<i;
        for(int j=1;j<=n;j++){
            rt[j]=rt[j-1];
            while((a[j]-a[j]/2)>=minlim)
                insert(rt[j],a[j]-a[j]/2,1,lim),a[j]/=2;
        }
        for(int j=1;j<=q;j++)
            if(qk[j])
                ans[j]-=query(rt[ql[j]-1],rt[qr[j]],qk[j],1,lim);
    }
    for(int j=1;j<=q;j++)printf("%lld\n",ans[j]);
    return 0;
}

/*
3 1000000000
1 2 3

1 10
1

3 4
0 1 2
*/
