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
    return C[m][a]*C[m-a][b];   //��m��ѭ����ѡa������ɫa����ʣ�µ���ѡb������ɫb����ʣ�µ�����ɫc
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
        //��ת
        for(int i=0;i<n;i++){
            int l=gcd(i,n);
            ans+=cal(a,b,c,n/l,l);
        }
        //��ת
        //nΪ�������ֱ�ѡһ����ɫ�����Ӵ����Գ��ᣬ������ӿ�����n��λ��
        if(n%2){
            ans+=cal(a-1,b,c,2,n/2)*n;
            ans+=cal(a,b-1,c,2,n/2)*n;
            ans+=cal(a,b,c-1,2,n/2)*n;
        }
        //nΪż��
        else{
            ans+=cal(a,b,c,2,n/2)*(n/2);    //�Գ��᲻�������ӣ���n/2�ֶԳ���
            //�Գ��ᴩ��2����ɫ���ӣ���n�ֶԳ���
            ans+=cal(a-1,b-1,c,2,n/2-1)*n;
            ans+=cal(a-1,b,c-1,2,n/2-1)*n;
            ans+=cal(a,b-1,c-1,2,n/2-1)*n;
            //�Գ��ᴩ��2��ͬ����ɫ�����ӣ���n/2�ֶԳ���
            ans+=cal(a-2,b,c,2,n/2-1)*(n/2);
            ans+=cal(a,b-2,c,2,n/2-1)*(n/2);
            ans+=cal(a,b,c-2,2,n/2-1)*(n/2);
        }
        printf("%lld\n",ans/(2*n));
    }
    return 0;
}
