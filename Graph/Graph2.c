#include <stdio.h>
#include <stdlib.h>

#define MAXV 200005

int head[MAXV], to[MAXV * 4], nxt[MAXV * 4], edge_cnt;
int rhead[MAXV], rto[MAXV * 4], rnxt[MAXV * 4], redge_cnt;
int visited[MAXV];
int order[MAXV], order_cnt;
int scc[MAXV], scc_cnt;

void link(int i, int j) {
    to[++edge_cnt] = j;
    nxt[edge_cnt] = head[i];
    head[i] = edge_cnt;
    
    rto[++redge_cnt] = i;
    rnxt[redge_cnt] = rhead[j];
    rhead[j] = redge_cnt;
}

void dfs1(int u) {
    visited[u] = 1;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (!visited[v]) dfs1(v);
    }
    order[++order_cnt] = u;
}

void dfs2(int u, int id) {
    scc[u] = id;
    for (int e = rhead[u]; e; e = rnxt[e]) {
        int v = rto[e];
        if (!scc[v]) dfs2(v, id);
    }
}

int node(int x, int sign) {
    if (sign == 1) return 2 * x;
    else return 2 * x + 1;
}

int neg_node(int u) {
    return u ^ 1;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    for (int i = 0; i < n; i++) {
        char s1, s2;
        int u, v;
        scanf(" %c %d %c %d", &s1, &u, &s2, &v);
        int n1 = node(u, s1 == '+' ? 1 : 0);
        int n2 = node(v, s2 == '+' ? 1 : 0);
        link(neg_node(n1), n2);
        link(neg_node(n2), n1);
    }
    
    for (int i = 2; i <= 2 * m + 1; i++) {
        if (!visited[i]) dfs1(i);
    }
    
    for (int i = order_cnt; i >= 1; i--) {
        int u = order[i];
        if (!scc[u]) {
            dfs2(u, ++scc_cnt);
        }
    }
    
    for (int i = 1; i <= m; i++) {
        if (scc[node(i, 1)] == scc[node(i, 0)]) {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }
    
    for (int i = 1; i <= m; i++) {
        if (scc[node(i, 1)] > scc[node(i, 0)]) {
            printf("+ ");
        } else {
            printf("- ");
        }
    }
    printf("\n");
    return 0;
}
