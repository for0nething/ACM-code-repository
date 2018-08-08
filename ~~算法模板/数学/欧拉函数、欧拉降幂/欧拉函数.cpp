

/*
分解质因数求欧拉函数
*/
getFactors(n);
int ret=n;
for(int i=0;i<fatCnt;i++){
    ret=ret/factor[i][0]*(factor[i][0]-1);
}

/*
    筛法求欧拉函数
*/
int euler[3000001];
void getEuler(){
    memset(euler,0,sizeof(euler));
    euler[1]=1;
    for(int i=2;i<=3000000;i++)
        if(!euler[i])
            for(int j=i;j<=3000000;j+=i){
                if(!euler[j])
                    euler[j]=j;
                euler[j]=euler[j]/i*(i-1);
            }
}

/*
    求单个数的欧拉函数
*/
ll euler(ll n){
    ll ans=n;
    for(ll i=2;i*i<=n;i++){
        if(n%i==0){
            ans-=ans/i;
            while(n%i==0)n/=i;
        }
    }
    if(n>1)ans-=ans/n;
    return ans;
}

/*
    线性筛 同时得到欧拉函数和素数表
*/
const int MAXN=10000000;
bool check[MAXN+10];
int phi[MAXN+10];
int prime[MAXN+10];
int tot;//素数的个数
void phi_and_prime_table(int N){
    memset(check,0,sizeof(check));
    phi[1]=1;
    tot=0;
    for(int i=2;i<=N;i++){
        if(!check[i]){
            prime[tot++]=i;
            phi[i]=i-1;
        }
        for(int j=0;j<tot;j++){
            if(i*prime[j]>N)break;
            check[i*prime[j]]=true;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            else
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}


