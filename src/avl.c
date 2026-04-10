#include "avl.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    KeyType key;
    struct Node * left;
    struct Node * right;
    int height;
} Node;
struct AVL
{
    struct Node * root;
};


/// PRIVATE FUNCTIONS ...........................

int max(int x, int y)
{
    return (x > y) ? x : y;
}

int calcHeight(Node * node)
{
    if (node == NULL) { return 0; }

    return 1 + max(calcHeight(node->left), calcHeight(node->right));
}
void updateHeight(Node * node)
{
    node->height = calcHeight(node);
}
int height(Node * node)
{
    return calcHeight(node);
}
int calcBalanceFactor(Node * node)
{
    if (node == NULL) { return 0; }

    return calcHeight(node->left) - calcHeight(node->right);
}
int balanceFactor(Node * node)
{
    return calcBalanceFactor(node);
}

Node * newNode(KeyType key)
{
    Node * newNode = malloc(sizeof(Node));

    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node * minNode(Node * root)
{
    if (root == NULL) { return NULL; }
    if (root->left == NULL) { return root; }

    return minNode(root->left);
}
Node * successor(Node * node)
{
    return minNode(node->right);
}
Node * maxNode(Node * root)
{
    if (root == NULL) { return NULL; }
    if (root->right == NULL) { return root; }

    return maxNode(root->right);
}
Node * antecessor(Node * node)
{
    return maxNode(node->left);
}


/// PRIVATE FUNCTIONS [AVL PROCEDURES] ..........

Node * rotate_l(Node * root)
{
    Node * pivot = root->right;

    root->right = pivot->left;
    pivot->left = root;

    updateHeight(root);
    updateHeight(pivot);

    return pivot;
}
Node * rotate_r(Node * root)
{
    Node * pivot = root->left;

    root->left = pivot->right;
    pivot->right = root;

    updateHeight(root);
    updateHeight(pivot);

    return pivot;
}
Node * rotate_lr(Node * root)
{
    root->left = rotate_l(root->left);

    return rotate_r(root);
}
Node * rotate_rl(Node * root)
{
    root->right = rotate_r(root->right);

    return rotate_l(root);
}

Node * rebalance(Node * node)
{
    if (node == NULL) { return NULL; }

    int bf = balanceFactor(node);
    int bf_left = balanceFactor(node->left);
    int bf_right = balanceFactor(node->right);
    
    if (bf > 1)
    {
        if (bf_left >= 0) { node = rotate_r(node); }
        else { node = rotate_lr(node); }
    }
    else if (bf < -1)
    {
        if (bf_right <= 0) { node = rotate_l(node); }
        else { node = rotate_rl(node); }
    }

    return node;
}


/// PRIVATE FUNCTIONS [INTERFACE DEFINITION] ....

void deleteTree(Node * root)
{
    if (root == NULL) { return; }
    
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

bool isInTree(Node * root, KeyType key)
{
    if (root == NULL) { return false; }
    if (key == root->key) { return true; }
    
    if (key < root->key) { return isInTree(root->left, key); }
    return isInTree(root->right, key);
}
Node * insertInTree(Node * root, KeyType key)
{
    if (root == NULL) { return newNode(key); }
    
    if (key < root->key) { root->left = insertInTree(root->left, key); }
    else if (key > root->key) { root->right = insertInTree(root->right, key); }
    
    return rebalance(root);
}
Node * removeFromTree_successor(Node * root, KeyType key)
{
    if (root == NULL) { return NULL; }

    if (key < root->key) { root->left = removeFromTree_successor(root->left, key); }
    else if (key > root->key) { root->right = removeFromTree_successor(root->right, key); }
    else
    {
        if (root->left == NULL)
        {
            Node * trash = root;
            root = root->right;
            free(trash);
        }
        else if (root->right == NULL)
        {
            Node * trash = root;
            root = root->left;
            free(trash);
        }
        else
        {
            Node * succ = successor(root);
            root->key = succ->key;
            root->right = removeFromTree_successor(root->right, succ->key);
        }
    }

    return rebalance(root);
}
Node * removeFromTree_antecessor(Node * root, KeyType key)
{
    if (root == NULL) { return NULL; }

    if (key < root->key) { root->left = removeFromTree_antecessor(root->left, key); }
    else if (key > root->key) { root->right = removeFromTree_antecessor(root->right, key); }
    else
    {
        if (root->left == NULL)
        {
            Node * trash = root;
            root = root->right;
            free(trash);
        }
        else if (root->right == NULL)
        {
            Node * trash = root;
            root = root->left;
            free(trash);
        }
        else
        {
            Node * ant = antecessor(root);
            root->key = ant->key;
            root->left = removeFromTree_antecessor(root->left, ant->key);
        }
    }

    return rebalance(root);
}

void printKeys_inOrder(Node * root)
{
    if (root == NULL) { return; }

    printKeys_inOrder(root->left);
    printf("%d ", root->key);
    printKeys_inOrder(root->right);
}
void printKeys_preOrder(Node * root)
{
    if (root == NULL) { return; }

    printf("%d ", root->key);
    printKeys_preOrder(root->left);
    printKeys_preOrder(root->right);
}
void printKeys_postOrder(Node * root)
{
    if (root == NULL) { return; }

    printKeys_postOrder(root->left);
    printKeys_postOrder(root->right);
    printf("%d ", root->key);
}
void printTree(Node * root, size_t level, int side)
{
    if (root == NULL) { return; }

    for (size_t i = 0; i < level; i++) { printf("\t"); }
    
    switch (side)
    {
        case -1: printf("<< %d\n", root->key); break;
        case 0: printf("%d\n", root->key); break;
        case 1: printf(">> %d\n", root->key); break;
    }

    printTree(root->left, level + 1, -1);
    printTree(root->right, level + 1, 1);
}
void printTree_info(Node * root, size_t level, int side)
{
    if (root == NULL) { return; }

    for (size_t i = 0; i < level; i++) { printf("\t"); }
    
    switch (side)
    {
        case -1: printf("<< (%d) [%d, %d]\n", root->key, height(root), balanceFactor(root)); break;
        case 0: printf("(%d) [%d, %d]\n", root->key, height(root), balanceFactor(root)); break;
        case 1: printf(">> (%d) [%d, %d]\n", root->key, height(root), balanceFactor(root)); break;
    }

    printTree_info(root->left, level + 1, -1);
    printTree_info(root->right, level + 1, 1);
}
void printTree_info_detailed(Node * root, size_t level, int side)
{
    if (root == NULL) { return; }

    for (size_t i = 0; i < level; i++) { printf("\t"); }
    
    switch (side)
    {
        case -1: printf("<< (%d) [h = %d, bf = %d]\n", root->key, height(root), balanceFactor(root)); break;
        case 0: printf("(%d) [h = %d, bf = %d]\n", root->key, height(root), balanceFactor(root)); break;
        case 1: printf(">> (%d) [h = %d, bf = %d]\n", root->key, height(root), balanceFactor(root)); break;
    }

    printTree_info_detailed(root->left, level + 1, -1);
    printTree_info_detailed(root->right, level + 1, 1);
}


/// INTERFACE IMPLEMENTATION ....................

AVL * avl_new(void)
{
    AVL * newAVL = malloc(sizeof(AVL));

    newAVL->root = NULL;

    return newAVL;
}
void avl_delete(AVL * bst)
{
    deleteTree(bst->root);
    free(bst);
}

bool avl_search(AVL * avl, KeyType key)
{
    return isInTree(avl->root, key);
}
void avl_insert(AVL * avl, KeyType key)
{
    avl->root = insertInTree(avl->root, key);
}
void avl_remove(AVL * avl, KeyType key)
{
    avl->root = removeFromTree_antecessor(avl->root, key);
}

void avl_print_inOrder(AVL * avl)
{
    printKeys_inOrder(avl->root);
    printf("\n");
}
void avl_print_preOrder(AVL * avl)
{
    printKeys_preOrder(avl->root);
    printf("\n");
}
void avl_print_postOrder(AVL * avl)
{
    printKeys_postOrder(avl->root);
    printf("\n");
}
void avl_visualize(AVL * avl)
{
    printTree_info(avl->root, 0, 0);
}
