#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef int ttt;
#define int long long
const int MOD=1e9+7;
const int MAX=2e4+5;
int p;
char s[MAX];
int a[MAX],b[MAX],c[MAX];
//数x是否大于y
bool big(int *x,int lenx,int *y,int leny){
    if(lenx!=leny)return lenx>leny;
    for(int i=lenx-1;i>=0;i--){
        if(x[i]!=y[i])return x[i]>y[i];
    }
    return 1;
}
//x-y 结果存在数组re中 返回结果数的长度
int sub(int *x,int lenx,int *y,int leny,int *re){
    memset(re,0,sizeof(int)*MAX);
    for(int i=0;i<lenx;i++){
        re[i]+=x[i]-y[i];
        if(re[i]<0)re[i]+=p,--re[i+1];
    }
    while(lenx&&!re[lenx-1])--lenx;
    return lenx;
}
//将sysx进制长度为len的数x转换为 sysre进制的数 存在re数组中
//返回re的长度
//x数组被修改 非传入的值
int trans(int *x,int len,int sysx,int sysre,int *re){
    int digit=0;
    while(len){
        int remain=0;
        for(int i=len-1;i>=0;i--){
            remain=1LL*remain*sysx+x[i];
            x[i]=remain/sysre;
            remain=remain%sysre;
        }
        re[digit++]=remain;
        while(len&&!x[len-1])--len;
    }
    return digit;
}
ttt main()
{
    scanf("%lld%s",&p,s);
    int n=strlen(s);
    reverse(s,s+n);
    for(int i=0;i<n;i++)b[i]=s[i]-'0';
    n=trans(b,n,10,p,a);
    int an=0;
    memset(b,0,sizeof(b));
    for(int i=n-1;i<=n;i++){
        for(int j=0;j<=i;j++){
            ++b[i];++b[j];
            int len=i+1;
            if(!big(b,len,a,n)){
                --b[i];--b[j];
                continue;
            }
            int lenc=sub(b,len,a,n,c);

            if(lenc>i){
                --b[i];--b[j];continue;
            }
            if(i==j){
                int val=1;
                bool flag=1,equal=1;
                for(int k=lenc-1;k>=0;k--){
                    if(c[k]>2){
                        val=0;break;
                    }
                    if(c[k]==1)equal=0;
                    if(flag&&c[k]==1)flag=0;
                    else if(c[k]==1)val=val*2%MOD;
                }
                if(val&&equal)--val;
                an+=val;
                an%=MOD;
            }
            else{
                int val=1;
                for(int k=lenc-1;k>=j;k--){
                    if(c[k]>1){
                        val=0;break;
                    }
                }
                for(int k=j-1;k>=0;--k){
                    if(c[k]>2){
                        val=0;break;
                    }
                    if(c[k]==1)val=2*val%MOD;
                }
                an+=val;
                an%=MOD;
            }
            --b[i];--b[j];
        }
    }
    printf("%lld\n",an);
    return 0;
}
