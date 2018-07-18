/*
KMP基本模板
*/
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
#include <stack>
#define mp make_pair
#define Elemtype int
typedef long long ll;
typedef unsigned long long ull;
const int MAX=1e6+5;
const int INF=-1e9;
using namespace std;
typedef pair<int,int> pii;
int f[MAX];
string x;
void getf(string x,int m)//m为串的长度 下标从1开始 最大为m
{
    f[0]=f[1]=0;
    for(int i=2,j=0;i<=m;i++)
    {
        while(j&&x[j+1]!=x[i])
            j=f[j];
        if(x[j+1]==x[i])
            j++;
        f[i]=j;
    }
}
bool kmp(string x,string y)//在y中匹配x（即y比x长）
{
    getf(x,x.size());
    for(int i=1,j=0;i<=y.size();i++)
    {
        while(j&&x[j+1]!=y[i])
            j=f[j];
        if(x[j+1]==y[i])
            j++;
        if(j>=x.size())
            return true;
    }
    return false;
}
