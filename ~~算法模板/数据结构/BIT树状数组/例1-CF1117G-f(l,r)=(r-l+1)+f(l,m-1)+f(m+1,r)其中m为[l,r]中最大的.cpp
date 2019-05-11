//#pragma comment(linker, "/STACK:1024000000,1024000000")
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
//#include <bitset>
//#include <utility>
//#include <complex>
#include <assert.h>
//#include <limits.h>
//#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;

#define rank rankk
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define xo(a,b) ((b)&1?(a):0)
#define fi first
#define se second
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;

const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=1e6+5;
const ll MOD=998244353;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
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
namespace{
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

pil b[MAX];
pii qs[MAX];
int stk[MAX],a[MAX],pre[MAX],top;
ll ans[MAX];
vector<pii>st[MAX];
priority_queue<pii>pq;
int n,q;
void addb(int pos,int val){
    while(pos<=n){
        b[pos].fi+=1;b[pos].se+=val;pos+=pos&-pos;
    }
}
pil query(int lo){
    pil re;re.fi=re.se=0;
    while(lo){
        re.fi+=b[lo].fi;re.se+=b[lo].se;lo-=lo&-lo;
    }
    return re;
}
void solve(){
    top=0;
    for(int i=1;i<=n;i++)pre[i]=b[i].fi=b[i].se=0;;
    for(int i=n;i>=1;i--){
        while(top&&a[stk[top]]<a[i])
            pre[stk[top]]=i,--top;
        stk[++top]=i;
    }
    for(int i=1;i<=n;i++)st[i].clear();
    for(int i=1;i<=q;i++)st[qs[i].fi].eb(mp(qs[i].se,i));
    while(!pq.empty())pq.pop();
    for(int i=1;i<=n;i++)pq.push(mp(pre[i],i));
    pq.push(mp(-1,-1));
    for(int i=n;i>=1;i--){
        pii tem=pq.top();
        while(tem.fi>=i){
            addb(tem.se,tem.fi+1);
            pq.pop();tem=pq.top();
        }
        pii l=query(i-1);
        for(auto u:st[i]){
            pil r=query(u.fi);
            int cnt=(u.fi-i+1)-(r.fi-l.fi);
            ans[u.se]+=1LL*(i+u.fi)*(u.fi-i+1)/2-(r.se-l.se+1LL*cnt*i);
        }
    }


}
int main(){
    read(n);read(q);
    for(int i=1;i<=n;i++)read(a[i]);
    for(int i=1;i<=q;i++)read(qs[i].fi);
    for(int i=1;i<=q;i++)read(qs[i].se);
    solve();
    reverse(a+1,a+1+n);
    for(int i=1;i<=q;i++)qs[i].fi=n+1-qs[i].fi,qs[i].se=n+1-qs[i].se,swap(qs[i].fi,qs[i].se);
    solve();
    for(int i=1;i<=q;i++)
        printf("%lld ",ans[i]+qs[i].se-qs[i].fi+1);
    return 0;
}
/*
7 3
abacaba
0 1 1
1 0 0
1 0 0
*/
