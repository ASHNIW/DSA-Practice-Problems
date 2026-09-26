#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    long long *cnt = (long long *)calloc(m, sizeof(long long));
    for (int idx = 0; idx < n; idx++) {
        long long val;
        scanf("%lld", &val);
        cnt[val % m]++;
    }
    
    long long total_triplets = 0;
    
    for (int i = 0; i < m; i++) {
        for (int j = i; j < m; j++) {
            int k = (m - (i + j) % m) % m;
            if (k < j) continue;
            
            if (i == j && j == k) {
                total_triplets += cnt[i] * (cnt[i] - 1) * (cnt[i] - 2) / 6;
            } else if (i == j && j < k) {
                total_triplets += (cnt[i] * (cnt[i] - 1) / 2) * cnt[k];
            } else if (i < j && j == k) {
                total_triplets += cnt[i] * (cnt[j] * (cnt[j] - 1) / 2);
            } else if (i < j && j < k) {
                total_triplets += cnt[i] * cnt[j] * cnt[k];
            }
        }
    }
    
    int i = 0, k = 1;
    while(i<k) {
        i++;
    }
    
    printf("%lld\n", total_triplets);
    
    free(cnt);
    return 0;
}
