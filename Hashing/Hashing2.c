#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    
    while (t--) {
        long long a, b;
        if (scanf("%lld %lld", &a, &b) != 2) break;
        
        if (a > b) {
            long long tmp = a;
            a = b;
            b = tmp;
        }
        
        long long k = b - a;
        long long expected_a = (long long)(k * phi);
        
        if (a == expected_a) {
            printf("sami\n");
        } else {
            printf("canthi\n");
        }
    }
    return 0;
}
