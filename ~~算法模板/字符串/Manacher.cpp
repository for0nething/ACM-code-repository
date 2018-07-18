/*
Manacher 最长回文子串
O(len)

*/
char now[2*MAX+5];//至少是初始串长度的2倍
int rl[2*MAX+5];//对于下标i 表示以i为中心的最长回文串半径
int MAXRIGHT,pos;//当前涉及到的回文串中达到最右的位置的下一个位置，及其中心
int Manacher(char *s)//下标从0开始
{
    MAXRIGHT=pos=0;
    int MAXLEN=0;//最长回文串长度
    int len=strlen(s);
    for(int i=0;i<len;i++)
        now[2*i]='#',now[2*i+1]=s[i];// 任意选定串中不出现的字符
    now[len=2*len]='#';
    for(int i=0;i<=len;i++)
    {
        /*
        i的位置必定在pos右侧 只需分情况讨论与MAXRIGHT的位置关系
        */
        if(i<MAXRIGHT)
            rl[i]=min(rl[2*pos-i],MAXRIGHT-i);
        else
            rl[i]=1;
        while(i-rl[i]>=0&&i+rl[i]<=len&&now[i-rl[i]]==now[i+rl[i]])
            ++rl[i];
        if(i+rl[i]>MAXRIGHT)
            MAXRIGHT=i+rl[i],pos=i;
        MAXLEN=max(MAXLEN,rl[i]);
    }
    return MAXLEN-1;
}
