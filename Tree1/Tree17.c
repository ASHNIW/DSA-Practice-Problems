#include <stdio.h>
#include <stdlib.h>

#define MAXL 200005
#define HASHSIZE (1 << 21)
#define HASHMASK (HASHSIZE - 1)

int deg[MAXL];
int head[MAXL], to[2 * MAXL], nxt[2 * MAXL], ecnt;
long long keys[HASHSIZE];
int vals[HASHSIZE];
int stack_node[MAXL];
int stack_parent[MAXL];
int stack_edge[MAXL];
int path[MAXL];

void add_edge(int a, int b) {
    to[ecnt] = b;
    nxt[ecnt] = head[a];
    head[a] = ecnt++;
}

int get_child(int parent, int d) {
    long long key = (long long)parent * 1000003LL + d;
    int h = (unsigned)key & HASHMASK;
    while (keys[h] != 0 && keys[h] != key) h = (h + 1) & HASHMASK;
    if (keys[h] == 0) return -1;
    return vals[h];
}

void set_child(int parent, int d, int child) {
    long long key = (long long)parent * 1000003LL + d;
    int h = (unsigned)key & HASHMASK;
    while (keys[h] != 0 && keys[h] != key) h = (h + 1) & HASHMASK;
    keys[h] = key;
    vals[h] = child;
}

int main() {
    int n, i;
    if (scanf("%d", &n) != 1) return 0;
    for (i = 0; i < HASHSIZE; i++) keys[i] = 0;
    ecnt = 0;
    for (i = 1; i <= n; i++) head[i] = -1;
    for (i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (i = 1; i <= n; i++) {
        int c = 0;
        for (int e = head[i]; e != -1; e = nxt[e]) c++;
        deg[i] = c;
    }

    long long ans = 0;
    int sp = 0;
    int path_top = 0;
    stack_node[sp] = 1;
    stack_parent[sp] = 0;
    stack_edge[sp] = head[1];
    path[path_top++] = deg[1];
    sp++;
    int node = 0;
    for (i = path_top - 1; i >= 0; i--) {
        int nx = get_child(node, path[i]);
        if (nx == -1) {
            nx = (int)(ans + 1);
            ans++;
            set_child(node, path[i], nx);
        }
        node = nx;
    }

    while (sp > 0) {
        int u = stack_node[sp - 1];
        int par = stack_parent[sp - 1];
        int e = stack_edge[sp - 1];
        if (e == -1) {
            sp--;
            path_top--;
            continue;
        }
        stack_edge[sp - 1] = nxt[e];
        int v = to[e];
        if (v == par) continue;
        path[path_top++] = deg[v];
        node = 0;
        for (i = path_top - 1; i >= 0; i--) {
            int nx = get_child(node, path[i]);
            if (nx == -1) {
                nx = (int)(ans + 1);
                ans++;
                set_child(node, path[i], nx);
            }
            node = nx;
        }
        stack_node[sp] = v;
        stack_parent[sp] = u;
        stack_edge[sp] = head[v];
        sp++;
    }

    printf("%lld\n", ans);
    return 0;
}