/*
　　给定一个N个元素的序列a，初始值全部为0，对这个序列进行以下两种操作：

　　操作1：格式为1 x k，把位置x的元素加上k（位置从1标号到N）。

　　操作2：格式为2 x y，求出区间[x,y]内所有元素的和。

说明：
    这是一个经典的树状数组问题，可以毫无压力地秒掉，现在，我们用CDQ分治解决它——带修改和查询的问题。

　　我们把他转化成一个二维偏序问题，每个操作用一个有序对(a,b)表示，其中a表示操作到来的时间，b表示操作的位置，
    时间是默认有序的，所以我们在合并子问题的过程中，就按照b从小到大的顺序合并。

　　问题来了：如何表示修改与查询？

　　具体细节请参见代码，这里对代码做一些解释，请配合代码来看。
    我们定义结构体Query包含3个元素：type，idx，val，其中idx表示操作的位置，type为1表示修改，val表示“加上的值”。
    而对于查询，我们用前缀和的思想把他分解成两个操作：sum[1,y]-sum[1,x-1]，即分解成两次前缀和的查询。
    在合并的过程中，type为2表示遇到了一个查询的左端点x-1，需要把该查询的结果减去当前“加上的值的前缀和”，
    type为3表示遇到了一个查询的右端点y，需要把查询的结果加上当前“加上的值的前缀和”，val表示“是第几个查询”。
    这样，我们就把每个操作转换成了带有附加信息的有序对(时间，位置)，然后对整个序列进行CDQ分治。

　　有几点需要注意：

对于位置相同的操作，要先修改后查询。
代码中为了方便，使用左闭右开区间。
合并问题的时候统计“加上的值的前缀和”，只能统计左边区间内的修改操作，改动查询结果的时候，只能修改右边区间内的查询结果。因为只有左边区间内的修改值对右边区间内的查询结果的影响还没有统计。
代码中，给定的数组是有初始值的，可以把每个初始值变为一个修改操作。
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

int n,m;
struct Query{
    int type,idx;
    ll val;
    bool operator<(const Query &rhs)const{//按照位置从小到大排序，修改优先于查询
        return idx==rhs.idx?type<rhs.type:idx<rhs.idx;
    }
}query[MAX];
int qidx,aidx;
ll ans[MAX];//答案数组
Query tmp[MAX];//归并用临时数组
void cdq(int L,int R){//左闭右开
    if(R-L<=1)return;
    int M=(L+R)>>1;cdq(L,M);cdq(M,R);
    ll sum=0;
    int p=L,q=M,o=0;//由左侧向右侧合并
    while(p<M &&q<R){
        if(query[p]<query[q]){//只统计左边区间内的修改值
            if(query[p].type==1)sum+=query[p].val;
            tmp[o++]=query[p++];
        }
        else{//只修改右边区间内的查询结果
            if(query[q].type==2)ans[query[q].val]-=sum;
            else if(query[q].type==3)ans[query[q].val]+=sum;
            tmp[o++]=query[q++];
        }
    }
    while(p<M)tmp[o++]=query[p++];
    while(q<R){
        if(query[q].type==2)ans[query[q].val]-=sum;
        else if(query[q].type==3)ans[query[q].val]+=sum;
        tmp[o++]=query[q++];
    }
    for(int i=0;i<o;++i)query[i+L]=tmp[i];//顺便把序排了?
}
int main()
{
    read(n);read(m);
    for(int i=1;i<=n;i++){
        query[qidx].idx=i;query[qidx].type=1;
        scanf("%lld",&query[qidx].val);++qidx;
    }
    for(int i=0;i<m;++i){
        int type;read(type);
        query[qidx].type=type;
        if(type==1)scanf("%d%lld",&query[qidx].idx,&query[qidx].val);
        else{//把查询操作分为两部分
            int l,r;read(l);read(r);
            query[qidx].idx=l-1;query[qidx].val=aidx;++qidx;
            query[qidx].type=3;query[qidx].idx=r;query[qidx].val=aidx;
            ++aidx;
        }
        ++qidx;
    }
    cdq(0,qidx);
    for(int i=0;i<aidx;++i)printf("%lld\n",ans[i]);
    return 0;
}
/*
*/
