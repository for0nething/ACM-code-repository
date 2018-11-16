

char pbuf[15000000] , *pp = pbuf;
inline void write(ll x)
{
    static int sta[12];
    int top = 0;
    if(!x) *pp ++ = '0';
    while(x) sta[top ++ ] = x % 10 , x /= 10;
    while(top -- ) *pp ++ = sta[top] ^ '0';
    *pp ++ = ' ';
}

int main(){
    /*
        e.g. 输出数组中元素
    */
    for(int i=0;i<lim;i++)
        write(a[i]);
    fwrite(pbuf , 1 , pp - pbuf , stdout);
    return 0;
}

/*
1
30
3
6
##.#..
7
.#.#.#.
5
##.##
*/
