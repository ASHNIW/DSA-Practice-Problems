
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *head;
    int *to;
    int *nxt;
    int edge_cnt;
} Graph;

void init_graph(Graph *g, int n) {
    g->head = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) g->head[i] = -1;
    g->to = (int*)malloc(2 * (n + 5) * sizeof(int));
    g->nxt = (int*)malloc(2 * (n + 5) * sizeof(int));
    g->edge_cnt = 0;
}

void add_edge(Graph *g, int u, int v) {
    g->to[g->edge_cnt] = v;
    g->nxt[g->edge_cnt] = g->head[u];
    g->head[u] = g->edge_cnt++;
}

int timer = 0;
int *tin, *tout;
int *char_list[26];
int char_count[26];
int char_cap[26];
char *s;

void dfs(int u, int p, Graph *g) {
    tin[u] = ++timer;
    int c = s[u - 1] - 'a';
    if (c >= 0 && c < 26) {
        if (char_count[c] >= char_cap[c]) {
            char_cap[c] = char_cap[c] == 0 ? 16 : char_cap[c] * 2;
            char_list[c] = (int*)realloc(char_list[c], char_cap[c] * sizeof(int));
        }
        char_list[c][char_count[c]++] = tin[u];
    }
    for (int e = g->head[u]; e != -1; e = g->nxt[e]) {
        int v = g->to[e];
        if (v != p) {
            dfs(v, u, g);
        }
    }
    tout[u] = timer;
}

int lower_bound(int *arr, int n, int val) {
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (arr[mid] >= val) r = mid;
        else l = mid + 1;
    }
    return l;
}

int upper_bound(int *arr, int n, int val) {
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (arr[mid] > val) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;
    
    s = (char*)malloc((N + 5) * sizeof(char));
    if (scanf("%s", s) != 1) return 0;
    
    Graph g;
    init_graph(&g, N);
    
    int i;
    for(i = 0;i<N-1;i ++) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            add_edge(&g, u, v);
            add_edge(&g, v, u);
        }
    }
    
    tin = (int*)malloc((N + 1) * sizeof(int));
    tout = (int*)malloc((N + 1) * sizeof(int));
    for (int c = 0; c < 26; c++) {
        char_list[c] = NULL;
        char_count[c] = 0;
        char_cap[c] = 0;
    }
    
    dfs(1, 0, &g);
    
    while(Q--) {
        int u;
        char ch[10];
        if (scanf("%d %s", &u, ch) == 2) {
            int c = ch[0] - 'a';
            if (c < 0 || c >= 26) {
                printf("0\n");
            } else {
                int l = lower_bound(char_list[c], char_count[c], tin[u]);
                int r = upper_bound(char_list[c], char_count[c], tout[u]);
                printf("%d\n", r - l);
            }
        }
    }
    
    free(s);
    free(tin);
    free(tout);
    for (int c = 0; c < 26; c++) {
        if (char_list[c]) free(char_list[c]);
    }
    free(g.head);
    free(g.to);
    free(g.nxt);
    return 0;
}
