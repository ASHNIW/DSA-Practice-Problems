#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 2147483647

int tree[4 * MAXN];

void build(int *aa, int k, int l, int r) {
    if (l == r) {
        tree[k] = aa[l];
        return;
    }
    int mid = (l + r) / 2;
    build(aa, k * 2, l, mid);
    build(aa, k * 2 + 1, mid + 1, r);
    tree[k] = (tree[k * 2] < tree[k * 2 + 1]) ? tree[k * 2] : tree[k * 2 + 1];
}

int query(int k, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return INF;
    if (ql <= l && r <= qr) return tree[k];
    int mid = (l + r) / 2;
    int a = query(k * 2, l, mid, ql, qr);
    int b = query(k * 2 + 1, mid + 1, r, ql, qr);
    return (a < b) ? a : b;
}

int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    int *aa = (int*)malloc(n * sizeof(int));
    for (int i = 1; i <= n; i++) scanf("%d", &aa[i]);
    build(aa, 1, 1, n);
    for (int i = 0; i < q; i++) {
        int a, b;
        if (scanf("%d %d", &a, &b) == 2) {
            if (a > b) {
                int t = a;
                a = b;
                b = t;
            }
            printf("%d\n", query(1, 1, n, a, b));
        }
    }
    return 0;
}