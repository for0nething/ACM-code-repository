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
const int MAX=1e6+5;
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

struct arr{
    int d[2],min[2],max[2],l,r;
};
int D,root,x,y,ans,n,m,tot,op;
inline int cmp(arr a,arr b){
    return a.d[D]<b.d[D]||(a.d[D]==b.d[D]&&a.d[D^1]<b.d[D^1]);
}
arr a[MAX];
inline void up(int k,int s){//ÓÃs¸üÐÂk
    a[k].min[0]=min(a[k].min[0],a[s].min[0]);
    a[k].max[0]=max(a[k].max[0],a[s].max[0]);
    a[k].min[1]=min(a[k].min[1],a[s].min[1]);
    a[k].max[1]=max(a[k].max[1],a[s].max[1]);
}
int build(int l,int r,int dd){
    D=dd;int mid=(l+r)>>1;
    nth_element(a+l+1,a+mid+1,a+r+1,cmp);
    a[mid].min[0]=a[mid].max[0]=a[mid].d[0];
    a[mid].min[1]=a[mid].max[1]=a[mid].d[1];
    if(l!=mid)a[mid].l=build(l,mid-1,dd^1);
    if(mid!=r)a[mid].r=build(mid+1,r,dd^1);
    if(a[mid].l)up(mid,a[mid].l);
    if(a[mid].r)up(mid,a[mid].r);
    return mid;
}
void insert(int k){
    int p=root;D=0;
    while(1){
        up(p,k);
        if(a[k].d[D]<=a[p].d[D]){
            if(!a[p].l){a[p].l=k;return;}
            p=a[p].l;
        }
        else if(!a[p].r){
            a[p].r=k;return;
        }
        else p=a[p].r;
        D^=1;
    }
}
int getdis(int k){
    int res=0;
    if(x<a[k].min[0])res+=a[k].min[0]-x;
    if(x>a[k].max[0])res+=x-a[k].max[0];
    if(y<a[k].min[1])res+=a[k].min[1]-y;
    if(y>a[k].max[1])res+=y-a[k].max[1];
    return res;
}
void ask(int k){
    int d0=abs(a[k].d[0]-x)+abs(a[k].d[1]-y);
    if(d0<ans)ans=d0;
    int dl=(a[k].l)?getdis(a[k].l):INF;
    int dr=(a[k].r)?getdis(a[k].r):INF;
    if(dl<dr){
        if(dl<ans)ask(a[k].l);
        if(dr<ans)ask(a[k].r);
    }
    else{
        if(dr<ans)ask(a[k].r);
        if(dl<ans)ask(a[k].l);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].d[0],&a[i].d[1]);
    if(n)root=build(1,n,0);
    for(int i=1;i<=m;i++){
        scanf("%d",&op);
        if(op==1){
            ++n;
            scanf("%d%d",&a[n].d[0],&a[n].d[1]);
            a[n].min[0]=a[n].max[0]=a[n].d[0];
            a[n].min[1]=a[n].max[1]=a[n].d[1];
            insert(n);
        }
        else if(op==2){
            ans=INF;
            scanf("%d%d",&x,&y);
            ask(root);
            printf("%d\n",ans);
        }
    }
    return 0;
}
/*
4 4
*/
