#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <stack>
#define mp make_pair
#define MIN(a,b) (a>b?b:a)
#define rank rankk
//#define MAX(a,b) (a>b?a:b)
typedef long long ll;
typedef unsigned long long ull;
const int MAX=2505;
const ll INF=1e18+5;
const int B=1024;//Ͱ�Ĵ�С
const double M=4e18;
using namespace std;
const int MOD=1e9+7;
typedef pair<int,int> pii;

char s[MAX];
int sa[MAX],t[MAX],t2[MAX],c[MAX],n;
int rank[MAX],height[MAX];//rank[i]�����׺i��sa�����е��±�
//height[i]����Ϊsa[i-1]��sa[i]�������ǰ׺��LCP���ĳ���
//sa���鴢���i�����ʼλ��
/*
����������׺j��k��������rank[j]<rank[k]������֤����׺j��k��LCP���ȵ���
height[rank[j]+1],height[rank[j]+2]����height[rank[k]]�е���Сֵ
��RMQ(height,rank[j]+1,rank[k])
*/
void build_sa(int m)
{
    int i,*x=t,*y=t2;//x��¼�����±꿪ʼ�Ĵ��������ţ���С��
    for(int i=0;i<m;i++)
        c[i]=0;//��ʼ��c
    for(int i=0;i<n;i++)
        ++c[x[i]=s[i]];//���ַ����ִ���++
    for(int i=1;i<m;i++)
        c[i]+=c[i-1];//��ǰ׺�ͣ�sa��ÿ���ַ����ֵ��±�����õ�ȷ����������Ϊ[0,n-1]
    for(int i=n-1;i>=0;i--)
        sa[--c[x[i]]]=i;//���±꣨��λ����Ӧ��λ��
    for(int k=1;k<=n;k<<=1)//ÿ�����/2
    {
        int p=0;
        //ֱ������sa��������ڶ��ؼ���
        for(int i=n-k;i<n;i++)//��Ϊ�����ܹ�����k��
            y[p++]=i;//�����k��һ������������ͬ��
        for(int i=0;i<n;i++)
            if(sa[i]>=k)
                y[p++]=sa[i]-k;//ǡ����֮ǰ�漰������

        /*�о�������Ҳ�� ��Ϊ���������û���õ�����*/
        //���������һ�ؼ���
        for(int i=0;i<m;i++)
            c[i]=0;
        for(int i=0;i<n;i++)
            ++c[x[y[i]]];
        for(int i=1;i<m;i++)
            c[i]+=c[i-1];
        for(i=n-1;i>=0;--i)
            sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;
        x[sa[0]]=0;
        for(int i=1;i<n;i++)
            x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
        if(p>=n)
            break;//�Ժ����������saҲ����ı䣬�˳�
        m=p;//�´λ�����������ֵ
    }
}
int m;//ģ�峤�ȣ���������������ȫ�ֱ�����
int cmp_suffix(char *pattern,int p)//�ж�ģ��s�Ƿ�Ϊ��׺p��ǰ׺
{
    return strncmp(pattern,s+sa[p],m);
}
int find(char *P)
{
    m=strlen(P);
    if(cmp_suffix(P,0)<0)
        return -1;
    if(cmp_suffix(P,n-1)>0)
        return -1;
    int L=0,R=n-1;
    while(L<=R)
    {
        int M=(L+R)/2;
        int res=cmp_suffix(P,M);
        if(!res)
            return M;
        if(res<0)//ģʽ���ȵ�M���С
            R=M-1;
        else//ģʽ���ȵ�M��Ĵ�
            L=M+1;
    }
    return -1;//�Ҳ���
}
void getHeight()
{
    int i,j,k=0;
    for(i=0;i<n;i++)
        rank[sa[i]]=i;
    for(int i=0;i<n;i++)
    {
        if(k)
            k--;
        int j=sa[rank[i]-1];
        while(s[i+k]==s[j+k])
            ++k;
        height[rank[i]]=k;
    }
}
int main()
{

}
