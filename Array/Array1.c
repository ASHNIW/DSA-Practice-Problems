#include <stdio.h>
#include <string.h>

void martian_conv(int num) {
    char buf[100];
    int i = 0;
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *symbols[] = {"R", "BR", "G", "BG", "B", "ZB", "P", "ZP", "Z", "BZ", "W", "BW", "B"};

    for (int j = 0; j < 13; j++) {
        while (num >= values[j]) {
            int len = strlen(symbols[j]);
            for (int k = 0; k < len; k++) {
                buf[i++] = symbols[j][k];
            }
            num -= values[j];
        }
    }
    buf[i] = '\0';
    printf("%s\n", buf);
}

int main() {
    int n;
    int count = 0;
    while (scanf("%d", &n) != EOF && count < 5) {
        martian_conv(n);
        count++;
    }
    return 0;
}
