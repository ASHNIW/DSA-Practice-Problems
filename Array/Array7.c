#include <stdio.h>

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int n, m;
        if (scanf("%d %d", &n, &m) != 2) break;
        int C[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &C[i][j]);
            }
        }
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        long long sum = 0;
        for (int i = x1 - 1; i <= x2 - 1; i++) {
            for (int j = y1 - 1; j <= y2 - 1; j++) {
                sum += C[i][j];
            }
        }
        printf("%lld\n", sum);
    }
    return 0;
}
