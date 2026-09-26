#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

void insertStart(struct Node** head, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = (*head);
    new_node->prev = NULL;
    if ((*head) != NULL) {
        (*head)->prev = new_node;
    }
    (*head) = new_node;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    struct Node* head = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        insertStart(&head, val);
    }

    struct Node* curr = head;
    struct Node* tail = NULL;
    while (curr != NULL) {
        printf("%d ", curr->data);
        if (curr->next == NULL) tail = curr;
        curr = curr->next;
    }
    printf("\n");

    curr = tail;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->prev;
    }
    printf("\n");
    return 0;
}
