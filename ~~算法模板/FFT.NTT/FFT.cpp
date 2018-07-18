const double PI=acos(-1.0);
struct Complex
{
    double real,image;
    Complex(double _real,double _image)
    {
        real=_real;
        image=_image;
    }
    Complex(){}
};
Complex operator +(const Complex &c1,const Complex &c2)
{
    return Complex(c1.real+c2.real,c1.image+c2.image);
}
Complex operator -(const Complex &c1,const Complex &c2)
{
    return Complex(c1.real-c2.real,c1.image-c2.image);
}
Complex operator *(const Complex &c1,const Complex &c2)
{
    return Complex(c1.real*c2.real-c1.image*c2.image,c1.real*c2.image+c1.image*c2.real);
}
int rev(int id,int len)//二进制逆序
{
    int ret=0;
    for(int i=0;(1<<i)<len;i++)
    {
        ret<<=1;
        if(id&(1<<i))
            ret|=1;
    }
    return ret;
}
//递归版本
Complex* RecursiveFFT(Complex a[],int n)//n表示向量a的维数
{
    if(n==1)
        return a;
    Complex wn=Complex(cos(2*PI/n),sin(2*PI)/n);
    Complex w=Complex(1,0);
    Complex* a0=new Complex[n>>1];
    Complex* a1=new Complex[n>>1];
    for(int i=0;i<n;i++)
        if(i&1)a1[(i-1)>>1]=a[i];
        else a0[i>>1]=a[i];
    Complex *y0,*y1;
    y0=RecursiveFFT(a0,n>>1);
    y1=RecursiveFFT(a1,n>>1);
    Complex* y=new Complex[n];
    for(int k=0;k<(n>>1);k++)
    {
        y[k]=y0[k]+w*y1[k];
        y[k+(n>>1)]=y0[k]-w*y1[k];
        w=w*wn;
    }
    delete a0;delete a1;
    delete y0;delete y1;
    return y;

}
//DFT=1时是DFT,DFT=-1则是逆DFT（IDFT） 返回长度为len的complex数组 需要自己接收
Complex* IterativeFFT(Complex* a,int len,int DFT=1)//对长度为len（2的幂）的数组进行DFT变换,默认1
{
    Complex* A=new Complex[len];//用A数组存储数组a分组之后新的顺序
    for(int i=0;i<len;i++)
        A[rev(i,len)]=a[i];
    for(int s=1;(1<<s)<=len;s++)
    {
        int m=(1<<s);
        Complex wm=Complex(cos(DFT*2*PI/m),sin(DFT*2*PI/m));
        for(int k=0;k<len;k+=m)//这一层节点的包含数组元素个数都是（1<<s)
        {
            Complex w=Complex(1,0);
            for(int j=0;j<(m>>1);j++)
            {
                Complex t=w*A[k+j+(m>>1)];
                Complex u=A[k+j];
                A[k+j]=u+t;
                A[k+j+(m>>1)]=u-t;
                w=w*wm;
            }
        }
    }
    if(DFT==-1)
        for(int i=0;i<len;i++)
        A[i].real/=len,A[i].image/=len;
    return A;
}
