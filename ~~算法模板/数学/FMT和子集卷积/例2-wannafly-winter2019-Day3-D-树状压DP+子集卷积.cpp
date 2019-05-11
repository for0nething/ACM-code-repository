
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
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


int n,m,tot;
int cnt[1<<14|5];
ll dis[16][25];
ll dp[16][1<<14|5];
int main(){
//    int now=1;
//    for(int i=0;i<14;i++)now*=3;
//    printf("%d\n",now*14*14);
    read(n);read(m);
    tot=(1<<n);
    for(int i=1;i<tot;i++)cnt[i]=cnt[i>>1]+(i&1);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)dis[i][j]=-INFF;
    for(int u,v,w,i=1;i<=m;i++){
        read(u);read(v);read(w);
        dis[u-1][v-1]=dis[v-1][u-1]=w;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<tot;j++)dp[i][j]=-INFF;
    for(int i=0;i<n;i++)dp[i][(1<<i)]=0;
    for(int i=0;i<tot;i++)//枚举子集
    {
        if(cnt[i]<=1)continue;
        for(int j=0;j<n;j++)//枚举树根
            if(i&(1<<j)){
                int now=i^(1<<j);//该子树除了根节点以外的部分的状态
                for(int k=0;k<n;k++)//枚举子树的根 由该子树向其转移
                    if((now&(1<<k))&&dis[j][k]>0){
                        int tmp=now^(1<<k);//该子树的除了子树根节点状态
                        for(tmp=(now)^(1<<k);true;tmp=now&(tmp-1)){//枚举子树除了选定的根以外的部分
                            int st=tmp|(1<<k);//该子树的实际状态
//                            cout<<"!!"<<endl;
                            dp[j][i]=max(dp[j][i],dp[j][i^st]+dp[k][st]+1LL*cnt[st]*(n-cnt[st])*dis[j][k]);
                            if(tmp==0)break;
                        }
                    }
            }
    }

    printf("%lld\n",dp[0][tot-1]);
    return 0;
}

/*
5
-5 0 5 0 0 0 3
-1 0 1 0 0 0 1

-1 0 1 0 0 -1 1
*/
