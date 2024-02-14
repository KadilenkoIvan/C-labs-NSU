#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

void inorder(int* sorted, struct Node* root) {
    if (root != NULL) {
        inorder(sorted, root->left);
        *sorted = root->key;
        sorted++;
        inorder(sorted, root->right);
    }
}

void sort_array(int* arr, int n) {
    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    inorder(arr, root);
}

int main() {
    int arr[] = { 50, 30, 20, 40, 70, 60, 80 };
    int n = sizeof(arr) / sizeof(arr[0]);

    sort_array(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
