/*
��������һ��N��Ԫ�ص�����a����ʼֵȫ��Ϊ0����������н����������ֲ�����

��������1����ʽΪ1 x k����λ��x��Ԫ�ؼ���k��λ�ô�1��ŵ�N����

��������2����ʽΪ2 x y���������[x,y]������Ԫ�صĺ͡�

˵����
    ����һ���������״�������⣬���Ժ���ѹ������������ڣ�������CDQ���ν�����������޸ĺͲ�ѯ�����⡣

�������ǰ���ת����һ����άƫ�����⣬ÿ��������һ�������(a,b)��ʾ������a��ʾ����������ʱ�䣬b��ʾ������λ�ã�
    ʱ����Ĭ������ģ����������ںϲ�������Ĺ����У��Ͱ���b��С�����˳��ϲ���

�����������ˣ���α�ʾ�޸����ѯ��

��������ϸ����μ����룬����Դ�����һЩ���ͣ�����ϴ���������
    ���Ƕ���ṹ��Query����3��Ԫ�أ�type��idx��val������idx��ʾ������λ�ã�typeΪ1��ʾ�޸ģ�val��ʾ�����ϵ�ֵ����
    �����ڲ�ѯ��������ǰ׺�͵�˼������ֽ������������sum[1,y]-sum[1,x-1]�����ֽ������ǰ׺�͵Ĳ�ѯ��
    �ںϲ��Ĺ����У�typeΪ2��ʾ������һ����ѯ����˵�x-1����Ҫ�Ѹò�ѯ�Ľ����ȥ��ǰ�����ϵ�ֵ��ǰ׺�͡���
    typeΪ3��ʾ������һ����ѯ���Ҷ˵�y����Ҫ�Ѳ�ѯ�Ľ�����ϵ�ǰ�����ϵ�ֵ��ǰ׺�͡���val��ʾ���ǵڼ�����ѯ����
    ���������ǾͰ�ÿ������ת�����˴��и�����Ϣ�������(ʱ�䣬λ��)��Ȼ����������н���CDQ���Ρ�

�����м�����Ҫע�⣺

����λ����ͬ�Ĳ�����Ҫ���޸ĺ��ѯ��
������Ϊ�˷��㣬ʹ������ҿ����䡣
�ϲ������ʱ��ͳ�ơ����ϵ�ֵ��ǰ׺�͡���ֻ��ͳ����������ڵ��޸Ĳ������Ķ���ѯ�����ʱ��ֻ���޸��ұ������ڵĲ�ѯ�������Ϊֻ����������ڵ��޸�ֵ���ұ������ڵĲ�ѯ�����Ӱ�컹û��ͳ�ơ�
�����У��������������г�ʼֵ�ģ����԰�ÿ����ʼֵ��Ϊһ���޸Ĳ�����
*/
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <bitset>
#include <utility>
#include <complex>
#include <assert.h>
#include <limits.h>
#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp

//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=3e5+10;
const int MOD=1e9+7;
//const long double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
const double eps=1e-6;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
//#define double long double
template<class T> inline
void read(T& num) {
    bool start=false,neg=false;
    char c;
    num=0;
    while((c=getchar())!=EOF) {
        if(c=='-') start=neg=true;
        else if(c>='0' && c<='9') {
            start=true;
            num=num*10+c-'0';
        } else if(start) break;
    }
    if(neg) num=-num;
}
inline int powMM(int a,int b,int M){
    int ret=1;
    a%=M;
    while (b){
        if (b&1) ret=1LL*ret*a%M;
        b>>=1;
        a=1LL*a*a%M;
    }
    return ret;
}
inline int add(int x,int y){return (x+y)%MOD;}
inline int mul(int x,int y){return 1LL*x*y%MOD;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,m;
struct Query{
    int type,idx;
    ll val;
    bool operator<(const Query &rhs)const{//����λ�ô�С���������޸������ڲ�ѯ
        return idx==rhs.idx?type<rhs.type:idx<rhs.idx;
    }
}query[MAX];
int qidx,aidx;
ll ans[MAX];//������
Query tmp[MAX];//�鲢����ʱ����
void cdq(int L,int R){//����ҿ�
    if(R-L<=1)return;
    int M=(L+R)>>1;cdq(L,M);cdq(M,R);
    ll sum=0;
    int p=L,q=M,o=0;//��������Ҳ�ϲ�
    while(p<M &&q<R){
        if(query[p]<query[q]){//ֻͳ����������ڵ��޸�ֵ
            if(query[p].type==1)sum+=query[p].val;
            tmp[o++]=query[p++];
        }
        else{//ֻ�޸��ұ������ڵĲ�ѯ���
            if(query[q].type==2)ans[query[q].val]-=sum;
            else if(query[q].type==3)ans[query[q].val]+=sum;
            tmp[o++]=query[q++];
        }
    }
    while(p<M)tmp[o++]=query[p++];
    while(q<R){
        if(query[q].type==2)ans[query[q].val]-=sum;
        else if(query[q].type==3)ans[query[q].val]+=sum;
        tmp[o++]=query[q++];
    }
    for(int i=0;i<o;++i)query[i+L]=tmp[i];//˳���������?
}
int main()
{
    read(n);read(m);
    for(int i=1;i<=n;i++){
        query[qidx].idx=i;query[qidx].type=1;
        scanf("%lld",&query[qidx].val);++qidx;
    }
    for(int i=0;i<m;++i){
        int type;read(type);
        query[qidx].type=type;
        if(type==1)scanf("%d%lld",&query[qidx].idx,&query[qidx].val);
        else{//�Ѳ�ѯ������Ϊ������
            int l,r;read(l);read(r);
            query[qidx].idx=l-1;query[qidx].val=aidx;++qidx;
            query[qidx].type=3;query[qidx].idx=r;query[qidx].val=aidx;
            ++aidx;
        }
        ++qidx;
    }
    cdq(0,qidx);
    for(int i=0;i<aidx;++i)printf("%lld\n",ans[i]);
    return 0;
}
/*
*/
