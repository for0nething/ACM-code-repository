/*
    �ֿ�
    num: �ֵĿ�ĸ���
    belong[i]: i������һ��
    block:��Ĵ�С
    l[i]:i������˵��λ��
    r[i]:i�����Ҷ˵��λ��

*/
const int maxn=1e5+5;
int belong[maxn],l[maxn],r[maxn];
int num,block;
void build()
{
    block=sqrt(n);//nΪ�ܸ���
    num=n/block;
    if(n%block)++num;
    for(int i=1;i<=num;i++)
        l[i]=(i-1)*block+1,r[i]=i*block;
    r[num]=n;
    for(int i=1;i<=n;i++)
        belong[i]=(i-1)/blcok+1;
}


