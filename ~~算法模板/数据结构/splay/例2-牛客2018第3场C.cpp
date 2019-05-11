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

int size[MAX],val[MAX],ch[MAX][2],par[MAX];
int ncnt,root;
queue<int>q;
void recycle(int x){
    if(ch[x][0])recycle(ch[x][0]);
    if(ch[x][1])recycle(ch[x][1]);
    q.push(x);
}
inline int newNode(int x){
    int cur;
    if(q.empty())cur=++ncnt;
    else cur=q.front(),q.pop();
    ch[cur][0]=ch[cur][1]=par[cur]=0;
    val[cur]=x;
    size[cur]=1;
    return cur;
}
inline bool chk(int x){
    return ch[par[x]][1]==x;
}
inline void pushup(int x){
    int l=ch[x][0],r=ch[x][1];
    size[x]=size[l]+size[r]+1;
}
inline void rotate(int x){
    int y=par[x],z=par[y],k=chk(x),w=ch[x][k^1];
    ch[y][k]=w;par[w]=y;
    ch[z][chk(y)]=x;par[x]=z;
    ch[x][k^1]=y;par[y]=x;
    pushup(y);pushup(x);
}
inline void splay(int x,int goal=0){
    while(par[x]!=goal){
        int y=par[x],z=par[y];
        if(z!=goal){
            if(chk(x)==chk(y))rotate(y);
            else rotate(x);
        }
        rotate(x);
    }
    if(!goal)root=x;
}
int build(int l,int r,int *arr){
    if(l>r)return 0;
    int mid=(l+r)>>1,cur=newNode(arr[mid]);
    if(l==r)return cur;
    if((ch[cur][0]=build(l,mid-1,arr)))par[ch[cur][0]]=cur;
    if((ch[cur][1]=build(mid+1,r,arr)))par[ch[cur][1]]=cur;
    pushup(cur);
    return cur;
}
inline int kth(int k){
    int cur=root;
    while(1){
        if(ch[cur][0]&&k<=size[ch[cur][0]])
            cur=ch[cur][0];
        else if(k>size[ch[cur][0]]+1)
            k-=size[ch[cur][0]]+1,cur=ch[cur][1];
        else return cur;
    }
}
inline void insert(int x,int y){
    int u=kth(x+1),v=kth(x+2);
    splay(u);splay(v,u);
    ch[v][0]=y;par[y]=v;
    pushup(v);pushup(u);
}
inline int remove(int x,int y){
    int u=kth(x),v=kth(x+y+1);
    splay(u);splay(v,u);
    int re=ch[v][0];
//    recycle(ch[v][0]);
    ch[v][0]=0;
    pushup(v);pushup(u);
    return re;
}
void dfs(int now){
    if(ch[now][0])dfs(ch[now][0]);
    if(val[now]>=1)
        printf("%d ",val[now]);
    if(ch[now][1])dfs(ch[now][1]);
}
int n,m;
int a[MAX],b[MAX];
int main(){
    read(n);read(m);
    for(int i=2;i<=n+1;i++)a[i]=i-1;
    a[1]=a[n+=2]=0xff3f3f3f;
    build(1,n,a);root=1;
    while(m--){
        int x,y;
        read(x);read(y);
        if(x==1)continue;
        int z=remove(1,x-1);
        insert(y,z);
    }
    dfs(root);
    return 0;

}

