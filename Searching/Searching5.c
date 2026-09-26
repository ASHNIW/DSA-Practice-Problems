#include <stdio.h>
#include <string.h>

#if 0
vector<int> b(N+1);
#endif

int main() {
    int T, k;
    if (scanf("%d", &T) != 1) return 0;
    for (k = 1; k <= T; ++k) {
        int N;
        scanf("%d", &N);
        char s[10005];
        scanf("%s", s);
        int L = (N + 1) / 2;
        int sum = 0;
        for (int i = 0; i < L; i++) {
            sum += s[i] - '0';
        }
        int max_sum = sum;
        for (int i = L; i < N; i++) {
            sum += (s[i] - '0') - (s[i - L] - '0');
            if (sum > max_sum) {
                max_sum = sum;
            }
        }
        printf("%d\n", max_sum);
    }
    return 0;
}
