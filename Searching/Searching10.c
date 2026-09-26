#include <stdio.h>

long long get_sum(long long n) {
    long long sum_i = n * (n + 1) / 2;
    long long sum_ceil;
    if (n % 2 == 0) {
        long long k = n / 2;
        sum_ceil = k * (k + 1);
    } else {
        long long k = (n + 1) / 2;
        sum_ceil = k * k;
    }
    return sum_i + sum_ceil;
}

long long get_val(long long pos) {
    long long low = 1, high = 50000000;
    long long ans = high;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (get_sum(mid) >= pos) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

int main() {
    int q;
    if (scanf("%d", &q) != 1) return 0;
    while (q--) {
        long long l, r;
        scanf("%lld %lld", &l, &r);
        if (l > r) {
            long long tmp = l;
            l = r;
            r = tmp;
        }
        long long v1 = get_val(l);
        long long v2 = get_val(r);
        printf("%lld\n", v2 - v1 + 1);
    }
    return 0;
}
