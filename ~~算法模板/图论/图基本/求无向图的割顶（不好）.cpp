
/*
    ����ǰ�����нڵ��pre��ʼ��Ϊ0
    �ҵ�һ�ε���ʱfaӦΪ����
    ��Ϊѵ��ָ��P314 ȱ���ŵ��ж��Ĵ��룩
    low[u]Ϊu�������������ص���������ȵ�preֵ
*/

int dfs(int u,int fa)//u��DFS���еĸ��ڵ���fa
{
    int lowu=pre[u]=++dfs_clock;
    int child=0;//�ӽڵ���Ŀ
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(!pre[v])//û���ʹ�v
        {
            child++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);//�ú����low��������u��low����
            if(lowv>=pre[u])
                iscut[u]=true;
        }
        else if(pre[v]<pre[u]&&v!=fa)
            lowu=min(lowu,pre[v]);//�÷���߸���u��low����
    }
    if(fa<0&&child==1)iscut[u]=0;
    low[u]=lowu;
    return lowu;
}

