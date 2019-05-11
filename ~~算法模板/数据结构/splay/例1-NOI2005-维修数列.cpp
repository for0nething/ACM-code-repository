#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define xo(a,b) ((b)&1?(a):0)
#define fi first
#define se second
#define tm tmp
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

//以下splay先插入了两个-INF（一个在前一个在后） 所以下标实际（不算-INF）从1开始 但建线段树不包含两个INF
int size[MAX],sum[MAX],upd[MAX],rev[MAX],la[MAX],ra[MAX],gss[MAX];
int val[MAX],ch[MAX][2],par[MAX],ncnt,root;
queue<int>q;
//回收x子树（线段树中对应的子树？）
void recycle(int x){
    if(ch[x][0])recycle(ch[x][0]);
    if(ch[x][1])recycle(ch[x][1]);
    q.push(x);
}
//使用垃圾回收机制的创建新结点
inline int newNode(int x){
    int cur;
    if(q.empty())cur=++ncnt;
    else cur=q.front(),q.pop();
    ch[cur][0]=ch[cur][1]=par[cur]=0;
    val[cur]=sum[cur]=gss[cur]=x;
    la[cur]=ra[cur]=max(0,x);
    upd[cur]=rev[cur]=0;
    size[cur]=1;
    return cur;
}
//x在其fa的哪个方向上（0左 1右 儿子）
inline bool chk(int x){
    return ch[par[x]][1]==x;
}
//线段树中的pushup
inline void pushup(int x){
    int l=ch[x][0],r=ch[x][1];
    size[x]=size[l]+size[r]+1;//??一个结点只有一个点？
    sum[x]=sum[l]+sum[r]+val[x];
    la[x]=max(la[l],sum[l]+val[x]+la[r]);
    ra[x]=max(ra[r],sum[r]+val[x]+ra[l]);
    gss[x]=max(ra[l]+val[x]+la[r],max(gss[l],gss[r]));
}
//单次旋转 将x旋转到其fa的位置
inline void rotate(int x){
    int y=par[x],z=par[y],k=chk(x),w=ch[x][k^1];
    ch[y][k]=w;par[w]=y;
    ch[z][chk(y)]=x;par[x]=z;
    ch[x][k^1]=y;par[y]=x;
    pushup(y);pushup(x);
}
//下传lazy标记（这里是lazy和rev）
inline void pushdown(int x){
    int l=ch[x][0],r=ch[x][1];
    if(upd[x]){
        upd[x]=rev[x]=0;
        if(l){
            upd[l]=1;val[l]=val[x];
            sum[l]=val[x]*size[l];
            la[l]=ra[l]=max(sum[l],0);
            gss[l]=val[x]<0?val[x]:sum[l];
        }
        if(r){
            upd[r]=1;val[r]=val[x];
            sum[r]=val[x]*size[r];
            la[r]=ra[r]=max(sum[r],0);
            gss[r]=val[x]<0?val[x]:sum[r];
        }
    }
    if(rev[x]){
        rev[l]^=1;rev[r]^=1;rev[x]=0;
        swap(la[l],ra[l]);swap(la[r],ra[r]);
        swap(ch[l][0],ch[l][1]);
        swap(ch[r][0],ch[r][1]);
    }
}
//splay操作 将x结点移动到goal的子节点（默认goal是0表示将x移动到根）
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
//建立二叉（类线段树用splay维护）
int build(int l,int r,int *arr){
    if(l>r)return 0;
    int mid=(l+r)>>1,cur=newNode(arr[mid]);
    if(l==r)return cur;
    if((ch[cur][0]=build(l,mid-1,arr)))par[ch[cur][0]]=cur;
    if((ch[cur][1]=build(mid+1,r,arr)))par[ch[cur][1]]=cur;
    pushup(cur);
    return cur;
}
//查询第k个
inline int kth(int k){
    int cur=root;
    while(1){
        pushdown(cur);
        if(ch[cur][0]&&k<=size[ch[cur][0]])
            cur=ch[cur][0];
        else if(k>size[ch[cur][0]]+1){
            k-=size[ch[cur][0]]+1;cur=ch[cur][1];
        }
        else return cur;
    }
}
//在x位置后插入y
inline void insert(int x,int y){
    int u=kth(x+1),v=kth(x+2);
    splay(u);splay(v,u);
    ch[v][0]=y;par[y]=v;
    pushup(v);pushup(u);
}
//查询数组x开始y个元素之间的和
inline int qsum(int x,int y){
    int u=kth(x),v=kth(x+y+1);
    splay(u);splay(v,u);
    return sum[ch[v][0]];
}
//最大子段和
inline int qgss(){
    return gss[root];
}
//删除数组x开始y个元素
inline void remove(int x,int y){
    int u=kth(x),v=kth(x+y+1);
    splay(u);splay(v,u);
    recycle(ch[v][0]);
    ch[v][0]=0;
    pushup(v);pushup(u);
}
//翻转整个区间相当于翻转每个区间的两部分
inline void reverse(int x,int y){
    int u=kth(x),v=kth(x+y+1);
    splay(u);splay(v,u);
    int w=ch[v][0];
    if(!upd[w]){//若非整体更新
        rev[w]^=1;
        swap(ch[w][0],ch[w][1]);
        swap(la[w],ra[w]);
        pushup(v);pushup(u);
    }
}
//将[x,y]区间更新为z
inline void update(int x,int y,int z){
    int u=kth(x),v=kth(x+y+1);
    splay(u);splay(v,u);
    int w=ch[v][0];
    upd[w]=1;val[w]=z;sum[w]=size[w]*z;
    la[w]=ra[w]=max(0,sum[w]);
    gss[w]=z<0?z:sum[w];
    pushup(v);pushup(u);
}
int n,m;
int arr[MAX];
char buf[35];
int main(){
    read(n);read(m);
    for(int i=2;i<=n+1;i++)read(arr[i]);
    gss[0]=val[0]=0xcfcfcfcf;
    arr[1]=arr[n+=2]=0xcfcfcfcf;
    build(1,n,arr);root=1;
    while(m--){
        scanf("%s",buf);
        int x,y,z;
        switch((buf[2]+buf[1])^*buf){
            case 'G'^('E'+'T')://查询区间和
                scanf("%d%d", &x, &y);
                printf("%d\n", qsum(x, y));
                break;
            case 'M'^('A'+'X')://查询最大子段和
                printf("%d\n", qgss());
                break;
            case 'R'^('E'+'V')://reverse区间
                scanf("%d%d", &x, &y);
                reverse(x, y);
                break;
            case 'M'^('A'+'K')://更新区间
                scanf("%d%d%d", &x, &y, &z);
                update(x, y, z);
                break;
            case 'D'^('E'+'L')://删除区间
                scanf("%d%d", &x, &y);
                remove(x, y);
                break;
            case 'I'^('N'+'S')://插入新区间（对应于一个子树）
                scanf("%d%d", &x, &y);
                memset(arr, 0, sizeof arr);
                for (int i = 1; i <= y; i++) {
                    scanf("%d", arr+i);
                }
                insert(x, build(1, y, arr));
                break;
        }
    }
    return 0;

}

