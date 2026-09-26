#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int parent[MAXN];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    
    while (m--) {
        int u, v;
        scanf("%d %d", &u, &v);
        int ru = find(u);
        int rv = find(v);
        if (ru != rv) {
            parent[ru] = rv;
        }
    }
    
    int reps[MAXN];
    int rep_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (find(i) == i) {
            reps[rep_cnt++] = i;
        }
    }
    
    printf("%d\n", rep_cnt - 1);
    for (int i = 1; i < rep_cnt; i++) {
        printf("%d %d\n", reps[i - 1], reps[i]);
    }
    
    return 0;
}
