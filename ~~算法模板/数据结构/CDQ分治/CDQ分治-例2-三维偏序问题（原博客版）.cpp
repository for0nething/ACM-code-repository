#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>

using namespace std;
const int MAXN = 500001; // 点的数量
const int MAXM = 500001; // 询问数量
const int MAXQ = MAXN+(MAXM<<2);
const int MAXL = 10000002; // 树状数组大小

int n, m, maxy = -1;

namespace IO { // 快读相关
    const int BUFSZ = 1e7;
    char buf[BUFSZ]; int idx, end;
    void init() { idx = BUFSZ; }
    char getch() {
        if( idx == BUFSZ ) {
            end = fread( buf, 1, BUFSZ, stdin ); idx = 0;
        }
        if( idx == end ) return EOF;
        return buf[idx++];
    }
    int getint() {
        int num = 0; char ch;
        while( isspace(ch=getch()) );
        do { num = num*10 + ch-'0'; } while( isdigit(ch=getch()) );
        return num;
    }
}
using IO::getint;

struct Query {
    int type, x, y, w, aid; // w表示对查询结果贡献(+还是-)，aid是“第几个查询”
    bool operator<( const Query &rhs ) const {
        return x == rhs.x ? type < rhs.type : x < rhs.x;
    }
}query[MAXQ];
int qidx = 0;
void addq( int type, int x, int y, int w, int aid ) {
    query[qidx++] = (Query){type,x,y,w,aid};
}

int ans[MAXM], aidx = 0;

namespace BIT { // 树状数组相关
    int arr[MAXL];
    inline int lowbit( int num ) { return num&(-num); }
    void add( int idx, int val ) {
        while( idx <= maxy ) {
            arr[idx] += val;
            idx += lowbit(idx);
        }
    }
    int query( int idx ) {
        int ans = 0;
        while( idx ) {
            ans += arr[idx];
            idx -= lowbit(idx);
        }
        return ans;
    }
    void clear( int idx ){
        while( idx <= maxy ) {
            if( arr[idx] ) arr[idx] = 0; else break;
            idx += lowbit(idx);
        }
    }
}

Query tmp[MAXQ];
void cdq( int L, int R ) {
    if( R-L <= 1 ) return;
    int M = (L+R)>>1; cdq(L,M); cdq(M,R);
    int p = L, q = M, o = L;
    while( p < M && q < R ) {
        if( query[p] < query[q] ) {
            if( query[p].type == 0 ) BIT::add( query[p].y, 1 );
            tmp[o++] = query[p++];
        } else {
            if( query[q].type == 1 ) ans[query[q].aid] += query[q].w * BIT::query( query[q].y );
            tmp[o++] = query[q++];
        }
    }
    while( p < M ) tmp[o++] = query[p++];
    while( q < R ) {
        if( query[q].type == 1 ) ans[query[q].aid] += query[q].w * BIT::query( query[q].y );
        tmp[o++] = query[q++];
    }
    for( int i = L; i < R; ++i ) {
        BIT::clear( tmp[i].y ); // 清空树状数组
        query[i] = tmp[i];
    }
}

int main() {
    IO::init(); n = getint(); m = getint();
    while( n-- ) {
        int x,y; x = getint(); y = getint(); ++x; ++y; // 为了方便，把坐标转化为[1,1e7+1]
        addq(0,x,y,0,0); maxy = max( maxy, y ); // 修改操作无附加信息
    }
    while( m-- ) {
        int x1,y1,x2,y2; x1 = getint(); y1 = getint(); x2 = getint(); y2 = getint(); ++x1; ++y1; ++x2; ++y2;
        addq(1,x1-1,y1-1,1,aidx); addq(1,x1-1,y2,-1,aidx);
        addq(1,x2,y1-1,-1,aidx); addq(1,x2,y2,1,aidx); ++aidx;
        maxy = max( maxy, max(y1,y2) );
    }
    cdq(0,qidx);
    for( int i = 0; i < aidx; ++i ) printf( "%d\n", ans[i] );
    return 0;
}
