int a[MAX],b[MAX],rt[MAX];
int bin[30];//2^i
struct trie{
    int cnt;//结点id
    int ch[MAX*25][2],sum[MAX*25];
    int insert(int x,int val){//插入值val x为前版本的结点 返回新的根节点
        int re,y;re=y=++cnt;
        for(int i=23;i>=0;i--)//固定位数 保证位对齐
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
    int query(int l,int r,int val){//询问在l、r结点之间 与val异或最大的结果
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
