//It is made by ljh2000
//有志者，事竟成，破釜沉舟，百二秦关终属楚；苦心人，天不负，卧薪尝胆，三千越甲可吞吴。
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <string>
#include <queue>
#include <cmath>
#include <ctime>
#include <assert.h>
#define lc root<<1
#define rc root<<1|1
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define reg(i,x) for(int i=first[x];i;i=next[i])
using namespace std;
typedef long long LL;
const int MAXN = 300011;
int ID,n,m,father[MAXN],tag[MAXN],tr[MAXN][2],top,stack[MAXN],cnt;
int sum[MAXN],val[MAXN],S;
//sum表示子树内所有的点的异或和,val表示x加上虚儿子子树的异或和
struct node{ int x,y,z; }e[MAXN];
inline bool isroot(int x){
    return (tr[father[x]][0]!=x) && (tr[father[x]][1]!=x);
}
inline void update(int x){
    sum[x]=sum[tr[x][0]]^sum[tr[x][1]]^val[x];
    }
inline int getint(){
    int w=0,q=0; char c=getchar(); while((c<'0'||c>'9') && c!='-') c=getchar();
    if(c=='-') q=1,c=getchar(); while (c>='0'&&c<='9') w=w*10+c-'0',c=getchar(); return q?-w:w;
}

inline void pushdown(int x){
	if(tag[x]==0) return ;
	int l=tr[x][0],r=tr[x][1];
	tag[l]^=1; tag[r]^=1; swap(tr[x][0],tr[x][1]);
	tag[x]=0;
}

inline void rotate(int x){
	int y=father[x],z=father[y];
	int l,r; l=(tr[y][1]==x); r=l^1;
	if(!isroot(y)) tr[z][(tr[z][1]==y)]=x;
	father[x]=z; father[y]=x;
	tr[y][l]=tr[x][r]; father[tr[x][r]]=y; tr[x][r]=y;
	update(y); update(x);
}

inline void splay(int x){
	top=0; stack[++top]=x;
	for(int i=x;!isroot(i);i=father[i]) stack[++top]=father[i];
	for(int i=top;i>=1;i--) pushdown(stack[i])/*!!!不是top啊!!!*/;
	int y,z;
	while(!isroot(x)) {
		y=father[x]; z=father[y];
		if(!isroot(y)) {
			if((tr[z][0]==y) ^ (tr[y][0]==x)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}

inline void access(int x){
	int last=0;
	while(x){
		splay(x);
		val[x]^=sum[tr[x][1]];//把原来的右儿子加入虚儿子的统计中
		//而对于sum数组即整个子树没有变化，所以无需考虑

		val[x]^=sum[last];//把原来是虚儿子的去掉
		tr[x][1]=last;//!!!
		update(x);//!!!顺序

		last=x; x=father[x];
	}
}

inline void move_to_root(int x){
	access(x);
	splay(x);
	tag[x]^=1;
}

inline void link(int x,int y){
	move_to_root(x);
	move_to_root(y);//!!!必须要把y也变成根，不然修改了y之后修改不到y的祖先，把y变成根节点就可以只修改自己了
	father[x]=y;  val[y]^=sum[x];//加入x的贡献
	update(y);
}

inline void cut(int x,int y){
	move_to_root(x);
	access(y);
	splay(y);assert(tr[y][0]==x);
	tr[y][0]=father[x]=0;
	update(y);//此处update的时候也可以消除x的贡献
}

inline void modify(int x,int vaL){
	access(x); splay(x);
	val[x]^=vaL; sum[x]^=vaL;//只要修改自己就好了
}

inline bool query(int x,int y){
	move_to_root(x); access(y);
	return val[y]==S?1:0;
}

inline void work(){
	srand(time(NULL));
	ID=getint(); n=getint(); m=getint(); int type,x,y;
	for(int i=1;i<n;i++) x=getint(),y=getint(),link(x,y);
	while(m--) {
		type=getint();
		if(type==1) {
			x=getint(); y=getint(); cut(x,y);
			x=getint(); y=getint(); link(x,y);
		}
		else if(type==2) {
			x=getint(); y=getint();
			e[++cnt].x=x;/*!!!*/ e[cnt].y=y; e[cnt].z=(rand()%10000+1)*(rand()%100000+1);
			modify(x,e[cnt].z); modify(y,e[cnt].z); S^=e[cnt].z;
		}
		else if(type==3) {
			x=getint();	S^=e[x].z;
			modify(e[x].x,e[x].z); modify(e[x].y,e[x].z);
		}
		else {
			x=getint(); y=getint();
			if(query(x,y)) puts("YES");
			else puts("NO");
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("207.in","r",stdin);
	freopen("207.out","w",stdout);
#endif
    work();
    return 0;
}
//有志者，事竟成，破釜沉舟，百二秦关终属楚；苦心人，天不负，卧薪尝胆，三千越甲可吞吴。
