vector <int> G[N];

int seq[N], tin[N], fa[N], dep[N], top[N], son[N], sz[N], label;

void dfs1(int u, int father) {
    fa[u] = father;
    son[u] = 0; sz[u] = 1;
    for(auto v : G[u]) {
        if(v == father) continue;
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int anc) {
    top[u] = anc; tin[u] = ++ label;
    seq[label] = u;
    if(son[u]) dfs2(son[u], anc);
    for(auto v : G[u]) {
        if(v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}

inline int lca(int u, int v) {
    while(top[u] ^ top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
