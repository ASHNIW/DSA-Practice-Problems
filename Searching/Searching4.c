#include <stdio.h>

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int f_hex(int x) {
    int sum = 0;
    while (x > 0) {
        sum += (x % 16);
        x /= 16;
    }
    return sum;
}

int search(int a, int b) {
    int count = 0;
    for (int x = a; x <= b; x++) {
        if (gcd(x, f_hex(x)) > 1) {
            count++;
        }
    }
    return count;
}

int main() {
    int t, l, r;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        scanf("%d %d", &l, &r);
        printf("%d\n", search(l, r));
    }
    return 0;
}
