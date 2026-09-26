#include <stdio.h>
#include <stdlib.h>

int cmp_asc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int cmp_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        scanf("%d", &n);
        int a[10005], b[10005];
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
        }
        qsort(a, n, sizeof(int), cmp_asc);
        qsort(b, n, sizeof(int), cmp_desc);
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] % b[i] == 0 || b[i] % a[i] == 0) {
                count++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}
