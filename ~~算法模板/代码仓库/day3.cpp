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
#define fi first
#define se second
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
const int MAX=2e5+5;
const int MOD=1e9+7;
//int MOD;
//const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
//const long double eps=1e-13;
//const double pi=acos(-1);
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
namespace{
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
//inline int mul(int x,int y){return 1LL*x*y%MOD;}
inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void muli(int &x,int y){x=1LL*x*y%MOD;}
inline int sub(int x,int y){int res=x-y;if(res<0)res+=MOD;return res;}
inline void subi(int &x,int y){x-=y;if(x<0)x+=MOD;}
inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);



#define eps 1e-9
const int MAXN=520;

//a[i][j]表示 对i求偏导中 xj的系数
double a[MAXN][MAXN],x[MAXN];//方程的左边的矩阵(初始存在a中，下标从0开始）和等式右边的值（初始存在x中，下标0开始），求解之后x存的就是结果
int equ,var;//方程数和未知数个数
/*
*返回0表示无解，1表示有解
*/
int Gauss()
{
    int i,j,k,col,max_r;
    for(k=0,col=0;k<equ&&col<var;k++,col++)
    {
        max_r=k;
        for(i=k+1;i<equ;i++)
            if(fabs(a[i][col])>fabs(a[max_r][col]))
                max_r=i;
        if(fabs(a[max_r][col])<eps)return 0;
        if(k!=max_r)
        {
            for(j=col;j<var;j++) swap(a[k][j],a[max_r][j]);
            swap(x[k],x[max_r]);
        }
        x[k]/=a[k][col];
        for(j=col+1;j<var;j++)
            a[k][j]/=a[k][col];
        a[k][col]=1;
        for(i=0;i<equ;i++)
            if(i!=k)
            {
                x[i]-=x[k]*a[i][k];
                for(j=col+1;j<var;j++)
                    a[i][j]-=a[k][j]*a[i][col];
                a[i][col]=0;
            }
    }
    return 1;
}
double xi[505][10];//xi求偏导前 第j次幂的系数
double xij[505][505];//xixj 求偏导前的系数
double c[505][505];//c i,j  第二轮i到j的个数
int sx[505],sy[505];
int from[505],to[505];
int n;
double ans;
vector<int>G[MAX];
//
void zhan(double *uxi,double wxi,double chang){//uxi：括号内u的系数  wxi：括号外的系数  chang:括号内的常数
//    memset(xi,0,sizeof(xi));
//    memset(xij,0,sizeof(xij));
    //ui^2
    for(int i=0;i<n;i++)
        printf("%f ",uxi[i]);
    cout<<" ok\n";
    for(int i=0;i<n;i++)xi[i][2]+=uxi[i]*uxi[i]*wxi;
//    {

//        //常数
//        xi[i][0]+=chang*chang*wxi;
//    }

    //ui*uj
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            xij[i][j]+=uxi[i]*uxi[j]*wxi*2;
    //ui
    for(int i=0;i<n;i++)
        xi[i][1]+=uxi[i]*wxi*chang*2;
}
//求偏导将结果入
void calx(){
//    memset(a,0,sizeof(a));
    for(int i=0;i<n;i++)//对xi求偏导 原本的常数没有了
    {
        a[i][i]+=xi[i][2]*2;
        for(int j=0;j<n;j++){
            if(j==i)continue;
            a[i][j]+=xij[i][j];
        }
        x[i]+=-xi[i][1];//仅xi的一次项有常数
    }
}
double tem[505];
double v[505];
void solve(int *z){
    //初始化
    memset(xi,0,sizeof(xi));
    memset(xij,0,sizeof(xij));
    memset(a,0,sizeof(a));
    memset(x,0,sizeof(x));
    //第一个平方项
    for(int i=0;i<n;i++){
        int nxt=from[i];
        memset(tem,0,sizeof(tem));
        tem[nxt]=-1;
        zhan(tem,1,z[i]);
    }
    //第二个平方项
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            memset(tem,0,sizeof(tem));
//            double chang=c[i][j];
            tem[i]=1;
            double tot=0;
            for(int k=0;k<n;k++)tot+=c[k][j];
            if(tot!=0){
                for(int k=0;k<n;k++)
                    tem[k]-=c[k][j]/tot;
                zhan(tem,c[i][j],0);
            }

//            calx();
        }
    calx();
    int ge=Gauss();
//    cout<<"ge="<<ge<<endl;
    memset(v,0,sizeof(v));
    double sum=0;
    for(int i=0;i<n;i++)
        sum+=(z[i]-x[from[i]])*(z[i]-x[from[i]]);
    for(int j=0;j<n;j++){
        double tot=0;
        for(int i=0;i<n;i++)tot+=c[i][j];
        if(tot!=0)
        {
            for(int i=0;i<n;i++)v[j]+=c[i][j]*x[i];
            v[j]/=tot;
        }
        for(int i=0;i<n;i++)
            sum+=c[i][j]*(x[i]-v[j])*(x[i]-v[j]);
    }

    ans+=sum;
    cout<<sum<<endl;
//    for(int j=0;j<n;j++)

}
int main(){
    read(n);equ=var=n;
    for(int i=0;i<n;i++){
        read(sx[i]);read(sy[i]);
    }
    for(int i=0;i<n;i++)read(from[i]);
    for(int i=0;i<n;i++){
        read(to[i]);
        G[to[i]].eb(from[i]);
    }
    for(int i=0;i<n;i++)++c[from[i]][to[i]];
    solve(sx);
    cout<<"~~"<<endl;
    for(int i=0;i<n;i++)cout<<x[i]<<" "<<v[i]<<endl;

    solve(sy);
    cout<<"~~"<<endl;
    for(int i=0;i<n;i++)cout<<x[i]<<" "<<v[i]<<endl;
    cout<<endl;
    printf("%.5f\n",ans);
    return 0;
}

/*

2
1 1
10 10
1 1
1 1
*/
