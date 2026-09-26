#include <stdio.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    long long a[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    int next_greater[n];
    for (int i = 0; i < n; i++) {
        next_greater[i] = -1;
        for (int j = i + 1; j < n; j++) {
            if (a[j] > a[i]) {
                next_greater[i] = j;
                break;
            }
        }
    }

    int next_smaller[n];
    for (int i = 0; i < n; i++) {
        next_smaller[i] = -1;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) {
                next_smaller[i] = j;
                break;
            }
        }
    }

    int i;
    for (i = 0; i < n; i++) {
        int fg = -1;
        int f = next_greater[i];
        if (f != -1) {
            int g = next_smaller[f];
            if (g != -1) {
                fg = a[g];
            }
        }
        printf("%d%c", fg, (i == n - 1) ? '\n' : ' ');
    }
    return 0;
}
