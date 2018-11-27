//
// Created by Pan梓涵 on 2018/11/26.
//
#include <cstdlib>
#include <cstdio>
#include "DeleteBTree.h"


/**
 * 从p结点中删除p->keyPtr[i]和他的孩子指针p->child[i]
 * @param p
 * @param i
 */
void remove(BTNode *p, int i) {
    int j;
    //前移删除keyPtr[i]和child[i]
    for (j = i + 1; j <= p->keyNum; j++) {
        p->keyPtr[j - 1] = p->keyPtr[j];
        p->child[j - 1] = p->child[j];
    }
    p->keyNum--;
}

/**
 * 查找被删关键字p->keyPtr[i](在非叶子节点中的)替代叶子节点(右子树中值最小的关键字)
 * 寻找替代值，右子树中的最小关键字
 * @param p
 * @param i
 */
void substitution(BTNode *p, int i) {
    BTNode *q;
    q = p->child[i];
    while (q->child[0] != nullptr) {
        q = q->child[0];
    }
    //复制关键值
    p->keyPtr[i] = q->keyPtr[1];
}

/**
 * 将双亲结点p中的最后一个关键字移入右结点中q中
 * 将左结点aq中的最后一个关键字移入双亲结点中
 * @param p
 * @param i
 */
void moveRight(BTNode *p, int i) {
    int j;
    BTNode *q = p->child[i];//右结点
    BTNode *aq = p->child[i - 1];//左结点

    //将右兄弟q中所有关键字向后移动一位
    for (j = q->keyNum; j > 0; j--) {
        q->keyPtr[j + 1] = q->keyPtr[j];
        q->child[j + 1] = q->child[j];
    }

    //从双亲结点中移动关键字到q中
    q->child[1] = q->child[0];
    q->keyPtr[1] = p->keyPtr[i];
    q->keyNum++;

    //将左兄弟aq中最后一个结点移到双亲结点中
    p->keyPtr[i] = aq->keyPtr[aq->keyNum];
    q->child[0] = aq->child[aq->keyNum];
    aq->keyNum--;
}

/**
 * 将双亲结点p中的第一个关键字移入左结点aq中
 * 将右结点p中的第一个关键字移入双亲结点中
 * @param p
 * @param i
 */
void moveLeft(BTNode *p, int i) {
    int j;
    BTNode *aq = p->child[i - 1];//左结点
    BTNode *q = p->child[i];//右结点

    //把双亲结点p中的关键字移动到左兄弟aq中
    aq->keyNum++;
    aq->keyPtr[aq->keyNum] = p->keyPtr[i];
    aq->child[aq->keyNum] = p->child[i]->child[0];

    //把右兄弟q中的关键字移动双亲结点p中
    p->keyPtr[i] = q->keyPtr[1];
    q->child[0] = q->child[1];
    q->keyNum--;

    //将右兄弟q中所有关键字向前移动一位
    for (j = 1; j <= q->keyNum; j++) {
        q->keyPtr[j] = q->keyPtr[j + 1];
        q->child[j] = q->child[j + 1];
    }
}

/**
 * 将双亲结点p、右结点q合并入左结点aq
 * 并调整双亲结点p中的剩余关键字
 * @param p
 * @param i
 */
void combine(BTNode *p, int i) {
    int j;
    BTNode *q = p->child[i];
    BTNode *aq = p->child[i - 1];

    //将双亲结点的关键字p->keyPtr[i]插入到左结点aq中
    aq->keyNum++;
    aq->keyPtr[aq->keyNum] = p->keyPtr[i];
    aq->child[aq->keyNum] = q->child[0];

    //将右结点q中的所有关键字插入到左结点中aq
    for (j = 1; j <= q->keyNum; j++) {
        aq->keyNum++;
        aq->keyPtr[aq->keyNum] = q->keyPtr[j];
        aq->child[aq->keyNum] = q->child[j];
    }

    //将双亲结点p中的p->keyPtr[i]后的所有关键字向前移动一位
    for (j = i; j < p->keyNum; j++) {
        p->keyPtr[j] = p->keyPtr[j + 1];
        p->child[j] = p->child[j + 1];
    }

    p->keyNum--;
    free(q);
}

/**
 * 删除节点p中的第i个关键字后，调整B树
 * @param p
 * @param i
 */
void adjustBTree(BTNode *p, int i) {
    if (i == 0) {//删除的是最左边关键字
        if (p->child[1]->keyNum > min) {//右结点可以借
            moveLeft(p, 1);
        } else {//右兄弟不够借
            combine(p, 1);
        }
    } else if (i == p->keyNum) {//删除的是最右边关键字
        if (p->child[i -1]->keyNum > min) {//左结点可以借
            moveRight(p, i);
        } else {//左兄弟不够借
            combine(p, i);
        }
    } else if (p->child[i - 1]->keyNum > min) {//删除关键字在中部，而且左结点够借
        moveRight(p, i);
    } else if (p->child[i + 1]->keyNum > min) {//删除关键字在中部，而且右结点够借
        moveLeft(p, i + 1);
    } else {//删除关键字在中部，且左右结点都不够借
        combine(p, i);
    }
}

/**
 * 反映是否在结点p中是否查找关键字i
 * @param p
 * @param key
 * @param i
 */
int findBTNode(BTNode *p, KeyType key, int &i) {
    if (key < p->keyPtr[1]) {
        i = 0;
        return 0;
    } else {
        int low = 1;
        int high = p->keyNum;
        int mid;

        while (low <= high) {
            mid = (low + high) / 2;
            if (key == p->keyPtr[mid]) {
                i = mid;
                return 1;
            } else if (key < p->keyPtr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        i = low > high ? low : high;
        i = i - 1;
        return 0;
    }
}

/**
 * 在结点p中查找并删除关键字k
 * @param p
 * @param key
 * @return
 */
int deleteBTNode(BTNode *p, KeyType key) {
    int i = 0;
    int foundTag;//查找标志
    if (p == nullptr) {
        return 0;
    } else {
        foundTag = findBTNode(p, key, i);//返回查找结构
        if (foundTag == 1) {//查找成功
            if (p->child[i - 1] != nullptr) {//删除是非叶子结点
                substitution(p, i);//寻找相邻关键字（右子树中最小的关键字）
                deleteBTNode(p->child[i], p->keyPtr[i]);//执行删除操作
            } else {
                remove(p, i);//从结点p中位置i处删除关键字
            }
        } else {
            foundTag = deleteBTNode(p->child[i], key);//沿孩子结点递归查找并删除关键字k
        }
        if (p->child[i] != nullptr) {
            if (p->child[i]->keyNum < min) {//删除后关键字个数小于min
                adjustBTree(p, i);//调整B树
            }
        }
        return foundTag;
    }
}

/**
 * 构建删除框架
 * @param tree
 * @param key
 */
void deleteBTree(BTree &tree, KeyType key) {
    BTNode *p;
    int deleteTag = deleteBTNode(tree, key);//删除关键字k
    if (deleteTag == 0) {//删除失败
        printf("关键字%d不在B树中\n", key);
    } else if (tree->keyNum == 0) {//调整
        p = tree;
        tree = tree->child[0];
        free(p);
    }
}










