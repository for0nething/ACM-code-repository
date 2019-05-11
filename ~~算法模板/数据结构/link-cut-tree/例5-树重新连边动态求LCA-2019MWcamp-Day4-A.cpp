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

int n,m;
int ch[MAX][2],fa[MAX],rev[MAX],stk[MAX];
bool isroot(int k){
    return ch[fa[k]][0]!=k&&ch[fa[k]][1]!=k;
}
void pushdown(int k){
    int l=ch[k][0],r=ch[k][1];
    if(rev[k]){
        rev[k]=0;rev[l]^=1;rev[r]^=1;
        swap(ch[k][0],ch[k][1]);
    }
}
bool chk(int k){
    return ch[fa[k]][1]==k;
}
void rotate(int x){
    int y=fa[x],z=fa[y],l,r;
    l=chk(x);r=l^1;
    if(!isroot(y))ch[z][chk(y)]=x;
    fa[x]=z;fa[y]=x;fa[ch[x][r]]=y;
    ch[y][l]=ch[x][r];ch[x][r]=y;
}
void splay(int x){
    int top=0;stk[++top]=x;
    for(int i=x;!isroot(i);i=fa[i])
        stk[++top]=fa[i];
    while(top)pushdown(stk[top--]);
    while(!isroot(x)){
        int y=fa[x],z=fa[y];
        if(!isroot(y)){
            if(ch[y][0]==x^ch[z][0]==y)rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}
int access(int x){
    int re=x;
    for(int i=0;x;i=x,x=fa[x]){
        splay(x);ch[x][1]=i;
        re=x;
    }
    return re;
}
void makeroot(int x){
    access(x);splay(x);
    rev[x]^=1;
}
void link(int x,int y){//将x连接到y的下面
    makeroot(x);
    fa[x]=y;
}
void cut(int x,int y){
    makeroot(x);access(y);splay(y);
    ch[y][0]=fa[x]=0;
}
int lca(int x,int y){
    makeroot(1);
    access(x);
    return access(y);
}
int par[MAX];
int main(){
    read(n);
    for(int i=2;i<=n;i++){
        read(par[i]);link(i,par[i]);
    }
    read(m);
    while(m--){
        char opt[10];
        scanf("%s",opt);
        int u,v;
        read(u);read(v);
        if(opt[0]=='C'){
            cut(u,par[u]);
            link(u,par[u]=v);
        }
        else{
            printf("%d\n",lca(u,v));
        }

    }
    return 0;
}
/*
*/
