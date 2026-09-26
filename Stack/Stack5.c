#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0';
}

bool isMatchingPair(char char1, char char2) {
    if (char1 == '(' && char2 == ')') return true;
    if (char1 == '{' && char2 == '}') return true;
    if (char1 == '[' && char2 == ']') return true;
    return false;
}

int main() {
    char exp[MAX];
    if (scanf("%s", exp) != 1) return 0;

    bool balanced = true;
    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[') {
            push(exp[i]);
        } else if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (top == -1 || !isMatchingPair(pop(), exp[i])) {
                balanced = false;
                break;
            }
        }
    }

    if (top != -1) {
        balanced = false;
    }

    if (balanced) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }
    return 0;
}
