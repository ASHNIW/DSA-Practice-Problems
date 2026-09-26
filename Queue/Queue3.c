#include <stdio.h>

#define MAX 100

int queue[MAX];
int front = -1;
int rear = -1;

void enqueue(int data) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = data;
}

void dequeue() {
    if (front == -1 || front > rear) return;
    front++;
}

void display() {
    int i;
    for (i = front; i <= rear; i++) {
        printf("%d%c", queue[i], (i == rear) ? '\n' : ' ');
    }
}

int main() {
    int size;
    if (scanf("%d", &size) != 1) return 0;

    for (int i = 0; i < size; i++) {
        int data;
        scanf("%d", &data);
        enqueue(data);
    }

    printf("Dequeuing elements:\n");
    while (front < rear) {
        dequeue();
        display();
    }
    return 0;
}
