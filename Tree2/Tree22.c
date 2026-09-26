
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long val;
    int id;
} Node;

typedef struct {
    Node *data;
    int size;
    int is_min;
} Heap;

void push_heap(Heap *h, long long val, int id) {
    int i = h->size++;
    h->data[i].val = val;
    h->data[i].id = id;
    while (i > 0) {
        int p = (i - 1) / 2;
        int cond = h->is_min ? (h->data[i].val < h->data[p].val) : (h->data[i].val > h->data[p].val);
        if (cond) {
            Node tmp = h->data[i];
            h->data[i] = h->data[p];
            h->data[p] = tmp;
            i = p;
        } else {
            break;
        }
    }
}

Node pop_heap(Heap *h) {
    Node top = h->data[0];
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int best = left;
        if (right < h->size) {
            int cond = h->is_min ? (h->data[right].val < h->data[left].val) : (h->data[right].val > h->data[left].val);
            if (cond) best = right;
        }
        int cond = h->is_min ? (h->data[best].val < h->data[i].val) : (h->data[best].val > h->data[i].val);
        if (cond) {
            Node tmp = h->data[i];
            h->data[i] = h->data[best];
            h->data[best] = tmp;
            i = best;
        } else {
            break;
        }
    }
    return top;
}

int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    long long *a = (long long*)malloc(n * sizeof(long long));
    long long initial_sum = 0;
    int i;
    for(i=0;i<n;i++) {
        if (scanf("%lld", &a[i]) != 1) a[i] = 0;
        initial_sum += a[i];
    }
    
    int max_nodes = 2 * n + 5;
    Heap min_h, max_h;
    min_h.data = (Node*)malloc(max_nodes * sizeof(Node));
    min_h.size = 0;
    min_h.is_min = 1;
    
    max_h.data = (Node*)malloc(max_nodes * sizeof(Node));
    max_h.size = 0;
    max_h.is_min = 0;
    
    char *deleted = (char*)calloc(max_nodes, sizeof(char));
    
    for (i = 0; i < n; i++) {
        push_heap(&min_h, a[i], i);
        push_heap(&max_h, a[i], i);
    }
    
    long long *ans = (long long*)malloc(n * sizeof(long long));
    ans[0] = initial_sum;
    
    int next_id = n;
    long long current_sum = initial_sum;
    
    for (int step = 1; step < n; step++) {
        while (min_h.size > 0 && deleted[min_h.data[0].id]) {
            pop_heap(&min_h);
        }
        Node mn = pop_heap(&min_h);
        deleted[mn.id] = 1;
        
        while (max_h.size > 0 && deleted[max_h.data[0].id]) {
            pop_heap(&max_h);
        }
        Node mx = pop_heap(&max_h);
        deleted[mx.id] = 1;
        
        long long diff = mx.val - mn.val;
        current_sum -= 2 * mn.val;
        ans[step] = current_sum;
        
        int new_id = next_id++;
        push_heap(&min_h, diff, new_id);
        push_heap(&max_h, diff, new_id);
    }
    
    for (i = 0; i < q; i++) {
        int k;
        if (scanf("%d", &k) == 1) {
            if (k >= 0 && k < n) {
                printf("%lld\n", ans[k]);
            }
        }
    }
    
    free(a);
    free(min_h.data);
    free(max_h.data);
    free(deleted);
    free(ans);
    return 0;
}
