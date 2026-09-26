
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *head;
    int *to;
    int *nxt;
    int edge_cnt;
} Adj;

void init_adj(Adj *a, int n, int max_edges) {
    a->head = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) a->head[i] = -1;
    a->to = (int*)malloc(max_edges * sizeof(int));
    a->nxt = (int*)malloc(max_edges * sizeof(int));
    a->edge_cnt = 0;
}

void add_dir_edge(Adj *a, int u, int v) {
    a->to[a->edge_cnt] = v;
    a->nxt[a->edge_cnt] = a->head[u];
    a->head[u] = a->edge_cnt++;
}

void free_adj(Adj *a) {
    free(a->head);
    free(a->to);
    free(a->nxt);
}

int n, m;
int *order, order_cnt;
int *visited;

void dfs1(int u, Adj *g) {
    visited[u] = 1;
    for (int e = g->head[u]; e != -1; e = g->nxt[e]) {
        int v = g->to[e];
        if (!visited[v]) dfs1(v, g);
    }
    order[order_cnt++] = u;
}

int *scc;
int scc_cnt;
int *rep;

void dfs2(int u, int c, Adj *rg) {
    scc[u] = c;
    for (int e = rg->head[u]; e != -1; e = rg->nxt[e]) {
        int v = rg->to[e];
        if (scc[v] == 0) dfs2(v, c, rg);
    }
}

int *s_in, *s_out;
int *matched_snk;
int *vis_dag;

int dfs_match(int u, Adj *dag, int *snk_visited) {
    vis_dag[u] = 1;
    if (s_out[u] == 0) {
        if (!snk_visited[u]) {
            snk_visited[u] = 1;
            return u;
        }
    }
    for (int e = dag->head[u]; e != -1; e = dag->nxt[e]) {
        int v = dag->to[e];
        if (!vis_dag[v]) {
            int res = dfs_match(v, dag, snk_visited);
            if (res != 0) return res;
        }
    }
    return 0;
}

int main() {
    if (scanf("%d %d", &n, &m) != 2) return 0;
    Adj g, rg;
    init_adj(&g, n, m + 5);
    init_adj(&rg, n, m + 5);
    
    int orig_m = m;
    while(m--) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            add_dir_edge(&g, u, v);
            add_dir_edge(&rg, v, u);
        }
    }
    
    order = (int*)malloc((n + 1) * sizeof(int));
    order_cnt = 0;
    visited = (int*)calloc(n + 1, sizeof(int));
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs1(i, &g);
    }
    
    scc = (int*)calloc(n + 1, sizeof(int));
    scc_cnt = 0;
    rep = (int*)malloc((n + 1) * sizeof(int));
    
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (scc[u] == 0) {
            scc_cnt++;
            rep[scc_cnt] = u;
            dfs2(u, scc_cnt, &rg);
        }
    }
    
    if (scc_cnt == 1) {
        printf("0\n");
        return 0;
    }
    
    Adj dag;
    init_adj(&dag, scc_cnt, orig_m + 5);
    s_in = (int*)calloc(scc_cnt + 1, sizeof(int));
    s_out = (int*)calloc(scc_cnt + 1, sizeof(int));
    
    for (int u = 1; u <= n; u++) {
        for (int e = g.head[u]; e != -1; e = g.nxt[e]) {
            int v = g.to[e];
            if (scc[u] != scc[v]) {
                add_dir_edge(&dag, scc[u], scc[v]);
                s_out[scc[u]]++;
                s_in[scc[v]]++;
            }
        }
    }
    
    int *sources = (int*)malloc((scc_cnt + 1) * sizeof(int));
    int num_sources = 0;
    int *sinks = (int*)malloc((scc_cnt + 1) * sizeof(int));
    int num_sinks = 0;
    
    for (int i = 1; i <= scc_cnt; i++) {
        if (s_in[i] == 0) sources[num_sources++] = i;
        if (s_out[i] == 0) sinks[num_sinks++] = i;
    }
    
    vis_dag = (int*)malloc((scc_cnt + 1) * sizeof(int));
    int *snk_visited = (int*)calloc(scc_cnt + 1, sizeof(int));
    
    int *pair_src = (int*)malloc((scc_cnt + 1) * sizeof(int));
    int *pair_snk = (int*)malloc((scc_cnt + 1) * sizeof(int));
    int pair_cnt = 0;
    
    for (int i = 0; i < num_sources; i++) {
        for (int j = 1; j <= scc_cnt; j++) vis_dag[j] = 0;
        int target_snk = dfs_match(sources[i], &dag, snk_visited);
        if (target_snk != 0) {
            pair_src[pair_cnt] = sources[i];
            pair_snk[pair_cnt] = target_snk;
            pair_cnt++;
        }
    }
    
    int *unpaired_src = (int*)malloc((num_sources + 1) * sizeof(int));
    int unp_src_cnt = 0;
    int *src_is_paired = (int*)calloc(scc_cnt + 1, sizeof(int));
    for (int i = 0; i < pair_cnt; i++) src_is_paired[pair_src[i]] = 1;
    for (int i = 0; i < num_sources; i++) {
        if (!src_is_paired[sources[i]]) unpaired_src[unp_src_cnt++] = sources[i];
    }
    
    int *unpaired_snk = (int*)malloc((num_sinks + 1) * sizeof(int));
    int unp_snk_cnt = 0;
    for (int i = 0; i < num_sinks; i++) {
        if (!snk_visited[sinks[i]]) unpaired_snk[unp_snk_cnt++] = sinks[i];
    }
    
    int *all_ordered_src = (int*)malloc((num_sources + num_sinks + 5) * sizeof(int));
    int *all_ordered_snk = (int*)malloc((num_sources + num_sinks + 5) * sizeof(int));
    
    for (int i = 0; i < pair_cnt; i++) {
        all_ordered_src[i] = pair_src[i];
        all_ordered_snk[i] = pair_snk[i];
    }
    
    int cur_s = pair_cnt;
    for (int i = 0; i < unp_src_cnt; i++) all_ordered_src[cur_s++] = unpaired_src[i];
    
    int cur_t = pair_cnt;
    for (int i = 0; i < unp_snk_cnt; i++) all_ordered_snk[cur_t++] = unpaired_snk[i];
    
    int total_ans = num_sources > num_sinks ? num_sources : num_sinks;
    printf("%d\n", total_ans);
    
    for (int i = 0; i < total_ans; i++) {
        int u_scc = all_ordered_snk[i % num_sinks];
        int v_scc = all_ordered_src[(i + 1) % num_sources];
        printf("%d %d\n", rep[u_scc], rep[v_scc]);
    }
    
    return 0;
}
