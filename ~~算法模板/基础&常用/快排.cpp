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

/*
    rand主元版快速排序
    如需指定主元位置只需在r_partition中pos的随机部分改成固定

*/
template<typename T>int r_partition(T a[],int p,int r)//闭区间
{
    int pos=rand()%(r-p+1);
    swap(a[p+pos],a[r]);
    T x=a[r];
    int i=p-1;
    for(int j=p;j<=r-1;j++)
    {
        if(a[j]<=x)
            swap(a[++i],a[j]);
    }
    swap(a[i+1],a[r]);
    return i+1;
}
template<typename T>void r_qsort(T a[],int p,int r)
{
    if(p<r)
    {
        int q=r_partition(a,p,r);
        r_qsort(a,p,q-1);
        r_qsort(a,q+1,r);
    }
}

/*
    测试样例
    另附上nth-element 这一不需要完整快排的高效查询排序后某位置的值的函数
*/
int a[10]={1,3,5,7,2,1,5,100,4,10};
int main()
{
    r_qsort(a,0,9);
    for(int i=0;i<10;i++)
        printf("%d ",a[i]);
    int n=10;
    nth_element(a,(a+(n-1)/2),a+n);
    printf("%d\n",a[(n-1)/2]);//排序后第 (n-1)/2+1小的
    return 0;
}
/*

5 5 10
3 1
3 4
4 5
1 4
5 3

*/
