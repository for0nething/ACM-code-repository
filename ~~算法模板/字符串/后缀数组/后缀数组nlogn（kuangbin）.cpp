const int MAXN=20010;
int t1[MAXN],t2[MAXN],c[MAXN];//求SA数组需要的中间变量，不需要赋值
//待排序的字符串放在s数组中，从s[0]到s[n-1],长度为n,且最大值小于m,
//除s[n-1]外的所有s[i]都大于0，r[n-1]=0 （即在原串后加一个0 原串的值都在[1,m)区间 函数第一行已加不用再自己改）
//函数结束以后结果放在sa数组中
bool cmp(int *r,int a,int b,int l)
{
    return r[a] == r[b] && r[a+l] == r[b+l];
}
void da(int str[],int sa[],int rank[],int height[],int n,int m)
{
    str[n++]=0;
    int i, j, p, *x = t1, *y = t2;
    //第一轮基数排序，如果s的最大值很大，可改为快速排序
    for(i = 0;i < m;i++)c[i] = 0;
    for(i = 0;i < n;i++)c[x[i] = str[i]]++;
    for(i = 1;i < m;i++)c[i] += c[i-1];
    for(i = n-1;i >= 0;i--)sa[--c[x[i]]] = i;
    for(j = 1;j <= n; j <<= 1)
    {
        p = 0;
        //直接利用sa数组排序第二关键字
        for(i = n-j; i < n; i++)y[p++] = i;//后面的j个数第二关键字为空的最小
        for(i = 0; i < n; i++)if(sa[i] >= j)y[p++] = sa[i] - j;
        //这样数组y保存的就是按照第二关键字排序的结果
        //基数排序第一关键字
        for(i = 0; i < m; i++)c[i] = 0;
        for(i = 0; i < n; i++)c[x[y[i]]]++;
        for(i = 1; i < m;i++)c[i] += c[i-1];
        for(i = n-1; i >= 0;i--)sa[--c[x[y[i]]]] = y[i];
        swap(x,y);
        //根据sa和x数组计算新的x数组 swap(x,y);
        p = 1; x[sa[0]] = 0;
        for(i = 1;i < n;i++)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if(p >= n)break;
        m = p;//下次基数排序的最大值
    }
    int k = 0; n--;
    for(i = 0;i <= n;i++)rank[sa[i]] = i;
    for(i = 0;i < n;i++)
    {
        if(k)k--;
        j = sa[rank[i]-1]; while(str[i+k] == str[j+k])k++; height[rank[i]] = k;
    }
}
int rank[MAXN],height[MAXN];
int RMQ[MAXN];
int mm[MAXN];//mm[i] : 满足2^x<=i的x的最大值（初始化mm[0]=-1）


int best[20][MAXN];

//init RMQ(int n) 之前需要 for(int i=1;i<=n;i++)RMQ[i]=height[i]; initRMQ(n);
void initRMQ(int n)
{
    mm[0]=-1;
    for(int i=1;i<=n;i++)
    mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
    for(int i=1;i<=n;i++)best[0][i]=i;
    for(int i=1;i<=mm[n];i++)
    for(int j=1;j+(1<<i)-1<=n;j++)
    {
        int a=best[i-1][j];
        int b=best[i-1][j+(1<<(i-1))];
        if(RMQ[a]<RMQ[b])best[i][j]=a; else best[i][j]=b;
    }
}
int askRMQ(int a,int b)
{
    int t; t=mm[b-a+1];
    b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}
int lcp(int a,int b)
{
    a=rank[a];b=rank[b];
    if(a>b)swap(a,b);
    return height[askRMQ(a+1,b)];
}
char str[MAXN];
int sa[MAXN];
//rank\sa\height数组已经声明 str为字符串数组 使用时需要传入int数组 并给出该数组长度（n,下标0开始）元素取值范围（m 每一项均大于0）

