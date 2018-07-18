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
char a[N],*S[N];//���ﴦ���ַ����ķ�ʽ�ȽϺ�
struct edge{
    int t,nx;
}E[N<<1];
inline void addedge(int x,int y)//2-sat�����ͼ�мӱ�
{
    E[++cnt].t=y;E[cnt].nx=G[x];G[x]=cnt;
}
inline void instrie(char *a,int len,int flg)//��trie���ַ���
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
            if(S[i][j]=='?')imark[i]=j;//����Ƿ��У�
        if(!~imark[i]){//���û��?
            addedge(i<<1,i<<1|1);//������ֻ�ӵ� i<<1|1�У��ʽ�i<<1ָ��i<<1|1 ��ʾֻ�к��߿���
            instrie(S[i],len[i],i<<1|1);
            pos[i<<1]=pos[i<<1|1];
        }
        else{//��?���ΰ�?���0\1���뵽trie��
            S[i][imark[i]]='0';
            instrie(S[i],len[i],i<<1);
            S[i][imark[i]]='1';
            instrie(S[i],len[i],i<<1|1);
        }
    }
    tot=(n<<1|1)+2;
    for(int i=1;i<=cc;i++)
        addedge(tot+(fa[i]<<1),tot+(i<<1)),addedge(tot+((i<<1)|1),tot+((fa[i]<<1)|1));
        //������������ ǰ�����ɸ����´� �������������ϴ�
    //����Ϊ����trie�ϵĲ�ͬ�ڵ�
    for(int i=2;i<=(n<<1|1);i++){
        loc[pos[i]].pb(i);//ĳ������Ӧ���ַ���
        if(nxt[pos[i]][0])
            addedge(i,tot+(nxt[pos[i]][0]<<1));//���i��ѡ�� ����������һ��Ϊ0�Ĵ� ���¸��£�ͨ��֮ǰ����ĵ����
        if(nxt[pos[i]][1])//���i��ѡ�� ����������һ��Ϊ1�Ĵ� ���¸��£�ͨ��֮ǰ����ĵ����
            addedge(i,tot+(nxt[pos[i]][1]<<1));
        addedge(i,tot+(fa[pos[i]]<<1|1));//���ϸ��� Ҳ��ͨ��֮ǰ����ĵ����
        addedge(tot+(pos[i]<<1),i^1);//��Ӧ�ĳ���㱻���´��ݵ���֮�� �õ�Ͳ���ѡ�������϶�Ӧ��ȡֵ ��Ӧȡ��һ��
        addedge(tot+(pos[i]<<1|1),i^1);//��Ӧ�ĳ���㱻���ϴ��ݵ���֮�� �õ�Ͳ���ѡ�������϶�Ӧ��ȡֵ ��Ӧȡ��һ��
    }
    //����Ϊ����tire��ͬһ�ڵ��Ӧ���ַ���
    tot+=(cc<<1|1)+2;
    for(int i=1;i<=cc;i++){
        if(!loc[i].size())continue;
        addedge(loc[i][0],tot);addedge(tot+1,loc[i][0]^1);//������� ���ýڵ���ַ�����Ӧ��Ŵ����� �Ȱ��±�0�����Ƽ���
        for(int j=1;j<loc[i].size();j++){
            addedge(tot+(j<<1|1),tot+((j-1)<<1|1));//���ϴ���
            addedge(tot+(j-1<<1),tot+(j<<1));//���´���
            addedge(loc[i][j],tot+(j<<1));//�������´��ݵ�
            addedge(tot+(j<<1|1),loc[i][j]^1);//��ǰ�㱻���ϴ��ݵ��� �Ͳ�����ѡ ��Ҫѡ��һ��
            addedge(loc[i][j],tot+((j-1<<1)|1));//�������ϴ��ݵ�
            addedge(tot+(j-1<<1),loc[i][j]^1);//��ǰ�㱻���´��ݵ��ˣ��Ͳ���ѡ ��Ҫѡ��һ��
        }
        tot+=(loc[i].size()<<1|1)+2;
    }
    for(int i=1;i<=tot;i++)
        if(!vis[i])tarjan(i);
    for(int i=1;i<=n;i++)
        if(g[i<<1]==g[i<<1|1])return puts("NO"),0;
    for(int i=1;i<=n;i++)
        if(!~imark[i]);//�ޣ��Ĳ��ø�
    else S[i][imark[i]]=g[i<<1|1]<g[i<<1]?'1':'0';//��?�ĸ�����Ӧ��1or0
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
