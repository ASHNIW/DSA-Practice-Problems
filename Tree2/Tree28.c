
#include <stdio.h>
#include <stdlib.h>

#define MAX_GHOST 100005

typedef struct {
    int count;
    int age;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
} MaxHeap;

void push_heap(MaxHeap *h, int count, int age) {
    int i = h->size++;
    h->data[i].count = count;
    h->data[i].age = age;
    while (i > 0) {
        int p = (i - 1) / 2;
        int better = 0;
        if (h->data[i].count > h->data[p].count) better = 1;
        else if (h->data[i].count == h->data[p].count && h->data[i].age > h->data[p].age) better = 1;
        if (better) {
            HeapNode tmp = h->data[i];
            h->data[i] = h->data[p];
            h->data[p] = tmp;
            i = p;
        } else {
            break;
        }
    }
}

void pop_heap(MaxHeap *h) {
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int best = left;
        if (right < h->size) {
            int right_better = 0;
            if (h->data[right].count > h->data[left].count) right_better = 1;
            else if (h->data[right].count == h->data[left].count && h->data[right].age > h->data[left].age) right_better = 1;
            if (right_better) best = right;
        }
        int best_better = 0;
        if (h->data[best].count > h->data[i].count) best_better = 1;
        else if (h->data[best].count == h->data[i].count && h->data[best].age > h->data[i].age) best_better = 1;
        if (best_better) {
            HeapNode tmp = h->data[i];
            h->data[i] = h->data[best];
            h->data[best] = tmp;
            i = best;
        } else {
            break;
        }
    }
}

int count_arr[MAX_GHOST];

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    int *ages = (int*)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        if (scanf("%d", &ages[i]) != 1) ages[i] = 0;
    }
    
    MaxHeap h;
    h.data = (HeapNode*)malloc((n + 5) * sizeof(HeapNode));
    h.size = 0;
    
    for(i = 0;i<n-1;i++) {
        int age = ages[i];
        count_arr[age]++;
        push_heap(&h, count_arr[age], age);
        while (h.size > 0 && h.data[0].count != count_arr[h.data[0].age]) {
            pop_heap(&h);
        }
        printf("%d %d\n", h.data[0].age, h.data[0].count);
    }
    if (n > 0) {
        int age = ages[n - 1];
        count_arr[age]++;
        push_heap(&h, count_arr[age], age);
        while (h.size > 0 && h.data[0].count != count_arr[h.data[0].age]) {
            pop_heap(&h);
        }
        printf("%d %d\n", h.data[0].age, h.data[0].count);
    }
    
    free(ages);
    free(h.data);
    return 0;
}
