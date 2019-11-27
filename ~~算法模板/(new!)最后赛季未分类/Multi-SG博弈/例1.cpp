//It is made by ljh2000
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <complex>
using namespace std;
typedef long long LL;
typedef long double LB;
typedef complex<double> C;
const double pi = acos(-1);


/*����
����n��ʯ��, ÿ�ο���ѡ�񽫴���ĳ����fһ��ƽ���ֳɶ����, ����ܲ�����ʧ�ܡ�
*/
/*����
����ÿ���ǵ���������Ϸ������Ӱ�죬������ֻҪ��ÿ�����꣬Ȼ���ÿ�ѵ�SG��XOR�����Ϳ����ˡ�
��ÿ�ѵĽ��Ҳֻ���ѵ�ʯ�������йأ���ô�ҾͿ��Զ���ÿ��ʯ�����������ˡ�
������һ���ض���ʯ��������SG���ҿ϶��ǰ������еĺ��״̬��SG��XOR��������ôö��һ�·ֳ��˶��ٶѣ��Ϳ���ֱ�����ˡ����Ӷ���O(ʯ����^2)��
��һ���۲죬�������ɸ����ķֳ����Ľ�С���Ǹ�������ͬ�ģ�������һ��������Ҳֻ�ܹ���2�ֲ�ͬ��SGֵ�����ԾͿ���ÿ�鶪��һ����������2�ֲ�ͬ��SGֵ���Ϳ����ˡ�
���۷ֿ� O(n^3/2)
*/
const int MAXN = 100011;
int n,F,SG[MAXN],ans,Tim,vis[MAXN];

inline int getint(){
    int w=0,q=0; char c=getchar(); while((c<'0'||c>'9') && c!='-') c=getchar();
    if(c=='-') q=1,c=getchar(); while (c>='0'&&c<='9') w=w*10+c-'0',c=getchar(); return q?-w:w;
}

inline int calc(int x){
    Tim++; int xiao,num,num2,now,nex;
    for(int i=2;i<=x;i=nex+1) {//ö�ٷֳɵĶѵ���Ŀ
        xiao=x/i;//������С�Ķ��ж��ٸ�ʯ��

        num2=x%i;//ע����㷽��
        num=i-num2;
        now=0;
        //ֻ��i��ż���йأ���ôֻ���ܹ�������SGֵ
        if(num&1) now^=SG[xiao];
        if(num2&1) now^=SG[xiao+1];
        vis[now]=Tim;

        nex=min(x/xiao,x);
        if(i+1<=nex) {
            now=0;
            num2=x%(i+1);
            num=(i+1)-num2;
            if(num&1) now^=SG[xiao];
            if(num2&1) now^=SG[xiao+1];
            vis[now]=Tim;
        }
    }
    int mex=0;
    for(;vis[mex]==Tim;mex++) ;
    return mex;
}

inline void init(){
    for(int i=0;i<F;i++) SG[i]=0;

    for(int i=F;i<=100000;i++)
        SG[i]=calc(i);
}

inline void work(){
    int T=getint(); F=getint(); int x;
    init();
    while(T--) {
        ans=0; n=getint();
        for(int i=1;i<=n;i++) x=getint(),ans^=SG[x];
        if(T!=0) printf("%d ",ans==0?0:1);//����ֱ�����SGֵ��...
        else printf("%d",ans==0?0:1);
    }
}

int main()
{
    work();
    return 0;
}
