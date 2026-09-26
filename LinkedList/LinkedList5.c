#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void insert_Data(struct node **head, int data) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void delete_Alt(struct node **head) {
    if (*head == NULL) return;
    struct node *prev = *head;
    struct node *node = (*head)->next;

    while (prev != NULL && node != NULL) {
        prev->next = node->next;
        free(node);
        prev = prev->next;
        if (prev != NULL) {
            node = prev->next;
        }
    }
}

void printList(struct node *head) {
    struct node *temp = head;
    while (temp != NULL) {
        printf("%d%c", temp->data, (temp->next == NULL) ? '\n' : ' ');
        temp = temp->next;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    struct node *head = NULL;
    for (int i = 1; i <= n; i++) {
        insert_Data(&head, i);
    }

    delete_Alt(&head);
    printList(head);
    return 0;
}
