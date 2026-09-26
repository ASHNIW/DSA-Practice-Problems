#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node *front = NULL;
struct node *rear = NULL;

void enqueue(int d) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = d;
    new_node->next = NULL;
    if (front == NULL && rear == NULL) {
        front = rear = new_node;
        return;
    }
    rear->next = new_node;
    rear = new_node;
}

void dequeue() {
    if (front == NULL) return;
    struct node* temp = front;
    front = front->next;
    if (front == NULL) rear = NULL;
    free(temp);
}

void print() {
    if (front == NULL) {
        printf("No data in the queue.\n");
        return;
    }
    struct node* temp = front;
    while (temp != NULL) {
        printf("%d%c", temp->data, (temp->next == NULL) ? '\n' : ' ');
        temp = temp->next;
    }
}

int main() {
    int size;
    if (scanf("%d", &size) != 1) return 0;

    for (int i = 0; i < size; i++) {
        int d;
        scanf("%d", &d);
        enqueue(d);
    }

    print();
    dequeue();
    print();
    return 0;
}
