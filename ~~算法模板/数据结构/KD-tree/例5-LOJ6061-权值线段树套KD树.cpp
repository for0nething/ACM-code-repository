#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
typedef pair<ll,ll>pll;
#define pb push_back
#define rank rankk
#define right riight
#define mp make_pair
const int maxn=5e5+5;;
const int MAX=1e9+7;

/*
    题意：二维平面，一些坐标上有一些物品。两种操作：
    1、在某坐标上放一些物品
    2、查询某个矩形范围内第k多的堆是多少个物品
    其中保证一个点只会1操作一次，强制在线

    做法：
    求第k大，显然权值线段树就可以。
    那么就只需能够快速check 权值线段树对应某权值区间在给定矩形范围内的物品数
    很显然这是一个KDT很容易解决的问题
    因此考虑权值线段树的每个结点都建一个KDT。
    注意到是在不断插入，KDT要保证复杂度需要重建。
    使用替罪羊树的想法不平衡时重建即可。
    总复杂度O(n sqrtn logn)
    空间上，插入最多5e5个，每个value在权值线段树上log层被插入（这里MAX设为1e9就是30层）
    KDT和权值线段树各需要 30*MAXN个point结点
    树套树内层的树就是一个结点池，用到哪里取哪里

*/
namespace KDT{
    const double alpha=0.75;
    const int DIM=2;
    struct point{
        int A[DIM],mmax[DIM],mmin[DIM];
        int l,r,siz;
        void init(){
            l=r=0;initval();
        }
        void initval(){
            siz=1;
            for(int i=0;i<DIM;i++)mmax[i]=mmin[i]=A[i];
        }
    }T[maxn*30];
    int TOT,Cur;
    bool cmp(int x,int y){
        return T[x].A[Cur]<T[y].A[Cur];
    }
    void update(int x){
        T[x].initval();
        int l=T[x].l,r=T[x].r;
        if(l)T[x].siz+=T[l].siz;
        if(r)T[x].siz+=T[r].siz;
        for(int i=0;i<DIM;i++){
            if(l){
                T[x].mmax[i]=max(T[x].mmax[i],T[l].mmax[i]);
                T[x].mmin[i]=min(T[x].mmin[i],T[l].mmin[i]);
            }
            if(r){
                T[x].mmax[i]=max(T[x].mmax[i],T[r].mmax[i]);
                T[x].mmin[i]=min(T[x].mmin[i],T[r].mmin[i]);
            }
        }
    }
    int id[maxn],tot;
    void build(int &x,int l,int r,int cur){
        x=0;if(l>r)return;
        int m=(l+r)/2,Cur=cur;
        nth_element(id+l,id+m,id+r+1,cmp);
        x=id[m];
        build(T[x].l,l,m-1,cur^1);
        build(T[x].r,m+1,r,cur^1);
        update(x);
    }
    void getid(int x){
        id[++tot]=x;
        if(T[x].l)getid(T[x].l);
        if(T[x].r)getid(T[x].r);
    }
    void rebuild(int &x,int cur){
        tot=0;getid(x);
        build(x,1,tot,cur);
    }
    void insert(int &x,int now,int cur){
        if(!x){x=now;return;}
        Cur=cur;
        if(cmp(now,x))insert(T[x].l,now,cur^1);
        else insert(T[x].r,now,cur^1);
        update(x);
        if(T[x].siz*alpha+3<max(T[T[x].l].siz,T[T[x].r].siz))
            rebuild(x,cur);
    }
    void addnode(int &x,int px,int py){
        TOT++;T[TOT].A[0]=px;T[TOT].A[1]=py;
        T[TOT].init();insert(x,TOT,0);
    }
    int x0,y0,x1,y1;
    int check(int x,int y){
        return x0<=x&&x<=x1&&y0<=y&&y<=y1;
    }
    int ok(point &A){
        return check(A.A[0],A.A[1]);
    }
    int allin(point &A){
        return x0<=A.mmin[0]&&A.mmax[0]<=x1 &&
               y0<=A.mmin[1]&&A.mmax[1]<=y1;
    }
    int allout(point &A){
        return A.mmax[0]<x0||x1<A.mmin[0]||
               A.mmax[1]<y0||y1<A.mmin[1];
    }
    int query(int x){
        if(!x)return 0;
        if(allin(T[x]))return T[x].siz;
        if(allout(T[x]))return 0;
        int ret=0;
        if(ok(T[x]))ret++;
        if(T[x].siz==1)return ret;
        ret+=query(T[x].l);
        ret+=query(T[x].r);
        return ret;
    }
}
struct Tnode{
    int l,r,KD_root;
    Tnode(){l=r=KD_root=0;}
}T[maxn*30];
int cnt;
void update(int &x,int px,int py,int pos,int L,int R){
    if(!x)x=++cnt;
    KDT::addnode(T[x].KD_root,px,py);
    if(L==R)return;
    int mid=(L+R)/2;
    if(pos<=mid)update(T[x].l,px,py,pos,L,mid);
    else update(T[x].r,px,py,pos,mid+1,R);
}
int query(int x,int k,int L,int R){
    if(!x)return 0;
    if(L==R)return L;
    int mid=(L+R)/2;
    if(T[x].r){
        int rk=KDT::query(T[T[x].r].KD_root);
        if(rk<k)return query(T[x].l,k-rk,L,mid);
        return query(T[x].r,k,mid+1,R);
    }
    return query(T[x].l,k,L,mid);
}
char buffer[36000000],*buf=buffer;
void read(int &x){
    for(x=0;*buf<48;++buf);
    while(*buf>=48)x=x*10+*buf-48,++buf;
}
int n,q;
int root,lastans;
int main(){
    fread(buffer,1,36000000,stdin);
    read(n);read(q);
    KDT::tot=0;
    for(int i=1;i<=q;i++){
        int opt;
        read(opt);
        if(opt==1){
            int x,y,v;read(x);read(y);read(v);
            x^=lastans;y^=lastans;v^=lastans;
            update(root,x,y,v,0,MAX);
        }
        else{
            int x1,y1,x2,y2,k;
            read(x1);read(y1);read(x2);read(y2);read(k);
            x1^=lastans;y1^=lastans;
            x2^=lastans;y2^=lastans;
            k^=lastans;
            KDT::x0=x1;KDT::y0=y1;
            KDT::x1=x2;KDT::y1=y2;
            lastans=query(root,k,0,MAX);
            if(!lastans)puts("NAIVE!ORZzyz.");
            else printf("%d\n",lastans);
        }
    }
    return 0;
}
/*
*/
