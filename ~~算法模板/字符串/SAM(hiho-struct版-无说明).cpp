const int MAXL=2e6+5;
const int MAXCH=26;
const char CH='a';
struct SAM
{
    int maxlen[MAXL],minlen[MAXL],trans[MAXL][MAXCH],slink[MAXL];
    int ind[MAXL];//树中子节点个数
    int edpts[MAXL];//结点的endpos个数
    bool pre[MAXL];//是否为前缀所在结点
    int tot;
    int new_state(int _maxlen,int _minlen,int *_trans,int _slink)
    {
        maxlen[tot]=_maxlen;
        minlen[tot]=_minlen;
        for(int i=0;i<MAXCH;i++)
        {
            if(_trans==NULL)
                trans[tot][i]=-1;
            else trans[tot][i]=_trans[i];
        }
        slink[tot]=_slink;
        return tot++;
    }
    int add_char(char ch,int u)
    {
        int c=ch-CH;
        int z=new_state(maxlen[u]+1,-1,NULL,-1);
        pre[z]=true;//该结点必为包含原串前缀的结点
        int v=u;
        while(v!=-1&&trans[v][c]==-1)
        {
            trans[v][c]=z;
            v=slink[v];
        }
        if(v==-1)//最简单的情况，suffix-path(u->s)上都没有对应字符ch的转移
        {
            minlen[z]=1;
            slink[z]=0;
            ++ind[0];
            return z;
        }
        int x=trans[v][c];
        if(maxlen[v]+1==maxlen[x])//较简单的情况，不用拆分x
        {
            minlen[z]=maxlen[x]+1;
            slink[z]=x;
            ++ind[x];
            return z;
        }
        int y=new_state(maxlen[v]+1,-1,trans[x],slink[x]);//最复杂的情况，拆分x
        slink[y]=slink[x];
        ind[y]+=2;
        minlen[x]=maxlen[y]+1;
        slink[x]=y;
        minlen[z]=maxlen[y]+1;
        slink[z]=y;
        int w=v;
        while(w!=-1&&trans[w][c]==x)//该部分字符串长度越来越短 一定都是要转移到y的 因为y保留的是x原本较短的部分
        {
            trans[w][c]=y;
            w=slink[w];
        }
        minlen[y]=maxlen[slink[y]]+1;
        return z;
    }
};
int main()
{

    return 0;
}

/*



4 1 1 3 1 5 5 1 3
*/
