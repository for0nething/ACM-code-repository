#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define next nxt
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;

const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=1e6+15;
const ll MOD=1e9+7;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<class T> inline
void read(T& num) {bool start=false,neg=false;char c;num=0;while((c=getchar())!=EOF) {if(c=='-') start=neg=true;else if(c>='0' && c<='9') {start=true;num=num*10+c-'0';} else if(start) break;}if(neg) num=-num;}
inline int powMM(int a,int b,int M){int ret=1;a%=M;while (b){if (b&1) ret=1LL*ret*a%M;b>>=1;a=1LL*a*a%M;}return ret;}
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

int n,m;
//par、fa分别是辅助树和实际树的父亲结点
int next[MAX],fa[MAX],ch[MAX][2],size[MAX],stk[MAX];
bool rev[MAX];
inline bool isroot(int k){
    return ch[fa[k]][0]!=k&&ch[fa[k]][1]!=k;
}
inline void pushup(int k){
    size[k]=size[ch[k][0]]+size[ch[k][1]]+1;
}
void pushdown(int k){
    int l=ch[k][0],r=ch[k][1];
    if(rev[k]){
        rev[k]^=1;rev[l]^=1;rev[r]^=1;
        swap(ch[k][0],ch[k][1]);
    }
}
void rotate(int x){
    int y=fa[x],z=fa[y],l,r;
    if(ch[y][0]==x)l=0;else l=1;r=l^1;
    if(!isroot(y)){
        if(ch[z][0]==y)ch[z][0]=x;
        else ch[z][1]=x;
    }
    fa[x]=z;fa[y]=x;fa[ch[x][r]]=y;
    ch[y][l]=ch[x][r];ch[x][r]=y;
    pushup(y);pushup(x);
}
void splay(int x){
    int top=0;stk[++top]=x;
    for(int i=x;!isroot(i);i=fa[i])stk[++top]=fa[i];
    for(int i=top;i;i--)pushdown(stk[i]);
    while(!isroot(x)){
        int y=fa[x],z=fa[y];
        if(!isroot(y)){
            if(ch[y][0]==x^ch[z][0]==y)rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}
void access(int x){
    int t=0;
    while(x){
        splay(x);ch[x][1]=t;
        t=x;x=fa[x];
    }
}
void rever(int x){
    access(x);splay(x);rev[x]^=1;
}
void link(int x,int y){
    rever(x);fa[x]=y;splay(x);
}
void cut(int x,int y){
    rever(x);access(y);splay(y);ch[y][0]=fa[x]=0;
}
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        int x;read(x);
        fa[i]=x+i;size[i]=1;
        if(fa[i]>n+1)fa[i]=n+1;
        next[i]=fa[i];
    }
    size[n+1]=1;
    read(m);
    for(int i=1;i<=m;i++){
        int opt;read(opt);
        if(opt==1){
            rever(n+1);int u;read(u);++u;
            access(u);splay(u);printf("%d\n",size[ch[u][0]]);
        }
        else{
            int x,y;read(x);read(y);++x;
            int tar=min(n+1,x+y);
            cut(x,next[x]);link(x,tar);next[x]=tar;
        }
    }
    return 0;

}

