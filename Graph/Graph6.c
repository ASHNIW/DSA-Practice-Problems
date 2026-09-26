#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 505
#define MAXM 1005

int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int match[MAXN], rmatch[MAXN];
int dist[MAXN];
int visited[MAXN];

void link(int u, int v) {
    to[++edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

int bfs(int n) {
    int q[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (match[i] == 0) {
            dist[i] = 0;
            q[rear++] = i;
        } else {
            dist[i] = -1;
        }
    }
    int reached_free = 0;
    while (front < rear) {
        int u = q[front++];
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            int next_u = rmatch[v];
            if (next_u == 0) {
                reached_free = 1;
            } else if (dist[next_u] == -1) {
                dist[next_u] = dist[u] + 1;
                q[rear++] = next_u;
            }
        }
    }
    return reached_free;
}

int dfs(int u) {
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        int next_u = rmatch[v];
        if (next_u == 0 || (dist[next_u] == dist[u] + 1 && dfs(next_u))) {
            match[u] = v;
            rmatch[v] = u;
            return 1;
        }
    }
    dist[u] = -1;
    return 0;
}

int main() {
    int n, m, k;
    if (scanf("%d %d %d", &n, &m, &k) != 3) return 0;
    
    for (int i = 0; i < k; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        link(u, v);
    }
    
    int matching = 0;
    while (bfs(n)) {
        for (int i = 1; i <= n; i++) {
            if (match[i] == 0) {
                if (dfs(i)) {
                    matching++;
                }
            }
        }
    }
    
    printf("%d\n", matching);
    for (int i = 1; i <= n; i++) {
        if (match[i] != 0) {
            printf("%d %d\n", i, match[i]);
        }
    }
    
    return 0;
}
