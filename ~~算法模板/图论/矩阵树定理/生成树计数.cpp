/*
Matrix-Tree ����(Kirchhoff ����-������)
1��G �Ķ������� D[G]��һ�� n*n �ľ��󣬲������㣺�� i��j ʱ,dij=0���� i=j ʱ��dij ���� vi �Ķ�����
2��G ���ڽӾ��� A[G]Ҳ��һ�� n*n �ľ��� �������㣺��� vi��vj ֮���б�ֱ���������� aij=1������ Ϊ 0��
���Ƕ��� G �� Kirchhoff ����(Ҳ��Ϊ������˹����)C[G]Ϊ C[G]=D[G]-A[G]��
�� Matrix-Tree ������� ����Ϊ��G �����в�ͬ���������ĸ��������� Kirchhoff ���� C[G]�κ�һ�� n-1 ������ʽ������ʽ�ľ���ֵ��
��ν n-1 ������ʽ�����Ƕ��� r(1��r��n)���� C[G]�ĵ� r �С��� r ��ͬʱȥ����õ����¾����� Cr[G] ��ʾ��

*/
// HDU 4305
//  ���������������ִ��룬������ 10007 ȡģ
const int MOD = 10007;
int INV[MOD];//��ax = 1( mod m) ��xֵ��������Ԫ(0<a<m)


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
    int det(int n)//������ʽ��ֵģ��MOD����Ҫʹ����Ԫ
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
                res = -1;//������(Ҳ��������ʽֵΪ0)
                break;
            }
            for(int j = i+1;j < n;j++)
            {
                //int mut = (mat[j][i]*INV[mat[i][i]])%MOD;//�����Ԫ
                int mut = (mat[j][i]*inv(mat[i][i],MOD))%MOD;
                for(int k = i;k < n;k++)
                    mat[j][k] = (mat[j][k]-(mat[i][k]*mut)%MOD+MOD)%MOD;
            }
            res = (res * mat[i][i])%MOD;
        }
        return res;
    }
};

int g[305][305];//�洢ԭͼ

    Matrix ret;
    ret.init();
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            if(i != j && g[i][j])
            {
                ret.mat[i][j] = -1;
                ret.mat[i][i]++;
            }
    printf("%d\n",ret.det(n-1));//ֱ��ȥ�����һ�� ���һ�� ����������� ���-1



/*
    ��ȡģ��
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
            if(i != j && g[i][j])//i!=j�Ƚ���Ҫ
            {
                a[i][i]++;
                a[i][j] = -1;
            }
        double ans = det(a,n-1);
        printf("%.0f\n",ans);
    }
    return 0;
}

