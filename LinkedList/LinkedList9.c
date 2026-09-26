#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;

void insert(int data) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    if (head == NULL) {
        head = new_node;
        head->next = head;
        return;
    }
    struct node *temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->next = head;
}

void display(struct node *h) {
    if (h == NULL) {
        printf("[h]=>\n");
        return;
    }
    struct node *temp = h;
    printf("[h]=>");
    do {
        printf("%d=>", temp->data);
        temp = temp->next;
    } while (temp != h);
    printf("[h]\n");
}

void splitAlt(struct node **odd, struct node **even) {
    struct node *temp = head;
    int pos = 1;
    do {
        struct node *next = temp->next;
        temp->next = NULL;
        if (pos % 2 == 1) {
            temp->next = *odd;
            *odd = temp;
        } else {
            temp->next = *even;
            *even = temp;
        }
        temp = next;
        pos++;
    } while (temp != head);
}

struct node *rev(struct node *h) {
    struct node *p = NULL;
    struct node *c = h;
    while (c != NULL) {
        struct node *n = c->next;
        c->next = p;
        p = c;
        c = n;
    }
    return p;
}

void closeCircle(struct node *h) {
    if (h == NULL) return;
    struct node *t = h;
    while (t->next != NULL) {
        t = t->next;
    }
    t->next = h;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 1; i <= n; i++) {
        insert(i);
    }

    printf("Complete linked_list:\n");
    display(head);

    struct node *odd = NULL, *even = NULL;
    splitAlt(&odd, &even);
    odd = rev(odd);
    even = rev(even);
    closeCircle(odd);
    closeCircle(even);

    printf("Odd:\n");
    display(odd);

    printf("Even:\n");
    display(even);
    return 0;
}