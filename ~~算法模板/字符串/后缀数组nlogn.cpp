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
const int B=1024;//桶的大小
const double M=4e18;
using namespace std;
const int MOD=1e9+7;
typedef pair<int,int> pii;

char s[MAX];
int sa[MAX],t[MAX],t2[MAX],c[MAX],n;
int rank[MAX],height[MAX];//rank[i]代表后缀i在sa数组中的下标
//height[i]定义为sa[i-1]和sa[i]的最长公共前缀（LCP）的长度
//sa数组储存第i大的起始位置
/*
对于两个后缀j和k，不妨设rank[j]<rank[k]，则不难证明后缀j和k的LCP长度等于
height[rank[j]+1],height[rank[j]+2]……height[rank[k]]中的最小值
即RMQ(height,rank[j]+1,rank[k])
*/
void build_sa(int m)
{
    int i,*x=t,*y=t2;//x记录各个下标开始的串的排序编号（大小）
    for(int i=0;i<m;i++)
        c[i]=0;//初始化c
    for(int i=0;i<n;i++)
        ++c[x[i]=s[i]];//该字符出现次数++
    for(int i=1;i<m;i++)
        c[i]+=c[i-1];//求前缀和，sa中每个字符出现的下标区间得到确定，总区间为[0,n-1]
    for(int i=n-1;i>=0;i--)
        sa[--c[x[i]]]=i;//该下标（排位）对应的位置
    for(int k=1;k<=n;k<<=1)//每组个数/2
    {
        int p=0;
        //直接利用sa数组排序第二关键字
        for(int i=n-k;i<n;i++)//因为后面总共不足k个
            y[p++]=i;//后面的k个一定排序两两不同，
        for(int i=0;i<n;i++)
            if(sa[i]>=k)
                y[p++]=sa[i]-k;//恰好是之前涉及不到的

        /*感觉不这样也行 因为后面根本就没有用到？？*/
        //基数排序第一关键字
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
            break;//以后继续倍增，sa也不会改变，退出
        m=p;//下次基数排序的最大值
    }
}
int m;//模板长度，简单起见，这里存在全局变量中
int cmp_suffix(char *pattern,int p)//判断模板s是否为后缀p的前缀
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
        if(res<0)//模式串比第M大的小
            R=M-1;
        else//模式串比第M大的大
            L=M+1;
    }
    return -1;//找不到
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
