/*
题目来源：
2019 bytedance MW camp Day1 C

*/
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
const int MAX=2e4+5;
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

const int MAXL=2e5+5;
const int MAXCH=26;
const char CH='a';
struct SAM{
    int maxlen[MAXL],minlen[MAXL],trans[MAXL][MAXCH],slink[MAXL];
    int h[MAXL],siz[MAXL],rs[MAXL],b[MAXL];
    //rs: 某状态总出现次数
    ll sub[MAXL];
    ll sz_sum[MAXL][26],sub_sum[MAXL][26];//siz和sub的前缀和
    vector<int>nxt[MAXL];
    int tot;
    void clear(){
        for(int i=0;i<tot;i++){
            for(int j=0;j<MAXCH;j++)
                sz_sum[i][j]=sub_sum[i][j]=0;
            sub[i]=0;siz[i]=0;
            rs[i]=0;h[i]=0;b[i]=0;
            nxt[i].clear();
        }
        tot=0;

    }
    int new_state(int _maxlen,int _minlen,int *_trans,int _slink){
        maxlen[tot]=_maxlen;minlen[tot]=_minlen;
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
        rs[z]=1;
        int v=u;
        while(v!=-1&&trans[v][c]==-1){
            trans[v][c]=z;v=slink[v];
        }
        if(v==-1){
            minlen[z]=1;slink[z]=0;return z;
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
            trans[w][c]=y;w=slink[w];
        }
        minlen[y]=maxlen[slink[y]]+1;
        return z;
    }
    void init_sam(char *st){
        tot=0;
        int pres=new_state(0,0,NULL,-1);
        int len=strlen(st+1);
        for(int i=1;i<=len;i++)pres=add_char(st[i],pres);
        for(int i=0;i<tot;i++)++h[maxlen[i]],sub[i]=0;//按最大长度拓扑
        for(int i=1;i<=len;i++)h[i]+=h[i-1];
        for(int i=tot-1;i>=0;i--)b[h[maxlen[i]]--]=i;//b下标范围[1,tot]
        for(int i=tot;i>=1;i--){
            int u=b[i];rs[slink[u]]+=rs[u];
        }
        rs[0]=0;
        for(int i=tot;i>=1;i--){
            int u=b[i];
            siz[u]=rs[u];//初始为总出现次数
            for(int j=0;j<MAXCH;j++)
                if(trans[u][j]!=-1)
                    siz[u]+=siz[trans[u][j]],sub[u]+=sub[trans[u][j]];
            sub[u]+=siz[u];
            ll sum1=0,sum2=0;
            for(int j=0;j<MAXCH;j++){
                if(trans[u][j]!=-1)
                {
                    sum1+=sub[trans[u][j]];
                    sum2+=siz[trans[u][j]];
                }
                sub_sum[u][j]=sum1;
                sz_sum[u][j]=sum2;
                if(trans[u][j]!=-1)nxt[u].eb(j);
            }
        }
    }
    char a[MAXL];
    char query(ll cnt){
        int pos=0,len=0;
        --cnt;
        for(int i=0;pos!=-1;i++){
            if(cnt<rs[pos]*i){//i:已枚举的长度
                cnt%=i;return a[cnt];
            }
            else cnt-=rs[pos]*i;
            int l=-1,r=nxt[pos].size()-1;
            while(l+1<r){
                int mid=(l+r)/2;int lo=nxt[pos][mid];
                if(i*sz_sum[pos][lo]+sub_sum[pos][lo]<=cnt)l=mid;
                else r=mid;
            }
            r=nxt[pos][r];
            if(r)cnt-=i*sz_sum[pos][r-1]+sub_sum[pos][r-1];
            pos=trans[pos][r];
            if(pos==-1)break;
            a[i]=r+'a';a[i+1]=0;
        }
    }
    void print(int x=0,int len=0){
        printf("x=%d %s: siz=%d rs=%d sub=%lld\n",x,a,siz[x],rs[x],sub[x]);
        for(int i=0;i<26;i++){
            if(trans[x][i]!=-1){
                a[len]=i+'a';
                print(trans[x][i],len+1);a[len]='\0';
            }
        }
    }
}sam;
ll qs[MAX];
char a[MAX],ans[MAX];
int Case,m;
int main(){
    while(scanf("%d",&m)&&m){
        scanf("%s",a+1);
        sam.init_sam(a);
        for(int i=1;i<=m;i++){
            read(qs[i]);
            ans[i-1]=sam.query(qs[i]);
        }
        ans[m]=0;
        sam.clear();
        printf("Case #%d: %s\n",++Case,ans);
    }
    return 0;
}
