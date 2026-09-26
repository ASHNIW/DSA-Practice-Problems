#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *start = NULL;

void create(int val) {
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    if (start == NULL) {
        start = temp;
    } else {
        struct node *p = start;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
}

void insertBefore(int target, int newVal) {
    if (start == NULL) {
        printf("Node not found!\n");
        return;
    }

    struct node *p1 = (struct node*)malloc(sizeof(struct node));
    p1->data = newVal;
    p1->next = NULL;

    if (start->data == target) {
        p1->next = start;
        start = p1;
        return;
    }

    struct node *p2 = start;
    while (p2->next != NULL && p2->next->data != target) {
        p2 = p2->next;
    }

    if (p2->next == NULL) {
        printf("Node not found!\n");
        free(p1);
    } else {
        p1->next = p2->next;
        p2->next = p1;
    }
}

void display() {
    printf("Linked List:");
    struct node *p = start;
    while (p != NULL) {
        printf("->%d", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        create(val);
    }
    int target, newVal;
    scanf("%d %d", &target, &newVal);
    insertBefore(target, newVal);
    display();
    return 0;
}
