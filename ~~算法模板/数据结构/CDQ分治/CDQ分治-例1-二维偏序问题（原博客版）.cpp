#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;
typedef long long ll;
const int MAXN = 500001; // ԭ�����С
const int MAXM = 500001; // ��������
const int MAXQ = (MAXM<<1)+MAXN;

int n,m;

struct Query {
    int type, idx; ll val;
    bool operator<( const Query &rhs ) const { // ����λ�ô�С���������޸������ڲ�ѯ
        return idx == rhs.idx ? type < rhs.type : idx < rhs.idx;
    }
}query[MAXQ];
int qidx = 0;

ll ans[MAXQ]; int aidx = 0; // ������

Query tmp[MAXQ]; // �鲢����ʱ����
void cdq( int L, int R ) {
    if( R-L <= 1 ) return;
    int M = (L+R)>>1; cdq(L,M); cdq(M,R);
    ll sum = 0;
    int p = L, q = M, o = 0;
    while( p < M && q < R ) {
        if( query[p] < query[q] ) { // ֻͳ����������ڵ��޸�ֵ
            if( query[p].type == 1 ) sum += query[p].val;
            tmp[o++] = query[p++];
        }
        else { // ֻ�޸��ұ������ڵĲ�ѯ���
            if( query[q].type == 2 ) ans[query[q].val] -= sum;
            else if( query[q].type == 3 ) ans[query[q].val] += sum;
            tmp[o++] = query[q++];
        }
    }
    while( p < M ) tmp[o++] = query[p++];
    while( q < R ) {
        if( query[q].type == 2 ) ans[query[q].val] -= sum;
        else if( query[q].type == 3 ) ans[query[q].val] += sum;
        tmp[o++] = query[q++];
    }
    for( int i = 0; i < o; ++i ) query[i+L] = tmp[i];
}

int main() {
    scanf( "%d%d", &n, &m );
    for( int i = 1; i <= n; ++i ) { // �ѳ�ʼԪ�ر�Ϊ�޸Ĳ���
        query[qidx].idx = i; query[qidx].type = 1;
        scanf( "%lld", &query[qidx].val ); ++qidx;
    }
    for( int i = 0; i < m; ++i ) {
        int type; scanf( "%d", &type );
        query[qidx].type = type;
        if( type == 1 ) scanf( "%d%lld", &query[qidx].idx, &query[qidx].val );
        else { // �Ѳ�ѯ������Ϊ������
            int l,r; scanf( "%d%d", &l, &r );
            query[qidx].idx = l-1; query[qidx].val = aidx; ++qidx;
            query[qidx].type = 3; query[qidx].idx = r; query[qidx].val = aidx; ++aidx;
        }
        ++qidx;
    }
    cdq(0,qidx);
    for( int i = 0; i < aidx; ++i ) printf( "%lld\n", ans[i] );
    return 0;
}
