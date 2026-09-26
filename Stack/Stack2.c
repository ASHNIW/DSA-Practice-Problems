#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct mystack {
    Node* top;
} mystack;

mystack* createStack() {
    mystack* ms = (mystack*)malloc(sizeof(mystack));
    ms->top = NULL;
    return ms;
}

void push(int data, mystack* ms) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = ms->top;
    ms->top = temp;
}

int pop(mystack* ms) {
    if (ms->top == NULL) return -1;
    Node* temp = ms->top;
    int val = temp->data;
    ms->top = ms->top->next;
    free(temp);
    return val;
}

void merge(mystack* ms1, mystack* ms2) {
    if (ms1->top == NULL) {
        ms1->top = ms2->top;
        return;
    }
    Node* curr = ms1->top;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = ms2->top;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    mystack* ms1 = createStack();
    mystack* ms2 = createStack();

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        push(val, ms1);
    }
    for (int i = 0; i < m; i++) {
        int val;
        scanf("%d", &val);
        push(val, ms2);
    }

    merge(ms1, ms2);

    Node* curr = ms1->top;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
    return 0;
}
