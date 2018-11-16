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

int opt,D,m=10000;
int sx,sy,ex,ey;
ll lastans;
struct node{
    int ls,rs,min[2],max[2],v[2];
    ll sum,s;
    node(int a,int b,int c){ls=rs=0;min[0]=max[0]=v[0]=a;min[1]=max[1]=v[1]=b;s=sum=c;}
    node(){}
    int &operator[](int x){
        return v[x];
    }
    friend bool operator==(node a,node b){
        return a[0]==b[0]&&a[1]==b[1];
    }
    friend bool operator<(node a,node b){
        return a[D]!=b[D]?a[D]<b[D]:a[D^1]<b[D^1];
    }
}tmp[MAX];
bool in(int X1,int Y1,int X2,int Y2)
{
	return sx<=X1&&X2<=ex&&sy<=Y1&&Y2<=ey;
}
bool out(int X1,int Y1,int X2,int Y2)
{
	return sx>X2||ex<X1||sy>Y2||ey<Y1;
}
struct kdt{
    node t[MAX],tem;
    int root,n;
    void pushup(int x){
        int l=t[x].ls,r=t[x].rs;
        for(int i=0;i<=1;i++){
            t[x].max[i]=t[x].min[i]=t[x][i];
            if(l){
                t[x].max[i]=max(t[x].max[i],t[l].max[i]);
                t[x].min[i]=min(t[x].min[i],t[l].min[i]);
            }
            if(r){
                t[x].max[i]=max(t[x].max[i],t[r].max[i]);
                t[x].min[i]=min(t[x].min[i],t[r].min[i]);
            }
        }
        t[x].sum=t[x].s+t[l].sum+t[r].sum;
    }
    int build(int l,int r,int d){
        if(l>r)return 0;
        int mid=(l+r)>>1;
        D=d;
        nth_element(t+l,t+mid,t+r);
        t[mid].ls=build(l,mid-1,d^1);
        t[mid].rs=build(mid+1,r,d^1);
        pushup(mid);
        return mid;
    }
    void insert(int &k,bool D){
        if(!k){
            k=++n;
            t[k][0]=t[k].min[0]=t[k].max[0]=tem[0];
            t[k][1]=t[k].min[1]=t[k].max[1]=tem[1];
        }
        if(tem==t[k]){
            t[k].s+=tem.s;t[k].sum+=tem.s;
            return;
        }
        if(tem[D]<t[k][D])insert(t[k].ls,D^1);
        else insert(t[k].rs,D^1);
        pushup(k);
    }
    ll query(int k){
        if(!k)return 0;
        ll re=0;
        if(in(t[k].min[0],t[k].min[1],t[k].max[0],t[k].max[1]))
            return t[k].sum;
        if(out(t[k].min[0],t[k].min[1],t[k].max[0],t[k].max[1]))
            return 0;
        if(in(t[k][0],t[k][1],t[k][0],t[k][1]))
            re+=t[k].s;
        re+=query(t[k].ls);
        re+=query(t[k].rs);
        return re;
    }

}a;

int main(){
    int ns;
    read(ns);
    while(1){
        read(opt);
        if(opt==3)break;
        read(sx);read(sy);
        sx^=lastans;sy^=lastans;
        if(opt==1){
            a.tem.min[0]=a.tem.max[0]=a.tem[0]=sx;
            a.tem.min[1]=a.tem.max[1]=a.tem[1]=sy;
            read(ex);
            ex^=lastans;
            a.tem.s=a.tem.sum=ex;
            a.insert(a.root,0);
            if(a.n==m){
                a.root=a.build(1,a.n,0);
                m+=10000;
            }
        }
        else if(opt==2){
            read(ex);read(ey);
            ex^=lastans;ey^=lastans;
            lastans=a.query(a.root);
            printf("%lld\n",lastans);
        }
    }
    return 0;
}
/*
4 4
*/
