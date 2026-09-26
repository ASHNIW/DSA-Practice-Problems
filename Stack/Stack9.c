#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int q[MAX];
int front = 0;
int rear = 0;

void q_push(int val) {
    q[rear++] = val;
}

int q_pop() {
    return q[front++];
}

int q_size() {
    return rear - front;
}

int q_front() {
    return q[front];
}

void push(int val) {
    int s = q_size();
    q_push(val);
    for (int i = 0; i < s; i++) {
        q_push(q_pop());
    }
}

void pop() {
    if (q_size() > 0) {
        q_pop();
    }
}

int top() {
    if (q_size() > 0) {
        return q_front();
    }
    return -1;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        push(val);
    }

    printf("top of element %d\n", top());

    for (int i = 0; i < m; i++) {
        pop();
    }

    printf("top of element %d\n", top());
    return 0;
}
