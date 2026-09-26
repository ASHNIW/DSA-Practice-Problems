#include <stdio.h>
#include <stdlib.h>

int cmp_ll(const void *a, const void *b) {
    long long v1 = *(const long long *)a;
    long long v2 = *(const long long *)b;
    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    int NA[N] ;
    for (int i = 0; i < N; i++) {
        scanf("%d", &NA[i]);
    }
    
    long long total_subs = (long long)N * (N + 1) / 2;
    long long *max_sums = (long long *)malloc(total_subs * sizeof(long long));
    long long count = 0;
    
    for (int l = 0; l < N; l++) {
        long long max_so_far = NA[l];
        long long curr_max = NA[l];
        max_sums[count++] = max_so_far;
        
        for (int r = l + 1; r < N; r++) {
            if (curr_max + NA[r] > NA[r]) {
                curr_max = curr_max + NA[r];
            } else {
                curr_max = NA[r];
            }
            if (curr_max > max_so_far) {
                max_so_far = curr_max;
            }
            max_sums[count++] = max_so_far;
        }
    }
    
    qsort(max_sums, count, sizeof(long long), cmp_ll);
    
    long long total_unique_sum = 0;
    for (long long i = 0; i < count; i++) {
        if (i == 0 || max_sums[i] != max_sums[i - 1]) {
            total_unique_sum += max_sums[i];
        }
    }
    
    printf("%lld\n", total_unique_sum);
    
    free(max_sums);
    return 0;
}
