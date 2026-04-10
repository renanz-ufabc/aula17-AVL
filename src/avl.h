#ifndef AVL_H
#define AVL_H
#include <stdbool.h>


typedef int KeyType;
typedef struct AVL AVL;  // 'AVL' refers to an AVL Binary Search Tree


AVL * avl_new(void);
void avl_delete(AVL * avl);

bool avl_search(AVL * avl, KeyType key);
void avl_insert(AVL * avl, KeyType key);
void avl_remove(AVL * avl, KeyType key);

void avl_print_inOrder(AVL * avl);
void avl_print_preOrder(AVL * avl);
void avl_print_postOrder(AVL * avl);
void avl_visualize(AVL * avl);


#endif
