#include <stdio.h>
#include "avl.h"


int main(void)
{
    // creating...

    AVL * t = avl_new();
    
    KeyType keys0[] = {1, 2, 3, 4, 5, 6, 7};
    const size_t size0 = 7;
    KeyType keys1[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    const size_t size1 = 9;

    KeyType * keys = keys0;
    const size_t size = size0;
    for (size_t i = 0; i < size; i++) { avl_insert(t, keys[i]); }

    // editing...

    avl_remove(t, 6);

    // visualizing...

    printf("\n");
    avl_visualize(t);
    printf("\n");

    // freeing...

    avl_delete(t);

    return 0;
}
