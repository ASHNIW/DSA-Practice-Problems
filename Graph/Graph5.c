#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005

typedef struct Edge {
    int to;
    int weight;
    int id;
    int in_cycle;
    struct Edge *nxt;
    struct Edge *rev;
} Edge;

Edge *head[MAXN];
int visited[MAXN];
int path_nodes[MAXN];
Edge *path_edges[MAXN];
int path_len = 0;
int target_node = 0;
int found = 0;

void add_edge_graph(int u, int v, int w, int id) {
    Edge *e1 = (Edge*)malloc(sizeof(Edge));
    Edge *e2 = (Edge*)malloc(sizeof(Edge));
    
    e1->to = v;
    e1->weight = w;
    e1->id = id;
    e1->in_cycle = 0;
    e1->nxt = head[u];
    e1->rev = e2;
    head[u] = e1;
    
    e2->to = u;
    e2->weight = w;
    e2->id = id;
    e2->in_cycle = 0;
    e2->nxt = head[v];
    e2->rev = e1;
    head[v] = e2;
}

int dfsi(int np, int lst) {
    visited[np] = 1;
    if (np == target_node) {
        found = 1;
        return 1;
    }
    for (Edge *e = head[np]; e; e = e->nxt) {
        int v = e->to;
        if (v != lst && !visited[v]) {
            path_edges[path_len] = e;
            path_nodes[path_len] = v;
            path_len++;
            if (dfsi(v, np)) return 1;
            path_len--;
        }
    }
    return 0;
}

int parent_dsu[MAXN];
int find_dsu(int i) {
    if (parent_dsu[i] == i) return i;
    return parent_dsu[i] = find_dsu(parent_dsu[i]);
}

int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    
    for (int i = 1; i <= n; i++) {
        parent_dsu[i] = i;
        head[i] = NULL;
    }
    
    int edge_id_counter = 0;
    
    for (int k = 0; k < q; k++) {
        int u, v, x;
        if (scanf("%d %d %d", &u, &v, &x) != 3) break;
        
        int ru = find_dsu(u);
        int rv = find_dsu(v);
        
        if (ru != rv) {
            parent_dsu[ru] = rv;
            add_edge_graph(u, v, x, ++edge_id_counter);
            printf("YES\n");
        } else {
            path_len = 0;
            target_node = v;
            found = 0;
            for (int i = 1; i <= n; i++) visited[i] = 0;
            
            path_nodes[0] = u;
            dfsi(u, 0);
            
            int has_cycle_edge = 0;
            int xor_sum = 0;
            for (int i = 0; i < path_len; i++) {
                if (path_edges[i]->in_cycle) {
                    has_cycle_edge = 1;
                    break;
                }
                xor_sum ^= path_edges[i]->weight;
            }
            
            if (!has_cycle_edge && (xor_sum ^ x) == 1) {
                for (int i = 0; i < path_len; i++) {
                    path_edges[i]->in_cycle = 1;
                    path_edges[i]->rev->in_cycle = 1;
                }
                Edge *new_e1 = (Edge*)malloc(sizeof(Edge));
                Edge *new_e2 = (Edge*)malloc(sizeof(Edge));
                new_e1->to = v;
                new_e1->weight = x;
                new_e1->id = ++edge_id_counter;
                new_e1->in_cycle = 1;
                new_e1->nxt = head[u];
                new_e1->rev = new_e2;
                head[u] = new_e1;
                
                new_e2->to = u;
                new_e2->weight = x;
                new_e2->id = edge_id_counter;
                new_e2->in_cycle = 1;
                new_e2->nxt = head[v];
                new_e2->rev = new_e1;
                head[v] = new_e2;
                
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    
    return 0;
}
