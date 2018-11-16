#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <climits>
#include <cmath>
#include <ctime>
#include <cassert>
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;
typedef long long ll;

int T;
int a[10], b[10];
ll C[20][20];

void init()
{
    C[0][0] = 1;
    for(int i = 1; i < 15; ++i) {
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; ++j) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
}

ll work(int k)
{ //每k条边必须相同，分成12/k组(以对边中点为轴旋转180°是分成5组)
    memcpy (b, a, sizeof(a));
    int sum = 0;
    for (int i = 1; i <= 6; ++i) {
        if(b[i] % k) return 0;
        b[i] /= k;
        sum += b[i];
    }
    ll res = 1;
    for (int i = 1; i <= 6; ++i) {
        res *= C[sum][b[i]];
        sum -= b[i];
    }
    return res;
}

ll solve()
{
    ll res = 0;
    //静止
    res += work(1);
    //以相对面中心为轴
    res += (ll)3 * 2 * work(4); //旋转90°和270°
    res += (ll)3 * work(2); //旋转180°
    // 以对顶点为轴,可以旋转120°或240°
    res += (ll)4 * 2 * work(3);
    // 以对边种点为轴，只能旋转180°
    for(int i = 1; i <= 6; ++i) {
        for(int j = 1; j <= 6; ++j) {
            if(a[i] == 0 || a[j] == 0) continue;
            a[i]--; a[j]--;  //将a[i]和a[j]设为选择的两条对边的颜色
            res += (ll)6 * work(2); //剩下的是5个循环长度为2的循环，6代表对边选择情况
            a[i]++; a[j]++;
        }
    }
    return res;
}

int main()
{
    init();
    scanf("%d", &T);
    while (T--) {
        memset (a, 0, sizeof(a));
        for (int i = 0; i < 12; ++i) {
            int tmp;
            scanf ("%d", &tmp);
            a[tmp]++;
        }
        printf("%lld\n", solve() / 24); // 最后还要除以总的置换数:24
    }
    return 0;
}
