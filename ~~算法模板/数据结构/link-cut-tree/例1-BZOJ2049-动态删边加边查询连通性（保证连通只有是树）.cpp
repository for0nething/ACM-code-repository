#include <bits/stdc++.h>
using namespace std;
#define rank rankk
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
int par[MAX],ch[MAX][2];
int stk[MAX];//pushdown的栈
bool rev[MAX];
inline bool isroot(int x){//是否是该splay的根
    return ch[par[x]][0]!=x&&ch[par[x]][1]!=x;
}
void pushdown(int k){
    int l=ch[k][0],r=ch[k][1];
    if(rev[k]){
        rev[k]^=1;rev[l]^=1;rev[r]^=1;
        swap(ch[k][0],ch[k][1]);
    }
}
void rotate(int x){
    int y=par[x],z=par[y],l,r;
    if(ch[y][0]==x)l=0;
    else l=1;
    r=l^1;
    if(!isroot(y)){
        if(ch[z][0]==y)ch[z][0]=x;
        else ch[z][1]=x;
    }
    par[x]=z;par[y]=x;par[ch[x][r]]=y;
    ch[y][l]=ch[x][r];ch[x][r]=y;
}
void splay(int x){
    int top=0;stk[++top]=x;
    for(int i=x;!isroot(i);i=par[i])
        stk[++top]=par[i];
    for(int i=top;i;i--)pushdown(stk[i]);
    while(!isroot(x)){
        int y=par[x],z=par[y];
        if(!isroot(y)){
            if(ch[y][0]==x^ch[z][0]==y)
                rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}
void access(int x){
    int t=0;
    while(x){
        splay(x);
        ch[x][1]=t;
        t=x;x=par[x];
    }
}
//将x设为根后 x到原本根的路径的点的深度发生了反转
//这里的rever函数实际上是重设真实树根
void rever(int x){
    access(x);
    splay(x);
    assert(ch[x][1]==0);
    rev[x]^=1;
}
void link(int x,int y){
    rever(x);par[x]=y;splay(x);
}
void cut(int x,int y){
    rever(x);access(y);splay(y);
    ch[y][0]=par[x]=0;
}
int find(int x){
    access(x);splay(x);
    int y=x;while(ch[y][0])y=ch[y][0];
    return y;
}
char opt[10];
int main(){
    read(n);read(m);
    while(m--){
        scanf("%s",opt);
        int u,v;read(u);read(v);
        if(opt[0]=='C')link(u,v);
        else if(opt[0]=='D')cut(u,v);
        else{
            if(find(u)==find(v))puts("Yes");
            else puts("No");
        }
    }
    return 0;

}

