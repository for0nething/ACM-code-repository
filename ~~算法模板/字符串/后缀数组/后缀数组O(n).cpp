/*
* ��׺����
* DC3�㷨�����Ӷ�O(n)
* ���е�������鶼Ҫ������
* stҪ��֤��βΪ0 ������ȫ��0  ��e.g. a[i]-'a'+1��
* da��st�±귶Χ [0,n]��һ�������һ��0 ����nһ������ַ������ȣ� st[i]��ȡֵ��Χ[0,m�� ����0ֻ���������ȡ��
*/
const int MAXN = 2010;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int wa[MAXN*3],wb[MAXN*3],wv[MAXN*3],wss[MAXN*3];
int c0(int *r,int a,int b)
{
    return r[a] == r[b] && r[a+1] == r[b+1] && r[a+2] == r[b+2];
}
int c12(int k,int *r,int a,int b)
{
    if(k == 2)
    return r[a] < r[b] || ( r[a] == r[b] && c12(1,r,a+1,b+1) );
    else return r[a] < r[b] || ( r[a] == r[b] && wv[a+1] < wv[b+1] );
}
void sort(int *r,int *a,int *b,int n,int m)
{
    int i;
    for(i = 0;i < n;i++)wv[i] = r[a[i]]; for(i = 0;i < m;i++)wss[i] = 0; for(i = 0;i < n;i++)wss[wv[i]]++;
    for(i = 1;i < m;i++)wss[i] += wss[i-1];
    for(i = n-1;i >= 0;i--)
    b[--wss[wv[i]]] = a[i];
}
void dc3(int *r,int *sa,int n,int m)
{
    int i, j, *rn = r + n;
    int *san = sa + n, ta = 0, tb = (n+1)/3, tbc = 0, p; r[n] = r[n+1] = 0;
    for(i = 0;i < n;i++)if(i %3 != 0)wa[tbc++] = i; sort(r + 2, wa, wb, tbc, m);
    sort(r + 1, wb, wa, tbc, m);
    sort(r, wa, wb, tbc, m);
    for(p = 1, rn[F(wb[0])] = 0, i = 1;i < tbc;i++) rn[F(wb[i])] = c0(r, wb[i-1], wb[i]) ? p - 1 : p++;
    if(p < tbc)dc3(rn,san,tbc,p);
    else for(i = 0;i < tbc;i++)san[rn[i]] = i;
    for(i = 0;i < tbc;i++) if(san[i] < tb)wb[ta++] = san[i] * 3;
    if(n % 3 == 1)wb[ta++] = n - 1; sort(r, wb, wa, ta, m);
    for(i = 0;i < tbc;i++)wv[wb[i] = G(san[i])] = i;
    for(i = 0, j = 0, p = 0;i < ta && j < tbc;p++)
    sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for(;i < ta;p++)sa[p] = wa[i++];
    for(;j < tbc;p++)sa[p] = wb[j++];
}
//str��saҲҪ����
void da(int str[],int sa[],int rank[],int height[],int n,int m)
{
    for(int i = n;i < n*3;i++) str[i] = 0;
    dc3(str, sa, n+1, m);
    int i,j,k = 0;
    for(i = 0;i <= n;i++)rank[sa[i]] = i;
    for(i = 0;i < n; i++)
    {
        if(k) k--;
        j = sa[rank[i]-1]; while(str[i+k] == str[j+k]) k++; height[rank[i]] = k;
    }
}
int st[MAXN*3],sa[MAXN*3],rank[MAXN*3],height[MAXN*3];
