#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void create(struct node **head, int data) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    struct node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void print(struct node *head) {
    printf("Link list data:");
    struct node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void fold(struct node **head) {

    int len = 0;
    struct node *temp = *head;
    while (temp != NULL) {
        len++;
        temp = temp->next;
    }
    if (len <= 1) return;

    int half = len / 2;
    struct node *arr[len];
    temp = *head;
    for (int i = 0; i < len; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    for (int i = 0; i < half; i++) {
        int t = arr[i]->data;
        arr[i]->data = arr[len - 1 - i]->data;
        arr[len - 1 - i]->data = t;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    struct node *head = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        create(&head, val);
    }

    print(head);
    fold(&head);
    printf("Link list data after fold:");
    print(head);
    return 0;
}
