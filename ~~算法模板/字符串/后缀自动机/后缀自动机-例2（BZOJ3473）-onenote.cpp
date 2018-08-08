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
const ll INFF=1200000000000000000ll;
//const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=2e6+10;
const int MOD=998244353;
//const int MOD=1e9+7;
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

int n,k;

const int MAXL=2e6+5;
string s[MAXL];
const int MAXCH=26;
const char CH='a';
struct SAM{
    int maxlen[MAXL],minlen[MAXL],trans[MAXL][MAXCH],slink[MAXL];
    int c[MAXL],a[MAXL];
    int last[MAXL],cnt[MAXL];
    ll dp[MAXL];
    int tot;
    int new_state(int _maxlen,int _minlen,int *_trans,int _slink){
        maxlen[tot]=_maxlen;
        minlen[tot]=_minlen;
        for(int i=0;i<MAXCH;i++){
            if(_trans==NULL)trans[tot][i]=-1;
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
            minlen[z]=1;
            slink[z]=0;
            return z;
        }
        int x=trans[v][c];
        if(maxlen[v]+1==maxlen[x]){
            minlen[z]=maxlen[x]+1;
            slink[z]=x;
            return z;
        }
        int y=new_state(maxlen[v]+1,-1,trans[x],slink[x]);
        minlen[x]=maxlen[y]+1;
        slink[x]=y;
        minlen[z]=maxlen[y]+1;
        slink[z]=y;
        int w=v;
        while(w!=-1&&trans[w][c]==x){
            trans[w][c]=y;
            w=slink[w];
        }
        minlen[y]=maxlen[slink[y]]+1;
        return z;
    }
    void toposort(){
        for(int i=1;i<tot;++i)++c[maxlen[i]];
        for(int i=1;i<tot;i++)c[i]+=c[i-1];
        for(int i=tot-1;i>=1;--i)a[c[maxlen[i]]--]=i;
    }
    void solve(){
        ll ans=0;int u;
        for(int i=1;i<=n;++i){
            u=0;
            for(int j=0;j<s[i].size();j++){
                u=trans[u][s[i][j]-CH];
                int now=u;
                while(now!=-1&&last[now]!=i)
                    ++cnt[now],last[now]=i,now=slink[now];
            }
        }
        toposort();
        cnt[0]=0;
        for(int i=1;i<tot;++i)
            u=a[i],dp[u]=dp[slink[u]]+(cnt[u]>=k?maxlen[u]-minlen[u]+1:0);
        for(int i=1;i<=n;++i){
            u=0;ans=0;
            for(int j=0;j<s[i].size();j++){
                u=trans[u][s[i][j]-CH];
                ans+=dp[u];
            }
            printf("%lld ",ans);
        }
    }
}sam;
int main()
{
    read(n);read(k);
    int pres=sam.new_state(0,0,NULL,-1);
    for(int i=1;i<=n;++i){
        cin>>s[i];
        pres=0;
        for(int j=0;j<s[i].size();j++)
            pres=sam.add_char(s[i][j],pres);
    }
    sam.solve();
    return 0;
}


/*
2 3
1 2


*/
