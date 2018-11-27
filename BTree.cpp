//
// Created by Pan梓涵 on 2018/11/24.
//

#include <malloc.h>
#include <stdio.h>
#include <cstring>
#include "BTree.h"

void initBTree(BTree &tree) {
    tree = (BTNode *)malloc(sizeof(BTNode));
    tree->keyNum = 0;
    tree->parent = nullptr;
    for (int i = 0; i <= m; i++) {
        Record *record;
        record = (Record *)malloc(sizeof(Record));
        record->key = 0;
        record->data = '\0';
        tree->recPtr[i] = *record;
        tree->child[i] = nullptr;
        tree->keyPtr[i] = 0;
    }
}

/**
 * 在p->key[1...p->keyNum]找k
 * @param p
 * @param k
 * @return
 */
int search(BTree p, int k) {
    int low = 1;
    int high = p->keyNum;
    int mid;

    while (low <= high) {
        mid = (low + high ) / 2;
        if (k == p->keyPtr[mid]) {
            return mid;
        } else if (k < p->keyPtr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low > high ? low : high;
}

/**
 * 在m阶B树tree查找关键字k，用result返回（pt， i， tag）
 * 若查找成功，则标记tag=1，指针pt所指结点中的第i个关键字等于k
 * 否则tag=1，若要插入关键字为k的记录，应位于pt结点中第i-1个和第i个关键字之间
 * @param tree
 * @param k
 * @param result
 */
void searchBTree(BTree tree, int k, Result &result) {
    int i = 0, found = 0;
    //初始，p指向根结点；p将用于指向待查结点，q指向其双亲
    BTree p = tree;
    BTree q = nullptr;

    while (p != nullptr && 0 == found) {
        //在keyPtr[1...p->keyNum]中查找p->keyPtr[i-1] < k ≤ p->keyPtr[i]
        i = search(p, k);
        //找到待查关键字
        if (i <= p->keyNum && p->keyPtr[i] == k) {
            found = 1;
        } else {
            q = p;
            p = p->child[i - 1];
        }
    }

    if (1 == found) {
        result.tag = 1;
        result.index = i;
        result.pt = p;
    } else {
        result.tag = 0;
        result.index = i;
        result.pt = q;
    }
}

/**
 * 将q结点分裂成两个结点，前一半保留在原结点，后一半移入ap
 * 所指的新结点
 * @param q
 * @param s
 * @param ap
 */
void split(BTree &q, int s, BTree &ap) {
    int n = q->keyNum;
    //生成新结点
    initBTree(ap);
    ap->keyPtr[0] = q->keyPtr[s];
    int i, j;
    //后一半移入ap结点
    for (i = s + 1, j = 1; i <= n; i++, j++) {
        ap->keyPtr[j] = q->keyPtr[i];
        ap->child[j] = q->child[i];
    }
    ap->keyNum = n - s;
    ap->parent = q->parent;
    //修改新结点的子结点的parent域
    for (i = 0; i <= n - s; i++) {
        if (ap->child[i] != nullptr) {
            ap->child[i]->parent = ap;
        }
    }
    //q结点的前一半保留，修改keyNum
    q->keyNum = s - 1;
}

/**
 * 生成新的根结点
 * @param tree
 * @param p
 * @param x
 * @param ap
 */
void newRoot(BTree &tree, BTree p, int x, BTree ap) {
    initBTree(tree);
    tree->keyNum = 1;
    tree->child[0] = p;
    tree->child[1] = ap;
    tree->keyPtr[1] = x;
    if (p != nullptr) p->parent = tree;
    if (ap != nullptr) ap->parent = tree;
    //新根的双亲是空指针
    tree->parent = nullptr;
}

/**
 * 关键字x和新结点指针ap分别插入到q->keyPtr[i]和q->child[i]
 * @param q
 * @param i
 * @param x
 * @param ap
 */
void insert(BTree &q, int i, int x, BTree ap) {
    int n = q->keyNum;
    int j;
    for (j = n; j >= i; j--) {
        q->keyPtr[j + 1] = q->keyPtr[j];
        q->child[j + 1] = q->child[j];
    }
    //插入
    q->keyPtr[i] = x;
    q->child[i] = ap;
    if (ap != nullptr) ap->parent = q;
    q->keyNum++;
}

/**
 * 在B树中的q结点的key[i-1]和key[i]之间插入关键字k
 * 若插入后结点关键字个数等于B树的阶，则沿着双亲指针链进行结点分裂，使tree仍是m阶b树
 * @param tree
 * @param k
 * @param q
 * @param i
 */
void insertBTree(BTree &tree, int k, BTree q, int i) {
    int x, s, finished = 0, needNewRoot = 0;
    BTree ap;
    if (nullptr == q) {
        newRoot(tree, nullptr, k, nullptr);
    } else {
        x = k;
        ap = nullptr;
        while (0 == needNewRoot && 0 == finished) {
            //x和ap分别插入到q->keyPtr[i]和q->child[i]
            insert(q, i, x, ap);
            if (q->keyNum < m) {
                //插入完成
                finished = 1;
            } else {
                 //分裂q结点
                 s = (m + 1) / 2;
                 split(q, s, ap);
                 x = q->keyPtr[s];
                 if (q->parent != nullptr) {
                    q = q->parent;
                    //在双亲结点中查找x的插入位置
                    i = search(q, x);
                 } else {
                    needNewRoot = 1;
                 }
            }
        }
        //tree是空树或者根结点已分裂为q和ap结点
        if (1 == needNewRoot) {
            newRoot(tree, q, x, ap);
        }
    }
}

/**
 * 在B树中，插入关键字k
 * @param tree
 * @param k
 */
void insertBTree(BTree &tree, int k) {
    Result result;
    searchBTree(tree, k, result);

    //查找成功，直接返回
    if (result.tag == 1) {
        return;
    } else {
        insertBTree(tree, k, result.pt, result.index);
    }
}

/**
 * 前序遍历
 * @param tree
 */
void preOrder(BTree tree) {
    if (tree == nullptr) {
        return;
    }
    for (int i = 1; i <= tree->keyNum; i++) {
        printf("%d,", tree->keyPtr[i]);
    }
    for (int j = 0; j <= tree->keyNum ; j++) {
        preOrder(tree->child[j]);
    }
}

/**
 * 后序遍历
 * @param tree
 */
void postOrder(BTree tree) {
    if (tree == nullptr) {
        return;
    }
    for (int i = 0; i <= tree->keyNum; i++) {
        preOrder(tree->child[i]);
    }
    for (int j = 1; j <= tree->keyNum; j++) {
        printf("%d,", tree->keyPtr[j]);
    }
}

/**
 * 输出B树
 * @param tree b树
 * @param i 当前第几层
 */
void output(BTree tree, int i) {
    char *base = "";
    char *newBase = nullptr;
    for (int j = 1; j < i; j++) {
        newBase = (char *)malloc(strlen(base) + strlen("*****"));
        strcpy(newBase, base);
        strcat(newBase, "*****");
        base = newBase;
    }

    if (tree == nullptr) {
        return;
    }
    for (int k = 0; k < tree->keyNum; k++) {
        output(tree->child[k], i + 1);
        printf("%s%d\n", base,tree->keyPtr[k + 1]);
    }
    output(tree->child[tree->keyNum], i + 1);
}