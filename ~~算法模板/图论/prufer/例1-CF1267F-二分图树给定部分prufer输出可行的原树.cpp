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
    ���⣺һ�������ֳɶ���ͼ��һ����n���㣬һ����m����
          �����������У��ֱ���[1,n]��[n+1,n+m]�ķ�Χ
          �Ƿ����һ��������prufer���а�����������������
    ��������������ͼ��Ӧ��prufer����ֻ����Ψһ����
            ���� ������[1,n]��[n+1,n+m]�����ָ����ֱ�Ϊ m-1,n-1
           ������Ϊprufer�������ɵ����ʱ��ֻʣһ�����Ӷ���ͼ�����ֵı�
           ���Ҳ�ֻ��ɾ��n-1���㣬���ֻ��ɾ��m-1���㣬ɾ�ĵ��father����prufer����
           ��˿��Խ�������������������Ϊ����prufer��ǰ׺�����²�1��n+1�ֱ���Ϊ�������е����²���
          ֮��̰�ĵذ�����prufer���л�ԭ�Ĺ����������ɡ�
          ������С��δ���ֵģ�����prufer������ǰ�������--��ǰ��ĳ��ִ�����
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
