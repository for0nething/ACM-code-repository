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
#define fi first
#define se second
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
const int MAX=5e5+5;
const int MOD=1e9+7;
//int MOD;
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
namespace{
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
//inline int mul(int x,int y){return 1LL*x*y%MOD;}
inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void muli(int &x,int y){x=1LL*x*y%MOD;}
inline int sub(int x,int y){int res=x-y;if(res<0)res+=MOD;return res;}
inline void subi(int &x,int y){x-=y;if(x<0)x+=MOD;}
inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

const int MAXL=2e6+5;
const int MAXCH=26;
const char CH='a';
struct SAM{
    int maxlen[MAXL],minlen[MAXL],trans[MAXL][MAXCH],slink[MAXL];
    int tot;
    int new_state(int _maxlen,int _minlen,int *_trans,int _slink){
        maxlen[tot]=_maxlen;
        minlen[tot]=_minlen;
        for(int i=0;i<MAXCH;i++){
            if(_trans==NULL)
                trans[tot][i]=-1;
            else trans[tot][i]=_trans[i];
        }
        slink[tot]=_slink;
        return tot++;
    }
    int add_char(char ch,int u){
        int c=ch-CH;
        int z=new_state(maxlen[u]+1,-1,NULL,-1);
        int v=u;
        while(v!=-1&&trans[v][c]==-1){
            trans[v][c]=z;
            v=slink[v];
        }
        if(v==-1){
            minlen[z]=1;slink[z]=0;return z;
        }
        int x=trans[v][c];
        if(maxlen[v]+1==maxlen[x]){
            minlen[z]=maxlen[x]+1;
            slink[z]=x;return z;
        }
        int y=new_state(maxlen[v]+1,-1,trans[x],slink[x]);
        minlen[x]=maxlen[y]+1;
        slink[x]=y;
        minlen[z]=maxlen[y]+1;
        slink[z]=y;
        int w=v;
        while(w!=-1&&trans[w][c]==x){
            trans[w][c]=y;w=slink[w];
        }
        minlen[y]=maxlen[slink[y]]+1;
        return z;
    }
}sam;
struct seg{
    int ls,rs;
    pii val;
}s[MAX<<2];
char st[MAX],a[MAX];
int h[MAX],to[MAX],nxt[MAX],rt[MAX];
int n,m,pres,len,scnt,ecnt;
pii ans[MAX];
vector<int>qs1[MAXL],qs2[MAXL];
inline void add_edge(int u,int v){
    ++ecnt;nxt[ecnt]=h[u];to[ecnt]=v;h[u]=ecnt;
}
void insert(int &k,int lo,int l,int r){
    if(!k)k=++scnt;
    if(l==r){
        ++s[k].val.fi;s[k].val.se=-lo;
        return ;
    }
    int mid=(l+r)/2;
    if(lo<=mid)insert(s[k].ls,lo,l,mid);
    else insert(s[k].rs,lo,mid+1,r);
    s[k].val=max(s[s[k].ls].val,s[s[k].rs].val);
}
int merge(int x,int y){//将y合并到x
    if(!x||!y)return x^y;
    if(!s[x].ls&&!s[x].rs){//叶结点
        s[x].val.fi+=s[y].val.fi;//叶节点的区间长度为1 单指一种取值
        return x;
    }
    s[x].ls=merge(s[x].ls,s[y].ls),s[x].rs=merge(s[x].rs,s[y].rs);
    s[x].val=max(s[s[x].ls].val,s[s[x].rs].val);
    return x;
}
pii query(int l,int r,int k,int ql,int qr){
    if(l>=ql&&r<=qr)return s[k].val;
    int mid=(l+r)/2;
    if(qr<=mid)return query(l,mid,s[k].ls,ql,qr);
    else if(ql>mid)return query(mid+1,r,s[k].rs,ql,qr);
    else return max(query(l,mid,s[k].ls,ql,qr),query(mid+1,r,s[k].rs,ql,qr));
}
int q;
int ql[MAX],qr[MAX],sl[MAX],sr[MAX];
int fa[MAXL][23],LOG[MAXL];
void dfs(int x){
//    cout<<x<<endl;
    for(int i=h[x];i;i=nxt[i]){
        int tow=to[i];
        dfs(tow);rt[x]=merge(rt[x],rt[tow]);
    }
    for(int u:qs2[x]){
        ans[u]=query(1,m,rt[x],ql[u],qr[u]);
    }
}

int main(){
    scanf("%s",st);n=strlen(st);
    read(m);
    pres=sam.new_state(0,0,NULL,-1);
    //广义SAM 维护每个结点的线段树
    for(int i=1;i<=m;i++){
        scanf("%s",a);
//        printf("~%s\n",a);
        len=strlen(a);
        pres=0;
        for(int j=0;j<len;j++)pres=sam.add_char(a[j],pres),insert(rt[pres],i,1,m);
    }
    read(q);
    for(int i=1;i<=q;i++){
        read(ql[i]);read(qr[i]);read(sl[i]);read(sr[i]);--sl[i];--sr[i];
        qs1[sr[i]].eb(i);//字符串的结尾位置加上查询
    }
    //倍增SAM的slink
    for(int i=1;i<sam.tot;i++){
        add_edge(sam.slink[i],i);fa[i][0]=sam.slink[i];LOG[i]=LOG[i>>1]+1;
    }
//    cout<<sam.tot<<"@@"<<endl;
    for(int i=sam.tot;i<=sam.tot+4;i++)LOG[i]=LOG[i>>1]+1;
    for(int i=1;(1<<i)<sam.tot;i++)
        for(int j=0;j<sam.tot;j++)fa[j][i]=fa[fa[j][i-1]][i-1];
    for(int u=0,dep=0,i=0;i<n;i++){
        while(u!=-1&&sam.trans[u][st[i]-CH]==-1)u=sam.slink[u],dep=sam.maxlen[u];
        //完全找不到 就回到 “空”起点 直接continue
        if(u==-1){
            u=0;dep=0;continue;
        }
        u=sam.trans[u][st[i]-CH];++dep;
        for(int v:qs1[i]){
            if(dep<sr[v]-sl[v]+1)continue;//最大匹配长度小于查询子串长度 continue
            int pos=u;
            for(int j=LOG[sam.maxlen[pos]+1];j>=0;j--){
                if(sam.maxlen[fa[pos][j]]>=sr[v]-sl[v]+1)
                    pos=fa[pos][j];
                qs2[pos].eb(v);//该查询的子串在SAM的该节点中 将查询放入结点
            }
        }
    }
    dfs(0);
    for(int i=1;i<=q;i++){
        if(!ans[i].fi)ans[i].se=-ql[i];
        printf("%d %d\n",-ans[i].se,ans[i].fi);
    }
    return 0;
}

/*

5
happybirthda? 3 4
happybirth?ay 3 5
happybirthd?y 3 5
hellow?rld 3 5
helllllowooorld 3 5

1
aa??aa 7 3

10
ee?ffff 3 5

1
a??a 5 1
1
aaa?????aaa???aaa           4 2
*/
