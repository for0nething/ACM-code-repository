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
typedef unsigned long long ull;
typedef long long ll;
//const int INF=0x3f3f3f3f;
const int INF=1e9;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const ll M=1e9+7;
const ll maxn=1e5+7;
const int MAXN=1005;
const int MAX=2e5+5;
const int MAX_N=MAX;
const ll MOD=1e9+7;
//const double eps=0.00000001;
//ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b){
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
/*
    匈牙利算法 BFS版 效率更高

*/
#define prev prevv
//顶点、边的编号均从0开始
//邻接表储存
struct edge
{
    int from,to,weight;
    edge(int f,int t,int w):from(f),to(t),weight(w){}
};
const int __maxNodes=MAX;
vector<int> G[__maxNodes];//存储顶点i出发的边的编号
vector<edge> edges;
typedef vector<int>::iterator iterator_t;
int num_nodes;
int num_left;
int num_right;
int num_edges;
queue<int>Q;
int prev[__maxNodes];
int matching[__maxNodes]; /* 存储求解结果 */
int check[__maxNodes];
int Hungarian()
{
    int ans=0;
    memset(matching,-1,sizeof(matching));
    memset(check,-1,sizeof(check));
    for(int i=0;i<num_left;i++)
    {
        if(matching[i]==-1)
        {
            while(!Q.empty())Q.pop();
            Q.push(i);
            prev[i]=-1;//设i为路径起点
            bool flag=false;//尚未找到增广路
            while(!Q.empty()&&!flag)
            {
                int u=Q.front();
                for(iterator_t ix=G[u].begin();ix!=G[u].end()&&!flag;++ix)
                {
                    int v=edges[*ix].to;
                    if(check[v]!=i)
                    {
                        check[v]=i;
                        Q.push(matching[v]);
                        if(matching[v]>=0)//此点为匹配点
                        {
                            prev[matching[v]]=u;
                        }
                        else//找到未匹配点，交替路变为增广路
                        {
                            flag=true;
                            int d=u,e=v;
                            while(d!=-1)
                            {
                                int t=matching[d];
                                matching[t]=e;
                                matching[e]=d;
                                d=prev[d];
                                e=t;
                            }
                        }
                    }
                }
                Q.pop();
            }
            if(matching[i]!=-1)
                ++ans;
        }
    }
    return ans;
}
int main()
{

}
