//#pragma comment(linker, "/STACK:1024000000,1024000000")
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
//#include <bitset>
//#include <utility>
//#include <complex>
#include <assert.h>
//#include <limits.h>
//#include <iomanip>
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
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;

const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=5005;
const ll MOD=1e9+7;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
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
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,a,b;
const int MAXL=2e4+5;
const int MAXCH=26;
const char CH='a';
struct SAM{
    int maxlen[MAXL],minlen[MAXL],trans[MAXL][MAXCH],slink[MAXL];
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
            trans[v][c]=z;v=slink[v];
        }
        if(v==-1){
            minlen[z]=1;
            slink[z]=0;
            return z;
        }
        int x=trans[v][c];
        if(maxlen[v]+1==maxlen[x]){
            minlen[z]=maxlen[x]+1;slink[z]=x;return z;
        }
        int y=new_state(maxlen[v]+1,-1,trans[x],slink[x]);
        minlen[x]=maxlen[y]+1;slink[x]=y;
        minlen[z]=maxlen[y]+1;slink[z]=y;
        int w=v;
        while(w!=-1&&trans[w][c]==x){
            trans[w][c]=y;
            w=slink[w];
        }
        minlen[y]=maxlen[slink[y]]+1;
        return z;
    }
    int solve(char s[]){//最大匹配长度
        int len=strlen(s),lo=0;
        for(int i=0;i<len;i++){
            if(trans[lo][s[i]-CH]==-1)return i;
            else lo=trans[lo][s[i]-CH];
        }
        return len;
    }
}SAM;
int dp[MAX],max_len[MAX];//pre[i]的代价   pre[i]包含的最长从i+1开始的前缀作为子串
char str[MAX];
int main(){
    int st=SAM.new_state(0,0,NULL,-1);
    read(n);read(a);read(b);
    scanf("%s",str);
    for(int i=0;i<n;i++){
        st=SAM.add_char(str[i],st);
        max_len[i]=SAM.solve(str+i+1);
    }
    dp[0]=a;
    for(int i=1;i<n;i++){
        dp[i]=dp[i-1]+a;
        for(int j=0;j<i;j++)
            if(j+max_len[j]>=i)dp[i]=min(dp[i],dp[j]+b);
    }
    printf("%d\n",dp[n-1]);
    return 0;
}
/*

*/
