#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    char str[MAX];
} StackItem;

StackItem stack[MAX];
int top = -1;

void push(char *s) {
    top++;
    strcpy(stack[top].str, s);
}

void pop(char *s) {
    if (top >= 0) {
        strcpy(s, stack[top].str);
        top--;
    }
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void postToPre(char *post_exp, char *result) {
    top = -1;
    int len = strlen(post_exp);

    for (int i = 0; i < len; i++) {
        char c = post_exp[i];
        if (!isOperator(c)) {
            char temp[2] = {c, '\0'};
            push(temp);
        } else {
            if (top >= 1) {
                char op2[MAX], op1[MAX];
                pop(op2);
                pop(op1);

                char combined[MAX];
                combined[0] = c;
                combined[1] = '\0';
                strcat(combined, op1);
                strcat(combined, op2);

                push(combined);
            }
        }
    }

    while (top > 0) {
        char op2[MAX], op1[MAX];
        pop(op2);
        pop(op1);
        char combined[MAX];
        strcpy(combined, op1);
        strcat(combined, op2);
        push(combined);
    }

    if (top >= 0) {
        strcpy(result, stack[top].str);
    } else {
        result[0] = '\0';
    }
}

int main() {
    char post_exp[MAX];
    if (scanf("%s", post_exp) != 1) return 0;

    char pre_exp[MAX];
    postToPre(post_exp, pre_exp);
    printf("%s\n", pre_exp);
    return 0;
}
