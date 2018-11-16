/*
求sigma i=1,a sigma j=1,b  d(i*j)   T,a,b<=50000
套式子 将gcd(i,j)=1的限制条件莫比乌斯反演打开
*/
bool check[MAX];
int mu[MAX],pre[MAX],prime[MAX];
ll f[MAX];
int t,tot,n,m;
ll cal(int lim){
    ll re=0;
    for(int i=1,j;i<=lim;i=j+1){
        int tem=lim/i;
        j=lim/tem;
        re+=1LL*tem*(j-i+1);
    }
    return re;
}
int main(){

    mu[1]=pre[1]=1;
    for(int i=2;i<=(int)5e4;i++){

        if(!check[i])prime[tot++]=i,mu[i]=-1;
        pre[i]=pre[i-1]+mu[i];
        for(int j=0;j<tot;j++){
            if(prime[j]*i>(int)5e4)break;
            check[i*prime[j]]=1;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            else mu[i*prime[j]]=-mu[i];
        }
    }
    read(t);
    while(t--){
        read(n);read(m);
        int i=1,j;
        ll ans=0;
        while(i<=n&&i<=m){
            int tem1=n/i,tem2=m/i;
            if(!f[tem1])f[tem1]=cal(tem1);
            if(!f[tem2])f[tem2]=cal(tem2);
            int j=min(n/tem1,m/tem2);
            ans+=(pre[j]-pre[i-1])*f[tem1]*f[tem2];
            i=j+1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
/*
1
30
3
6
##.#..
7
.#.#.#.
5
##.##
*/
