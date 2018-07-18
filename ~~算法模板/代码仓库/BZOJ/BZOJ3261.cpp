/*
题意：
给定一个非负整数序列 {a}，初始长度为 N。
有   M个操作，有以下两种操作类型：
1 、A x：添加操作，表示在序列末尾添加一个数 x，序列的长度 N+1。
2 、Q l r x：询问操作，你需要找到一个位置 p，满足 l<=p<=r，使得：
a[p] xor a[p+1] xor … xor a[N] xor x 最大，输出最大是多少。

每次加点将trie树的这条链的权都+1
修改当然是新建一个结点（类可持久化线段树）
然后查询的时候判断一个结点存在，只要做区间减法判权是否非0
即若sum[r]-sum[l-1]=0则该结点不存在
实现的时候数列开始加入一个数0会比较好处理

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
//#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp

//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;
//const double INF=1e20;
const int INF=0x3f3f3f3f;
//const int INF= 0x7fffffff;
//const ll INF=0x3f3f3f3f3f3f3f3fll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=6e5+10;
//const int M=(1<<20)+5;
//const int M=2500007;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const int MOD=1e9+7;
//const ull MOD=1e7+7;
//const ll MOD=998244353;
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
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
    while (b){
        if (b&1LL) ret=ret*a%M;
        b>>=1LL;
        a=a*a%M;
    }
    return ret;
}

ll mul(ll a , ll b,ll Q){
    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
}

//const long double eps=-1.0;
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);
void open()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
}
//#define debug

int bin[30];
int n,m;
int a[MAX],b[MAX],rt[MAX];
struct trie{
    int cnt;//结点id
    int ch[MAX*25][2],sum[MAX*25];
    int insert(int x,int val){
        int re,y;re=y=++cnt;
        for(int i=23;i>=0;i--)//固定位数
        {
            ch[y][0]=ch[x][0];ch[y][1]=ch[x][1];
            sum[y]=sum[x]+1;
            int t=val&bin[i];t>>=i;
            x=ch[x][t];
            ch[y][t]=++cnt;
            y=ch[y][t];
        }
        sum[y]=sum[x]+1;
        return re;
    }
    int query(int l,int r,int val){
        int tmp=0;
        for(int i=23;i>=0;i--){
            int t=val&bin[i];t>>=i;
            if(sum[ch[r][t^1]]-sum[ch[l][t^1]])
                tmp+=bin[i],r=ch[r][t^1],l=ch[l][t^1];
            else r=ch[r][t],l=ch[l][t];
        }
        return tmp;
    }
}trie;
int main()
{
    bin[0]=1;
    for(int i=1;i<30;i++)bin[i]=bin[i-1]<<1;
    read(n);read(m);
    ++n;
    for(int i=2;i<=n;i++)read(a[i]);
    for(int i=1;i<=n;i++)b[i]=b[i-1]^a[i];
    for(int i=1;i<=n;i++)
        rt[i]=trie.insert(rt[i-1],b[i]);
    char ch[5];
    int l,r,x;
    while(m--)
    {
        scanf("%s",ch);
        if(ch[0]=='A'){
            ++n;
            read(a[n]);b[n]=b[n-1]^a[n];
            rt[n]=trie.insert(rt[n-1],b[n]);
        }
        else{
            read(l);read(r);read(x);
            printf("%d\n",trie.query(rt[l-1],rt[r],b[n]^x));
        }
    }
    return 0;
}
/*
1 3 1 3
2 3 2 5
*/
