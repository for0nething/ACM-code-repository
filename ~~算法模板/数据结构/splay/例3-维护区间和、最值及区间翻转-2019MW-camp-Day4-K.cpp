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

int size[MAX],rev[MAX],lazy[MAX];
int ch[MAX][2],par[MAX];
ll minv[MAX],maxv[MAX],val[MAX],sum[MAX];
int ncnt,root;
inline int newNode(int x){
    int cur=++ncnt;
    ch[cur][0]=ch[cur][1]=par[cur]=0;
    val[cur]=sum[cur]=minv[cur]=maxv[cur]=x;
    lazy[cur]=0;
    size[cur]=1;
    rev[cur]=0;
    return cur;
}
inline bool chk(int x){
    return ch[par[x]][1]==x;
}
void pushup(int x){
    int l=ch[x][0],r=ch[x][1];
    size[x]=size[l]+size[r]+1;
    sum[x]=sum[l]+sum[r]+val[x];
    minv[x]=maxv[x]=val[x];
    if(l)minv[x]=min(minv[x],minv[l]),maxv[x]=max(maxv[x],maxv[l]);
    if(r)minv[x]=min(minv[x],minv[r]),maxv[x]=max(maxv[x],maxv[r]);
}
inline void rotate(int x){
    int y=par[x],z=par[y],k=chk(x),w=ch[x][k^1];
    ch[y][k]=w;par[w]=y;
    ch[z][chk(y)]=x;par[x]=z;
    ch[x][k^1]=y;par[y]=x;
    pushup(y);pushup(x);
}
inline void pushdown(int x){
    int l=ch[x][0],r=ch[x][1];
    if(lazy[x]){
        if(l){
            lazy[l]+=lazy[x];
            minv[l]+=lazy[x];maxv[l]+=lazy[x];
            val[l]+=lazy[x];
            sum[l]+=lazy[x]*size[l];
        }
        if(r){
            lazy[r]+=lazy[x];
            minv[r]+=lazy[x];maxv[r]+=lazy[x];
            val[r]+=lazy[x];
            sum[r]+=lazy[x]*size[r];
        }
        lazy[x]=0;
    }
    if(rev[x]){
        rev[l]^=1;rev[r]^=1;rev[x]=0;
        swap(ch[l][0],ch[l][1]);
        swap(ch[r][0],ch[r][1]);
    }
}
inline void splay(int x,int goal=0){
    while(par[x]!=goal){
        int y=par[x],z=par[y];
        if(z!=goal){
            if(chk(x)==chk(y))rotate(y);
            else rotate(x);
        }
        rotate(x);
    }
    if(!goal)root=x;
}
int build(int l,int r,int *arr){
    if(l>r)return 0;
    int mid=(l+r)>>1,cur=newNode(arr[mid]);
    if(l==r)return cur;
    if((ch[cur][0]=build(l,mid-1,arr)))par[ch[cur][0]]=cur;
    if((ch[cur][1]=build(mid+1,r,arr)))par[ch[cur][1]]=cur;
    pushup(cur);
    return cur;
}
inline int kth(int k){
    int cur=root;
    while(1){
        pushdown(cur);
        if(ch[cur][0]&&k<=size[ch[cur][0]])cur=ch[cur][0];
        else if(k>size[ch[cur][0]]+1){
            k-=size[ch[cur][0]]+1;cur=ch[cur][1];
        }
        else return cur;
    }
}
inline void query(int x,int y){
    int u=kth(x),v=kth(y+2);
    splay(u);splay(v,u);
    int l=ch[v][0];
    printf("%lld %lld %lld\n",sum[l],minv[l],maxv[l]);
}
inline void reverse(int x,int y){
    int u=kth(x),v=kth(y+2);
    splay(u);splay(v,u);
    int w=ch[v][0];
    rev[w]^=1;
    swap(ch[w][0],ch[w][1]);
    pushup(v);pushup(u);
}
inline void update(int x,int y,int c){//Çø¼ä¼Óc
    int u=kth(x),v=kth(y+2);
    splay(u);splay(v,u);
    int w=ch[v][0];
    minv[w]+=c;maxv[w]+=c;val[w]+=c;lazy[w]+=c;
    sum[w]+=1LL*size[w]*c;
    pushup(v);pushup(u);
}
int n,m;
int a[MAX];
char opt[10];
int main(){
    read(n);
    for(int i=2;i<=n+1;i++)read(a[i]);
    minv[0]=minv[n+2]=INF;
    maxv[0]=maxv[n+2]=-INF;n+=2;
    build(1,n,a);root=1;
    read(m);
    while(m--){
        int l,r,v;
        scanf("%s%d%d",opt,&l,&r);
        if(opt[0]=='c'){
            read(v);
            update(l,r,v);
        }
        else if(opt[0]=='r')reverse(l,r);
        else query(l,r);
    }
    return 0;
}

