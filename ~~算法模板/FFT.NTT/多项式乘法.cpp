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
#define rank rankk
typedef unsigned long long ull;
typedef long long ll;
const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const ll M=1e6+3;
const ll maxn=1e5+7;
const int MAX=5e5+5;
const int MAX_N=MAX;
//const ll MOD=1e6+3;
const double PI=acos(-1.0);
//const double eps=0.00000001;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b){
    ll ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
struct Complex
{
    double real,image;
    Complex(double _real=0.0,double _image=0.0)
    {
        real=_real;
        image=_image;
    }
};
Complex operator +(const Complex &c1,const Complex &c2)
{
    return Complex(c1.real+c2.real,c1.image+c2.image);
}
Complex operator -(const Complex &c1,const Complex &c2)
{
    return Complex(c1.real-c2.real,c1.image-c2.image);
}
Complex operator *(const Complex &c1,const Complex &c2)
{
    return Complex(c1.real*c2.real-c1.image*c2.image,c1.real*c2.image+c1.image*c2.real);
}
int rev(int id,int len)//二进制逆序
{
    int ret=0;
    for(int i=0;(1<<i)<len;i++)
    {
        ret<<=1;
        if(id&(1<<i))
            ret|=1;
    }
    return ret;
}
//DFT=1时是DFT,DFT=-1则是逆DFT（IDFT）
Complex* IterativeFFT(Complex* a,int len,int DFT=1)//对长度为len（2的幂）的数组进行DFT变换,默认1
{
    Complex* A=new Complex[len];//用A数组存储数组a分组之后新的顺序
    for(int i=0;i<len;i++)
        A[rev(i,len)]=a[i];
    for(int s=1;(1<<s)<=len;s++)
    {
        int m=(1<<s);
        Complex wm=Complex(cos(DFT*2*PI/m),sin(DFT*2*PI/m));
        for(int k=0;k<len;k+=m)//这一层节点的包含数组元素个数都是（1<<s)
        {
            Complex w=Complex(1,0);
            for(int j=0;j<(m>>1);j++)
            {
                Complex t=w*A[k+j+(m>>1)];
                Complex u=A[k+j];
                A[k+j]=u+t;
                A[k+j+(m>>1)]=u-t;
                w=w*wm;
            }
        }
    }
    if(DFT==-1)
        for(int i=0;i<len;i++)
        A[i].real/=len,A[i].image/=len;
    return A;
}
int n,m,da,len;
Complex a[MAX],b[MAX];
int main()
{
    scanf("%d%d",&n,&m);
    n++;m++;
    da=max(n,m);
    for(int i=0;i<n;i++)
        scanf("%lf",&a[i].real);
    for(int i=0;i<m;i++)
        scanf("%lf",&b[i].real);
    Complex *a1= new Complex[(1<<len)],*b1=new Complex[1<<len];
    while((1<<len)<(da<<1))
        ++len;
    a1=IterativeFFT(a,(1<<len));b1=IterativeFFT(b,(1<<len));
    for(int i=0;i<(1<<len);i++)
        a1[i]=a1[i]*b1[i];
    a1=IterativeFFT(a1,(1<<len),-1);
//    printf("len= %d \n",1<<len);
    for(int i=0;i<n+m-1;i++)
        printf("%d ",(int)trunc(a1[i].real+0.5));
    printf("\n");
    return 0;
}
