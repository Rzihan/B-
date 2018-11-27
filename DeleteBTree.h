//
// Created by Pan梓涵 on 2018/11/26.
//

#ifndef BTREE_DELETEBTREE_H
#define BTREE_DELETEBTREE_H


#include "BTree.h"

/**
 * 从p结点中删除p->keyPtr[i]和他的孩子指针p->child[i]
 * @param p
 * @param i
 */
void remove(BTNode *p, int i);

/**
 * 查找被删关键字p->keyPtr[i](在非叶子节点中的)替代叶子节点(右子树中值最小的关键字)
 * @param p
 * @param i
 */
void substitution(BTNode *p, int i);

/**
 * 将双亲结点p中的最后一个关键字移入右结点中q中
 * 将左结点ap中的最后一个关键字移入双亲结点中
 * @param p
 * @param i
 */
void moveRight(BTNode *p, int i);

/**
 * 将双亲结点p中的第一个关键字移入左结点ap中
 * 将右结点p中的第一个关键字移入双亲结点中
 * @param p
 * @param i
 */
void moveLeft(BTNode *p, int i);

/**
 * 将双亲结点p、右结点q合并入左结点ap
 * 并调整双亲结点p中的剩余关键字
 * @param p
 * @param i
 */
void combine(BTNode *p, int i);

/**
 * 删除节点p中的第i个关键字后，调整B树
 * @param p
 * @param i
 */
void adjustBTree(BTNode *p, int i);

/**
 * 反映是否在结点p中是否查找关键字i
 * @param p
 * @param key
 * @param i
 */
int findBTNode(BTNode *p, KeyType key, int &i);

/**
 * 在结点p中查找并删除关键字k
 * @param p
 * @param key
 * @return
 */
int deleteBTNode(BTNode *p, KeyType key);

/**
 * 构建删除框架
 * @param tree
 * @param key
 */
void deleteBTree(BTree &tree, KeyType key);

#endif //BTREE_DELETEBTREE_H
