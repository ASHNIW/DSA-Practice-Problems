#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define LOG 18

int up[MAXN][LOG];
int depth[MAXN];

int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    
    for (int i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);
        up[i][0] = p;
        depth[i] = depth[p] + 1;
        for (int j = 1; j < LOG; j++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
    
    for (int i = 0; i < q; i++) {
        int x, k;
        scanf("%d %d", &x, &k);
        if (k > depth[x]) {
            printf("-1\n");
        } else {
            for (int j = LOG - 1; j >= 0; j--) {
                if (k & (1 << j)) {
                    x = up[x][j];
                }
            }
            printf("%d\n", x);
        }
    }
    return 0;
}