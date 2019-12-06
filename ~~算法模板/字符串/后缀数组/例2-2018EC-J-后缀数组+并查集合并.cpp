#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
#define pb push_back
#define rank rankk
#define mp make_pair
const int MAX=2e5+5;

/*
做法:
最初只考虑每个后缀和本身的时候，要使所有后缀值相等，
Suf_i 会得到 1/(n-i+1)的 p （这里p的总和不是1，最后要除掉）
考虑按height从大到小合并，相当于两个集合合并。
此时两部分总共的p已知，原本p的状态下集合内的val和已知
故只需列一个与新的p1',p2'有关的式子，解出新的p，更新新集合的val
最终全合并完即可
*/
int n;
int sa[MAX*3];

const int MAXN = 2e5+5;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int wa[MAXN*3],wb[MAXN*3],wv[MAXN*3],wss[MAXN*3];
int c0(int *r,int a,int b)
{
    return r[a] == r[b] && r[a+1] == r[b+1] && r[a+2] == r[b+2];
}
int c12(int k,int *r,int a,int b)
{
    if(k == 2)
    return r[a] < r[b] || ( r[a] == r[b] && c12(1,r,a+1,b+1) );
    else return r[a] < r[b] || ( r[a] == r[b] && wv[a+1] < wv[b+1] );
}
void sort(int *r,int *a,int *b,int n,int m)
{
    int i;
    for(i = 0;i < n;i++)wv[i] = r[a[i]]; for(i = 0;i < m;i++)wss[i] = 0; for(i = 0;i < n;i++)wss[wv[i]]++;
    for(i = 1;i < m;i++)wss[i] += wss[i-1];
    for(i = n-1;i >= 0;i--)
    b[--wss[wv[i]]] = a[i];
}
void dc3(int *r,int *sa,int n,int m)
{
    int i, j, *rn = r + n;
    int *san = sa + n, ta = 0, tb = (n+1)/3, tbc = 0, p; r[n] = r[n+1] = 0;
    for(i = 0;i < n;i++)if(i %3 != 0)wa[tbc++] = i; sort(r + 2, wa, wb, tbc, m);
    sort(r + 1, wb, wa, tbc, m);
    sort(r, wa, wb, tbc, m);
    for(p = 1, rn[F(wb[0])] = 0, i = 1;i < tbc;i++) rn[F(wb[i])] = c0(r, wb[i-1], wb[i]) ? p - 1 : p++;
    if(p < tbc)dc3(rn,san,tbc,p);
    else for(i = 0;i < tbc;i++)san[rn[i]] = i;
    for(i = 0;i < tbc;i++) if(san[i] < tb)wb[ta++] = san[i] * 3;
    if(n % 3 == 1)wb[ta++] = n - 1; sort(r, wb, wa, ta, m);
    for(i = 0;i < tbc;i++)wv[wb[i] = G(san[i])] = i;
    for(i = 0, j = 0, p = 0;i < ta && j < tbc;p++)
    sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for(;i < ta;p++)sa[p] = wa[i++];
    for(;j < tbc;p++)sa[p] = wb[j++];
}
//str和sa也要三倍
void da(int str[],int sa[],int rank[],int height[],int n,int m)
{
    for(int i = n;i < n*3;i++) str[i] = 0;
    dc3(str, sa, n+1, m);
    int i,j,k = 0;
    for(i = 0;i <= n;i++)rank[sa[i]] = i;
    for(i = 0;i < n; i++)
    {
        if(k) k--;
        j = sa[rank[i]-1]; while(str[i+k] == str[j+k]) k++; height[rank[i]] = k;
    }
}
int rank[MAXN*3],height[MAXN*3],last[MAX];




char ss[MAX];
int sss[MAX];

double val[MAX],p[MAX];
int fa[MAX];
int t;
vector<pii>v;
inline int find(int x){if(x==fa[x])return x;return fa[x]=find(fa[x]);}
void unite(int x,int y,int H){
    x=find(x);y=find(y);
    double px=(p[x]+p[y])/(val[x]/p[x]+ val[y]/p[y]-2*H )*(val[y]/p[y]-H),py=p[x]+p[y]-px;
    fa[x]=y;
    val[y]=val[x]*px/p[x]+H*py;
    p[y]=p[x]+p[y];
}
double sum;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%s",ss);
        n=strlen(ss);
        sum=0;v.clear();
        for(int i=0;i<n;i++)sss[i]=ss[i]-'a'+1;
        da(sss,sa,rank,height,n,26+2);
        for(int i=1;i<=n;i++){
            fa[i]=i;p[i]=1.0/(n-sa[i]);sum+=p[i];
            val[i]=1;
            v.pb(mp(height[i],i));
        }
        sort(v.begin(),v.end());
        reverse(v.begin(),v.end());
        for(pii tmp:v){
            int H=tmp.first,id1=tmp.second,id2=id1-1;
            if(id2>0)unite(id1,id2,H);
        }
        printf("%.10f\n",val[find(1)]/sum);

    }
    return 0;
}
/*
*/
