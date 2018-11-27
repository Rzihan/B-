//
// Created by Pan梓涵 on 2018/11/24.
//

#ifndef BTREE_STATUS_H
#define BTREE_STATUS_H

//函数结果返回值
typedef enum status {
    TRUE,
    FALSE,
    OK,
    ERROR,
    OVERFLOW,
    EMPTY
}Status;

#endif //BTREE_STATUS_H
