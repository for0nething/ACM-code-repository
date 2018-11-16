/*
Matrix-Tree 定理(Kirchhoff 矩阵-树定理)
1、G 的度数矩阵 D[G]是一个 n*n 的矩阵，并且满足：当 i≠j 时,dij=0；当 i=j 时，dij 等于 vi 的度数。
2、G 的邻接矩阵 A[G]也是一个 n*n 的矩阵， 并且满足：如果 vi、vj 之间有边直接相连，则 aij=1，否则 为 0。
我们定义 G 的 Kirchhoff 矩阵(也称为拉普拉斯算子)C[G]为 C[G]=D[G]-A[G]，
则 Matrix-Tree 定理可以 描述为：G 的所有不同的生成树的个数等于其 Kirchhoff 矩阵 C[G]任何一个 n-1 阶主子式的行列式的绝对值。
所谓 n-1 阶主子式，就是对于 r(1≤r≤n)，将 C[G]的第 r 行、第 r 列同时去掉后得到的新矩阵，用 Cr[G] 表示。

*/
// HDU 4305
//  求生成树计数部分代码，计数对 10007 取模
const int MOD = 10007;
int INV[MOD];//求ax = 1( mod m) 的x值，就是逆元(0<a<m)


long long inv(long long a,long long m)
{
    if(a == 1)return 1;
    return inv(m%a,m)*(m-m/a)%m;
}
struct Matrix
{
    int mat[330][330];
    void init()
    {
        memset(mat,0,sizeof(mat));
    }
    int det(int n)//求行列式的值模上MOD，需要使用逆元
    {
        for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            mat[i][j] = (mat[i][j]%MOD+MOD)%MOD;
        int res = 1;
        for(int i = 0;i < n;i++)
        {
            for(int j = i;j < n;j++)
                if(mat[j][i]!=0)
                {
                    for(int k = i;k < n;k++) swap(mat[i][k],mat[j][k]);
                    if(i != j)
                        res = (-res+MOD)%MOD;
                    break;
                }
            if(mat[i][i] == 0)
            {
                res = -1;//不存在(也就是行列式值为0)
                break;
            }
            for(int j = i+1;j < n;j++)
            {
                //int mut = (mat[j][i]*INV[mat[i][i]])%MOD;//打表逆元
                int mut = (mat[j][i]*inv(mat[i][i],MOD))%MOD;
                for(int k = i;k < n;k++)
                    mat[j][k] = (mat[j][k]-(mat[i][k]*mut)%MOD+MOD)%MOD;
            }
            res = (res * mat[i][i])%MOD;
        }
        return res;
    }
};

int g[305][305];//存储原图

    Matrix ret;
    ret.init();
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            if(i != j && g[i][j])
            {
                ret.mat[i][j] = -1;
                ret.mat[i][i]++;
            }
    printf("%d\n",ret.det(n-1));//直接去掉最后一行 最后一列 如果无生成树 输出-1



/*
    不取模版
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
            if(i != j && g[i][j])//i!=j比较重要
            {
                a[i][i]++;
                a[i][j] = -1;
            }
        double ans = det(a,n-1);
        printf("%.0f\n",ans);
    }
    return 0;
}

