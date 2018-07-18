/*极其容易MLE版本 */
struct Trie
{
    int ch[MAX_NODE][sigma_size];//点数、“字母”种数
    int val[MAX_NODE];
    int num;//结点总数
    Trie(){num=1;memset(ch[0],0,sizeof(ch[0]));}//初始时仅有根节点
    int idx(char c)//返回对应字符的编号
    {
        return c-'a';
    }
    /*
    clear函数，初始化trie
    */
    void clear() { num = 1; memset(ch[0], 0, sizeof(ch[0])); }
    /*
        插入字符串s,附加信息为v。注意v必须非0，因为0代表：本结点不是单词结点
    */
    void insert(char *s,int v)
    {
        int u=0,len=strlen(s);
        for(int i=0;i<len;i++)
        {
            int c=idx(s[i]);
            if(!ch[u][c])//结点不存在
            {
                memset(ch[num],0,sizeof(ch[num]));
                val[num]=0;//中间节点的附加信息为0
                ch[u][c]=num++;//新建结点
            }
            u=ch[u][c];//往下走
        }
        val[u]=v;//字符串的最后一个字符的附加信息为v
    }
    /*
     查询字符串的“附加信息”
     查询过程中间中断返回0
    */
    int check(char *s)
    {
        int u=0,len=strlen(s);
        for(int i=0;i<len;i++)
        {
            int c=idx(s[i]);
            if(!ch[u][c])
                return 0;
            u=ch[u][c];
        }
        return val[u];
    }
    /*
    找字符串s的长度不超过len的前缀
    */
    void find_prefixes(const char *s,int len,vector <int> &ans)
    {
        int u=0;
        for(int i=0;i<len;i++)
        {
            if(s[i]=='\0')
                break;
            int c=idx(s[i]);
            if(!ch[u][c])
                break;
            u=ch[u][c];
            if(val[u]!=0)//过程中所有找到的全都push进去
                ans.push_back(val[u]);
        }
    }
};

/*不易MLE版本 */
struct Trie {
    bool isWord;
    Trie* child[26];
    Trie(bool isWord):isWord(isWord)
    {
        memset(child,0,sizeof(child));
    }
    void addWord(string &s)
    {
        Trie*cur =this;
        for(char c: s)
        {
            Trie* next=cur->child[c-'a'];
            if(next==nullptr)
                next=cur->child[c-'a']=new Trie(false);
            cur=next;
        }
        cur->isWord=true;
    }
    int checkstr(string s)//返回字符串在字典树中最长前缀
    {
        Trie*cur=this;int re=0;
        for(char c:s)
        {
            Trie* next=cur->child[c-'a'];
            if(next==nullptr)break;
            else{cur=next;++re;}
        }
        return re;
    }
    ~Trie()
    {
        for(int i=0;i<26;++i)
        {
            if(child[i])
                delete child[i];
        }
    }
};
//Trie *tri=new Trie(0);  以此来建Trie
