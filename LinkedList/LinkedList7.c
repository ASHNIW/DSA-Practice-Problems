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

void del_before(int key) {
    if (start == NULL || start->next == NULL) {
        printf("Invalid Node!\n");
        return;
    }

    if (start->next->data == key) {
        struct node *temp = start;
        start = start->next;
        free(temp);
        return;
    }

    struct node *p1 = start;
    struct node *p2 = start->next;

    while (p2 != NULL && p2->data != key) {
        p1 = p1->next;
        p2 = p2->next;
    }

    if (p2 == NULL) {
        printf("Invalid Node!\n");
        return;
    }

    p1->next = p2;
    free(p2);
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
    int key_pos;
    scanf("%d", &key_pos);
    del_before(key_pos);
    display();
    return 0;
}
