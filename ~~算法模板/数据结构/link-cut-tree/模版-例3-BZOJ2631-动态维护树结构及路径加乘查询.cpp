/*

ʹ��LCT��LCA
��һ����expose����access��
�ڶ�����expose����access��
���һ�ΰ���߱��ʵ�ߵ�λ��

���ǵ�һ���Ƚ���һ����access �������·��Ϊһ��ʵ��
�ڶ���accessʱ������ʹ�ڶ����㵽����·�����ʵ�ߣ���ԭ����ʵ·��һ���н�


*/

#include <bits/stdc++.h>
using namespace std;
#define rank rankk
#define next nxt
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const int MAX=2e5+15;
const ll MOD=51061;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<class T> inline
void read(T& num) {bool start=false,neg=false;char c;num=0;while((c=getchar())!=EOF) {if(c=='-') start=neg=true;else if(c>='0' && c<='9') {start=true;num=num*10+c-'0';} else if(start) break;}if(neg) num=-num;}
inline int powMM(int a,int b,int M){int ret=1;a%=M;while (b){if (b&1) ret=1LL*ret*a%M;b>>=1;a=1LL*a*a%M;}return ret;}
namespace{
template<class T> inline int add(int x,T y){x+=y;if(x>=MOD)x-=MOD;return x;}
template<class T> inline void addi(int &x,T y){x+=y;if(x>=MOD)x-=MOD;}
template<class T> inline int mul(int x,T y){return 1LL*x*y%MOD;}
template<class T> inline void muli(int &x,T y){x=1LL*x*y%MOD;}
template<class T> inline int sub(int x,T y){int res=x-y;if(res<0)res+=MOD;return res;}
template<class T> inline void subi(int &x,T y){x-=y;if(x<0)x+=MOD;}
template<class T> inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int n,m;
int val[MAX],sum[MAX],size[MAX],mval[MAX],aval[MAX],fa[MAX],rev[MAX];
int ch[MAX][2],stk[MAX];
void cal(int k,int mulv,int addv){//��mulv\addv����k���
    if(!k)return;
    val[k]=(val[k]*mulv+addv)%MOD;
    sum[k]=(sum[k]*mulv+addv*size[k])%MOD;
    aval[k]=(aval[k]*mulv+addv)%MOD;//Ҫ�´��ļӵ����ı��
    mval[k]=mval[k]*mulv%MOD;//Ҫ�´��ĳ˱��
}
bool isroot(int k){//�Ƿ�������splay�ĸ�
    return ch[fa[k]][0]!=k&&ch[fa[k]][1]!=k;
}
void pushup(int k){//���ӽڵ���¸��ڵ��pushup
    int l=ch[k][0],r=ch[k][1];
    sum[k]=(sum[l]+sum[r]+val[k])%MOD;
    size[k]=(size[l]+size[r]+1)%MOD;
}
void pushdown(int k){//���ڵ�����������¸���
    int l=ch[k][0],r=ch[k][1];
    if(rev[k]){//����������Ҫ��ת
        rev[k]^=1;rev[l]^=1;rev[r]^=1;
        swap(ch[k][0],ch[k][1]);
    }
    int tem_mul=mval[k],tem_add=aval[k];
    mval[k]=1;aval[k]=0;
    if(tem_mul!=1||tem_add!=0){
        cal(l,tem_mul,tem_add);
        cal(r,tem_mul,tem_add);
    }
}
void rotate(int x){//��תx����fa��λ��
    int y=fa[x],z=fa[y],l,r;
    l=(ch[y][1]==x);r=l^1;
    if(!isroot(y))ch[z][ch[z][1]==y]=x;
    fa[x]=z;fa[y]=x;fa[ch[x][r]]=y;
    ch[y][l]=ch[x][r];ch[x][r]=y;
    pushup(y);pushup(x);
}
void splay(int x){//��תx�����ڵ�splay�ĸ�
    int top=0;stk[++top]=x;
    for(int i=x;!isroot(i);i=fa[i])
        stk[++top]=fa[i];//��Ҫ���µ�·����ջ
    while(top)pushdown(stk[top--]);//һ·����pushdown����
    while(!isroot(x)){
        int y=fa[x],z=fa[y];
        if(!isroot(y)){
            if(ch[y][0]==x^ch[z][0]==y)rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}
void access(int x){//��x������·���ı߱�Ϊʵ��
    for(int i=0;x;i=x,x=fa[x]){
        splay(x);ch[x][1]=i;pushup(x);//ǿ���޸������Ҷ��� ��Ҫpushup
    }
}
void makeroot(int x){//��x����Ϊ�µ��桤����
    access(x);splay(x);//��ʱxֻ����������Ҷ��ӣ���ΪxΪ��·����������㣩
    rev[x]^=1;//��תx��ԭ�����桤������·��
}
void split(int x,int y){//��y���ó��桤���� ����x�ŵ��������ĸ� ���㴦��
    makeroot(y);access(x);splay(x);
}
void link(int x,int y){//����x\y������ ��δ�ں������ж��Ƿ�Ϸ���
    makeroot(x);fa[x]=y;
}
void cut(int x,int y){//�ж�x/y������ ͬ��δ�жϲ����Ƿ�Ϸ�
    makeroot(x);access(y);splay(y);//��ʱch[y][0]��Ӧ����x
    ch[y][0]=fa[x]=0;
}
int main(){
    read(n);read(m);
    for(int i=1;i<=n;i++)val[i]=sum[i]=mval[i]=size[i]=1;
    for(int u,v,i=1;i<n;i++){
        read(u);read(v);link(u,v);
    }
    char opt[10];
    while(m--){
        scanf("%s",opt);
        int u,v;read(u);read(v);
        if(opt[0]=='+'){//u��v��·����c
            int c;read(c);
            split(u,v);//��ʱuֻ����������Ҷ���
            //��u����������ΪҪ���µ�·��
            cal(u,1,c);
        }
        else if(opt[0]=='-'){//�ж�u v ���±�u' v'
            cut(u,v);read(u);read(v);
            link(u,v);
        }
        else if(opt[0]=='*'){//u��v��·����c
            int c;read(c);
            split(u,v);cal(u,c,0);
        }
        else if(opt[0]=='/'){//��u��v��·����Ȩֵ��
            split(u,v);printf("%d\n",sum[u]);
        }
    }
    return 0;

}

