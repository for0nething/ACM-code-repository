#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int sum[maxn];
int tot;
const int BUF = 25000000;
char Buf[BUF],*buf=Buf;
inline void read(int &a)
{
    for(a=0;*buf<48;buf++);
    while(*buf>47) a=a*10+*buf++-48;
}
inline int useless(int a,int b,int c)
{
    return 1LL*(sum[c]-sum[b] ) * ( b-a ) <= 1LL*( sum[b]-sum[a] ) * ( c-b );
}

int que[maxn], head, tail;
int main()
{
    tot = fread(Buf,1,BUF,stdin);
    int n,k;
    while(1)
    {
        if(buf-Buf+1>=tot)break;
        read(n),read(k);
        for(int i = 1; i <= n; i++){
            read(sum[i]);
            sum[i] += sum[i-1];
        }
         head = 1, tail = 0;
        double ans = 0;
        for(int i = k; i <= n; i++)
        {
            while( head < tail && useless( que[tail-1], que[tail], i-k) ) --tail;

            que[++tail] = i - k;

            while( head < tail && useless( que[head+1], que[head], i) ) ++head;

            ans = max( ans, ( sum[i]-sum[que[head]] ) * 1.0 / (i-que[head]) );
        }
        printf("%.2f\n", ans);
      }
      return 0;
}
