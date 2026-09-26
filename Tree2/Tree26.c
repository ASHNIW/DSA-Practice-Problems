
#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

long long tree_sum[4 * MAXN];
long long lazy_a[4 * MAXN];
long long lazy_d[4 * MAXN];
long long initial_arr[MAXN];

void build(int k,int l,int r) {
    lazy_a[k] = 0;
    lazy_d[k] = 0;
    if (l == r) {
        tree_sum[k] = initial_arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * k, l, mid);
    build(2 * k + 1, mid + 1, r);
    tree_sum[k] = tree_sum[2 * k] + tree_sum[2 * k + 1];
}

void apply_lazy(int k, int l, int r, long long a, long long d) {
    long long len = r - l + 1;
    tree_sum[k] += len * a + d * len * (len - 1) / 2;
    lazy_a[k] += a;
    lazy_d[k] += d;
}

void push(int k, int l, int r) {
    if (lazy_a[k] != 0 || lazy_d[k] != 0) {
        int mid = (l + r) / 2;
        apply_lazy(2 * k, l, mid, lazy_a[k], lazy_d[k]);
        apply_lazy(2 * k + 1, mid + 1, r, lazy_a[k] + (mid + 1 - l) * lazy_d[k], lazy_d[k]);
        lazy_a[k] = 0;
        lazy_d[k] = 0;
    }
}

void update(int k, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        long long a = (long long)(l - ql + 1);
        long long d = 1;
        apply_lazy(k, l, r, a, d);
        return;
    }
    push(k, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) update(2 * k, l, mid, ql, qr);
    if (qr > mid) update(2 * k + 1, mid + 1, r, ql, qr);
    tree_sum[k] = tree_sum[2 * k] + tree_sum[2 * k + 1];
}

long long query(int k, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree_sum[k];
    }
    push(k, l, r);
    int mid = (l + r) / 2;
    long long res = 0;
    if (ql <= mid) res += query(2 * k, l, mid, ql, qr);
    if (qr > mid) res += query(2 * k + 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    for (int i = 1; i <= n; i++) {
        if (scanf("%lld", &initial_arr[i]) != 1) initial_arr[i] = 0;
    }
    build(1, 1, n);
    while (q--) {
        int type, a, b;
        if (scanf("%d %d %d", &type, &a, &b) != 3) break;
        if (type == 1) {
            update(1, 1, n, a, b);
        } else {
            printf("%lld\n", query(1, 1, n, a, b));
        }
    }
    return 0;
}
