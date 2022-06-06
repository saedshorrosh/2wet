//
// Created by Saed Shorrosh on 05/06/2022.
//
#ifndef INC_2WET_UPTREENODE_H
#define INC_2WET_UPTREENODE_H
#include "Employee.h"
template<class T>
class UpTreeNode{
    int size=0;
    int parent;
    T t;
public:
    int getSize() const {
        return size;
    }

    void setSize(int size) {
        UpTreeNode::size = size;
    }

    void setParent(int parent) {
        UpTreeNode::parent = parent;
    }

    int getParent() const {
        return parent;
    }


};
#endif //INC_2WET_UPTREENODE_H
