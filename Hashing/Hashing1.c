#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef struct {
    int val;
    int idx;
} Element;

int cmp(const void *a, const void *b) {
    Element *e1 = (Element*)a;
    Element *e2 = (Element*)b;
    if (e1->val != e2->val)
        return e1->val - e2->val;
    return e1->idx - e2->idx;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    int *arr = (int*)malloc(n * sizeof(int));
    int max = 0;
    int i;
    for(i=0;i<n;i++) {
        scanf("%d", &arr[i]);
        if(arr[i]>max) {
            max = arr[i];
        }
    }
    
    Element *elems = (Element*)malloc(n * sizeof(Element));
    for (i = 0; i < n; i++) {
        elems[i].val = arr[i];
        elems[i].idx = i;
    }
    qsort(elems, n, sizeof(Element), cmp);
    
    int *compressed = (int*)malloc(n * sizeof(int));
    int distinct_cnt = 0;
    for (i = 0; i < n; i++) {
        if (i == 0 || elems[i].val != elems[i - 1].val) {
            distinct_cnt++;
        }
        compressed[elems[i].idx] = distinct_cnt - 1;
    }
    
    int *first_pos = (int*)malloc(distinct_cnt * sizeof(int));
    for (i = 0; i < distinct_cnt; i++) first_pos[i] = -1;
    for (i = 0; i < n; i++) {
        int c = compressed[i];
        if (first_pos[c] == -1) {
            first_pos[c] = i;
        }
    }
    
    int *seen = (int*)calloc(distinct_cnt, sizeof(int));
    int *suffix_distinct = (int*)malloc((n + 1) * sizeof(int));
    suffix_distinct[n] = 0;
    for (i = n - 1; i >= 0; i--) {
        int c = compressed[i];
        if (!seen[c]) {
            seen[c] = 1;
            suffix_distinct[i] = suffix_distinct[i + 1] + 1;
        } else {
            suffix_distinct[i] = suffix_distinct[i + 1];
        }
    }
    
    long long total_unique_pairs = 0;
    for (int u = 0; u < distinct_cnt; u++) {
        int pos = first_pos[u];
        if (pos + 1 < n) {
            total_unique_pairs += suffix_distinct[pos + 1];
        }
    }
    
    printf("%lld\n", total_unique_pairs);
    
    free(arr);
    free(elems);
    free(compressed);
    free(first_pos);
    free(seen);
    free(suffix_distinct);
    return 0;
}
