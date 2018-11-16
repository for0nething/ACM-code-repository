#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <bitset>
#include <utility>
#include <complex>
#include <assert.h>
#include <limits.h>
#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;


const int INF=0x3f3f3f3f;
//const ll INFF=1200000000000000000ll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=1e5+2;
const int MOD=1e9+7;
//const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
//const double eps=1e-6;
//#define double long double
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
//#define double long double
template<class T> inline
void read(T& num) {
    bool start=false,neg=false;
    char c;
    num=0;
    while((c=getchar())!=EOF) {
        if(c=='-') start=neg=true;
        else if(c>='0' && c<='9') {
            start=true;
            num=num*10+c-'0';
        } else if(start) break;
    }
    if(neg) num=-num;
}
inline int powMM(int a,int b,int M){
    int ret=1;
    a%=M;
    while (b){
        if (b&1) ret=1LL*ret*a%M;
        b>>=1;
        a=1LL*a*a%M;
    }
    return ret;
}
inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
//inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int SIZ=150;
const int CNT=158;
int t,n,tot;
int a[MAX],bel[MAX],cnt[MAX],st[MAX],en[MAX];

int lim;
ll tp[MAX][CNT];
ll pre[MAX],bck[MAX];
ll dp[CNT][CNT];
ll ans;
int s1,s2;
ll q1[MAX],q2[MAX];
struct BIT{
    int a[MAX];
    inline int lowbit(int x){return x&-x;}
    inline void ins_bck(int x){//��׺��
        for(;x<=lim;x+=lowbit(x))++a[x];
    }
    inline void ins_pre(int x){
        for(;x>0;x-=lowbit(x))++a[x];
    }
    inline void del_pre(int x){
        for(;x>0;x-=lowbit(x))--a[x];
    }
    inline int find_pre(int x){//С�ڵ���x�����ֵ
        while (x&&!a[x]) x^=lowbit(x);
        if (!x) return 0;
        int t=lowbit(x)>>1,y=a[x];
        while (t){
            if (y-a[x-t]) y-=a[x-t];
            else{y=a[x-t];x=x-t;}
            t>>=1;
        }
        return x;
    }
    inline int find_bck(int x){//���ڵ���x����Сֵ
        while (x<=lim&&!a[x]) x+=lowbit(x);
        if (x>lim) return lim+1;
        int t=lowbit(x)>>1,y=a[x];
        while (t){
            if (y-a[x+t]) y-=a[x+t];
            else{y=a[x+t];x=x+t;}
            t>>=1;
        }
        return x;
    }
    inline int query_pre(int x){
        int ans=0;
        while(x){
            ans+=a[x];x-=lowbit(x);
        }
        return ans;
    }
    inline int query_bck(int x){
        int ans=0;
        while(x<=lim){
            ans+=a[x];x+=lowbit(x);
        }
        return ans;
    }
    void clear_bck(int x){
        while(x<=lim){
            if(a[x])a[x]=0;else break;
            x+=lowbit(x);
        }
    }
    void clear_pre(int x){
        while(x){
            if(a[x])a[x]=0;else break;
            x-=lowbit(x);
        }
    }
    void clear(){
        memset(a,0,sizeof(a));
    }
}pts,bit,pts2;//pts为加的点
struct node{
    int val,id;
    bool operator<(const node &z)const{
        if(val!=z.val)return val<z.val;
        else return id<z.id;
    }
}c[MAX];
void cal1(){
    for(int j,i=1;i<=n;i=j){
        j=i;
        while(j<=n&&c[j].val==c[i].val){
            int who=c[j].id,st=bel[who]+1;
            while(st<=tot)tp[who][st]=cnt[st],++st;
            ++j;
        }
        for(int s=i;s<j;++s)++cnt[bel[c[s].id]];
    }
    for(int i=1;i<=tot;i++)cnt[i]=0;
}
void cal2(){
    for(int j,i=n;i>=1;i=j){
        j=i;
        while(j>=1&&c[j].val==c[i].val){
            int who=c[j].id,st=bel[who]-1;
            while(st>=1)tp[who][st]+=cnt[st],--st;
            --j;
        }
        for(int s=j+1;s<=i;++s)++cnt[bel[c[s].id]];
    }
    for(int i=1;i<=tot;i++)cnt[i]=0;
}
int qs(int id1,int id2){
    int l1=st[id1],r1=min(n,en[id1]),l2=st[id2],r2=min(n,en[id2]);
    int lo1=l1,lo2=l2,re=0;
    while(lo1<=r1&&lo2<=r2){
        if(c[lo1].val<=c[lo2].val)++lo1;
        else{++lo2;re+=r1-lo1+1;}
    }
    return re;
}
void init(){
    for(int i=1;i<=tot;i++)
        for(int j=st[i]-1;j>=1;j--)
            if(j%SIZ)tp[j][i]+=tp[j+1][i];
    for(int i=1;i<=tot;i++)
        for(int j=en[i]+1;j<=n;j++)
            if(j%SIZ!=1)tp[j][i]+=tp[j-1][i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=tot;j++){
            tp[i][j]+=tp[i][j-1];
        }
    for(int i=1;i<=tot;i++){
        bit.clear();
        int l=0;
        for(int j=st[i];j<=n&&j<=en[i];j++){
            l+=bit.query_bck(a[j]+1);
            pre[j]=l;//sum记录前比其大的
            bit.ins_pre(a[j]);
        }
        bit.clear();
        l=0;
        for(int j=min(n,en[i]);j>=st[i];j--){
            l+=bit.query_pre(a[j]-1);
            bck[j]=l;//sum2记录后比其小的
            bit.ins_bck(a[j]);
        }
    }
    //每个块内排序
    for(int i=1;i<=tot;i++){
        int l=st[i],r=en[i]>n?n:en[i];
        for(int j=l;j<=r;j++){
            c[j].id=j;c[j].val=a[j];
        }
        sort(c+l,c+r+1);
    }
    for(int i=1;i<=tot;i++)dp[i][i]=pre[en[i]>n?n:en[i]];
    for(int i=1;i<=tot-1;i++)
        for(int j=i+1;j<=tot;j++)
            dp[i][j]=qs(i,j);
    for(int i=tot;i>=1;i--)
        for(int j=i+1;j<=tot;j++)
            dp[i][j]+=dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1];
}
ll eme(){
    int i=1,j=1;
    ll t=0;
    while(i<=s1&&j<=s2){
        if(q1[i]<=q2[j])++i;
        else{
            ++j;
            t+=s1-i+1;
        }
    }
    return t;
}
ll ask(int x,int l,int r){
    s1=s2=0;
    ll t=pre[r];
    if(l!=st[x])t-=pre[l-1];
    for(int i=st[x];i<=en[x]&&i<=n;i++)
        if (c[i].id<l)q1[++s1]=c[i].val;
    for(int i=st[x];i<=en[x]&&i<=n;i++)
        if (c[i].id>=l&&c[i].id<=r) q2[++s2]=c[i].val;
    t-=eme();
    return t;
}
ll query(int l,int r){
    if(l>r)return 0LL;
    s1=s2=0;
    int bl=bel[l],br=bel[r];
    if(bl==br)
        return ask(bl,l,r);
    ll re=dp[bl+1][br-1];
    re+=bck[l];re+=pre[r];
    for(int i=st[bl];i<=en[bl]&&i<=n;i++)
        if (c[i].id>=l) q1[++s1]=c[i].val;
    for(int i=st[br];i<=en[br]&&i<=n;i++)
        if (c[i].id<=r) q2[++s2]=c[i].val;
    re+=tp[l][br-1]-tp[l][bl]+tp[r][br-1]-tp[r][bl]+eme();
    return re;
}
multiset<ll>z;
multiset<ll>::iterator it;
int main(){
    read(t);
    while(t--){
        read(n);lim=n+1;
        SIZ=max(350,(n+CNT-2)/(CNT-1));
        for(int i=1;i<=CNT-1;i++)st[i]=(i-1)*SIZ+1,en[i]=i*SIZ;
        z.clear();
        for(int i=1;i<=n;i++)read(a[i]),bel[i]=1+(i-1)/SIZ,c[i].val=a[i],c[i].id=i;
        tot=1+(n-1)/SIZ;
        sort(c+1,c+1+n);
        cal1();cal2();
        init();
        pts.clear();pts2.clear();
        ans=query(1,n);
        printf("%lld",ans);
        z.insert(-ans);
        pts2.ins_pre(n+1);
        for(int q=1;q<=n;q++){
            printf(" ");
            ll tem;
            read(tem);
            if(q==n)break;
            tem^=ans;
            assert(tem>=1&&tem<=n);
            int l=pts.find_pre(tem),r=pts2.find_bck(tem);
            ll lin=-query(l+1,r-1);
            it=lower_bound(z.begin(),z.end(),lin);
            z.erase(it);
            if(l+1<=tem-1)
                z.insert(-query(l+1,tem-1));
            if(tem+1<=r-1)
                z.insert(-query(tem+1,r-1));
            ans=-(*z.begin());
            printf("%lld",ans);
            pts.ins_bck(tem);pts2.ins_pre(tem);
        }
        printf("\n");
        for(int i=1;i<=n;i++)
            for(int j=1;j<=tot;j++)tp[i][j]=0;
        for(int i=1;i<=tot;i++)
            for(int j=1;j<=tot;j++)dp[i][j]=0;
        for(int i=1;i<=n;i++)pre[i]=bck[i]=0;
    }
    return 0;
}
/*
2
1000000 1000000 999999 1000000 10 1000000000000
*/
