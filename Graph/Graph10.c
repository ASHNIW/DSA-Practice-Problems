#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 505
#define MAXM 1005

int head[MAXN], to[MAXM * 4], cap[MAXM * 4], flow[MAXM * 4], nxt[MAXM * 4], edge_cnt;
int orig_u[MAXM], orig_v[MAXM];
int parent_edge[MAXN], parent_node[MAXN];
int visited[MAXN];

void link(int i, int h) {
    to[edge_cnt] = h;
    cap[edge_cnt] = 1;
    flow[edge_cnt] = 0;
    nxt[edge_cnt] = head[i];
    head[i] = edge_cnt++;
    
    to[edge_cnt] = i;
    cap[edge_cnt] = 1;
    flow[edge_cnt] = 0;
    nxt[edge_cnt] = head[h];
    head[h] = edge_cnt++;
}

int bfs(int n, int s, int t) {
    int q[MAXN], front = 0, rear = 0;
    memset(visited, 0, sizeof(visited));
    memset(parent_edge, -1, sizeof(parent_edge));
    
    q[rear++] = s;
    visited[s] = 1;
    
    while (front < rear) {
        int u = q[front++];
        if (u == t) return 1;
        
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (!visited[v] && cap[e] - flow[e] > 0) {
                visited[v] = 1;
                parent_edge[v] = e;
                parent_node[v] = u;
                q[rear++] = v;
            }
        }
    }
    return 0;
}

int max_flow(int n, int s, int t) {
    int total_flow = 0;
    while (bfs(n, s, t)) {
        for (int v = t; v != s; v = parent_node[v]) {
            int e = parent_edge[v];
            flow[e] += 1;
            flow[e ^ 1] -= 1;
        }
        total_flow++;
    }
    return total_flow;
}

void mark_reachable(int s) {
    int q[MAXN], front = 0, rear = 0;
    memset(visited, 0, sizeof(visited));
    
    q[rear++] = s;
    visited[s] = 1;
    
    while (front < rear) {
        int u = q[front++];
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (!visited[v] && cap[e] - flow[e] > 0) {
                visited[v] = 1;
                q[rear++] = v;
            }
        }
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    memset(head, -1, sizeof(head));
    edge_cnt = 0;
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &orig_u[i], &orig_v[i]);
        link(orig_u[i], orig_v[i]);
    }
    
    int k = max_flow(n, 1, n);
    printf("%d\n", k);
    
    mark_reachable(1);
    
    for (int i = 0; i < m; i++) {
        int u = orig_u[i];
        int v = orig_v[i];
        if ((visited[u] && !visited[v]) || (visited[v] && !visited[u])) {
            printf("%d %d\n", u, v);
        }
    }
    
    return 0;
}
