#include<iostream>
#include<algorithm>
#include<queue>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<set>
#include<map>
#define INF 0x3f3f3f3f
#define MAXN 45
#define MAXM 1500
#define MOD 1000000007
#define MAXNODE 8*MAXN
#define eps 1e-9
using namespace std;
typedef long long LL;
int T;
LL C[MAXN][MAXN];
void getC(){
    for(int i=0;i<MAXN;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
}
int gcd(int a,int b){
    return a%b?gcd(b,a%b):b;
}
LL cal(int a,int b,int c,int l,int m){
    if(a<0||b<0||c<0) return 0;
    if(a%l||b%l||c%l) return 0;
    a/=l;
    b/=l;
    return C[m][a]*C[m-a][b];   //从m个循环中选a个用颜色a，从剩下的中选b个用颜色b，再剩下的用颜色c
}
int main(){
//    freopen("in.txt","r",stdin);
    getC();
    scanf("%d",&T);
    while(T--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        int n=a+b+c;
        LL ans=0;
        //旋转
        for(int i=0;i<n;i++){
            int l=gcd(i,n);
            ans+=cal(a,b,c,n/l,l);
        }
        //翻转
        //n为奇数，分别选一种颜色的珠子穿过对称轴，这个珠子可以有n个位置
        if(n%2){
            ans+=cal(a-1,b,c,2,n/2)*n;
            ans+=cal(a,b-1,c,2,n/2)*n;
            ans+=cal(a,b,c-1,2,n/2)*n;
        }
        //n为偶数
        else{
            ans+=cal(a,b,c,2,n/2)*(n/2);    //对称轴不穿过珠子，有n/2种对称轴
            //对称轴穿过2种颜色珠子，有n种对称轴
            ans+=cal(a-1,b-1,c,2,n/2-1)*n;
            ans+=cal(a-1,b,c-1,2,n/2-1)*n;
            ans+=cal(a,b-1,c-1,2,n/2-1)*n;
            //对称轴穿过2个同样颜色的珠子，有n/2种对称轴
            ans+=cal(a-2,b,c,2,n/2-1)*(n/2);
            ans+=cal(a,b-2,c,2,n/2-1)*(n/2);
            ans+=cal(a,b,c-2,2,n/2-1)*(n/2);
        }
        printf("%lld\n",ans/(2*n));
    }
    return 0;
}
