#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
typedef long long ll;

const int N = 1 << 18;//能不能改并不确定
const int P = (479 << 21) + 1;//貌似可以随用随改？（998244353 时G取3是可以的）
const int G = 3;//原根
const int NUM = 20;

ll  wn[NUM];
ll  a[N], b[N];
char A[N], B[N];

ll quick_mod(ll a, ll b, ll m)
{
    ll ans = 1;
    a %= m;
    while(b)
    {
        if(b & 1)
        {
            ans = ans * a % m;
            b--;
        }
        b >>= 1;
        a = a * a % m;
    }
    return ans;
}

void GetWn()//预处理原根的幂次
{
    for(int i = 0; i < NUM; i++)
    {
        int t = 1 << i;
        wn[i] = quick_mod(G, (P - 1) / t, P);
    }
}

void Prepare(char A[], char B[], ll a[], ll b[], int &len)
{
    len = 1;
    int L1 = strlen(A);
    int L2 = strlen(B);
    while(len <= 2 * L1 || len <= 2 * L2) len <<= 1;
    for(int i = 0; i < len; i++)
    {
        if(i < L1) a[i] = A[L1 - i - 1] - '0';//逆着放？
        else a[i] = 0;
        if(i < L2) b[i] = B[L2 - i - 1] - '0';
        else b[i] = 0;
    }
}

void Rader(ll a[], int len)
{
    int j = len >> 1;
    for(int i = 1; i < len - 1; i++)
    {
        if(i < j) swap(a[i], a[j]);
        int k = len >> 1;
        while(j >= k)
        {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
    }
}
void NTT(ll a[], int len, int on=1)//NTT的数组 下标从0开始 数组长度len(这里的len必须为2的幂次）
{
    Rader(a, len);
    int id = 0;
    for(int h = 2; h <= len; h <<= 1)
    {
        id++;
        for(int j = 0; j < len; j += h)
        {
            ll w = 1;
            for(int k = j; k < j + h / 2; k++)
            {
                ll u = a[k] % P;
                ll t = w * a[k + h / 2] % P;
                a[k] = (u + t) % P;
                a[k + h / 2] = (u - t + P) % P;
                w = w * wn[id] % P;
            }
        }
    }
    if(on == -1)
    {
        for(int i = 1; i < len / 2; i++)
            swap(a[i], a[len - i]);
        ll inv = quick_mod(len, P - 2, P);
        for(int i = 0; i < len; i++)
            a[i] = a[i] * inv % P;
    }
}
void Conv(ll a[], ll b[], int n)//多项式乘法 NTT 与其还原
{
    NTT(a, n, 1);
    NTT(b, n, 1);
    for(int i = 0; i < n; i++)
        a[i] = a[i] * b[i] % P;
    NTT(a, n, -1);
}
void Transfer(ll a[], int n)//进位转化
{
    int t = 0;
    for(int i = 0; i < n; i++)
    {
        a[i] += t;
        if(a[i] > 9)
        {
            t = a[i] / 10;
            a[i] %= 10;
        }
        else t = 0;
    }
}
void Print(ll a[], int n)//输出
{
    bool flag = 1;
    for(int i = n - 1; i >= 0; i--)
    {
        if(a[i] != 0 && flag)
        {
            //使用putchar()速度快很多
            putchar(a[i] + '0');
            flag = 0;
        }
        else if(!flag)
            putchar(a[i] + '0');
    }
    puts("");
}
int main()
{
    GetWn();//预处理原根的幂次
    while(scanf("%s %s", A, B) != EOF)
    {
        int len;
        Prepare(A, B, a, b, len);//将字符串形式转化
        Conv(a, b, len);//多项式乘法 NTT 与其还原
        Transfer(a, len);//进位转化
        Print(a, len);//输出
    }
    return 0;
}
