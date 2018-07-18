/*
路径还原



*/

//求从s出发到各个顶点的最短距离
int prev[MAX_V];
void dijkstra(int s)
{
    fill(d,d+V,INF);
    fill(used,used+V,false);
    fill(prev,prev+V,-1);
    d[s]=0;
    while(true)
    {
        int v=-1;
        for(int u=0;u<V;u++)
        {
            if(!used[u]&&(v==-1||d[u]<d[v]))
                v=u;
        }
        if(v==-1)
            break;
        for(int u=0;u<V;u++)
        {
            if(d[u]>d[v]+cost[v][u])
            {
                d[u]=d[v]+cost[v][u];
                prev[u]=v;
            }
        }
    }
}


//到顶点t的最短路
vector <int> get_path(int t)
{
    vector <int> path;
    for(;t!=-1;t=prev[t])
        path.push_back(t);
    reverse(path.begin(),path.end());
    return path;
}
