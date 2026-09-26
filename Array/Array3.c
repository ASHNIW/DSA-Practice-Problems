#include <stdio.h>

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int n;
        if (scanf("%d", &n) != 1) break;
        int arr[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        int i = 0, count = 0;
        while (i < n - 1) {
            while ((i < n - 1) && (arr[i + 1] <= arr[i]))
                i++;
            if (i == n - 1)
                break;
            int buy = i++;
            while ((i < n) && (arr[i] >= arr[i - 1])) {
                if (arr[i] > arr[i - 1]) {}
                i++;
            }
            int sell = i - 1;
            printf("(%d %d)", buy, sell);
            count++;
        }
        if (count == 0)
            printf("No Profit");
        printf("\n");
    }
    return 0;
}
