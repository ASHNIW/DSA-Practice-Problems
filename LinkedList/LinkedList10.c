#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;

void create(int val) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    if (head == NULL) {
        head = temp;
    } else {
        struct node *p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
}

int main() {
    int n, val, k, i;
    if (scanf("%d", &n) != 1) return 0;

    for (i = 0; i < n; i++) {
        scanf("%d", &val);
        create(val);
    }

    scanf("%d", &k);

    struct node *p = head;
    for (i = 0; i < k && p != NULL; i++) {
        p = p->next;
    }

    printf("Linked List:");
    while (p != NULL) {
        printf("->%d", p->data);
        p = p->next;
    }
    printf("\n");

    return 0;
}
