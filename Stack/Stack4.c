#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int arr[MAX_SIZE];
int top1 = -1;
int top2 = MAX_SIZE;

void push1(int x) {
    if (top1 < top2 - 1) {
        arr[++top1] = x;
    }
}

void push2(int x) {
    if (top1 < top2 - 1) {
        arr[--top2] = x;
    }
}

int pop1() {
    if (top1 >= 0) {
        return arr[top1--];
    }
    return -1;
}

int pop2() {
    if (top2 < MAX_SIZE) {
        return arr[top2++];
    }
    return -1;
}

int main() {
    int val;
    int inputs[20];
    int count = 0;
    while (scanf("%d", &val) == 1) {
        inputs[count++] = val;
    }

    if (count == 0) {

        push1(5);
        push2(4);
        printf("Popped element from stack1 is:%d\n", pop1());
        printf("Popped element from stack2 is:%d\n", pop2());
        return 0;
    }

    for (int i = 0; i < count; i++) {
        if (i % 2 == 0) push1(inputs[i]);
        else push2(inputs[i]);
    }

    if (top1 >= 0) {
        printf("Popped element from stack1 is:%d\n", pop1());
    }
    if (top2 < MAX_SIZE) {
        printf("Popped element from stack2 is:%d\n", pop2());
    }
    return 0;
}
