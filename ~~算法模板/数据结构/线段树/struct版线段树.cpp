struct seg_tree{
    int cnt[MAX<<2],val[MAX<<2],lazy[MAX];
    void change(int x,int v){
        addi(val[x],mul(v,cnt[x]));addi(lazy[x],v);
    }
    void pushup(int x){
        val[x]=add(val[x<<1],val[x<<1|1]);
    }
    void pushdown(int x){
        if(lazy[x]){
            change(x<<1,lazy[x]);change(x<<1|1,lazy[x]);
            lazy[x]=0;
        }
    }
    void build(int k,int l,int r){
        val[k]=lazy[k]=0;
        if(l==r){cnt[k]=a[l];val[k]=mul(a[l],b[l]);return; }
        int mid=(l+r)/2;
        build(k<<1,l,mid);build(k<<1|1,mid+1,r);
        cnt[k]=add(cnt[k<<1],cnt[k<<1|1]);
        pushup(k);
    }
    void update(int k,int l,int r,int val,int ul,int ur){
        if(l>=ul&&r<=ur){change(k,val);return;}
        int mid=(l+r)/2;
        pushdown(k);
        if(ul<=mid)update(k<<1,l,mid,val,ul,ur);
        if(ur>mid)update(k<<1|1,mid+1,r,val,ul,ur);
        pushup(k);
    }
    int query(int k,int l,int r,int ql,int qr){
        if(l>=ql&&r<=qr)return val[k];
        int mid=(l+r)/2,re=0;
        pushdown(k);
        if(ql<=mid)addi(re,query(k<<1,l,mid,ql,qr));
        if(qr>mid)addi(re,query(k<<1|1,mid+1,r,ql,qr));
        pushup(k);
        return re;
    }
}T[2];
