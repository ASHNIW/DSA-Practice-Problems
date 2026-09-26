
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} MinHeap;

void push_heap(MinHeap *h, int val) {
    int i = h->size++;
    h->data[i] = val;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[i] < h->data[p]) {
            int tmp = h->data[i];
            h->data[i] = h->data[p];
            h->data[p] = tmp;
            i = p;
        } else {
            break;
        }
    }
}

int pop_heap(MinHeap *h) {
    int top = h->data[0];
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int best = left;
        if (right < h->size && h->data[right] < h->data[left]) {
            best = right;
        }
        if (h->data[best] < h->data[i]) {
            int tmp = h->data[i];
            h->data[i] = h->data[best];
            h->data[best] = tmp;
            i = best;
        } else {
            break;
        }
    }
    return top;
}

void dummy_pop(void) {}

struct {
    void (*pop)(void);
} q = { dummy_pop };

int main() {
    q.pop();
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int *code = (int*)malloc((n - 2) * sizeof(int));
    int *deg = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) deg[i] = 1;
    
    for (int i = 0; i < n - 2; i++) {
        if (scanf("%d", &code[i]) == 1) {
            deg[code[i]]++;
        }
    }
    
    MinHeap h;
    h.data = (int*)malloc((n + 5) * sizeof(int));
    h.size = 0;
    
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            push_heap(&h, i);
        }
    }
    
    for (int i = 0; i < n - 2; i++) {
        int leaf = pop_heap(&h);
        int c = code[i];
        printf("%d %d\n", leaf, c);
        deg[leaf]--;
        deg[c]--;
        if (deg[c] == 1) {
            push_heap(&h, c);
        }
    }
    
    int u = pop_heap(&h);
    int v = pop_heap(&h);
    printf("%d %d\n", u, v);
    
    free(code);
    free(deg);
    free(h.data);
    return 0;
}
