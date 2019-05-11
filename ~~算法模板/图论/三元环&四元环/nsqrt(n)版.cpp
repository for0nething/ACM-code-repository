
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int bas = 1e5+1;
const int maxn = 1e5+5;
vector<int> G[maxn];
int n, m;
//unordered_set<LL> _hash;
set<LL> _hash;
int deg[maxn], vis[maxn];
int bel[maxn];
void init()
{
	for(int i = 1; i <= n; ++i)
	{
		deg[i] = bel[i] = vis[i] = 0;
		G[i].clear();
	}
}
void work()
{
	int x = sqrt(1.0*m);
	LL ans = 0;
	for(int a = 1; a <= n; ++a)
	{
		vis[a] = 1;
		//ɨһ����a���������е㣬Ϊ�����ṩO(1)�������Ƿ��������
		for(int i = 0; i < G[a].size(); ++i)
		bel[G[a][i]] = a;
		for(int i = 0; i < G[a].size(); ++i)
		{
			int b = G[a][i];
			if(vis[b]) continue;
			if(deg[b] <= x)
			{
				//���b����<=sqrt(m)����ö��b�����б�
				for(int j = 0; j < G[b].size(); ++j)
				{
					int c = G[b][j];
					if(bel[c] == a) ++ans;
				}
			}
			else
			{
				//���b����>sqrt(m)����ö��a�����б�
				for(int j = 0; j < G[a].size(); ++j)
				{
					int c = G[a][j];
					if(_hash.find(1ll*b*bas+c) != _hash.end())
					++ans;
				}
			}
		}
	}
	//ͳ�ƺ�ÿ����Ԫ����ÿ���߶��ᱻͳ��һ�Σ�����Ӧ��/3
	printf("%lld\n", ans/3);
}
int main()
{
	int t, u, v;
	while(~scanf("%d %d", &n, &m))
	{
		init(); _hash.clear();
		for(int i = 1; i <= m; ++i)
		{
			scanf("%d %d", &u, &v);
			++deg[u], ++deg[v];
			G[u].push_back(v);
			G[v].push_back(u);
			_hash.insert(1ll*u*bas+v);
			_hash.insert(1ll*v*bas+u);
		}
		work();
	}
	return 0;
}
