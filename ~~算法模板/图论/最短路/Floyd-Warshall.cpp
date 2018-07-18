/*
任意两点间的最短路问题
（Floyd-Warshall算法）
在O(V^3)时间里求出所有两点间的最短路长度。
可以处理边是负数的情况，判断图中是否有负圈，只需检查是否存在
d[i][j]是负数的顶点i即可

*/
int d[MAX_V][MAX_V];//d[u][v]表示边e=(u,v)的权值（不存在时设为INF，不过d[i][i]=0
int V;//顶点数
void warshall_floyd()
{
    for(int k=0;k<V;k++)
        for(int i=0;i<V;i++)
            for(int j=0;j<V;j++)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
/*
如果复杂度在可承受的范围内，单源最短路也可用Floyd求解
*/
