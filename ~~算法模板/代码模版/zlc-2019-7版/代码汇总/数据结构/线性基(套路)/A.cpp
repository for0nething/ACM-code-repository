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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=50+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct L_B{
    LL A[63];bool have_0;
    void clear(){memset(A,0,sizeof(A));have_0=0;}
    LL XORMIN(LL x){
        int i;
        rREP(i,63) if ((A[i]^x)<x) x^=A[i];
        return x;
    }
    LL XORMAX(LL x){
        int i;
        rREP(i,63) if ((A[i]^x)>x) x^=A[i];
        return x;
    }
    void insert(LL x){
        int i;
        if (!have_0&&!XORMIN(x)) have_0=1;
        rREP(i,63) if ((x>>i)&1){
            if (!A[i]) A[i]=x;x^=A[i];
        }
    }
    void rebuild(){
        int i,j;
        rREP(i,63) rREP(j,i) if ((A[i]>>j)&1) A[i]^=A[j];
    }
    LL querykth(LL k){
        LL ret=0;int i;k-=have_0;
        REP(i,63) if (A[i]) {if(k&1) ret^=A[i];k>>=1;}
        if (k) return -1;
        return ret;
    }
}A;
int main(){
    int i,j,T,n,m,x=0;
    LL k;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        A.clear();
        REP(i,n) scanf("%lld",&k),A.insert(k);
        A.rebuild();
        scanf("%d",&m);
        printf("Case #%d:\n",++x);
        REP(i,m) scanf("%lld",&k),printf("%lld\n",A.querykth(k));
    }
}
/*
2
2
1 2
4
1 2 3 4

3
1 2 3
5
1 2 3 4 5
*/
