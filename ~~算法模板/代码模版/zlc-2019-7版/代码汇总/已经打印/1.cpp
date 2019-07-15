/* 
 Author: ’‘¡¢≥ø
 Result: AC	Submission_id: 797177
 Created at: Tue May 08 2018 15:47:11 GMT+0800 (CST)
 Problem_id: 809	Time: 4162	Memory: 101544
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
//typedef __int128 LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

struct node{
    int l,r;
    int A,B,P;
    LL sum,cnt;
}T[maxn*40];int tot;
LL f(int a,int b,int c,int n){
    if (a==0) return b/c*(n+1);
//    printf("f:%d %d %d %d\n",a,b,c,n);
    if (a>=c||b>=c){
        return (LL)(a/c)*n*(n+1)/2+(LL)(b/c)*(n+1)+f(a%c,b%c,c,n);
    }else{
        LL m=((LL)a*n+b)/c;
        return n*m-f(c,c-b-1,a,m-1);
    }
}
LL getsum(int a,int b,int m,int n){//C=2
    LL ans=a*((LL)n*(n+1)/2)+(LL)b*(n+1)-f(a,b,m,n)*m;
    return ans;
}
void change(int x,LL A,LL B,LL P){
    T[x].A=A; T[x].B=B; T[x].P=P;
    T[x].sum=getsum(A,B,P,T[x].cnt-1);
}
void checknode(int &x,int L,int R){
    if (x) return;
    x=++tot;T[x].cnt=R-L+1;
    T[x].P=0;T[x].sum=0;
    T[x].l=T[x].r=0;
}
void pushdown(int x,int L,int R){
    if (T[x].P){
        int mid=(L+R)/2;
        checknode(T[x].l,L,mid);
        checknode(T[x].r,mid+1,R);
        LL A=T[x].A,B=T[x].B;
        change(T[x].l,A,B,T[x].P);
        LL s=((mid-L+1)*A+B)%T[x].P;
        change(T[x].r,A,s,T[x].P);
//        printf("%d :%lld + k(%lld) %% %d;\n",T[x].r,s,A,T[x].P);
//        printf("(%d %d) = %I64d; (cnt=%I64d)\n",mid+1,R,T[T[x].r].sum,T[T[x].r].cnt);
        T[x].P=0;
    }
}
void pushup(int x){
    T[x].sum=T[T[x].l].sum+T[T[x].r].sum;
}
void update(int &x,int l,int r,LL A,LL p,LL q,int L,int R){
    checknode(x,L,R);
    if (l<=L&&R<=r){
        change(x,p,(A+(LL)p*L)%q,q);
//        printf("%d :%d+%d*%d %% %d; = %I64d\n",x,A,p,L,q,T[x].sum);
        return;
    }int mid=(L+R)/2;
    pushdown(x,L,R);
    if (l<=mid) update(T[x].l,l,r,A,p,q,L,mid);
    if (mid<r) update(T[x].r,l,r,A,p,q,mid+1,R);
    pushup(x);
}
LL query(int x,int l,int r,int L,int R){
    if (!x) return 0;
    checknode(x,L,R);
//    if (l<=L&&R<=r) printf("%d %d:%lld\n",L,R,T[x].sum);
    if (l<=L&&R<=r) return T[x].sum;
    LL ret=0;int mid=(L+R)/2;
    pushdown(x,L,R);
    if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
    if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
    pushup(x);
    return ret;
}
void CHK(LL a,LL b,LL c,LL k){
    LL ans=0,i;
    FOR(i,0,k) ans+=(a*i+b)%c;swap(a,b);
    printf("%I64d  %I64d\n",getsum(a,b,c,k),ans);
}

int root;
int main() {
    int m,n,i,T;
    scanf("%d",&T);
    while (T--){
        tot=root=0;
        scanf("%d%d",&n,&m);
        REP(i,m){
            int op;
            scanf("%d",&op);
            if (op==1){
                int l,r,p,q;
                scanf("%d%d%d%d",&l,&r,&p,&q);
                p%=q;
                int s=(-(LL)p*(l-1)%q+q)%q;
//                printf("s=%d\n",s);
                update(root,l,r,s,p,q,1,n);
            }else{
                int l,r;
                scanf("%d%d",&l,&r);
                printf("%lld\n",query(root,l,r,1,n));
                update(root,l,r,0,0,1,1,n);
            }
        }
    }
    return 0;
}
/*
2
3 5
2 1 3
1 1 3 5 7
2 2 3
1 1 2 3 4
2 1 3

1000000000 2
1 1 1000000000 3 998244353
2 1 1000000000

*/