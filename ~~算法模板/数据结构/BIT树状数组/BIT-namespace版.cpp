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
