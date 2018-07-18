/*
并查集
复杂度为阿克曼函数的反函数，比O(log(n))还快
*/

int par[MAX_N];//父亲
int rank[MAX_N];//树的高度
//初始化n个元素(为方便操作 改为n+1个元素)
void init(int n)
{
    for(int i=0;i<=n;i++)
    {
        par[i]=i;
        rank[i]=0;
    }
}
//查询树的根，期间加入了路径压缩
int find(int x)
{
    if(par[x]==x)
        return x;
    else
        return par[x]=find(par[x]);
}
//合并x和y所属的集合
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y)
        return ;
    if(rank[x]<rank[y])
        par[x]=y;
    else
    {
        par[y]=x;
        if(rank[x]==rank[y])
            rank[x]++;
    }
}
//判断x和y是否属于同一个集合
bool same(int x,int y)
{
    return find(x)==find(y);
}
