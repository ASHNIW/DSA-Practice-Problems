#include <stdio.h>
#include <string.h>

int main() {
    char nums[13][256] = {
        "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX",
        "SEVEN", "EIGHT", "NINE", "TEN", "ELEVEN", "TWELVE"
    };
    int val;
    int inputs[100];
    int count = 0;

    while (scanf("%d", &val) != EOF) {
        inputs[count++] = val;
        if (val == 999) {
            int counts[26] = {0};
            for (int i = 0; i < count - 1; i++) {
                int num = inputs[i];
                if (num >= 0 && num <= 12) {
                    for (int j = 0; nums[num][j] != '\0'; j++) {
                        counts[nums[num][j] - 'A']++;
                    }
                }
            }
            for (int i = 0; i < count; i++) {
                if (inputs[i] == 999) {
                    printf("0999. ");
                } else {
                    printf("%d ", inputs[i]);
                }
            }
            int first = 1;
            int n;
            for (n = 0; n < 26; n++) {
                while (counts[n] > 0) {
                    if (!first) printf(" ");
                    printf("%c", 'A' + n);
                    first = 0;
                    counts[n]--;
                }
            }
            printf("\n");
            count = 0;
        }
    }
    return 0;
}
