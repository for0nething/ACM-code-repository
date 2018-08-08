/*
    2-SAT问题是这样的：有n个布尔变量xi,另有m个需要满足的条件，每个条件的形式都是
    “xi为真/假或者xj为真/假”。比如“x1为真或者x3为假”、“x7为假或者x2为假”都是合法的条件。
    这里或指的是两个条件至少有一个是正确的
*/
const int maxn=1e5+5;
struct TwoSAT
{
    int n;
    vector<int>G[maxn*2];
    bool mark[maxn*2];
    int S[maxn*2],c;//s数组存储当前被标记的点
    bool dfs(int x)
    {
        if(mark[x^1])return false;//真假同时被标记，逻辑矛盾
        if(mark[x])return true;//记忆化
        mark[x]=1;
        S[c++]=x;
        for(int i=0;i<G[x].size();i++)
            if(!dfs(G[x][i]))return false;//同一个强连通分量应该同一种颜色
        return true;
    }
    void init(int n)
    {
        this->n=n;
        for(int i=0;i<n*2;i++)G[i].clear();
        memset(mark,0,sizeof(mark));
    }
    //x=xval or y=yval
    /*
        x为xval 或者 y为yval需要有一个满足
    */
    void add_clause(int x,int xval,int y,int yval)
    {
        x=x*2+xval;y=y*2+yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }
    bool solve()
    {
        for(int i=0;i<n*2;i+=2)
        {
            if(!mark[i]&&!mark[i+1])//真假都没标记 故需要dfs
            {
                c=0;//清零
                if(!dfs(i))//尝试标记为true
                {
                    while(c>0)mark[S[--c]]=false;
                    if(!dfs(i+1))return false;//尝试标记为false
                }
            }
        }
        return true;
    }
};
int main()
{


}
/*

*/
