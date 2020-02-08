#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
typedef pair<ll,ll>pll;
#define pb push_back
#define rank rankk
#define right riight
#define mp make_pair
const int maxn=2e6+5;;
const int MAX=1e9+7;

/*
    题意：一棵树，分成二分图，一部分n个点，一部分m个点
          给定两个序列，分别在[1,n]，[n+1,n+m]的范围
          是否存在一棵树，其prufer序列包含以上两个子序列
    做法：上述二分图对应的prufer序列只存在唯一限制
            —— 序列中[1,n]，[n+1,n+m]的数字个数分别为 m-1,n-1
           这是因为prufer序列生成到最后时，只剩一条连接二分图两部分的边
           故右侧只被删了n-1个点，左侧只被删了m-1个点，删的点的father构成prufer序列
           因此可以将给定的两个子序列作为最终prufer的前缀，余下补1或n+1分别作为左右序列的余下部分
          之后贪心地按正常prufer序列还原的过程来做即可。
          （即最小的未出现的，是与prufer序列最前面的连，--最前面的出现次数）
*/
int n,m,ka,kb,ida,idb;
int a[maxn],b[maxn],ge[maxn];
priority_queue<int>que;
vector<pii>v;
int main(){
    scanf("%d%d%d%d",&n,&m,&ka,&kb);
    if(ka>m-1||kb>n-1){puts("No");return 0;}
    ge[1]=m-1-ka;ge[n+1]=n-1-kb;
    for(int i=1;i<=ka;i++)scanf("%d",&a[i]),++ge[a[i]];
    for(int i=1;i<=kb;i++)scanf("%d",&b[i]),++ge[b[i]];
    for(int i=1;i<=n+m;i++)if(!ge[i])que.push(-i);
    ida=idb=1;
    for(int i=1;i<=n+m-2;i++){
        int who=-que.top();que.pop();
        if(who<=n){
            int nxt=idb<=kb?b[idb]:n+1;
            v.pb(mp(who,nxt));
            --ge[nxt];if(!ge[nxt])que.push(-nxt);
            ++idb;
        }
        else{
            int nxt=ida<=ka?a[ida]:1;
            v.pb(mp(who,nxt));
            --ge[nxt];if(!ge[nxt])que.push(-nxt);
            ++ida;
        }
    }
    int tm=-que.top();que.pop();
    v.pb(mp(tm,-que.top()));
    puts("Yes");
    for(pii tmp:v)printf("%d %d\n",tmp.first,tmp.second);
    return 0;
}
/*
*/
