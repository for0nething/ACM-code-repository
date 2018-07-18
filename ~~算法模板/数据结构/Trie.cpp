/*��������MLE�汾 */
struct Trie
{
    int ch[MAX_NODE][sigma_size];//����������ĸ������
    int val[MAX_NODE];
    int num;//�������
    Trie(){num=1;memset(ch[0],0,sizeof(ch[0]));}//��ʼʱ���и��ڵ�
    int idx(char c)//���ض�Ӧ�ַ��ı��
    {
        return c-'a';
    }
    /*
    clear��������ʼ��trie
    */
    void clear() { num = 1; memset(ch[0], 0, sizeof(ch[0])); }
    /*
        �����ַ���s,������ϢΪv��ע��v�����0����Ϊ0��������㲻�ǵ��ʽ��
    */
    void insert(char *s,int v)
    {
        int u=0,len=strlen(s);
        for(int i=0;i<len;i++)
        {
            int c=idx(s[i]);
            if(!ch[u][c])//��㲻����
            {
                memset(ch[num],0,sizeof(ch[num]));
                val[num]=0;//�м�ڵ�ĸ�����ϢΪ0
                ch[u][c]=num++;//�½����
            }
            u=ch[u][c];//������
        }
        val[u]=v;//�ַ��������һ���ַ��ĸ�����ϢΪv
    }
    /*
     ��ѯ�ַ����ġ�������Ϣ��
     ��ѯ�����м��жϷ���0
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
    ���ַ���s�ĳ��Ȳ�����len��ǰ׺
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
            if(val[u]!=0)//�����������ҵ���ȫ��push��ȥ
                ans.push_back(val[u]);
        }
    }
};

/*����MLE�汾 */
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
    int checkstr(string s)//�����ַ������ֵ������ǰ׺
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
//Trie *tri=new Trie(0);  �Դ�����Trie
