
const int MAXN=500010;
int a[MAXN],b[MAXN];
//�ö��ֲ��ҵķ����ҵ�һ��λ�ã�ʹ��num>b[i-1] ����num<b[i],����num����b[i]
int Search(int num,int low,int high)
{
    int mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(num>=b[mid]) low=mid+1;
        else
            high=mid-1;
    }
    return low;
}
int DP(int n)
{
    int i,len,pos; b[1]=a[1];
    len=1;
    for(i=2;i<=n;i++)
    {
        if(a[i]>=b[len])//���a[i]��b[]��������󻹴�ֱ�Ӳ��뵽���漴��
        {
            len=len+1; b[len]=a[i];
        }
        else//�ö��ֵķ�����b[]�������ҳ���һ����a[i]���λ�ò�����a[i]������λ��
        {
            pos=Search(a[i],1,len);
            b[pos]=a[i];
        }
    }
    return len;
}
