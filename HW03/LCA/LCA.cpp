#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 1010;
const int MAXM = 1010;
const int MAXLOG = 11;
int fa[MAXN][MAXLOG], dep[MAXN];
vector<int> G[MAXN];
bool isRoot[MAXN];

void dfs(int u, int father) {
    dep[u] = dep[father] + 1;
    fa[u][0] = father;
    for (int i = 1; (1 << i) <= dep[u]; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v != father)
            dfs(v, u);
    }
}

int LCA(int u, int v) {
    int d = dep[u] - dep[v];
    if (d < 0) {
        swap(u, v);
        d = -d;
    }
    for (int i = 0; (1 << i) <= d; i++)
        if ((1 << i) & d) u = fa[u][i];
    if (u == v) return u;
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        for (int i = 1; i <= N; i++) {
            G[i].clear();
            memset(fa[i], 0, sizeof(fa[i])); // 初始化 fa 数组
        }
        memset(isRoot, true, sizeof(isRoot));
        for (int i = 1; i < N; i++) {
            int a, b;
            cin >> a >> b;
            G[a].push_back(b);
            isRoot[b] = false;
        }
        int root;
        for (int i = 1; i <= N; i++)
            if (isRoot[i]) {
                root = i;
                break;
            }
        dfs(root, 0);
        for (int i = 1; i <= M; i++) {
            int x, y;
            cin >> x >> y;
            cout << LCA(x, y) << endl;
        }
    }
    return 0;
}
