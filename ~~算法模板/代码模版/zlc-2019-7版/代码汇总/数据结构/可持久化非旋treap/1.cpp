#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// 内存回收: 没写, 写的话可以直接用个东西保存指向它的pointer个数
// 辣鸡蓝桥杯的题目, 喵的什么垃圾评测机, 全MLE是个什么东西
namespace persist_treap {
	typedef pair<int,int> Pair;
	const int maxn=1e7;//maxn>=2
	struct node {
		int l,r,len,size;
		ll val,lazy,sum;
		node(ll _val=0) {
			l=r=len=0; val=_val; lazy=0;
			sum=val; size=1;
		}
	} T[maxn];
	int root;
	int pool[maxn],st,ed;//ends
	void init() {
		int i; ed=maxn-1; root=0; T[0].size=0;//0:no use
		REP(i,maxn-1) pool[i]=i+1;//start from 1
	}
	void delnode(int pos) {
		if (ed==maxn-1) ed=0;
		// T[pos]=node();// no use
		pool[ed++]=pos;
	}
	int insnode(ll x) {//value
		// assert(st+1!=ed);// no !!!
		int pos=pool[st++];
		if (st==maxn-1) st=0;
		T[pos]=node(x);
		return pos;
	}
	int persistnode(int ini) {
		// assert(st+1!=ed);// no !!!
		int pos=pool[st++];
		T[pos]=T[ini];
		if (st==maxn-1) st=0;
		return pos;
	}
	void ADD(int x,ll val) { //update
		T[x].lazy+=val; T[x].val+=val;
		T[x].sum+=T[x].size*val;
	}
	bool pushdown(int x) {
		if (!T[x].lazy) return 0;
		if (T[x].l) {
			T[x].l=persistnode(T[x].l);
			ADD(T[x].l,T[x].lazy);
		}
		if (T[x].r) {
			T[x].r=persistnode(T[x].r);
			ADD(T[x].r,T[x].lazy);
		}
		T[x].lazy=0;
		return 1; // changed; -1/2空间
	}
	void pushup(int x) {
		T[x].sum=T[x].val;
		T[x].len=0; T[x].size=1;
		if (T[x].l) {
			T[x].sum+=T[T[x].l].sum;
			T[x].len=max(T[x].len,T[T[x].l].len+1);
			T[x].size+=T[T[x].l].size;
		}
		if (T[x].r) {
			T[x].sum+=T[T[x].r].sum;
			T[x].len=max(T[x].len,T[T[x].r].len+1);
			T[x].size+=T[T[x].r].size;
		}
	}
	int merge(int x,int y,bool downx=0,bool downy=0) {
		if (!x||!y) return x|y;
		if (T[x].len>T[y].len) {
			if (!downx) x=persistnode(x);
			bool okay=pushdown(x);
			T[x].r=merge(T[x].r,y,okay,downy);
			pushup(x); return x;
		} else {
			if (!downy) y=persistnode(y);
			bool okay=pushdown(y);
			T[y].l=merge(x,T[y].l,downx,okay);
			pushup(y); return y;
		}
	}
	pii split(int x,int k,bool down=0) {
		if (!x) return make_pair(0,0);
		if (!down) x=persistnode(x);
		bool persisted=pushdown(x); //persist:newnode
		// printf("split: %lld; sz=%d; k=%d\n",T[x].val,T[x].size,k);
		pii P;
		if (!k||T[T[x].l].size>=k) {
			// printf("to_left %d\n",T[x].l);
			P=split(T[x].l,k,persisted);
			T[x].l=P.second; pushup(x); P.second=x;
		} else {
			P=split(T[x].r,k-T[T[x].l].size-1,persisted);
			T[x].r=P.first; pushup(x); P.first=x;
		} return P;
	}
	void print_dfs(int x) {
		if (!x) return;
		print_dfs(T[x].l);
		printf("%lld ",T[x].val);
		print_dfs(T[x].r);
	}

	ll query(int l,int r) {//用个东西记录一下??
		pii A=split(root,l-1);
		// print_dfs(A.first); puts("A.first");
		pii B=split(A.second,r-l+1);
		// print_dfs(B.first); puts("B.first"); 
		// print_dfs(B.second); puts("B.second"); 
		return T[B.first].sum;
	}
	void update(int l,int r,ll val) {
		pii A=split(root,l-1);
		pii B=split(A.second,r-l+1);
		ADD(B.first,val);
		root=merge(merge(A.first,B.first),B.second);
	}
	void insert(int k,int val) {//after kth
		pii A=split(root,k);
		int y=insnode(val);
		// print_dfs(A.first); puts("okay");
		// printf("root=%d\n",root);
		root=merge(A.first,merge(y,A.second));
	}
	void transto(int l,int r,int x,int y) {
		pii A=split(root,l-1);
		pii B=split(A.second,r-l+1);
		pii A_=split(root,x-1);
		pii B_=split(A_.second,y-x+1);
		root=merge(merge(A.first,B_.first),B.second);
	}
}
int i;
int A[maxn];
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	T=1;
	FOR(_,1,T){
		int i,n,m;
		scanf("%d%d",&n,&m);
		FOR(i,1,n) scanf("%d",&A[i]);
		persist_treap::init();
		FOR(i,1,n) persist_treap::insert(i,A[i]);
		FOR(i,1,m) {
			int op,l,r;
			scanf("%d%d%d",&op,&l,&r);
			if (op==1) {
				int d;
				scanf("%d",&d);
				persist_treap::update(l,r,d);
			} else if (op==2) {
				int x,y;
				scanf("%d%d",&x,&y);
				persist_treap::transto(l,r,x,y);
			} else {
				printf("%lld\n",persist_treap::query(l,r));
			}
		}
	}
	return 0;
}
/*
0
5 100
1 2 3 4 5
3 3 5
3 1 2
3 1 1
3 4 4
3 5 5
2 1 3 3 5
3 3 5
1 2 4 2
3 3 5
2 1 3 3 5
3 1 5
*/