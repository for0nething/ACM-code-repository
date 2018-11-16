const int maxn=1e5+5;
struct node
{
    int l,r,sum;
}T[maxn*40];
int rt[maxn];
int cnt;
int n,m;
void update(int l,int r,int &x,int y,int pos)
{
    T[++cnt]=T[y];++T[cnt].sum;x=cnt;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(pos<=mid)update(l,mid,T[x].l,T[y].l,pos);
    else update(mid+1,r,T[x].r,T[y].r,pos);
}
int query(int l,int r,int x,int y,int k)
{
    if(l==r)return l;
    int mid=(l+r)>>1;
    int sum=T[T[y].l].sum-T[T[x].l].sum;
    if(sum>=k)return query(l,mid,T[x].l,T[y].l,k);
    else return query(mid+1,r,T[x].r,T[y].r,k-sum);
}
int a[maxn];
vector<int>v;
int getid(int x)//返回离散化后的排名（按值从小到大）
{
    return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);v.pb(a[i]);
    }
    sort(v.begin(),v.end());v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=1;i<=n;i++)
        update(1,n,rt[i],rt[i-1],getid(a[i]));
    for(int u,vs,k,i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&vs,&k);
        printf("%d\n",v[query(1,n,rt[u-1],rt[vs],k)-1]);
    }
    return 0;
}
