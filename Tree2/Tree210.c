
#include <stdio.h>
#include <stdlib.h>

void heapify(int arr[],int n,int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
        
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) return 0;
    
    int *arr = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        if (scanf("%d", &arr[i]) != 1) arr[i] = 0;
    }
    
    for (int i = m / 2 - 1; i >= 0; i--) {
        heapify(arr, m, i);
    }
    
    long long total_gain = 0;
    for (int i = 0; i < n; i++) {
        if (arr[0] <= 0) break;
        total_gain += arr[0];
        arr[0]--;
        heapify(arr, m, 0);
    }
    
    printf("%lld\n", total_gain);
    
    free(arr);
    return 0;
}
