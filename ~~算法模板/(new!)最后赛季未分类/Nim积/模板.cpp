/*
在一个二维平面中，有 n 个灯亮着并告诉你坐标，每回合需要找到一个矩形，
这个矩形 (x,y) 坐标最大的那个角落的点必须是亮着的灯，然后我们把四个角落的灯状态反转，不能操作为败。

Turning Corners 是裸的二维 Nim 问题，直接上模板就好了。

复杂度是 O(Tnlogxlogy) 的。
*/

#define Resolve(i, x) for (int u = (x), i = 0; (1ll << i) <= u; ++ i) if (u >> i & 1)

ll f(ll x, ll y);

ll g(int x, int y) {
    if (!x || !y) return 1ll << (x | y);
    if (~ tab[x][y]) return tab[x][y];
    ll res = 1;
    Resolve(i, x ^ y) res <<= (1 << i);
    Resolve(i, x & y) res = f(res, 3ll << ((1 << i) - 1));
    return tab[x][y] = res;
}

ll f(ll x, ll y) {
    if (!x || !y) return x | y;
    if (x == 1 || y == 1) return max(x, y);
    ll res = 0;
    Resolve(i, x) Resolve(j, y) res ^= g(i, j);
    return res;
}
