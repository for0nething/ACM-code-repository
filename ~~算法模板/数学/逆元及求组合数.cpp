#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
const int MAX=1e5+5;
/*
    fi���鴢��׳�
    inv���鴢����Ԫ
    ������Ԫ�����ְ취
    ����1�����������һ������Ԫ���÷���С����
        ֮�������  inv[i]=(i+1)inv[i+1]  (����ͬʱ��i!��Ȼ����)
    ����2������û����

*/
const int MAXN=1e5+5;
ll fi[MAXN],inv[MAXN];
ll quick(ll a,ll b)
{
    ll an=1LL;
    while(b)
    {
        if(b&1)
        {
            an=an*a%MOD;
        }
        a=a*a%MOD;
        b/=2;
    }
    return an%MOD;
}
ll C(ll a,ll b)
{
    if(a<0||b<0||b>a)
        return 0LL;
    return (fi[a]*inv[b]%MOD)*inv[a-b]%MOD;
}

int main()
{


    for(ll i=0;i<=1e5;i++)
    {
        fi[i]=i?(fi[i-1]*i%MOD):1;
    }

    /*������Ԫ�ĵ�һ�ַ��� MOD��ҪΪ����*/
    inv[100000]=quick(fi[100000],MOD-2);
    for(ll i=1e5-1;i>=0;i--)
        inv[i]=(i+1)*inv[i+1]%MOD;

    /*������Ԫ�ĵڶ��ַ��� ��Ҫ��Ϊ����*/
    inv[1]=inv[0]=1;
    for (int i=2;i<=100000;i++)
    {
        inv[i]=(LL)(mod-mod/i)*inv[mod%i]%mod;
    }
    for (int i=2;i<=100000;i++)
    {
        inv[i]=(inv[i]*inv[i-1])%mod;
    }

}
    /*
    ����������ǽ׳ˣ���ģP�µ���Ԫ P���Է�����
   */
   for(inv[1]=1,i=2;i<P;i++)
        inv[i]=1LL*(P-inv[P%i])*(P/i)%P;



/*
    ���ư�Ԥ�����������
*/
static const int MOD = 1000000007;
const int N = 2020;
int C[N][N];
void init() {
        for (int i = 0; i < N; i ++) C[i][0] = C[i][i] = 1;
        for (int i = 1; i < N; i ++) {
                for (int j = 1; j < i; j ++) {
                        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
                }
        }
}
