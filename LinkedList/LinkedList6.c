#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node* createNode(int data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insertEnd(struct node** head, int data) {
    struct node* new_node = createNode(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    struct node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

int GetNth(struct node* head, int index) {
    struct node* current = head;
    int count = 0;
    while (current != NULL) {
        if (count == index) {
            return current->data;
        }
        count++;
        current = current->next;
    }
    return -1;
}

void reverseList(struct node** head) {
    struct node* prev = NULL;
    struct node* current = *head;
    struct node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void printList(struct node* head) {
    struct node* p = head;
    while (p != NULL) {
        printf("%d%c", p->data, (p->next == NULL) ? '\n' : ' ');
        p = p->next;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    struct node* head = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        insertEnd(&head, val);
    }

    int index;
    scanf("%d", &index);
    printf("Node at index=%d:%d\n", index, GetNth(head, index));

    reverseList(&head);
    printf("Reversed:");
    printList(head);
    return 0;
}
