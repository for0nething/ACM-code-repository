#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define next nxt
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=2e5+15;
const ll MOD=51061;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<class T> inline
void read(T& num) {bool start=false,neg=false;char c;num=0;while((c=getchar())!=EOF) {if(c=='-') start=neg=true;else if(c>='0' && c<='9') {start=true;num=num*10+c-'0';} else if(start) break;}if(neg) num=-num;}
inline int powMM(int a,int b,int M){int ret=1;a%=M;while (b){if (b&1) ret=1LL*ret*a%M;b>>=1;a=1LL*a*a%M;}return ret;}
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

#define N 50005
int n;
char opt[10];
double K[MAX<<2],B[MAX<<2];
bool better(double k1,double b1,double k2,double b2,double x){
    return k1*x+b1>k2*x+b2;
}
void insert(int x,int l,int r,double k,double b){
    if(l==r){
        if(better(k,b,K[x],B[x],l)){
            K[x]=k,B[x]=b;return;
        }
    }
    else{
        int mid=(l+r)/2;
        if(k>K[x]){//斜率大于原本维护的直线
            if(better(k,b,K[x],B[x],mid)){
                swap(K[x],k);swap(B[x],b);
                insert(x<<1,l,mid,k,b);//原本的直线影响的范围只能在左侧了
            }
            else insert(x<<1|1,mid+1,r,k,b);
        }
        else{
            if(better(k,b,K[x],B[x],mid)){
                swap(K[x],k);swap(B[x],b);
                insert(x<<1|1,mid+1,r,k,b);
            }
            else insert(x<<1,l,mid,k,b);
        }
    }
}
double query(int x,int l,int r,int pos){
    double res=K[x]*pos+B[x];
    if(l==r)return res;
    else{
        int mid=(l+r)>>1;
        if(pos<=mid)return max(query(x<<1,l,mid,pos),res);
        else return max(query(x<<1|1,mid+1,r,pos),res);
    }
}
double b,k;
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        scanf("%s",opt);
        if(opt[0]=='P'){
            scanf("%lf%lf",&b,&k);
            insert(1,1,N,k,b-k);
        }
        else{
            int u;read(u);
            printf("%d\n",(int)query(1,1,N,u)/100);
        }
    }
    return 0;
}

