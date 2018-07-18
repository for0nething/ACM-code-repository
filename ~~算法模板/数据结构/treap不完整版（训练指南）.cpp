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
//#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define mp make_pair
#define pb push_back
#define xo(a,b) ((b)&1?(a):0)
#define tm tmp

//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;
//const double INF=1e20;
const int INF=0x3f3f3f3f;
//const int INF= 0x7fffffff;
//const ll INF=0x3f3f3f3f3f3f3f3fll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=2005;
//const ll MAXN=2e8;
//const int MAX_N=MAX;
const ll MOD=1e9+7;
//const ull MOD=1e7+7;
//const ll MOD=998244353;
//const long double pi=acos(-1.0);
//const double eps=0.00000001;
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
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
//const long double eps=-1.0;
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);
void open()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
}
struct Node
{
    Node *ch[2];//��������
    int r;//���ȼ� ��ֵԽ�� ���ȼ�Խ��
    int v;//ֵ
    int s;//�������е�siz
    int cmp(int x)const{
        if(x==v)return -1;
        return x<v?0:1;
    }
    void maintain()
    {
        s=ch[0]->s+ch[1]->s+1;
    }
};
Node *null=new Node();
//d=0�������� d=1��������
void rotate(Node* &o,int d)
{
    Node* k=o->ch[d^1];o->ch[d^1]=k->ch[d];k->ch[d]=o;
    o->maintain();k->maintain();//ע�������ά��o����ά��k
    o=k;
}
//����oΪ���������в����ֵx���޸�o
void insert(Node* &o,int x)
{
    if(o==null)
    {
        o=new Node();o->ch[0]=o->ch[1]=null;o->v=x;o->r=rand();
    }
    else
    {
        int d=o->cmp(x);
        insert(o->ch[d],x);if(o->ch[d]->r>o->r)rotate(o,d^1);
    }
}
//����oΪ����������ɾ����ֵΪx�Ľ��
void remove(Node* &o,int x)
{
    int d=o->cmp(x);
    if(d==-1)
    {
        if(o->ch[0]==null)o=o->ch[1];
        else if(o->ch[1]==null)o=o->ch[0];
        else
        {
            int d2=(o->ch[0]->r>o->ch[1]->r?1:0);
            rotate(o,d2);remove(o->ch[d2],x);
        }
    }
    else
        remove(o->ch[d],x);
}
int find(Node* o,int x)
{
    while(o!=null)
    {
        int d=o->cmp(x);
        if(d==-1)return 1;//����
        else o=o->ch[d];
    }
    return 0;//������
}
/*
    ���������У�ÿ��������һ��������size����ʾ����Ϊ�����������ܽ����
    ����������֧�������²�����
    1��Kth(k):�ҳ���kСԪ��
    2��Rank(x):ֵx�ġ����Ρ�������xС�Ľ��ĸ���+1
    ��Treapʵ���������ķ����������ģ����������һ����Ա����s����������size�򣩣�Ȼ���дһ��maintain����
    Ϊ�˼��ٳ���Ŀ����ԣ�һ����һ����ʵ��ָ��null�����ָ��NULL
*/

int main()
{

}
/*
16 20
21
22
23
24
25
26
27
28
101
102
103
104
105
106
107
108
1 2
3 4
5 6
7 8
9 10
11 12
13 14
15 16
1 10
2 9
3 12
4 11
5 14
6 13
7 16
8 15
1 12
1 13
3 16
6 15


B
C
C
B
C
B
C
B
A
C
C
A
C
A
C
A
*/
