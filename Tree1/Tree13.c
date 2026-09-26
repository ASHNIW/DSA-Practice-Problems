#include <stdio.h>

#define MAXN 1005

int pref[MAXN][MAXN];
char row[MAXN];

int main() {
    int n, q, i, j;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    for(i=1;i<=n;i++) {
        scanf("%s", row);
        for (j = 1; j <= n; j++) {
            int val = (row[j - 1] == '*') ? 1 : 0;
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + val;
        }
    }
    for (int k = 0; k < q; k++) {
        int y1, x1, y2, x2;
        if (scanf("%d %d %d %d", &y1, &x1, &y2, &x2) == 4) {
            if (y1 > y2 || x1 > x2) {
                printf("0\n");
            } else {
                int ans = pref[y2][x2] - pref[y1 - 1][x2] - pref[y2][x1 - 1] + pref[y1 - 1][x1 - 1];
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
