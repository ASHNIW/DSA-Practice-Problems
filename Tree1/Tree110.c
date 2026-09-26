#include <stdio.h>

#define MAXN 200005

int arr[MAXN];
int bit[MAXN];
int n;

void update(int i, int x) {
    while (i <= n) {
        bit[i] += x;
        i += i & (-i);
    }
}

int find_kth(int k) {
    int idx = 0;
    int step = 1;
    while (step * 2 <= n) step *= 2;
    for (; step >= 1; step /= 2) {
        int nx = idx + step;
        if (nx <= n && bit[nx] < k) {
            idx = nx;
            k -= bit[nx];
        }
    }
    return idx + 1;
}

int main() {
    int i;
    if (scanf("%d", &n) != 1) return 0;
    for (i = 1; i <= n; i++) scanf("%d", &arr[i]);
    for (i = 1; i <= n; i++) update(i, 1);
    for (i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);
        int idx = find_kth(p);
        printf("%d ", arr[idx]);
        update(idx, -1);
    }
    printf("\n");
    return 0;
}