
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <map>
//#pragma comment(linker, "/STACK:102400000,102400000")
using namespace std;
typedef long long LL;
const int inf=0x3f3f3f3f;
const double pi= acos(-1.0);
const double esp=1e-6;
LL gcd(LL a,LL b) {
    while(b!=0) {
        LL r=b;
        b=a%b;
        a=r;
    }
    return a;
}
LL modxp(LL a,LL b) {
    LL res=1;
    while(b!=0) {
        if(b&1) res*=a;
        a=a*a;
        b>>=1;
    }
    return res;
}
int main() {
    LL n,i;
    LL ans;
    while(~scanf("%lld",&n)) {
        if(n==-1) break;
        if(!n){
            puts("0");
            continue;
        }//不要掉了这种情况
        ans=0;
        for(i=1; i<=n; i++)
            ans+=modxp(3,gcd(n,i));
        if(n&1) {
            ans+=modxp(3,n/2+1)*n;
        } else {
            ans+=modxp(3,n/2+1)*(n/2);
            ans+=modxp(3,n/2)*(n/2);
        }
        printf("%lld\n",ans/(n*2));
    }
    return 0;
}
