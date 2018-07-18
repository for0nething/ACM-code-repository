
// sa[i]表示 第i小（下标从0开始，含空串）的后缀的起始点编号
//rank[i]表示 原串下标i开始的后缀在所有后缀中的排名
//height[i] 表示 第i小的（下标从0开始，含空串）的后缀与第i-1小的后缀有多少公共前缀

#define rank rankk

int n,k;
int rank[MAX];
int tmp[MAX];
//比较rank[i],rank[i+k] 和rank[j],rank[j+k]
bool compare_sa(int i,int j)
{
    if(rank[i]!=rank[j])
        return rank[i]<rank[j];
    else
    {
        int ri=i+k<=n?rank[i+k]:-1;
        int rj=j+k<=n?rank[j+k]:-1;
        return ri<rj;
    }
}
//计算字符串S的后缀数组
void construct_sa(string S,int *sa)
{
    n=S.length();
    //初始长度为1,rank直接取字符的编码
    for(int i=0;i<=n;i++)
    {
        sa[i]=i;
        rank[i]=i<n?S[i]:-1;
    }
    //利用对长度为k的排序的结果对长度为2k的排序
    for(k=1;k<=n;k<<=1)
    {
        sort(sa,sa+n+1,compare_sa);
        //先在tmp中临时存储新计算的rank，再转存回rank中
        tmp[sa[0]]=0;
        for(int i=1;i<=n;i++)
            tmp[sa[i]]=tmp[sa[i-1]]+compare_sa(sa[i-1],sa[i])?1:0;
        for(int i=0;i<=n;i++)
            rank[i]=tmp[i];
    }
}
/*
基于后缀数组的字符串匹配
假设已经计算好了字符串S的后缀数组，现在要求字符串T在字符串S中出现的位置
只要通过二分搜索就可以在O(TlogS)的时间完成

*/
bool contain(string S,int *sa,string T)
{
    int l=0,r=S.length(),mid;
    while(r-l>1)
    {
        mid=(l+r)/2;
        //比较S从位置sa[c]开始长度为T的字串与T
        if(S.compare(sa[mid],T.length(),T)==0)
            l=mid;
        else
            r=mid;
    }
    return S.compare(sa[r],T.length(),T)==0;
}
//传入字符串S和对应的后缀数组sa，计算高度数组lcp
void construct_lcp(string s,int *sa,int *lcp)
{
    int n=S.length();
    for(int i=0;i<=n;i++)rank[sa[i]]=i;
    int h=0;
    lcp[0]=0;
    for(int i=0;i<n;i++)
    {
        //计算字符串中从位置i开始的后缀及其在后缀数组中的前一个后缀的lcp
        int j=sa[rank[i]-1];//-1 并没有关系 因为是空串的下标为0
        if(h>0)--h;
        for(;j+h<n&&i+h<n;h++)
        {
            if(S[j+h]!=S[i+h])break;
        }
        lcp[rank[i]-1]=h;
    }
}
/*
将后缀数组与数据结构中的 Range Minimum Query结合
不光可以得到后缀数组内相邻两个后缀的最长公共前缀，还可以得到任意两个后缀的最长公共前缀
假设有 rk[i]<rk[j] 则从位置i和j开始的后缀的最长公共前缀的长度就是lcp[rk[i]] lcp[rk[i]+1] …… lcp[rk[j]-1]中的最小值
*/
int main()
{

}
