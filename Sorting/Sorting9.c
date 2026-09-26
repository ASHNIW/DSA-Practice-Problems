#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n, k, p;
        scanf("%d %d %d", &n, &k, &p);
        int dp[1505];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            int stack_vals[35];
            int pref[35];
            pref[0] = 0;
            for (int j = 1; j <= k; j++) {
                scanf("%d", &stack_vals[j]);
                pref[j] = pref[j - 1] + stack_vals[j];
            }
            for (int cur_p = p; cur_p >= 0; cur_p--) {
                for (int x = 1; x <= k && x <= cur_p; x++) {
                    dp[cur_p] = max(dp[cur_p], dp[cur_p - x] + pref[x]);
                }
            }
        }
        printf("%d\n", dp[p]);
    }
    return 0;
}
