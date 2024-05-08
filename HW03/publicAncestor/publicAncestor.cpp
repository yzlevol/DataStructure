#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 1005;
const int maxlog = 20;

int fa[maxn][maxlog], dep[maxn], G[maxn][maxn], hasParent[maxn];

void dfs(int u, int father) {
    fa[u][0] = father;
    dep[u] = dep[father] + 1;
    for (int i = 1; (1 << i) <= dep[u]; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = 1; i <= G[u][0]; i++) {
        int v = G[u][i];
        if (v == father)
            continue;
        dfs(v, u);
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = maxlog - 1; i >= 0; i--)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = maxlog - 1; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;

        memset(G, 0, sizeof(G));
        memset(fa, 0, sizeof(fa));
        memset(dep, 0, sizeof(dep));
        memset(hasParent, 0, sizeof(hasParent));

        int root = 1;
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            G[u][++G[u][0]] = v;
            G[v][++G[v][0]] = u;
            hasParent[v] = true;
        }
        for (int i = 1; i <= n; i++) {
            if (!hasParent[i]) {
                root = i;
                break;
            }
        }
        dfs(root, 0);
        while (m--) {
            int u, v;
            cin >> u >> v;
            cout << LCA(u, v) << endl;
        }
    }
    return 0;
}