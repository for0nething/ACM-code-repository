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
const int MAX=1e5+10;
const int M=1e6+15;
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
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
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
const int N=5e6+10;
int n,lst,cnt,tot,cc,len[N],imark[N],pos[N],G[N],fa[N],nxt[N][2];
char a[N],*S[N];//这里处理字符串的方式比较好
struct edge{
    int t,nx;
}E[N<<1];
inline void addedge(int x,int y)//2-sat处理的图中加边
{
    E[++cnt].t=y;E[cnt].nx=G[x];G[x]=cnt;
}
inline void instrie(char *a,int len,int flg)//向trie加字符串
{
    int cur=0;
    for(int i=0;i<len;i++)
    {
        if(!nxt[cur][a[i]-'0'])nxt[cur][a[i]-'0']=++cc,fa[cc]=cur;
        cur=nxt[cur][a[i]-'0'];
    }
    pos[flg]=cur;
}
vector<int>loc[N];
int vis[N],dfn[N],low[N],s[N],tp,g[N],ig,it;
void tarjan(int x)
{
    dfn[x]=low[x]=++it;vis[x]=1;s[++tp]=x;
    for(int i=G[x];i;i=E[i].nx)
    {
        int to=E[i].t;
        if(!vis[to])tarjan(to);
        if(vis[to]!=2)low[x]=min(low[x],low[to]);
    }
    if(dfn[x]==low[x]){
        int k;++ig;
        do{k=s[tp--];vis[k]=2;g[k]=ig;}while(tp&&k!=x);
    }
}
int main()
{
    freopen("binary.in","r",stdin);
    freopen("binary.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",S[i]=a+lst);
        lst+=(len[i]=strlen(S[i]))+1;
        S[i][len[i]]='\n';
        imark[i]=-1;
        for(int j=0;j<len[i];j++)
            if(S[i][j]=='?')imark[i]=j;//标记是否有？
        if(!~imark[i]){//如果没有?
            addedge(i<<1,i<<1|1);//接下来只加到 i<<1|1中，故将i<<1指向i<<1|1 表示只有后者可以
            instrie(S[i],len[i],i<<1|1);
            pos[i<<1]=pos[i<<1|1];
        }
        else{//有?依次把?变成0\1加入到trie中
            S[i][imark[i]]='0';
            instrie(S[i],len[i],i<<1);
            S[i][imark[i]]='1';
            instrie(S[i],len[i],i<<1|1);
        }
    }
    tot=(n<<1|1)+2;
    for(int i=1;i<=cc;i++)
        addedge(tot+(fa[i]<<1),tot+(i<<1)),addedge(tot+((i<<1)|1),tot+((fa[i]<<1)|1));
        //把树链穿起来 前者是由根向下串 后者是由下向上串
    //以下为处理trie上的不同节点
    for(int i=2;i<=(n<<1|1);i++){
        loc[pos[i]].pb(i);//某个结点对应的字符串
        if(nxt[pos[i]][0])
            addedge(i,tot+(nxt[pos[i]][0]<<1));//如果i被选了 且有其他下一个为0的串 向下更新，通过之前抽象的点进行
        if(nxt[pos[i]][1])//如果i被选了 且有其他下一个为1的串 向下更新，通过之前抽象的点进行
            addedge(i,tot+(nxt[pos[i]][1]<<1));
        addedge(i,tot+(fa[pos[i]]<<1|1));//向上更新 也是通过之前抽象的点进行
        addedge(tot+(pos[i]<<1),i^1);//对应的抽象点被向下传递到了之后 该点就不能选这条链上对应的取值 而应取另一个
        addedge(tot+(pos[i]<<1|1),i^1);//对应的抽象点被向上传递到了之后 该点就不能选这条链上对应的取值 而应取另一个
    }
    //以下为处理tire上同一节点对应的字符串
    tot+=(cc<<1|1)+2;
    for(int i=1;i<=cc;i++){
        if(!loc[i].size())continue;
        addedge(loc[i][0],tot);addedge(tot+1,loc[i][0]^1);//抽象出点 将该节点的字符串对应编号串起来 先把下标0的限制加入
        for(int j=1;j<loc[i].size();j++){
            addedge(tot+(j<<1|1),tot+((j-1)<<1|1));//向上传递
            addedge(tot+(j-1<<1),tot+(j<<1));//向下传递
            addedge(loc[i][j],tot+(j<<1));//加入向下传递的
            addedge(tot+(j<<1|1),loc[i][j]^1);//当前点被向上传递到了 就不能在选 需要选另一种
            addedge(loc[i][j],tot+((j-1<<1)|1));//加入向上传递的
            addedge(tot+(j-1<<1),loc[i][j]^1);//当前点被向下传递到了，就不能选 需要选另一种
        }
        tot+=(loc[i].size()<<1|1)+2;
    }
    for(int i=1;i<=tot;i++)
        if(!vis[i])tarjan(i);
    for(int i=1;i<=n;i++)
        if(g[i<<1]==g[i<<1|1])return puts("NO"),0;
    for(int i=1;i<=n;i++)
        if(!~imark[i]);//无？的不用改
    else S[i][imark[i]]=g[i<<1|1]<g[i<<1]?'1':'0';//有?的给出对应的1or0
    printf("YES\n%s",a);
    return 0;
}
/*
5 10 4
1 2 1
2 3 3
3 4 3
4 5 7
0 1
0 5
*/
