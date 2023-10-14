void dfs0(int u, int p) {
    L[u] = ++totdfn; Node[totdfn] = u; sz[u] = 1;
    for (int v : g[u]) if (v != p) {
        dfs0(v, u); sz[u] += sz[v];
        if (!big[u] || sz[big[u]] < sz[v]) big[u] = v;
    }
    R[u] = totdfn;
}
void dfs1(int u, int p, bool keep) {
    // 计算轻儿子的答案
    for (int v : g[u]) if (v != p && v != big[u]) dfs1(v, u, false);
    // 计算重儿子答案并保留计算过程中的数据（用于继承）
    if (big[u]) dfs1(big[u], u, true);
    for (int v : g[u]) if (v != p && v != big[u]) {
        // 子树结点的 DFS 序构成一段连续区间，可以直接遍历
        for (int i = L[v]; i <= R[v]; i++) add(Node[i]);
    }
    add(u);
    ans[u] = getAns();
    if (keep == false) for (int i = L[u]; i <= R[u]; i++) del(Node[i]);
}
