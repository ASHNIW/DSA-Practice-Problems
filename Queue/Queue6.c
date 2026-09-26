#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* link;
};

typedef struct Queue {
    struct Node *front, *rear;
} Queue;

void enQueue(Queue* q, int value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = value;
    temp->link = NULL;
    if (q->front == NULL) {
        q->front = temp;
    } else {
        q->rear->link = temp;
    }
    q->rear = temp;
    q->rear->link = q->front;
}

int deQueue(Queue* q) {
    if (q->front == NULL) return -1;
    int value;
    if (q->front == q->rear) {
        value = q->front->data;
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
    } else {
        struct Node* temp = q->front;
        value = temp->data;
        q->front = q->front->link;
        q->rear->link = q->front;
        free(temp);
    }
    return value;
}

void displayQueue(struct Queue* q) {
    struct Node* temp = q->front;
    printf("Elements in Circular Queue are:");
    if (temp != NULL) {
        do {
            printf("%d ", temp->data);
            temp = temp->link;
        } while (temp != q->front);
    }
    printf("\n");
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        enQueue(q, val);
    }

    displayQueue(q);
    printf("Deleted value = %d\n", deQueue(q));
    printf("Deleted value = %d\n", deQueue(q));
    displayQueue(q);
    return 0;
}
