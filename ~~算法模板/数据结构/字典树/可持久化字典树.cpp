int a[MAX],b[MAX],rt[MAX];
int bin[30];//2^i
struct trie{
    int cnt;//���id
    int ch[MAX*25][2],sum[MAX*25];
    int insert(int x,int val){//����ֵval xΪǰ�汾�Ľ�� �����µĸ��ڵ�
        int re,y;re=y=++cnt;
        for(int i=23;i>=0;i--)//�̶�λ�� ��֤λ����
        {
            ch[y][0]=ch[x][0];ch[y][1]=ch[x][1];
            sum[y]=sum[x]+1;
            int t=val&bin[i];t>>=i;
            x=ch[x][t];
            ch[y][t]=++cnt;
            y=ch[y][t];
        }
        sum[y]=sum[x]+1;
        return re;
    }
    int query(int l,int r,int val){//ѯ����l��r���֮�� ��val������Ľ��
        int re=0;
        for(int i=23;i>=0;i--){
            int t=val&bin[i];t>>=i;
            if(sum[ch[r][t^1]]-sum[ch[l][t^1]])
                re+=bin[i],r=ch[r][t^1],l=ch[l][t^1];
            else r=ch[r][t],l=ch[l][t];
        }
        return re;
    }
}trie;
