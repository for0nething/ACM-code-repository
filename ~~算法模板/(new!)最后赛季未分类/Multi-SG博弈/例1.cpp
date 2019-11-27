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


/*题意
给出n堆石子, 每次可以选择将大于某个数f一堆平均分成多个堆, 最后不能操作的失败。
*/
/*做法
考虑每堆是单独的子游戏，互不影响，所以我只要对每堆做完，然后把每堆的SG给XOR起来就可以了。
而每堆的结果也只跟堆的石子数量有关，那么我就可以对于每种石子数量做好了。
而对于一种特定的石子数量的SG，我肯定是把他所有的后继状态的SG给XOR起来，那么枚举一下分成了多少堆，就可以直接算了。复杂度是O(石子数^2)。
进一步观察，发现若干个数的分出来的较小的那个块是相同的，而且这一段最多最多也只能贡献2种不同的SG值，所以就可以每块丢到一起做，算算2种不同的SG值，就可以了。
数论分块 O(n^3/2)
*/
const int MAXN = 100011;
int n,F,SG[MAXN],ans,Tim,vis[MAXN];

inline int getint(){
    int w=0,q=0; char c=getchar(); while((c<'0'||c>'9') && c!='-') c=getchar();
    if(c=='-') q=1,c=getchar(); while (c>='0'&&c<='9') w=w*10+c-'0',c=getchar(); return q?-w:w;
}

inline int calc(int x){
    Tim++; int xiao,num,num2,now,nex;
    for(int i=2;i<=x;i=nex+1) {//枚举分成的堆的数目
        xiao=x/i;//数量较小的堆有多少个石子

        num2=x%i;//注意计算方法
        num=i-num2;
        now=0;
        //只与i奇偶性有关，那么只可能贡献两种SG值
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
        if(T!=0) printf("%d ",ans==0?0:1);//不能直接输出SG值啊...
        else printf("%d",ans==0?0:1);
    }
}

int main()
{
    work();
    return 0;
}
