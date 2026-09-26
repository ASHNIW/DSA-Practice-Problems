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

void del(int key) {
    while (start != NULL && start->data == key) {
        struct node *temp = start;
        start = start->next;
        free(temp);
    }
    struct node *p2 = start;
    while (p2 != NULL && p2->next != NULL) {
        if (p2->next->data == key) {
            struct node *temp = p2->next;
            p2->next = temp->next;
            free(temp);
        } else {
            p2 = p2->next;
        }
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
    int key;
    scanf("%d", &key);
    del(key);
    display();
    return 0;
}
