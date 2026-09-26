#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int s[MAXN];
int temp[MAXN];

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void sol() {
    int N;
    if (scanf("%d", &N) != 1) return;
    for (int i = 0; i < N; i++) {
        scanf("%d", &s[i]);
        temp[i] = s[i];
    }
    qsort(temp, N, sizeof(int), cmp);

    int unique[MAXN];
    int u_count = 0;
    for (int i = 0; i < N; i++) {
        if (i == 0 || temp[i] != temp[i - 1]) {
            unique[u_count++] = temp[i];
        }
    }

    long long total_treats = 0;
    for (int i = 0; i < N; i++) {

        int low = 0, high = u_count - 1, rank = 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (unique[mid] == s[i]) {
                rank = mid + 1;
                break;
            } else if (unique[mid] < s[i]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        total_treats += rank;
    }
    printf("%lld\n", total_treats);
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        sol();
    }
    return 0;
}
