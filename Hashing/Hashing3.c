#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FEST 10005
#define NAME_LEN 15

typedef struct {
    char name[NAME_LEN];
    long long top3[3];
    int count;
} Festival;

int cmp_desc(const void *a, const void *b) {
    long long v1 = *(const long long *)a;
    long long v2 = *(const long long *)b;
    if (v2 > v1) return 1;
    if (v2 < v1) return -1;
    return 0;
}

int find_or_add(Festival *festivals, int *num_festivals, const char *name) {
    for (int i = 0; i < *num_festivals; i++) {
        if (strcmp(festivals[i].name, name) == 0) {
            return i;
        }
    }
    strcpy(festivals[*num_festivals].name, name);
    festivals[*num_festivals].count = 0;
    festivals[*num_festivals].top3[0] = 0;
    festivals[*num_festivals].top3[1] = 0;
    festivals[*num_festivals].top3[2] = 0;
    (*num_festivals)++;
    return (*num_festivals) - 1;
}

void add_spending(Festival *f, long long amount) {
    if (f->count < 3) {
        f->top3[f->count++] = amount;
        qsort(f->top3, f->count, sizeof(long long), cmp_desc);
    } else {
        if (amount > f->top3[2]) {
            f->top3[2] = amount;
            qsort(f->top3, 3, sizeof(long long), cmp_desc);
        }
    }
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    
    Festival *festivals = (Festival *)malloc(MAX_FEST * sizeof(Festival));
    
    while(t--) {
        int n;
        if (scanf("%d", &n) != 1) break;
        
        int num_festivals = 0;
        for (int i = 0; i < n; i++) {
            char name[NAME_LEN];
            long long amount;
            scanf("%s %lld", name, &amount);
            int idx = find_or_add(festivals, &num_festivals, name);
            add_spending(&festivals[idx], amount);
        }
        
        char best_name[NAME_LEN] = "";
        long long best_sum = -1;
        
        for (int i = 0; i < num_festivals; i++) {
            long long sum = 0;
            for (int j = 0; j < festivals[i].count; j++) {
                sum += festivals[i].top3[j];
            }
            if (sum > best_sum) {
                best_sum = sum;
                strcpy(best_name, festivals[i].name);
            } else if (sum == best_sum) {
                if (strcmp(festivals[i].name, best_name) < 0) {
                    strcpy(best_name, festivals[i].name);
                }
            }
        }
        
        printf("%s %lld\n", best_name, best_sum);
    }
    
    free(festivals);
    return 0;
}
