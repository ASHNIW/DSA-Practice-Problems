#include <stdio.h>
#include <stdlib.h>

typedef struct QNode {
    unsigned pageNumber;
    struct QNode *prev, *next;
} QNode;

typedef struct Queue {
    unsigned count;
    unsigned numberOfFrames;
    QNode *front, *rear;
} Queue;

QNode* newQNode(unsigned pageNumber) {
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    temp->pageNumber = pageNumber;
    temp->prev = temp->next = NULL;
    return temp;
}

Queue* createQueue(int numberOfFrames) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->count = 0;
    queue->front = queue->rear = NULL;
    queue->numberOfFrames = numberOfFrames;
    return queue;
}

void removeNode(Queue* queue, QNode* node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        queue->front = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        queue->rear = node->prev;
    }
    queue->count--;
}

void addToFront(Queue* queue, QNode* node) {
    node->next = queue->front;
    node->prev = NULL;
    if (queue->front != NULL) {
        queue->front->prev = node;
    }
    queue->front = node;
    if (queue->rear == NULL) {
        queue->rear = node;
    }
    queue->count++;
}

void referencePage(Queue* queue, unsigned pageNumber) {
    QNode* curr = queue->front;
    QNode* found = NULL;
    while (curr != NULL) {
        if (curr->pageNumber == pageNumber) {
            found = curr;
            break;
        }
        curr = curr->next;
    }

    if (found != NULL) {
        removeNode(queue, found);
        addToFront(queue, found);
    } else {
        if (queue->count == queue->numberOfFrames) {
            QNode* lru = queue->rear;
            removeNode(queue, lru);
            free(lru);
        }
        QNode* newNode = newQNode(pageNumber);
        addToFront(queue, newNode);
    }
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return 0;

    Queue* queue = createQueue(k);

    for (int i = 0; i < n; i++) {
        unsigned page;
        scanf("%u", &page);
        referencePage(queue, page);
    }

    QNode* curr = queue->front;
    while (curr != NULL) {
        printf("%u%c", curr->pageNumber, (curr->next == NULL) ? '\n' : ' ');
        curr = curr->next;
    }
    return 0;
}
