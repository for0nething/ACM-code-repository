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
        //����һ��������Խ�̣�����Խ�ͣ�����ԽС
        //�����������س�����
    }
    return sum;//��(nowx,nowy)����������
}

double xans,yans;//���մ�
double ans=1e18+7,t;//�������¶�
const double delta=0.993;//����ϵ��

void simulate_anneal()
{
    double xx=xans;//�ն�һ����ʼλ��
    double yy=yans;
    t=1926;//t���¶�
    while(t>1e-14)
    {
        double xtemp=xans+(rand()*2-RAND_MAX)*t;
        double ytemp=yans+(rand()*2-RAND_MAX)*t;
        //���һ���µ����꣬�仯����Ϊt
        //����Ҫע��rand()��rand()*2-RAND_MAX������
        //rand()�ķ�Χ��0~RAND_MAX-1
        //rand()*2-RAND_MAX�ķ�Χ��-RAND_MAX��RAND_MAX-1

        double new_ans=potential_energy(xtemp,ytemp);//���㵱ǰ�������
        double DE=new_ans-ans;
        if(DE<0)//�����һ�����Ž�
        {
            xx=xtemp;
            yy=ytemp;//�ͽ���
            xans=xx;
            yans=yy;
            ans=new_ans;
        }
        else if(exp(-DE/t)*RAND_MAX>rand())//�ܷ���������
        {
            //��������
            xx=xtemp;
            yy=ytemp;
        }
        t*=delta;//����
    }
}

void SA()//ϴ������AC��
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
