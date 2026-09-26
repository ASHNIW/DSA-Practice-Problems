#include <stdio.h>

int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;

    int arr[N + 1];
    int arr2[N + 1];
    for (int i = 1; i <= N; i++) {
        scanf("%d", &arr[i]);
        arr2[i] = sumOfDigits(arr[i]);
    }

    for (int q = 0; q < Q; q++) {
        int x;
        scanf("%d", &x);
        int ans = -1;
        for (int y = x + 1; y <= N; y++) {
            if (arr[x] < arr[y]) {
                if (arr2[x] < arr2[y]) {
                    ans = y;
                    break;
                }
            }
        }
        printf("%d ", ans);
    }
    printf("\n");
    return 0;
}
