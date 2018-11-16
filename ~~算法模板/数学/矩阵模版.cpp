/*
int类型matrix模版
*/
const int m_num=50;//矩阵的大小
const int MOD=1e9+7;
inline void add(int &a,int b)//保证a、b已全取过一次MOD（可以为负）
{
    a=(1LL*a+b+MOD)%MOD;if(a<0)a+=MOD;
}
/*
    求行列式的值的求逆元函数
*/
long long inv(long long a,long long m)//函数方法求a模m的逆元
{
    if(a == 1)return 1;
    return inv(m%a,m)*(m-m/a)%m;
}

/*
    矩阵 e[i][j]表示第i行第j列的矩阵元素的值
*/
struct matrix
{
    int e[m_num][m_num];
    int row,col;
    matrix(){}
    matrix(int _r,int _c):row(_r),col(_c){memset(e,0,sizeof(e));}
    matrix operator * (const matrix &tem)const
    {
        matrix ret=matrix(row,tem.col);//新形成的矩阵规模为 左行右列
        for(int i=1;i<=ret.row;i++)
            for(int j=1;j<=ret.col;j++)
                for(int k=1;k<=col;k++)
                    add(ret.e[i][j],1LL*e[i][k]*tem.e[k][j]%MOD);
        return ret;
    }
    matrix operator + (const matrix &tem)const
    {
        matrix ret=matrix(row,col);
        for(int i=1;i<=row;i++)
            for(int j=1;j<=col;j++)add(ret.e[i][j],(e[i][j]+tem.e[i][j])%MOD);
        return ret;
    }
    void getE()//化为单位阵
    {
        for(int i=1;i<=row;i++)
            for(int j=1;j<=col;j++)e[i][j]=(i==j?1:0);
    }
    /*
        逆元版求行列式 似乎有问题// 需要注意 结果为0时返回的为-1
    */
    int det(int n)//n^3 求行列式的值模上MOD，需要使用逆元 即上述的逆元函数，如需要可提前预处理
    {
        for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            e[i][j] = (e[i][j]%MOD+MOD)%MOD;
        int res = 1;
        for(int i = 1;i <= n;i++)
        {
            for(int j = i;j <= n;j++)//向后找该列非0的
            if(e[j][i]!=0)
            {
                for(int k = i;k <= n;k++) swap(e[i][k],e[j][k]);
                if(i != j)
                    res = (-res+MOD)%MOD;
                break;
            }
            if(e[i][i] == 0)
            {
                res = -1;//不存在(也就是行列式值为0)
                break;
            }
            for(int j = i+1;j <= n;j++)
            {
                //int mut = (mat[j][i]*INV[mat[i][i]])%MOD;//打表逆元
                int mut = (e[j][i]*inv(e[i][i],MOD))%MOD;
                for(int k = i;k <= n;k++)
                e[j][k] = (e[j][k]-(e[i][k]*mut)%MOD+MOD)%MOD;
            }
            res = (res * e[i][i])%MOD;
        }
        return res;
    }
    /*
        不需逆元版取模行列式
    */
    ll Det (int n, int mod)
    {
        for (int i = 1; i <=n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                e[i][j] %= mod;
            }
        }
        ll res = 1;
        for (int i = 1; i <= n; ++i)
        {
            if (!e[i][i])
            {
                bool flag = false;
                for (int j = i + 1; j <= n; ++j)
                {
                    if (e[j][i])
                    {
                        flag = true;
                        for (int k = i; k <= n; ++k)
                        {
                            swap (e[i][k], e[j][k]);
                        }
                        res = -res;
                        break;
                    }
                }
                if (!flag)
                {
                    return 0;
                }
            }
            for (int j = i + 1; j <= n; ++j)
            {
                while (e[j][i])
                {
                    ll t = e[i][i] / e[j][i];
                    for (int k = i; k <= n; ++k)
                    {
                        e[i][k] = (e[i][k] - t * e[j][k]) % mod;
                        swap (e[i][k], e[j][k]);
                    }
                    res = -res;
                }
            }
            res = (res * e[i][i]) % mod;
        }
        return (res + mod) % mod;
    }
};
matrix m_qpow(matrix tem,int x)//矩阵快速幂
{
    matrix ret=matrix(tem.row,tem.row);
    ret.getE();
    while(x)
    {
        if(x&1)ret=ret*tem;
        x>>=1;tem=tem*tem;
    }
    return ret;
}



/*
    不取模版double行列式
    (代码为生成树计数的）
*/
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
#include <bitset>
#include <utility>
#include <assert.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp

const double eps = 1e-8;
const int MAXN = 110;
int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    if(x < 0)return -1;
    else return 1;
}
double b[MAXN][MAXN];
double det(double a[][MAXN],int n)
{
    int i, j, k, sign = 0;
    double ret = 1;
    for(i = 0;i < n;i++)
    for(j = 0;j < n;j++) b[i][j] = a[i][j];
    for(i = 0;i < n;i++)
    {
        if(sgn(b[i][i]) == 0)
        {
            for(j = i + 1; j < n;j++)
                if(sgn(b[j][i]) != 0)
                    break;
            if(j == n)return 0;
            for(k = i;k < n;k++)
                swap(b[i][k],b[j][k]);
            sign++;
        }
        ret *= b[i][i];
        for(k = i + 1;k < n;k++)
            b[i][k]/=b[i][i];
        for(j = i+1;j < n;j++)
            for(k = i+1;k < n;k++)
                b[j][k] -= b[j][i]*b[i][k];
    }
    if(sign & 1)ret = -ret;
    return ret;
}
double a[MAXN][MAXN];
int g[MAXN][MAXN];
int main()
{
    int T;
    int n,m;
    int u,v;
    scanf("%d",&T); while(T--)
    {
        scanf("%d%d",&n,&m);
        memset(g,0,sizeof(g)); while(m--)
        {
            scanf("%d%d",&u,&v);
            u--;v--;
            g[u][v] = g[v][u] = 1;
        }
        memset(a,0,sizeof(a));
        for(int i = 0;i < n;i++)
            for(int j = 0;j < n;j++)
            if(i != j && g[i][j])
            {
                a[i][i]++;
                a[i][j] = -1;
            }
        double ans = det(a,n-1);
        printf("%.0lf\n",ans);
    }
    return 0;
}






/*
    不取模long long版行列式 （使用范围较局限）
*/
void determinant()
{
    long long ans = 1;
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = i+1; j <= n; j++)
        {
            int x = i, y = j;
            while(BB[y][i])
            {
                long long t = BB[x][i] / BB[y][i];
                for(int k = 1; k <= n; k++)
                {
                    BB[x][k] = BB[x][k] - BB[y][k]*t;
                }
                swap(x, y);
            }
            if(x != i)
            {
                for(int k = 1; k <= n; k++) swap(BB[x][k], BB[y][k]);
                cnt ^= 1;
            }
        }
        if(BB[i][i] == 0)
        {
            ans = 0; break;
        }
        else ans = ans * BB[i][i];
    }
    if(cnt) printf("%lld\n", -ans);
    else printf("%lld\n", ans);

}
