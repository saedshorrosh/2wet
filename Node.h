//
// Created by Saed Shorrosh on 05/06/2022.
//

#ifndef INC_2WET_NODE_H
#define INC_2WET_NODE_H
template<class T,class K>
class Node {

public:
    Node *right;
    Node *left;
    Node *getParent() const;
    Node *parent;
    T data;
    K key;
    int BF = 0, height = 0;
    Node() {
        right = NULL;
        left = NULL;
        parent = NULL;
    }

    ~Node() = default;


    void setRight(Node *right) {
        Node::right = right;
    }

    void setLeft(Node *left) {
        this->left = left;
    }

    K &getKey() {
        return this->key;
    }

    T &getData() {
        return this->data;
    }

    int getHeight() {
        return this->height;
    }

    int getBF() {
        return this->BF;
    }

    Node *getLeft() {
        return this->left;
    }

    Node *getRight() {
        return this->right;
    }

    int calculateBF() {
        if (this->left != NULL && this->right != NULL) {
            return (this->left->height) - (this->right->height);
        } else if (this->right != NULL) {
            return ((-1) - (this->right->height));
        } else if (this->left != NULL) {
            return 1 + (this->left->height);
        } else {
            return 0;//leaf
        }
    }

    Node(T data, K key) {
        this->data = data;
        this->key = key;
        right = NULL;
        left = NULL;
        parent = NULL;
    }
    void setParent(Node *parent) {
        parent = parent;
    }

};
#endif //INC_2WET_NODE_H
