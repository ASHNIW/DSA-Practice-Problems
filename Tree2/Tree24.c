
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w;
} Edge;

int cmp_edge(const void *a, const void *b) {
    Edge *e1 = (Edge*)a;
    Edge *e2 = (Edge*)b;
    return e2->w - e1->w;
}

int find_set(int *parent, int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find_set(parent, parent[i]);
}

void union_sets(int *parent, int *rank, int i, int j) {
    int root_i = find_set(parent, i);
    int root_j = find_set(parent, j);
    if (root_i != root_j) {
        if (rank[root_i] < rank[root_j]) {
            parent[root_i] = root_j;
        } else if (rank[root_i] > rank[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank[root_i]++;
        }
    }
}

int printheap(int N) {
    return N;
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n, m;
        if (scanf("%d %d", &n, &m) != 2) break;
        Edge *edges = (Edge*)malloc(m * sizeof(Edge));
        for (int i = 0; i < m; i++) {
            if (scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w) != 3) {
                edges[i].u = edges[i].v = edges[i].w = 0;
            }
        }
        
        qsort(edges, m, sizeof(Edge), cmp_edge);
        
        int *parent = (int*)malloc((n + 1) * sizeof(int));
        int *rank = (int*)calloc(n + 1, sizeof(int));
        for (int i = 1; i <= n; i++) parent[i] = i;
        
        long long total_weight = 0;
        int edges_count = 0;
        
        for (int i = 0; i < m && edges_count < n - 1; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            if (find_set(parent, u) != find_set(parent, v)) {
                union_sets(parent, rank, u, v);
                total_weight += edges[i].w;
                edges_count++;
            }
        }
        
        printf("%lld\n", total_weight);
        
        free(edges);
        free(parent);
        free(rank);
    }
    return 0;
}
