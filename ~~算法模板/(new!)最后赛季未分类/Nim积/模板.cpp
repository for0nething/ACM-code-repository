/*
��һ����άƽ���У��� n �������Ų����������꣬ÿ�غ���Ҫ�ҵ�һ�����Σ�
������� (x,y) ���������Ǹ�����ĵ���������ŵĵƣ�Ȼ�����ǰ��ĸ�����ĵ�״̬��ת�����ܲ���Ϊ�ܡ�

Turning Corners ����Ķ�ά Nim ���⣬ֱ����ģ��ͺ��ˡ�

���Ӷ��� O(Tnlogxlogy) �ġ�
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
