#include <iostream>
#include "BTree.h"
#include "DeleteBTree.h"

void testInsert() {
    BTree tree;
    initBTree(tree);

    for (int i = 0; i < 20; i++) {
        int num = rand() % 100 + 1;
        insertBTree(tree, num);
    }
//    insertBTree(tree, 6);
//    insertBTree(tree, 5);
//    insertBTree(tree, 7);
//    insertBTree(tree, 8);
//    insertBTree(tree, 10);
//    insertBTree(tree, 50);
//    insertBTree(tree, 100);

    printf("**************preOrder************\n");
    preOrder(tree);
    printf("\n");
    printf("**************postOrder************\n");
    postOrder(tree);
    printf("\n");

    printf("**********************\n");
    output(tree, 1);
}

void testDelete() {
    BTree tree;
    initBTree(tree);

    for (int i = 0; i < 15; i++) {
        int num = rand() % 100 + 1;
        insertBTree(tree, num);
    }
    printf("**************preOrder************\n");
    preOrder(tree);
    printf("\n");
    printf("**************postOrder************\n");
    postOrder(tree);
    printf("\n");

    printf("**************delete************\n");
    deleteBTree(tree, 35);

    printf("**************preOrder************\n");
    preOrder(tree);
    printf("\n");
    printf("**************postOrder************\n");
    postOrder(tree);
    printf("\n");

    deleteBTree(tree, 28);
    deleteBTree(tree, 25);
}

int main() {
    testInsert();
//    testDelete();
    return 0;
}