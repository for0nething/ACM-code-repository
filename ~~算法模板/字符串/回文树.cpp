/*
回文树
空间复杂度 O(N*字符集大小）
时间复杂度 O（N*log(字符集大小））

*/
const int MAXN=1e5+5;
const int N=26;//字符集大小
struct Palindromic_Tree
{
    int next[MAXN][N];
//next指针和字典树类似，指向的串由当前串两端加上同一个字符构成
    int fail[MAXN];//fail指针，失配后跳转到fail指针指向的节点
    int cnt[MAXN];//节点i表示的本质不同的串的个数（建树时求出的是不完全的，count（）函数之后才全）
    int num[MAXN];//num[i]表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数
    int len[MAXN];//len[i]表示节点i表示的回文串的长度
    int S[MAXN];//第i次添加的字符（一开始设S[0]=-1(可以是任意一个串S中不会出现的字符））
    int last;//指向上一个字符所在的节点，方便下次add
    int n;//字符数组指针
    int p;//节点

    int newnode(int l)//新建节点
    {
        for(int i=0;i<N;++i)
            next[p][i]=0;
        cnt[p]=0;
        num[p]=0;
        len[p]=l;
        return p++;
    }

    void init()//初始化
    {
        p=0;
        newnode(0);
        newnode(-1);
        last=0;
        n=0;
        S[n]=-1;//开始放一个字符集中没有的字符，减少特判
        fail[0]=1;
    }

    int get_fail(int x)//和KMP一样，失配后找一个尽量最长的
    {
        while(S[n-len[x]-1]!=S[n])
            x=fail[x];
        return x;
    }
    void add(int c)
    {
        c-='a';
        s[++n]=c;
        int cur=get_fail(last);//通过上一个回文串找这个回文串匹配位置
        if(!next[cur][c])//若该回文串未出现过，说明出现了一个新的本质不同的回文串
        {
            int now=newnode(len[cur]+2);//新建节点
            fail[now]=next[get_fail(fail[cur])][c];
            next[cur][c]=now;
            num[now]=num[fail[now]]+1;
        }
        last=next[cur][c];
        cnt[last]++;
    }

    void count()
    {
        for(int i=p-1;i>=0;--i)
            cnt[fail[i]]+=cnt[i];
        //父亲累加儿子的cnt，因为若fail[v]=u，则u一定是v的回文子串
    }
};
