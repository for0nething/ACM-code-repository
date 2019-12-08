#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
typedef pair<ll,ll>pll;
#define pb push_back
#define rank rankk
#define right riight
#define mp make_pair
const int MAX=5e5+5;
/*
    题意:
    n个点，m辆车，一辆车固定时间从某点出发固定时间到达另一点
    0时刻在1点，想最小化一个式子到达n
    式子为 sum(wait_time) + final_time
    其中wait_time为AT^2+BT+C，T为在某一节点的等候时间 final_time为最终到达n点的时间
    做法：
    显然这种二次式子可以斜率优化，对每个结点维护一个下凸壳即可
    按时间维护序列后某个点的凸壳新插的点横坐标单调递增，由于系数都是固定的，查询的斜率也是单调递增的，
    故只需要维护每个凸壳当前到的位置即可
*/
int n,m;
ll a,b,c;
inline ll sqr(const int x){return (ll)x*x;}
struct convex_hull{
    typedef pll point;
#define x first
#define y second
    vector<point> p;
    int head,tail;
    convex_hull():head(0),tail(0){}
    inline void init(){
        head=tail=0;
    }
    inline ll cross(point &p,point &q,point &r){
        return (q.x-p.x)*(r.y-p.y)-(q.y-p.y)*(r.x-p.x);
    }
    inline void insert(ll x,ll y){
        point q(x,y);
        while(head>tail+1&&cross(p[head-1],p[head],q)<=0LL)--head;
        p.resize(head+2);
        p[++head]=q;
    }
    inline ll update(ll x){
        ll tm=x;
        if(head<=tail)return -1;
        x=2*a*x+b;
        while(head>tail+1&&(p[tail+2].y-p[tail+1].y)<=x*(p[tail+2].x-p[tail+1].x))++tail;
        return p[tail+1].y+x*(tm-p[tail+1].x)+c-a*tm*tm;
    }
#undef x
#undef y
}hull[MAX];
int st[MAX],en[MAX];
vector<int>ot[1005],in[1005];
ll dp[MAX];
ll ans=0x3f3f3f3f3f3f3f3f;
int main(){
    scanf("%d%d%lld%lld%lld",&n,&m,&a,&b,&c);
    for(int u,v,i=1;i<=m;i++){
        scanf("%d%d%d%d",&st[i],&en[i],&u,&v);
        ot[u].pb(i);in[v].pb(i);
    }
    for(int i=1;i<=n;i++)hull[i].init();
    hull[1].insert(0,0);
    for(int i=1;i<=1000;i++){
        for(int id:in[i]){
            if(dp[id]==-1)continue;
            if(en[id]==n)ans=min(ans,dp[id]+i);
            int pos=en[id],x=i,y=dp[id]+1LL*a*i*i;
            hull[pos].insert(x,y);
        }
        for(int id:ot[i]){
            int pos=st[id];
            dp[id]=hull[pos].update(i);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
/*

100

a


*/
