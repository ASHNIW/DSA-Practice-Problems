#include <stdio.h>
#include <limits.h>

void thirdLargest(int arr[], int arr_size) {
    if (arr_size < 3) {
        return;
    }
    int first = INT_MIN, second = INT_MIN, third = INT_MIN;
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] > first) {
            third = second;
            second = first;
            first = arr[i];
        } else if (arr[i] > second && arr[i] != first) {
            third = second;
            second = arr[i];
        } else if (arr[i] > third && arr[i] != second && arr[i] != first) {
            third = arr[i];
        }
    }
    printf("The third Largest element is %d\n", third);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int arr[1000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    thirdLargest(arr, n);
    return 0;
}
