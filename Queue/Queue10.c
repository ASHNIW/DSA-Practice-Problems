#include <stdio.h>

#define MAX 100

int queue[MAX];
int front = -1;
int rear = -1;

void enqueue(int data, int n) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = data;
}

void reverse() {
    int i = front, j = rear;
    while (i < j) {
        int temp = queue[i];
        queue[i] = queue[j];
        queue[j] = temp;
        i++;
        j--;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);
        enqueue(t, n);
    }

    printf("Queue:");
    for (int i = front; i <= rear; i++) {
        printf("%d%c", queue[i], (i == rear) ? '\n' : ' ');
    }

    reverse();

    printf("Reversed Queue:");
    for (int i = front; i <= rear; i++) {
        printf("%d%c", queue[i], (i == rear) ? '\n' : ' ');
    }
    return 0;
}
