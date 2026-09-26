#include <stdio.h>

void bubble_sort(int arr[], int no) {
    int i, j, temp;
    for (i = 0; i < no - 1; i++) {
        for (j = 0; j < no - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int MEGA_SALE(int arr[], int no, int k) {
    bubble_sort(arr, no);
    int earned = 0;
    for (int i = 0; i < no && i < k; i++) {
        if (arr[i] < 0) {
            earned += (-arr[i]);
        }
    }
    return earned;
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n, m;
        scanf("%d %d", &n, &m);
        int arr[105];
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        printf("%d\n", MEGA_SALE(arr, n, m));
    }
    return 0;
}
