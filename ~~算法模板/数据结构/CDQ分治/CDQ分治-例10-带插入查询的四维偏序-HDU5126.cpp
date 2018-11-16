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
const int MAX=3e5+5;
const int MOD=1e9+7;
const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-6;
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
inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n;
struct node{
    int d1,d2,d3,d4,part,opt,val;
}a[MAX],tmp3d[MAX],tmp2d[MAX];
const int LEFT=0;
const int RIGHT=1;
namespace BIT{
    int arr[MAX];
    inline int lowbit(int x){return x&-x;}
    void add(int idx){
        for(;idx<=n;idx+=lowbit(idx))++arr[idx];
    }
    int query(int idx){
        int re=0;
        for(;idx;idx-=lowbit(idx))re+=arr[idx];
        return re;
    }
    void clear(int idx){
        for(;idx<=n&&arr[idx];idx+=lowbit(idx))arr[idx]=0;
    }
}
int ans[MAX];
bool cmp1(int x,int y){
    return tmp2d[x].d3<tmp2d[y].d3||(tmp2d[x].d3==tmp2d[y].d3&&tmp2d[x].opt<tmp2d[y].opt);
}
bool cmp2(int x,int y){
    return a[x].d2<a[y].d2||(a[x].d2==a[y].d2&&a[x].opt<a[y].opt);
}
void cdq3d(int l,int r){
    if(l==r)return;
    int mid=(l+r)/2;cdq3d(l,mid);cdq3d(mid+1,r);
    int p=l,q=mid+1,o=l;
    while(p<=mid&&q<=r){
        if(cmp1(p,q)){
            if(tmp2d[p].part==LEFT&&!tmp2d[p].opt)
                BIT::add(tmp2d[p].d4);
            tmp3d[o++]=tmp2d[p++];
        }
        else{
            if(tmp2d[q].part==RIGHT&&tmp2d[q].opt)
                ans[tmp2d[q].opt]+=tmp2d[q].val*BIT::query(tmp2d[q].d4);
            tmp3d[o++]=tmp2d[q++];
        }
    }
    while(p<=mid)tmp3d[o++]=tmp2d[p++];
    while(q<=r){
        if(tmp2d[q].part==RIGHT&&tmp2d[q].opt)
        ans[tmp2d[q].opt]+=tmp2d[q].val*BIT::query(tmp2d[q].d4);
        tmp3d[o++]=tmp2d[q++];
    }
    for(int i=l;i<=r;i++)
    {
        if(tmp3d[i].part==LEFT&&!tmp3d[i].opt)
            BIT::clear(tmp3d[i].d4);
        tmp2d[i]=tmp3d[i];
    }
}
void cdq2d(int l,int r){
    if(l==r)return;
    int mid=(l+r)/2;
    cdq2d(l,mid);cdq2d(mid+1,r);
    int p=l,q=mid+1,o=l;
    while(p<=mid&&q<=r){
        if(cmp2(p,q)){
            a[p].part=LEFT;
            tmp2d[o++]=a[p++];
        }
        else{
            a[q].part=RIGHT;
            tmp2d[o++]=a[q++];
        }
    }
    while(p<=mid)
        a[p].part=LEFT,tmp2d[o++]=a[p++];
    while(q<=r)
        a[q].part=RIGHT,tmp2d[o++]=a[q++];
    for(int i=l;i<=r;i++)a[i]=tmp2d[i];
    cdq3d(l,r);
}
bool cmp(const node& lhs,const node& rhs){
    if(lhs.d1!=rhs.d1)return lhs.d1<rhs.d1;
    else if(lhs.d2!=rhs.d2)return lhs.d2<rhs.d2;
    else if(lhs.d3!=rhs.d3)return lhs.d3<rhs.d3;
    else if(lhs.d4!=rhs.d4)return lhs.d4<rhs.d4;
    else return lhs.opt<rhs.opt;
}
int t;
vector<int>v;
int cnt,opt,acnt;
int main()
{
    read(t);
    while(t--){
        read(n);cnt=acnt=0;
        v.clear();
        for(int i=0;i<n;i++){
            read(opt);
            if(opt==1){
                a[cnt].d1=i;
                read(a[cnt].d2);read(a[cnt].d3);read(a[cnt].d4);a[cnt].opt=0;
                v.pb(a[cnt].d4);++cnt;
            }
            else{
                int sx,sy,sz,ex,ey,ez;
                read(sx);read(sy);read(sz);read(ex);read(ey);read(ez);
                v.pb(sz-1);v.pb(ez);++acnt;
                a[cnt++]=node{i,ex,ey,ez,0,acnt,1};
                a[cnt++]=node{i,sx-1,ey,ez,0,acnt,-1};
                a[cnt++]=node{i,ex,sy-1,ez,0,acnt,-1};
                a[cnt++]=node{i,ex,ey,sz-1,0,acnt,-1};
                a[cnt++]=node{i,sx-1,sy-1,ez,0,acnt,1};
                a[cnt++]=node{i,sx-1,ey,sz-1,0,acnt,1};
                a[cnt++]=node{i,ex,sy-1,sz-1,0,acnt,1};
                a[cnt++]=node{i,sx-1,sy-1,sz-1,0,acnt,-1};
            }
        }
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        for(int i=0;i<cnt;i++)a[i].d4=lower_bound(v.begin(),v.end(),a[i].d4)-v.begin()+1;
        sort(a,a+cnt,cmp);

        n=v.size();

        cdq2d(0,cnt-1);
        for(int i=1;i<=acnt;i++)printf("%d\n",ans[i]),ans[i]=0;
    }
    return 0;
}
/*
2
2
1 1 1 1
2 1 1 1 1 1 1

*/
