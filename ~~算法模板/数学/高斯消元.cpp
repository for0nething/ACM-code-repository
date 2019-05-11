#define eps 1e-9
const int MAXN=220;


double a[MAXN][MAXN],x[MAXN];//方程的左边的矩阵(初始存在a中，下标从0开始）和等式右边的值（初始存在x中，下标0开始），求解之后x存的就是结果
int equ,var;//方程数和未知数个数
/*
*返回0表示无解，1表示有解
如果存在无关变量 默认不返回有解的结果（x中的值无效） 直接return 0
如果想在存在无关变量的情况下仍然有返回 需要按代码中的注释进行修改
*/
int Gauss()
{
    int i,j,k,col,max_r;
    for(k=0,col=0;k<equ&&col<var;k++,col++)
    {
        max_r=k;
        for(i=k+1;i<equ;i++)
            if(fabs(a[i][col])>fabs(a[max_r][col]))
                max_r=i;
        if(fabs(a[max_r][col])<eps)return 0;
        //若想在存在无关变量的情况下仍然有返回 将return 0改成continue！
        if(k!=max_r)
        {
            for(j=col;j<var;j++) swap(a[k][j],a[max_r][j]);
            swap(x[k],x[max_r]);
        }
        x[k]/=a[k][col];
        for(j=col+1;j<var;j++)
            a[k][j]/=a[k][col];
        a[k][col]=1;
        for(i=0;i<equ;i++)
            if(i!=k)
            {
                x[i]-=x[k]*a[i][k];
                for(j=col+1;j<var;j++)
                    a[i][j]-=a[k][j]*a[i][col];
                a[i][col]=0;
            }
    }
    return 1;
}
