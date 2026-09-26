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

void disp() {
    int i;
    for (i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
}

int main() {
    int size;
    if (scanf("%d", &size) != 1) return 0;

    for (int i = 0; i < size; i++) {
        int data;
        scanf("%d", &data);
        if (i > 0) {
            disp();
        }
        printf("Enqueuing %d\n", data);
        enqueue(data);
    }
    disp();
    printf("\n");
    return 0;
}
