#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;
int matched[MAXN];
int ans = 0;

void link(int i, int j) {
    to[++edge_cnt] = j;
    nxt[edge_cnt] = head[i];
    head[i] = edge_cnt;
}

void dfs(int p, int i) {
    for (int e = head[i]; e; e = nxt[e]) {
        int v = to[e];
        if (v != p) {
            dfs(i, v);
        }
    }
    if (p != 0 && !matched[i] && !matched[p]) {
        matched[i] = 1;
        matched[p] = 1;
        ans++;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        link(u, v);
        link(v, u);
    }
    dfs(0, 1);
    printf("%d\n", ans);
    return 0;
}
