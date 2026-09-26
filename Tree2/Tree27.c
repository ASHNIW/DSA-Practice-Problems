
#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 1000003

typedef struct {
    int val;
    int count;
    int used;
} HashEntry;

HashEntry hash_table[HASH_SIZE];

int find_slot(int val) {
    unsigned int h = ((unsigned int)val * 2654435761U) % HASH_SIZE;
    while (hash_table[h].used && hash_table[h].val != val) {
        h = (h + 1) % HASH_SIZE;
    }
    return h;
}

int get_count(int val) {
    int slot = find_slot(val);
    if (!hash_table[slot].used) return 0;
    return hash_table[slot].count;
}

void set_count(int val, int count) {
    int slot = find_slot(val);
    hash_table[slot].val = val;
    hash_table[slot].count = count;
    hash_table[slot].used = 1;
}

int cmp_int(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    int *init_s = (int*)malloc(N * sizeof(int));
    int i;
    for(i=0;i<N;i++) {
        if (scanf("%d", &init_s[i]) != 1) init_s[i] = 0;
    }
    
    int *unique_vals = (int*)malloc(300005 * sizeof(int));
    int unique_cnt = 0;
    int current_size = N;
    int max_val = init_s[0];
    
    for (i = 0; i < N; i++) {
        int v = init_s[i];
        if (v > max_val) max_val = v;
        int c = get_count(v);
        if (c == 0) {
            unique_vals[unique_cnt++] = v;
        }
        set_count(v, c + 1);
    }
    
    int Q;
    if (scanf("%d", &Q) != 1) Q = 0;
    
    while (Q--) {
        int val;
        if (scanf("%d", &val) != 1) break;
        if (val > max_val) {
            int c = get_count(val);
            if (c == 0) unique_vals[unique_cnt++] = val;
            set_count(val, 1);
            max_val = val;
            current_size++;
        } else if (val == max_val) {
        } else {
            int c = get_count(val);
            if (c == 0) {
                unique_vals[unique_cnt++] = val;
                set_count(val, 1);
                current_size++;
            } else if (c == 1) {
                set_count(val, 2);
                current_size++;
            }
        }
        printf("%d\n", current_size);
    }
    
    qsort(unique_vals, unique_cnt, sizeof(int), cmp_int);
    
    int first = 1;
    for (i = 0; i < unique_cnt; i++) {
        int v = unique_vals[i];
        if (get_count(v) >= 1) {
            if (!first) printf(" ");
            printf("%d", v);
            first = 0;
        }
    }
    
    for (i = unique_cnt - 1; i >= 0; i--) {
        int v = unique_vals[i];
        if (get_count(v) == 2 && v != max_val) {
            if (!first) printf(" ");
            printf("%d", v);
            first = 0;
        }
    }
    printf("\n");
    
    free(init_s);
    free(unique_vals);
    return 0;
}
