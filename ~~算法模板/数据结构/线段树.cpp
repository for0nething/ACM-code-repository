/*
    区间和的修改、查询
*/
int sum[maxn*4];
void pushup(int x){
    sum[x]=sum[x<<1]+sum[x<<1|1];
}
void build(int x,int l,int r){
	if (l==r){
        sum[x]=1;
		return;
	}int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void update(int x,int l,int r,int L,int R){//negative
    if (!sum[x]) return;
	if (l<=L&&R<=r){
        sum[x]=0;
		return;
	}int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,L,mid);
	if (r>mid) update(x<<1|1,l,r,mid+1,R);
	pushup(x);
}
int query(int x,int l,int r,int L,int R){
    if (!sum[x]) return 0;
	if (l<=L&&R<=r) return sum[x];
	int mid=(L+R)/2,ret=0;
	if (mid>=l) ret+=query(x<<1,l,r,L,mid);
	if (r>mid) ret+=query(x<<1|1,l,r,mid+1,R);
	pushup(x);
	return ret;
}
