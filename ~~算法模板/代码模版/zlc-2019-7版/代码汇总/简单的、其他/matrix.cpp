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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int T;
int n,m;
struct matrix{
    int A[107][107];
    matrix(){
        memset(A,0,sizeof(A));
    }
}F[107];
matrix mul(matrix &A,matrix &B){
    matrix C;int i,j,k;
    FOR(i,0,n)
        FOR(j,0,n)
            FOR(k,0,n)
                C.A[i][j]=((LL)A.A[i][k]*B.A[k][j]+C.A[i][j])%M;
    return C;
}
char a[107];
int i,j,k;
int main(){
    int x;
    scanf("%d%d",&n,&x);
    scanf("%s",a);
    REP(i,n) F[a[i]-'0'].A[i][i+1]=1;
    REP(i,n+1) F[0].A[i][i]=F[1].A[i][i]=1;
    F[0].A[0][0]++;F[1].A[0][0]++;
    F[0].A[n][n]++;F[1].A[n][n]++;
    FOR(i,2,x) F[i]=mul(F[i-1],F[i-2]);
    printf("%d\n",F[x].A[0][n]);
}
/*
*/
