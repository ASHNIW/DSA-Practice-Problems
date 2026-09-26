#include <stdio.h>
#include <string.h>

#define MAX 100
#define LEN 100

int main() {
    int total_dollar, items;
    if (scanf("%d %d", &total_dollar, &items) != 2) return 0;

    char name[MAX][LEN];
    int price[MAX];
    int afford[MAX] = {0};
    int orig_order[MAX];
    int sorted_indices[MAX];

    int i, j;
    for (i = 0; i < items; i++) {
        scanf("%s %d", name[i], &price[i]);
        orig_order[i] = i;
        sorted_indices[i] = i;
    }

    for (i = 0; i < items; i++) {
        for (j = i + 1; j < items; j++) {
            if (price[sorted_indices[i]] > price[sorted_indices[j]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }

    int remaining = total_dollar;
    int bought = 0;
    for (i = 0; i < items; i++) {
        int idx = sorted_indices[i];
        if (price[idx] <= remaining) {
            afford[idx] = 1;
            remaining -= price[idx];
            bought++;
        }
    }

    for (i = 0; i < items; i++) {
        if (afford[i]) {
            printf("I can afford %s\n", name[i]);
        } else {
            printf("I can't afford %s\n", name[i]);
        }
    }

    if (bought == 0) {
        printf("I need more Dollar!\n");
    }
    printf("%d\n", remaining);

    return 0;
}
