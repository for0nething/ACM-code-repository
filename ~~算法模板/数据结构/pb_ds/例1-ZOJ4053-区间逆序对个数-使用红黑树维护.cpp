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
const int MAX=1e5+5;
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

#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using Tree=tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update>;
Tree t[MAX];
int bel[MAX],l[MAX],r[MAX],siz[MAX],ge[MAX];
ll icnt[MAX],a[MAX];
int tcnt,T,n;
multiset<ll>ans;
vector<ll>anv;
int build(int L,int R){//用[l,r]的区间建出一棵树
    for(int i=L;i<=R;i++)bel[i]=tcnt;
    icnt[tcnt]=0;
    for(int i=L;i<=R;i++){
        t[tcnt].insert(a[i]);
        icnt[tcnt]+=t[tcnt].size()-t[tcnt].order_of_key(a[i]+1);
    }
    l[tcnt]=L;r[tcnt]=R;
    return tcnt++;
}
void sub(int id,int l,int r){//编号为id的树删去[l,r]区间
    Tree& x=t[id];
    for(int i=l;i<=r;i++)x.erase(a[i]);
}
inline ll f(ll x){
    return x>>20;
}
int main(){
    read(T);
    while(T--){
        read(n);
        ans.clear();anv.clear();
        for(int i=1;i<=n;i++)t[i].clear();
        for(int i=1;i<=n;i++)read(a[i]),bel[i]=1,icnt[i]=0,ge[a[i]]=0;
//        tcnt=1;
//        build(1,n);
        l[1]=1;r[1]=n;tcnt=2;
        for(int i=1;i<=n;i++){
            a[i]=(a[i]<<20LL)|(++ge[a[i]]);
            icnt[1]+=t[1].size()-t[1].order_of_key((f(a[i])+1)<<20);
            t[1].insert(a[i]);
        }
        anv.pb(icnt[1]);ans.insert(icnt[1]);
//        printf("%lld\n",icnt[1]);
        for(int i=1;i<=n;i++){
            ll u;read(u);
            u^=anv.back();
//            cout<<u<<"!"<<endl;
            int who=bel[u],L=l[who],R=r[who],tl,tr;
            int mid=(L+R)/2;
            if(u<=mid){
                tl=build(L,u-1);tr=who;
                ans.insert(icnt[tl]);
                sub(tr,L,u);l[tr]=u+1;
            }
            else{
                tl=who;tr=build(u+1,R);
                ans.insert(icnt[tr]);
                sub(tl,u,R);r[tl]=u-1;
            }
//            it=lower_bound(ans.begin(),ans.end(),icnt[who]);
            ans.erase(ans.find(icnt[who]));
            icnt[who]-=t[tr].order_of_key(f(a[u])<<20)+t[tl].size()-t[tl].order_of_key((f(a[u])+1)<<20LL);
            if(u<=mid){
                for(int i=L;i<u;i++)
                    icnt[who]-=t[tr].order_of_key(f(a[i])<<20);
                icnt[who]-=icnt[tl];
            }
            else{
                for(int i=u+1;i<=R;i++)
                    icnt[who]-=t[tl].size()-t[tl].order_of_key((f(a[i])+1)<<20);
                icnt[who]-=icnt[tr];
            }
            ans.insert(icnt[who]);
            anv.pb(*(ans.rbegin()));
//            cout<<
        }
        anv.pop_back();
        bool st=0;
        for(ll u:anv){if(st)printf(" ");printf("%lld",u);st=1;}
        printf("\n");

    }
    return 0;
}
/*
2 1
3 4
5 6
*/
