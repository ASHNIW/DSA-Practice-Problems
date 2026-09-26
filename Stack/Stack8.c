#include <stdio.h>

int arr[1000000];
int st[1000000];

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int max_stamina = 0;
    int i, j;

    for (i = n - 1; i >= 0; i--) {
        int next_higher = -1;
        for (j = i + 1; j < n; j++) {
            if (arr[i] < arr[j]) {
                next_higher = j;
                break;
            }
        }
        if (next_higher != -1) {
            j = next_higher;
            st[i] = arr[i] ^ st[j];
        } else {
            st[i] = arr[i];
        }
        if (st[i] > max_stamina) {
            max_stamina = st[i];
        }
    }

    printf("%d\n", max_stamina);
    return 0;
}
