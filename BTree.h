//
// Created by Pan梓涵 on 2018/11/24.
//
#include "Record.h"
#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

//***************B树***************

const int m = 3;                //B树的阶
const int max = m - 1;          //结点的最大关键字数量
const int min = (m - 1) / 2;    //结点的最小关键字数量

typedef struct BTNode {
    int keyNum;                 //结点中关键字的数量
    struct BTNode *parent;      //指向双亲的结点
    KeyType keyPtr[m + 1];      //关键字自向量，0号单元闲置
    BTNode *child[m + 1];       //子树指针向量
    Record recPtr[m + 1];       //记录向量，0号单元闲置
}BTNode, *BTree;

//***************在B树中的查找结果类型***************
typedef struct {
    BTNode *pt;                 //指向找到的结点
    int index;                  //[1...m]，在结点中的关键字序号
    int tag;                    //1：查找成功；0：查找失败
}Result;

/**
 * 初始化
 * @param tree
 */
void initBTree(BTree &tree);

/**
 * 在m阶B树tree查找关键字k，用result返回（pt， i， tag）
 * 若查找成功，则标记tag=1，指针pt所指结点中的第i个关键字等于k
 * 否则tag=1，若要插入关键字为k的记录，应位于pt结点中第i-1个和第i个关键字之间
 * @param tree
 * @param k
 * @param result
 */
void searchBTree(BTree tree, int k, Result &result);

/**
 * 在B树中的q结点的key[i-1]和key[i]之间插入关键字k
 * 若插入后结点关键字个数等于B树的阶，则沿着双亲指针链进行结点分裂，使tree仍是m阶b树
 * @param tree
 * @param k
 * @param q
 * @param i
 */
void insertBTree(BTree &tree, int k, BTree q, int i);

/**
 * 在B树中，插入关键字k
 * @param tree
 * @param k
 */
void insertBTree(BTree &tree, int k);

/**
 * 前序遍历
 * @param tree
 */
void preOrder(BTree tree);

/**
 * 后序遍历
 * @param tree
 */
void postOrder(BTree tree);

/**
 * 输出B树
 * @param tree b树
 * @param i 当前第几层
 */
void output(BTree tree, int i);
#endif //BTREE_BTREE_H
