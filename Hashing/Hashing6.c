#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

int main() {
    int M, Q, N;
    if (scanf("%d %d %d", &M, &Q, &N) != 3) return 0;
    
    int *A = (int *)malloc(N * sizeof(int));
    int *hash = (int *)calloc(1000005, sizeof(int));
    int i;
    for(i=0;i<N;i++) {
        scanf("%d", &A[i]);
        hash[A[i]]++;
    }
    
    int **groups = (int **)malloc(M * sizeof(int *));
    int *group_sizes = (int *)calloc(M, sizeof(int));
    int *group_caps = (int *)calloc(M, sizeof(int));
    
    for (i = 0; i < M; i++) {
        group_caps[i] = 16;
        groups[i] = (int *)malloc(group_caps[i] * sizeof(int));
    }
    
    for (i = 0; i < N; i++) {
        int rem = A[i] % M;
        int q = A[i] / M;
        if (group_sizes[rem] == group_caps[rem]) {
            group_caps[rem] *= 2;
            groups[rem] = (int *)realloc(groups[rem], group_caps[rem] * sizeof(int));
        }
        groups[rem][group_sizes[rem]++] = q;
    }
    
    int max_rating = 0;
    for (int r = 0; r < M; r++) {
        if (group_sizes[r] == 0) continue;
        qsort(groups[r], group_sizes[r], sizeof(int), cmp_int);
        
        int left = 0;
        for (int right = 0; right < group_sizes[r]; right++) {
            while (groups[r][right] - groups[r][left] > 2 * Q) {
                left++;
            }
            int current_len = right - left + 1;
            if (current_len > max_rating) {
                max_rating = current_len;
            }
        }
    }
    
    printf("%d\n", max_rating);
    
    for (i = 0; i < M; i++) {
        free(groups[i]);
    }
    free(groups);
    free(group_sizes);
    free(group_caps);
    free(hash);
    free(A);
    return 0;
}
