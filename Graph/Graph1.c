#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int u, v;
    int l;
    int *tokens;
} Road;

int parent[MAXN];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

int is_connected(int n, Road *roads, int m, int *banned_token) {
    int i;
    for(i=0;i<MAXN;++i) {
        parent[i] = i;
    }
    int comps = n;
    for (i = 0; i < m; i++) {
        int valid = 1;
        for (int j = 0; j < roads[i].l; j++) {
            if (banned_token[roads[i].tokens[j]]) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            int root_u = find(roads[i].u);
            int root_v = find(roads[i].v);
            if (root_u != root_v) {
                parent[root_u] = root_v;
                comps--;
            }
        }
    }
    return comps == 1;
}

int main() {
    int n, m, k;
    if (scanf("%d %d %d", &n, &m, &k) != 3) return 0;
    
    long long *c = (long long*)malloc((k + 1) * sizeof(long long));
    for (int i = 1; i <= k; i++) {
        if (scanf("%lld", &c[i]) != 1) {
            c[i] = 0;
        }
    }
    
    Road *roads = (Road*)malloc(m * sizeof(Road));
    for (int i = 0; i < m; i++) {
        if (scanf("%d %d %d", &roads[i].u, &roads[i].v, &roads[i].l) != 3) {
            roads[i].u = 0;
            roads[i].v = 0;
            roads[i].l = 0;
        }
        roads[i].tokens = (int*)malloc(roads[i].l * sizeof(int));
        for (int j = 0; j < roads[i].l; j++) {
            if (scanf("%d", &roads[i].tokens[j]) != 1) {
                roads[i].tokens[j] = 0;
            }
        }
    }
    
    int *banned = (int*)calloc(MAXN, sizeof(int));
    if (!is_connected(n, roads, m, banned)) {
        printf("-1\n");
        return 0;
    }
    
    long long total_cost = 0;
    for (int i = k; i >= 1; i--) {
        banned[i] = 1;
        if (!is_connected(n, roads, m, banned)) {
            banned[i] = 0;
            total_cost += c[i];
        }
    }
    
    printf("%lld\n", total_cost);
    return 0;
}
