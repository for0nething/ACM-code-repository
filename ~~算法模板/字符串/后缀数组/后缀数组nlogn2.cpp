
// sa[i]��ʾ ��iС���±��0��ʼ�����մ����ĺ�׺����ʼ����
//rank[i]��ʾ ԭ���±�i��ʼ�ĺ�׺�����к�׺�е�����
//height[i] ��ʾ ��iС�ģ��±��0��ʼ�����մ����ĺ�׺���i-1С�ĺ�׺�ж��ٹ���ǰ׺

#define rank rankk

int n,k;
int rank[MAX];
int tmp[MAX];
//�Ƚ�rank[i],rank[i+k] ��rank[j],rank[j+k]
bool compare_sa(int i,int j)
{
    if(rank[i]!=rank[j])
        return rank[i]<rank[j];
    else
    {
        int ri=i+k<=n?rank[i+k]:-1;
        int rj=j+k<=n?rank[j+k]:-1;
        return ri<rj;
    }
}
//�����ַ���S�ĺ�׺����
void construct_sa(string S,int *sa)
{
    n=S.length();
    //��ʼ����Ϊ1,rankֱ��ȡ�ַ��ı���
    for(int i=0;i<=n;i++)
    {
        sa[i]=i;
        rank[i]=i<n?S[i]:-1;
    }
    //���öԳ���Ϊk������Ľ���Գ���Ϊ2k������
    for(k=1;k<=n;k<<=1)
    {
        sort(sa,sa+n+1,compare_sa);
        //����tmp����ʱ�洢�¼����rank����ת���rank��
        tmp[sa[0]]=0;
        for(int i=1;i<=n;i++)
            tmp[sa[i]]=tmp[sa[i-1]]+compare_sa(sa[i-1],sa[i])?1:0;
        for(int i=0;i<=n;i++)
            rank[i]=tmp[i];
    }
}
/*
���ں�׺������ַ���ƥ��
�����Ѿ���������ַ���S�ĺ�׺���飬����Ҫ���ַ���T���ַ���S�г��ֵ�λ��
ֻҪͨ�����������Ϳ�����O(TlogS)��ʱ�����

*/
bool contain(string S,int *sa,string T)
{
    int l=0,r=S.length(),mid;
    while(r-l>1)
    {
        mid=(l+r)/2;
        //�Ƚ�S��λ��sa[c]��ʼ����ΪT���ִ���T
        if(S.compare(sa[mid],T.length(),T)==0)
            l=mid;
        else
            r=mid;
    }
    return S.compare(sa[r],T.length(),T)==0;
}
//�����ַ���S�Ͷ�Ӧ�ĺ�׺����sa������߶�����lcp
void construct_lcp(string s,int *sa,int *lcp)
{
    int n=S.length();
    for(int i=0;i<=n;i++)rank[sa[i]]=i;
    int h=0;
    lcp[0]=0;
    for(int i=0;i<n;i++)
    {
        //�����ַ����д�λ��i��ʼ�ĺ�׺�����ں�׺�����е�ǰһ����׺��lcp
        int j=sa[rank[i]-1];//-1 ��û�й�ϵ ��Ϊ�ǿմ����±�Ϊ0
        if(h>0)--h;
        for(;j+h<n&&i+h<n;h++)
        {
            if(S[j+h]!=S[i+h])break;
        }
        lcp[rank[i]-1]=h;
    }
}
/*
����׺���������ݽṹ�е� Range Minimum Query���
������Եõ���׺����������������׺�������ǰ׺�������Եõ�����������׺�������ǰ׺
������ rk[i]<rk[j] ���λ��i��j��ʼ�ĺ�׺�������ǰ׺�ĳ��Ⱦ���lcp[rk[i]] lcp[rk[i]+1] ���� lcp[rk[j]-1]�е���Сֵ
*/
int main()
{

}
