#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>

int Read()
{
    int x=0,y=1;
    char c=getchar();
    while(!isdigit(c))
    {
        if(c=='-')
        {
            y=-1;
        }
        c=getchar();
    }
    while(isdigit(c))
    {
        x=(x<<3)+(x<<1)+(c^48);
        c=getchar();
    }
    return x*y;
}

struct Node
{
    int x,y,weight;
}node[10005];
int n;

double potential_energy(double nowx,double nowy)
{
    double sum=0;
    for(int i=1;i<=n;i++)
    {
        double delx=nowx-node[i].x;
        double dely=nowy-node[i].y;
        sum+=(sqrt(delx*delx+dely*dely))*node[i].weight;
        //物重一定，绳子越短，重物越低，势能越小
        //势能又与物重成正比
    }
    return sum;//在(nowx,nowy)处的总势能
}

double xans,yans;//最终答案
double ans=1e18+7,t;//势能与温度
const double delta=0.993;//降温系数

void simulate_anneal()
{
    double xx=xans;//钦定一个初始位置
    double yy=yans;
    t=1926;//t是温度
    while(t>1e-14)
    {
        double xtemp=xans+(rand()*2-RAND_MAX)*t;
        double ytemp=yans+(rand()*2-RAND_MAX)*t;
        //随机一个新的坐标，变化幅度为t
        //这里要注意rand()和rand()*2-RAND_MAX的区别
        //rand()的范围是0~RAND_MAX-1
        //rand()*2-RAND_MAX的范围是-RAND_MAX到RAND_MAX-1

        double new_ans=potential_energy(xtemp,ytemp);//计算当前解的势能
        double DE=new_ans-ans;
        if(DE<0)//如果是一个更优解
        {
            xx=xtemp;
            yy=ytemp;//就接受
            xans=xx;
            yans=yy;
            ans=new_ans;
        }
        else if(exp(-DE/t)*RAND_MAX>rand())//能否接受这个差
        {
            //更新坐标
            xx=xtemp;
            yy=ytemp;
        }
        t*=delta;//降温
    }
}

void SA()//洗把脸就AC了
{
    simulate_anneal();
    simulate_anneal();
    simulate_anneal();
}

int main()
{
    n=Read();
    for(int i=1;i<=n;i++)
    {
        node[i].x=Read();
        node[i].y=Read();
        node[i].weight=Read();
    }
    SA();
    printf("%.3lf %.3lf",xans,yans);
    return 0;
}
