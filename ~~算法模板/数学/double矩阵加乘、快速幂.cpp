const int m_num=5;//����Ĵ�С
/*
    ���� e[i][j]��ʾ��i�е�j�еľ���Ԫ�ص�ֵ
*/
struct matrix
{
    double e[m_num][m_num];
    int row,col;
    matrix(){}
    matrix(int _r,int _c):row(_r),col(_c){memset(e,0,sizeof(e));}
    matrix operator * (const matrix &tem)const
    {
        matrix ret=matrix(row,tem.col);//���γɵľ����ģΪ ��������
        for(int i=1;i<=ret.row;i++)
            for(int j=1;j<=ret.col;j++)
                for(int k=1;k<=col;k++)
                    ret.e[i][j]+=1LL*e[i][k]*tem.e[k][j];
        return ret;
    }
    matrix operator + (const matrix &tem)const
    {
        matrix ret=matrix(row,col);
        for(int i=1;i<=row;i++)
            for(int j=1;j<=col;j++)ret.e[i][j]+=e[i][j]+tem.e[i][j];
        return ret;
    }
    void getE()//��Ϊ��λ��
    {
        for(int i=1;i<=row;i++)
            for(int j=1;j<=col;j++)e[i][j]=(i==j?1:0);
    }
};
matrix m_qpow(matrix tem,int x)//���������
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
