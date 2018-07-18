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
#include<bitset>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define rank rankk
#define DFT FFT
typedef unsigned long long ull;
typedef long long ll;
const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll M=1e9+7;
const ll maxn=2e5+7;
const int MAXN=1005;
const int MAX=1e5+5;
const int MAX_N=MAX;
const int N=55;
const ll MOD=1e9+7;
//const double eps=0.00000001;
//ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
void open()
{
    freopen("1004.in","r",stdin);
    freopen("out.txt","w",stdout);
}

struct MAX_CLIQUE {
    static const int N=60;

    bool G[N][N];
    int n, Max[N], Alt[N][N], ans;

    bool DFS(int cur, int tot) {
        if(cur==0) {
            if(tot>ans) {
                ans=tot;
                return 1;
            }
            return 0;
        }
        for(int i=0; i<cur; i++) {
            if(cur-i+tot<=ans) return 0;
            int u=Alt[tot][i];
            if(Max[u]+tot<=ans) return 0;
            int nxt=0;
            for(int j=i+1; j<cur; j++)
                if(G[u][Alt[tot][j]]) Alt[tot+1][nxt++]=Alt[tot][j];
            if(DFS(nxt, tot+1)) return 1;
        }
        return 0;
    }

    int MaxClique() {
        ans=0, memset(Max, 0, sizeof Max);
        for(int i=n-1; i>=0; i--) {
            int cur=0;
            for(int j=i+1; j<n; j++) if(G[i][j]) Alt[1][cur++]=j;
            DFS(cur, 1);
            Max[i]=ans;
        }
        return ans;
    }
};

MAX_CLIQUE edge;
int k;
int main() {
    scanf("%d%d", &edge.n,&k);
    for(int i=0; i<edge.n; i++)
        for(int j=0; j<edge.n; j++)
            scanf("%d", &edge.G[i][j]);
    int da=edge.MaxClique();
    printf("%.7f\n",(double)k*k*(da-1)/(2.0*da));
    return 0;
}

