#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int priority;
    struct Node *left;
    struct Node *right;
} Node;

Node* create_node(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->priority = rand();
    n->left = NULL;
    n->right = NULL;
    return n;
}

void split(Node* t, int key, Node** l, Node** r) {
    if (!t) {
        *l = *r = NULL;
    } else if (key < t->key) {
        split(t->left, key, l, &t->left);
        *r = t;
    } else {
        split(t->right, key, &t->right, r);
        *l = t;
    }
}

void merge(Node** t, Node* l, Node* r) {
    if (!l || !r) {
        *t = l ? l : r;
    } else if (l->priority > r->priority) {
        merge(&l->right, l->right, r);
        *t = l;
    } else {
        merge(&r->left, l, r->left);
        *t = r;
    }
}

int find_val(Node* t, int key) {
    while (t) {
        if (t->key == key) return 1;
        if (key < t->key) t = t->left;
        else t = t->right;
    }
    return 0;
}

void insert_key(Node** root, int key) {
    if (find_val(*root, key)) return;
    Node *l, *r;
    split(*root, key, &l, &r);
    Node* n = create_node(key);
    merge(&l, l, n);
    merge(root, l, r);
}

int lower_bound(Node* root, int key) {
    int ans = -1;
    Node* curr = root;
    while (curr) {
        if (curr->key >= key) {
            ans = curr->key;
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return ans;
}

void free_tree(Node* t) {
    if (!t) return;
    free_tree(t->left);
    free_tree(t->right);
    free(t);
}

int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    
    Node* root = NULL;
    int i;
    for(i=0;i<q;i++) {
        int type, val;
        scanf("%d %d", &type, &val);
        if (type == 1) {
            insert_key(&root, val);
        } else if (type == 2) {
            int ans = lower_bound(root, val);
            printf("%d\n", ans);
        }
    }
    
    free_tree(root);
    return 0;
}
