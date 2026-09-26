#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void sortedInsert(struct Node** head_ref, struct Node* new_node) {
    struct Node* current;
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        current = *head_ref;
        while (current->next != NULL && current->next->data < new_node->data) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    struct Node* head = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data = val;
        new_node->next = NULL;
        sortedInsert(&head, new_node);
    }

    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d%c", temp->data, (temp->next == NULL) ? '\n' : ' ');
        temp = temp->next;
    }
    return 0;
}
