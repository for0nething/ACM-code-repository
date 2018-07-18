/*
    POJ 1741
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
const int MAX=4e4+10;
//const int M=2500007;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const ll MOD=1e9+7;
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
struct node
{
    int to,dis,nxt;
}edg[MAX<<2];
int n,ecnt,tot,rt,k;//totΪĳһʱ�̵������ܵ��� rtΪ����
int h[MAX],siz[MAX],f[MAX];//f[i]��¼��ǰ״̬i����������Ĵ�С
int a[MAX],d[MAX];//d�����¼ĳ�㵽���ڵ�ľ���
bool vi[MAX];
int an;
void add_edge(int u,int v,int d)
{
    edg[++ecnt]=node{v,d,h[u]};
    h[u]=ecnt;
}
void dfs(int now,int fa)//������ ����siz
{
    siz[now]=1;f[now]=0;
    for(int i=h[now];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(!vi[to]&&to!=fa){
            dfs(to,now);siz[now]+=siz[to];f[now]=max(f[now],siz[to]);
        }
    }
    f[now]=max(tot-siz[now],f[now]);
//    cout<<f[now]<<endl;
    if(f[now]<f[rt])rt=now;
}
void pre(int now,int prre)//����ÿһ�㵽���ڵ����
{
    a[++a[0]]=d[now];
    for(int i=h[now];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(!vi[to]&&to!=prre){
            d[to]=d[now]+edg[i].dis;pre(to,now);
        }
    }
}
//��ʼd[now]=ds�Դ�Ϊ��׼(��֤ÿ����Ȳ���)
int cal(int now,int ds)//������ĳһ��Ϊ�� �ж���a[i]+a[j]<=k�ĵ�ԣ�������һ�����ϣ�
{
    int re=0;
    d[now]=ds;a[0]=0;pre(now,0);
    sort(a+1,a+a[0]+1);
    int l=1,r=a[0];
    while(l<r)
    {
        if(a[l]+a[r]<=k)re+=r-l,++l;
        else --r;
    }
    return re;
}
void solve(int x)//�����xΪ���ĸ���
{
    an+=cal(x,0);vi[x]=1;//��ʼΪ���и���
    for(int i=h[x];i;i=edg[i].nxt)
    {
        int to=edg[i].to;
        if(!vi[to]){
            an-=cal(to,edg[i].dis);tot=siz[to];rt=0;//ȥ����һ��������
            dfs(to,0);solve(rt);
        }
    }
}
int main()
{
    #ifdef debug
        freopen("2.in","r",stdin);
    #endif // debug
    read(n);
    for(int u,v,w,i=1;i<n;i++)
    {
        read(u);read(v);read(w);
        add_edge(u,v,w);add_edge(v,u,w);
    }
    read(k);f[0]=n+1;
    tot=n;
    dfs(1,0);
    solve(rt);
    printf("%d\n",an);
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
