#include <stdio.h>

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    for (int t = 0; t < T; t++) {
        int n;
        long long d;
        scanf("%d %lld", &n, &d);
        long long x[1005];
        for (int i = 0; i < n; i++) {
            scanf("%lld", &x[i]);
        }
        long long cur = d;
        for (int i = n - 1; i >= 0; i--) {
            cur = (cur / x[i]) * x[i];
        }
        printf("%lld\n", cur);
    }
    return 0;
}
