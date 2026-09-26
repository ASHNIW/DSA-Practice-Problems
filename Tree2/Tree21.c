
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *head;
    int *to;
    int *nxt;
    int edge_cnt;
} Graph;

void init_graph(Graph *g, int n) {
    g->head = (int*)malloc((n + 1) * sizeof(int));
    g->to = (int*)malloc(2 * n * sizeof(int));
    g->nxt = (int*)malloc(2 * n * sizeof(int));
    for (int i = 0; i <= n; i++) g->head[i] = -1;
    g->edge_cnt = 0;
}

void add_edge(Graph *g, int u, int v) {
    g->to[g->edge_cnt] = v;
    g->nxt[g->edge_cnt] = g->head[u];
    g->head[u] = g->edge_cnt++;
}

void free_graph(Graph *g) {
    free(g->head);
    free(g->to);
    free(g->nxt);
}

int cmp_u64(const void *a, const void *b) {
    uint64_t x = *(const uint64_t*)a;
    uint64_t y = *(const uint64_t*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static inline uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

uint64_t dfs(int u, int p, Graph *g) {
    uint64_t child_hashes[64];
    uint64_t *arr = child_hashes;
    int cap = 64;
    int cnt = 0;
    
    for (int e = g->head[u]; e != -1; e = g->nxt[e]) {
        int v = g->to[e];
        if (v == p) continue;
        if (cnt >= cap) {
            cap *= 2;
            uint64_t *new_arr = (uint64_t*)malloc(cap * sizeof(uint64_t));
            for (int i = 0; i < cnt; i++) new_arr[i] = arr[i];
            if (arr != child_hashes) free(arr);
            arr = new_arr;
        }
        arr[cnt++] = dfs(v, u, g);
    }
    
    qsort(arr, cnt, sizeof(uint64_t), cmp_u64);
    
    uint64_t h = 14695981039346656037ULL;
    for (int i = 0; i < cnt; i++) {
        h ^= splitmix64(arr[i]);
        h *= 1099511628211ULL;
    }
    h ^= (uint64_t)cnt;
    
    if (arr != child_hashes) free(arr);
    return h;
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        if (scanf("%d", &n) != 1) break;
        Graph g1, g2;
        init_graph(&g1, n);
        init_graph(&g2, n);
        
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            if (scanf("%d %d", &u, &v) == 2) {
                add_edge(&g1, u, v);
                add_edge(&g1, v, u);
            }
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            if (scanf("%d %d", &u, &v) == 2) {
                add_edge(&g2, u, v);
                add_edge(&g2, v, u);
            }
        }
        
        uint64_t h1 = dfs(1, 0, &g1);
        uint64_t h2 = dfs(1, 0, &g2);
        
        if (h1 == h2) printf("YES\n");
        else printf("NO\n");
        
        free_graph(&g1);
        free_graph(&g2);
    }
    return 0;
}
