#include <stdio.h>

#define MAXN 100005

int par1[MAXN];
int par2[MAXN];
int eu[MAXN];
int ev[MAXN];

void init(int par[], int n) {
    int i;
    for (i = 1; i <= n; i++) par[i] = i;
}

int find(int par[], int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

void unite(int par[], int a, int b) {
    a = find(par, a);
    b = find(par, b);
    if (a != b) par[a] = b;
}

int main() {
    int n, m1, m2, i;
    int h = 0;
    if (scanf("%d %d %d", &n, &m1, &m2) != 3) return 0;
    init(par1, n);
    init(par2, n);
    for (i = 0; i < m1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(par1, u, v);
    }
    for (i = 0; i < m2; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(par2, u, v);
    }
    for (i = 2; i <= n; i++) {
        if (find(par1, i) != find(par1, 1) && find(par2, i) != find(par2, 1)) {
            unite(par1, i, 1);
            unite(par2, i, 1);
            eu[h] = 1;
            ev[h] = i;
            h++;
        }
    }
    printf("%d\n", h);
    for (i = 0; i < h; i++) printf("%d %d\n", eu[i], ev[i]);
    return 0;
}