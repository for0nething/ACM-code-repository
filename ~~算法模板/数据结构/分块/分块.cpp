/*
    分块
    num: 分的块的个数
    belong[i]: i属于哪一块
    block:块的大小
    l[i]:i这块的左端点的位置
    r[i]:i这块的右端点的位置

*/
const int maxn=1e5+5;
int belong[maxn],l[maxn],r[maxn];
int num,block;
void build()
{
    block=sqrt(n);//n为总个数
    num=n/block;
    if(n%block)++num;
    for(int i=1;i<=num;i++)
        l[i]=(i-1)*block+1,r[i]=i*block;
    r[num]=n;
    for(int i=1;i<=n;i++)
        belong[i]=(i-1)/blcok+1;
}


