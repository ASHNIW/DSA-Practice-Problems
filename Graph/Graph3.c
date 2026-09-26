#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 505
#define MAXM 2005

int head[MAXN], to[MAXM * 2], cap[MAXM * 2], flow[MAXM * 2], nxt[MAXM * 2], edge_cnt;
int parent_edge[MAXN];
int parent_node[MAXN];

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    cap[edge_cnt] = 1;
    flow[edge_cnt] = 0;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt++;
    
    to[edge_cnt] = u;
    cap[edge_cnt] = 0;
    flow[edge_cnt] = 0;
    nxt[edge_cnt] = head[v];
    head[v] = edge_cnt++;
}

int bfs(int n, int s, int t) {
    int q[MAXN], front = 0, rear = 0;
    int visited[MAXN];
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

int path_nodes[MAXN];

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    memset(head, -1, sizeof(head));
    edge_cnt = 0;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    
    int k = max_flow(n, 1, n);
    printf("%d\n", k);
    
    for (int i = 0; i < k; i++) {
        int curr = 1;
        int path_len = 0;
        path_nodes[path_len++] = curr;
        
        while (curr != n) {
            for (int e = head[curr]; e != -1; e = nxt[e]) {
                if (flow[e] > 0) {
                    flow[e] = 0;
                    curr = to[e];
                    path_nodes[path_len++] = curr;
                    break;
                }
            }
        }
        
        printf("%d\n", path_len);
        for (int j = 0; j < path_len; j++) {
            printf("%d%c", path_nodes[j], j == path_len - 1 ? '\n' : ' ');
        }
    }
    
    return 0;
}
