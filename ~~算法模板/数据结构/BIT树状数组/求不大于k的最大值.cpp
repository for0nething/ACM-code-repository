const int MAX=1000000;
inline int lowbit(int x){return x&-x;}
inline void insert(int x){
    for (;x<=MAX;x+=lowbit(x)) a[x]++;
}
inline int find(int x){
    while (x&&!a[x]) x^=lowbit(x);
    if (!x) return 0;
    int t=lowbit(x)>>1,y=a[x];
    while (t){
        if (y-a[x-t]) y-=a[x-t];
        else{y=a[x-t];x=x-t;}
        t>>=1;
    }
    return x;
}
