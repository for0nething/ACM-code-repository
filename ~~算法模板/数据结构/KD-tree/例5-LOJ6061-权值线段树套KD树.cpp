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
    ���⣺��άƽ�棬һЩ��������һЩ��Ʒ�����ֲ�����
    1����ĳ�����Ϸ�һЩ��Ʒ
    2����ѯĳ�����η�Χ�ڵ�k��Ķ��Ƕ��ٸ���Ʒ
    ���б�֤һ����ֻ��1����һ�Σ�ǿ������

    ������
    ���k����ȻȨֵ�߶����Ϳ��ԡ�
    ��ô��ֻ���ܹ�����check Ȩֵ�߶�����ӦĳȨֵ�����ڸ������η�Χ�ڵ���Ʒ��
    ����Ȼ����һ��KDT�����׽��������
    ��˿���Ȩֵ�߶�����ÿ����㶼��һ��KDT��
    ע�⵽���ڲ��ϲ��룬KDTҪ��֤���Ӷ���Ҫ�ؽ���
    ʹ�������������뷨��ƽ��ʱ�ؽ����ɡ�
    �ܸ��Ӷ�O(n sqrtn logn)
    �ռ��ϣ��������5e5����ÿ��value��Ȩֵ�߶�����log�㱻���루����MAX��Ϊ1e9����30�㣩
    KDT��Ȩֵ�߶�������Ҫ 30*MAXN��point���
    �������ڲ��������һ�����أ��õ�����ȡ����

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
