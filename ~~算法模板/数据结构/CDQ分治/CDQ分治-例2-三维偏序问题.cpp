/*
平面上有N个点，每个点的横纵坐标在[0,1e7]之间，有M个询问，
每个询问为查询在指定矩形之内有多少个点，矩形用(x1,y1,x2,y2)的方式给出，其中(x1,y1)为左下角坐标，(x2,y2)为右上角坐标。
*/
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
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=3e5+10;
const int MOD=1e9+7;
//const long double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-6;
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
inline int add(int x,int y){return (x+y)%MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

struct Query{
    int type,x,y,w,aid;//w表示对查询结果贡献（+还是-），aid是“第几个查询”
    bool operator<(const Query &rhs)const{
        return x==rhs.x?type<rhs.type:x<rhs.x;
    }
}query[MAX];
int n,m,qidx,aidx,maxy;
void addq(int type,int x,int y,int w,int aid){
    query[qidx++]=(Query){type,x,y,w,aid};
}
int ans[MAX];
namespace BIT{
    int arr[MAX];
    inline int lowbit(int num){return num&(-num);}
    void add(int idx,int val){
        while(idx<=maxy){
            arr[idx]+=val;idx+=lowbit(idx);
        }
    }
    int query(int idx){
        int ans=0;
        while(idx){
            ans+=arr[idx];
            idx-=lowbit(idx);
        }
        return ans;
    }
    void clear(int idx){
        while(idx<=maxy){
            if(arr[idx])arr[idx]=0;
            else break;
            idx+=lowbit(idx);
        }
    }
}
Query tmp[MAX];
void cdq(int L,int R){//左闭右开
    if(R-L<=1)return;
    int M=(R-L)>>1;cdq(L,M);cdq(M,R);
    int p=L,q=M,o=L;
    while(p<M&&q<R){
        if(query[p]<query[q]){
            if(query[p].type==0)BIT::add(query[p].y,1);
            tmp[o++]=query[p++];
        }
        else{
            if(query[q].type==1&&query[q].w)ans[query[q].aid]+=query[q].w*BIT::query(query[q].y);
            tmp[o++]=query[q++];
        }
    }
    while(p<M)tmp[o++]=query[p++];
    while(q<R){
        if(query[q].type==1&&query[q].w)ans[query[q].aid]+=query[q].w*BIT::query(query[q].y);
        tmp[o++]=query[q++];
    }
    for(int i=L;i<R;i++){
        BIT::clear(tmp[i].y);//清空树状数组
        query[i]=tmp[i];
    }
}
int main()
{
    read(n);read(m);
    while(n--){
        int x,y;
        read(x);read(y);++x;++y;//为了方便(防止出现负数)，把坐标转化为[1,1e7+1]
        addq(0,x,y,0,0);maxy=max(maxy,y);//修改操作无附加信息
    }
    while(m--){
        int xl,yl,xr,yr;
        read(xl);read(yl);read(xr);read(yr);
        addq(1,xl-1,yl-1,1,aidx);
        addq(1,xl-1,yr,-1,aidx);
        addq(1,xr,yl-1,-1,aidx);
        ++aidx;
        maxy=max(maxy,yr);
    }
    cdq(0,qidx);
    for(int i=0;i<aidx;i++)printf("%d\n",ans[i]);
    return 0;
}
/*
*/
