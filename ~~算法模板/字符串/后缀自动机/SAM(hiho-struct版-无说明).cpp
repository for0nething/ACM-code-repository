const int MAXL=2e6+5;
const int MAXCH=26;
const char CH='a';
struct SAM
{
    int maxlen[MAXL],minlen[MAXL],trans[MAXL][MAXCH],slink[MAXL];
    int ind[MAXL];//�����ӽڵ����
    int edpts[MAXL];//����endpos����
    bool pre[MAXL];//�Ƿ�Ϊǰ׺���ڽ��
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
        /*
            �������Զ���������һ������ �ص�root��0��
            ��������һ�в����޸�
            �����(2018.8.3UPD:��ȫ���ü���仰��)
            if(trans[u][c]!=-1&&maxlen[trans[u][c]]==maxlen[u]+1)return trans[u][c];
            ��û��if�ɹ��������������
        */
        int z=new_state(maxlen[u]+1,-1,NULL,-1);
        pre[z]=true;//�ý���Ϊ����ԭ��ǰ׺�Ľ��
        int v=u;
        while(v!=-1&&trans[v][c]==-1)
        {
            trans[v][c]=z;
            v=slink[v];
        }
        if(v==-1)//��򵥵������suffix-path(u->s)�϶�û�ж�Ӧ�ַ�ch��ת��
        {
            minlen[z]=1;
            slink[z]=0;
            ++ind[0];
            return z;
        }
        int x=trans[v][c];
        if(maxlen[v]+1==maxlen[x])//�ϼ򵥵���������ò��x
        {
            minlen[z]=maxlen[x]+1;
            slink[z]=x;
            ++ind[x];
            return z;
        }
        int y=new_state(maxlen[v]+1,-1,trans[x],slink[x]);//��ӵ���������x
        ind[y]+=2;
        minlen[x]=maxlen[y]+1;
        slink[x]=y;
        minlen[z]=maxlen[y]+1;
        slink[z]=y;
        int w=v;
        while(w!=-1&&trans[w][c]==x)//�ò����ַ�������Խ��Խ�� һ������Ҫת�Ƶ�y�� ��Ϊy��������xԭ���϶̵Ĳ���
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
