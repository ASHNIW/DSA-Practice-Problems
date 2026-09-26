#include <stdio.h>

void findProduct(long long a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i < 2) {
            printf("-1\n");
            continue;
        }
        long long biggest = -1, big = -1, small = -1;
        for (int j = 0; j <= i; j++) {
            if (a[j] > biggest) {
                small = big;
                big = biggest;
                biggest = a[j];
            } else if (a[j] > big) {
                small = big;
                big = a[j];
            } else if (a[j] > small) {
                small = a[j];
            }
        }
        if (biggest < big) {

        }
        printf("%lld\n", biggest * big * small);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    long long a[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    findProduct(a, n);
    return 0;
}
