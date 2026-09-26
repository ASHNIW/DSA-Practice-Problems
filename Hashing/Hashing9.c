#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL 1000005

int count_divisors(int n) {
    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i == n) count++;
            else count += 2;
        }
    }
    return count;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    int original_N = N;
    int *A = (int *)malloc(original_N * sizeof(int));
    for (int i = 0; i < original_N; i++) {
        scanf("%d", &A[i]);
    }
    
    int freq_div[1000] = {0};
    int i = 0;
    freq_div[count_divisors(A[i++])]++;
    while(--N) {
        freq_div[count_divisors(A[i++])]++;
    }
    
    long long total_pairs = 0;
    for (int d = 0; d < 1000; d++) {
        if (freq_div[d] > 1) {
            total_pairs += (long long)freq_div[d] * (freq_div[d] - 1) / 2;
        }
    }
    
    printf("%lld\n", total_pairs);
    
    free(A);
    return 0;
}
