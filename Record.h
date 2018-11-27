//
// Created by Pan梓涵 on 2018/11/24.
//

#ifndef BTREE_RECORD_H
#define BTREE_RECORD_H

//***************键值的类型***************
typedef int KeyType;

//***************记录***************
typedef struct {
    KeyType key;
    char data;
}Record;//记录

#endif //BTREE_RECORD_H
