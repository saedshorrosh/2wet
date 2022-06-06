//

// Created by Saed Shorrosh on 26/04/2022.
//

#ifndef DS_HW1_AVLTREE_H
#define DS_HW1_AVLTREE_H

#include <iostream>
#include "Node.h"

typedef enum {
    TREE_SUCCESS,
    TREE_ALLOCATION_ERROR,
    TREE_FAILURE,
    TREE_INVALID_INPUT
} Result;

template<class T, class K>
class AvlTree {
public:

    int size = 0;
    void printTree(const std::string &prefix, Node<T,K> *node, bool isLeft) {
        if (node != nullptr) {
            std::cout << prefix;

            std::cout << (isLeft ? "|L--- " : "|R--- ");

            // print the value of the node
            std::cout << "id: " << node->getKey() << "  BF: " << node->getBF() <<
                      "  height: " << node->getHeight() << std::endl;

            // enter the next tree level - left and right branch
            printTree(prefix + (isLeft ? "|   " : "    "), node->getLeft(), true);
            printTree(prefix + (isLeft ? "|   " : "    "), node->getRight(), false);
        }
    }

    void printTree() {
        printTree("", Head->right, false);
    }

    AvlTree() {
        this->Head = new Node<T,K>;
    }

    ~AvlTree() {
        clearTree();
        delete Head;
    };

    AvlTree(const AvlTree &avlTree){
        Node<T,K> * newHead=new Node<T,K>;
        Head=newHead;
        Head->right=avlTree.Head->right;
        size=avlTree.size;
        if(newHead->right!=NULL){
            newHead->getRight()->setParent(newHead);
        }
    };
    AvlTree& operator=(const AvlTree& avlTree){
        if(&avlTree==this){
            return *this;
        }
        clearTree();
        size=avlTree.size;
        delete Head;
        Node<T,K> * newHead=new Node<T,K>();
        Head=newHead;
        Head->right=avlTree.Head->right;
        if(Head->right!=NULL){
            Head->getRight()->setParent(newHead);
        }
        avlTree.Head->setRight(NULL);
        return *this;
    }

    int max(int a, int b) {
        return a > b ? a : b;
    }

    class iterator;

    class iterator {
    public:
        Node<T,K> *nodePtr=NULL;
        Node<T,K> *root;

        friend class AvlTree;

        int counter = 0;

        T operator*() const {
            return (*nodePtr).data;
        }

        K getKey() {
            return nodePtr->key;
        }

        Node<T,K>* findSuccessor(Node<T,K>* _root, Node<T,K>* succ, K key)
        {
            // base case
            if (_root == nullptr) {
                return succ;
            }

            // if a node with the desired value is found, the successor is the minimum value
            // node in its right subtree (if any)
            if (_root->key == key)
            {
                if (_root->right != nullptr) {
                    return findMinimum(_root->right);
                }
            }
                // if the given key is less than the root node, recur for the left subtree
            else if (key < _root->key)
            {
                // update successor to the current node before recursing in the left subtree
                succ = _root;
                return findSuccessor(_root->left, succ, key);
            }

                // if the given key is more than the root node, recur for the right subtree
            else {
                return findSuccessor(_root->right, succ, key);
            }

            return succ;
        }

        void operator++() {
            counter++;
            nodePtr= findSuccessor(root,nodePtr,nodePtr->key);
        }

        Node<T,K> * findMinimum(Node<T,K>* root)
        {
            while (root->left) {
                root = root->left;
            }

            return root;
        }

        Node<T,K> * maxValue(Node <T,K>* node){
            Node<T,K> * current = node;
            // Loop down to find the leftmost leaf
            while (current->right != NULL)
            {
                current = current->right;
            }
            return current;
        }

        Node<T,K>* findPredecessor(Node<T,K>* root, Node<T,K>* prec, K key)
        {
            // base case
            if (root == nullptr) {
                return prec;
            }

            // if a node with the desired value is found, the predecessor is the maximum
            // value node in its left subtree (if any)
            if (root->key == nodePtr->key)
            {
                if (root->left != nullptr) {
                    return maxValue(root->left);
                }
            }

                // if the given key is less than the root node, recur for the left subtree
            else if (key < root->key) {
                return findPredecessor(root->left, prec, nodePtr->key);
            }

                // if the given key is more than the root node, recur for the right subtree
            else {
                // update predecessor to the current node before recursing
                // in the right subtree
                prec = root;
                return findPredecessor(root->right, prec, nodePtr->key);
            }
            return prec;
        }

        void operator--() {
            counter++;
            nodePtr=findPredecessor(root,nodePtr,nodePtr->key);
        }




        iterator(const iterator &iterator) = default;


        explicit iterator(Node<T,K> *node) : nodePtr(node) {
            nodePtr=node;
        }


        iterator &operator=(const iterator &) = default;
    };

    iterator begin() const {
        Node<T,K> *node = Head->right;
        while (node != NULL && node->left != NULL) {
            node = node->left;
        }
        iterator iterator(node);
        iterator.root=Head->right;
        return iterator;
    }

    iterator begin(Node<T,K> *node) const {
        iterator iterator(node);
        iterator.root=Head->right;
        return iterator;
    }

    bool balance_tree(Node<T,K> *node) {
        int BF = node->BF;
        if (node->parent == NULL) {
            return false;
        }
        if (BF == 2 && node->left->calculateBF() >= 0) {
            this->LL(node);
            return true;
        } else if ((BF == 2) && (node->left->calculateBF() == -1)) {
            this->LR(node);
            return true;
        } else if (BF == -2 && (node->right->calculateBF() <= 0)) {
            this->RR(node);
            return true;
        } else if (BF == -2 && (node->right->calculateBF() == 1)) {
            this->RL(node);
            return true;
        }
        return false;
    }

    Node<T,K> *search(const K &key) {
        if (Head == NULL) {
            return NULL;
        }
        if(Head->right==NULL){
            return NULL;
        }
        Node<T,K> *temp = this->Head->right;
        while (temp != NULL) {
            K current_key = temp->getKey();
            if (current_key == key) {
                return temp;
            }
            if (key < current_key) {
                temp = temp->getLeft();
            } else {
                temp = temp->getRight();
            }
        }
        return NULL;
    }


    void updateHeight(Node<T,K> *node) {
        if (node->left != NULL && node->right != NULL) {
            node->height = 1 + max((node->left->height), (node->right->height));
        } else if (node->left != NULL) {
            node->height = 1 + node->left->height;
        } else if (node->right != NULL) {
            node->height = 1 + node->right->height;
        } else {
            node->height = 0;
        }
    }

    Node<T,K> *insert(const T data, const K key) {
        Node<T,K> *node = this->Head;
        if (search(key) != NULL) {
            return NULL;
        }
        size++;
        if ((node->right == NULL) && (node->parent == NULL)) {
            Node<T,K> *newNode = new Node<T,K>(data, key);
            node->right = newNode;
            newNode->parent = node;
            updateHeight(node);
            return newNode;
        }
        bool *rotation_flag = new bool(false);
        Node<T,K> *value = insertAux(node->right, data, key, rotation_flag);
        delete (rotation_flag);
        return value;
    }

    Node<T,K> *insertAux(Node<T,K> *node, const T &data, const K &key, bool *rotation_flag) {
        Node<T,K> *returnValue = NULL;
        if (key < node->key) {
            if (node->left == NULL) {
                Node<T,K> *newNode = new Node<T,K>(data, key);
                node->left = newNode;
                node->left->parent = node;
                if (!(*rotation_flag)) {
                    updateHeight(node);
                    node->BF = node->calculateBF();
                }
                *rotation_flag = balance_tree(node);
                return newNode;
            }

            returnValue = insertAux(node->left, data, key, rotation_flag);
        } else {
            if (node->right == NULL) {
                Node<T,K> *newNode = new Node<T,K>(data, key);
                node->right = newNode;
                node->right->parent = node;
                if (!(*rotation_flag)) {
                    updateHeight(node);
                    node->BF = node->calculateBF();
                }
                *rotation_flag = balance_tree(node);
                return newNode;
            }
            returnValue = insertAux(node->right, data, key, rotation_flag);
        }
        if (!(*rotation_flag)) {
            updateHeight(node);
            node->BF = node->calculateBF();
        }
        *rotation_flag = balance_tree(node);
        return returnValue;
    }



    void RR(Node<T,K>*node) {
        Node <T,K>*newHead = node->right;
        Node <T,K>*newLeft = node;
        Node <T,K>*opLeft = newHead->left;
        Node <T,K>*parent = node->parent;
        Node <T,K>*newRight = newHead->right;
        if (parent != NULL) {
            if (parent->left == node) {
                parent->left = newHead;
            } else {
                parent->right = newHead;
            }
        }
        newHead->parent = parent;
        newHead->left = newLeft;
        newLeft->parent = newHead;
        newHead->right = newRight;
        if (newRight != NULL) {
            newRight->parent = newHead;
        }
        newLeft->right = opLeft;
        if (opLeft != NULL) {
            opLeft->parent = newLeft;
        }
        newHead->parent = parent;
        newHead->left = newLeft;
        newLeft->parent = newHead;
        newHead->right = newRight;
        if (newRight != NULL) {
            newRight->parent = newHead;
        }
        newLeft->right = opLeft;
        if (opLeft != NULL) {
            opLeft->parent = newLeft;
        }
        updateHeight(node);
        updateHeight(newHead);
        node->BF = node->calculateBF();
        newHead->BF = newHead->calculateBF();
    }

    void LR(Node<T,K> *node) {
        this->RR(node->left);
        this->LL(node);
    }

    void RL(Node<T,K> *node) {
        this->LL(node->right);
        this->RR(node);
    }

    void LL(Node<T,K> *node) {
        Node <T,K>*newHead = node->left;
        Node <T,K>*newRight = node;
        Node <T,K>*opRight = newHead->right;
        Node<T,K> *parent = node->parent;
        Node <T,K>*newLeft = newHead->left;
        if (parent != NULL) {
            if (parent->left == node) {
                parent->left = newHead;
            } else {
                parent->right = newHead;
            }
        }
        newHead->parent = parent;
        newHead->right = newRight;
        newRight->parent = newHead;
        newHead->left = newLeft;
        if (newLeft != NULL) {
            newLeft->parent = newHead;
        }
        newRight->left = opRight;
        if (opRight != NULL) {
            opRight->parent = newRight;
        }
        updateHeight(node);
        updateHeight(newHead);
        node->BF = node->calculateBF();
        newHead->BF = newHead->calculateBF();
    }

    Result removeByNode(Node<T,K> *node) {
        if (node != NULL) {
            size--;
            Node<T,K> *parentPointer = node->parent;
            Node<T,K> *leftPointer = node->left;
            Node<T,K> *rightPointer = node->right;
            if (leftPointer != NULL && rightPointer != NULL) {
                iterator it = this->begin(node);
                ++it;
                Node<T,K> *next = it.nodePtr;
                Node<T,K> *tempRight = next->right;
                if (node->parent->right != NULL) {
                    if (node->parent->right->key == node->key) {
                        node->parent->right = next;
                    }
                }
                if (node->parent->left != NULL) {
                    if (node->parent->left->key == node->key) {
                        node->parent->left = next;
                    }
                }
                Node<T,K> *nextParent = next->parent;
                if (next->parent->right != NULL) {
                    if (next->parent->right->key == next->key) {
                        if (tempRight == NULL) {
                            next->parent->right = NULL;
                        } else {
                            next->parent->right = tempRight;
                            tempRight->parent = next->parent;
                        }
                    }
                }
                if (next->parent->left != NULL) {
                    if (next->parent->left->key == next->key) {
                        if (tempRight == NULL) {
                            next->parent->left = NULL;
                        } else {
                            next->parent->left = tempRight;
                            tempRight->parent = next->parent;
                        }
                    }
                }
                if (next != leftPointer) {
                    next->left = leftPointer;
                }
                if (next != rightPointer) {
                    next->right = rightPointer;
                }
                if (next != parentPointer) {
                    next->parent = parentPointer;
                }
                if (next->left != NULL) {
                    next->left->parent = next;
                }
                if (next->right != NULL) {
                    next->right->parent = next;
                }
                Node<T,K> *itrPointer;
                if (tempRight != NULL) {
                    itrPointer = tempRight;
                } else {
                    itrPointer = nextParent;
                }
                if (itrPointer == node) {
                    itrPointer = leftPointer;
                }
                while (itrPointer->parent != NULL) {
                    updateHeight(itrPointer);
                    itrPointer->BF = itrPointer->calculateBF();
                    balance_tree(itrPointer);
                    itrPointer = itrPointer->parent;
                }
                delete node;
                return TREE_SUCCESS;
            } else if (leftPointer != NULL || rightPointer != NULL) {
                Node<T,K> *activePointer=NULL;
                if (leftPointer != NULL) {
                    activePointer = leftPointer;
                } else if (rightPointer != NULL) {
                    activePointer = rightPointer;
                }
                if (parentPointer->right->key == node->key) {
                    parentPointer->right = activePointer;
                } else if (parentPointer->left->key == node->key) {
                    parentPointer->left = activePointer;
                }
                activePointer->parent = parentPointer;
                Node<T,K> *itrPointer = node;
                while (itrPointer->parent != NULL) {
                    updateHeight(itrPointer);
                    itrPointer->BF = itrPointer->calculateBF();
                    balance_tree(itrPointer);
                    itrPointer = itrPointer->parent;
                }
                delete node;
                return TREE_SUCCESS;
            } else {
                if (parentPointer->right != NULL) {
                    if (parentPointer->right->key == node->key) {
                        parentPointer->right = NULL;
                        Node<T,K> *itrPointer = node;
                        while (itrPointer->parent != NULL) {
                            updateHeight(itrPointer);
                            itrPointer->BF = itrPointer->calculateBF();
                            balance_tree(itrPointer);
                            itrPointer = itrPointer->parent;
                        }
                        delete node;
                        return TREE_SUCCESS;
                    }
                }
                if (parentPointer->left != NULL) {
                    if (parentPointer->left->key == node->key) {
                        parentPointer->left = NULL;
                        Node<T,K> *itrPointer = node;
                        while (itrPointer->parent != NULL) {
                            updateHeight(itrPointer);
                            itrPointer->BF = itrPointer->calculateBF();
                            balance_tree(itrPointer);
                            itrPointer = itrPointer->parent;
                        }
                        delete node;
                        return TREE_SUCCESS;
                    }
                }
            }
        }
        return TREE_FAILURE;
    }

    Result remove(K key) {
        Node<T,K> *node = search(key);
        return removeByNode(node);
    }

    void treeToArray(Node<T,K> *array[]) {
        iterator it = begin();
        while (it.counter < size) {
            array[it.counter] = it.nodePtr;
            ++it;
        }
    }

    void clearTree() {
        if(Head==NULL){
            return;
        }
        if (this->Head->right == NULL) {
            return;
        }
        Node<T,K> **array = new Node<T,K> *[this->size];
        treeToArray(array);
        for (int i = 0; i < this->size; i++) {
            delete array[i];
        }
        delete[] array;
        this->Head->right = NULL;
        this->size = 0;
    }

public:
    Node<T,K> *Head;

    void setHead(Node<T,K> *head) {
        this->Head = head;
    }

    Node<T,K> *getHighestNode() {
        if (size == 0) {
            return NULL;
        } else {
            Node<T,K> *nodePtr = Head;
            Node<T,K> *prev;
            while (nodePtr != NULL) {
                prev = nodePtr;
                nodePtr = nodePtr->right;
            }
            return prev;
        }
    }

    Node<T,K> *getInf(K key) {
        if(getHighestNode()->getKey()<key){
            return NULL;
        }
        Node<T,K> *current_node = search(key);
        if (current_node != NULL) {
            return current_node;
        }
        Node<T,K> *node = insert(T(), key);
        iterator itr = begin(node);
        ++itr;
        Node<T,K> *val = itr.nodePtr;
        removeByNode(node);
        return val;
    }

    Node<T,K> *getSup(K key) {
        iterator it=begin();
        if(key<it.nodePtr->key){
            return NULL;
        }
        Node <T,K>*current_node = search(key);
        if (current_node != NULL) {
            return current_node;
        }
        Node<T,K> *node = insert(T(), key);
        iterator itr = begin(node);
        --itr;
        Node<T,K> *val = itr.nodePtr;
        removeByNode(node);
        return val;
    }

    void arrayToTree(Node<T,K> **array, int length) {
        Head->setRight(arrayToTreeAux(array, 0, length - 1));
        if (Head->right != NULL) {
            Head->right->setParent(Head);
        }
        size = length;
    }

    Node<T,K> *arrayToTreeAux(Node<T,K> *array[], int beginning, int end) {
        if (beginning > end) {
            return nullptr;
        }
        int middle = (beginning + end) / 2;
        Node<T,K> *new_node = array[middle];
        new_node->setLeft(arrayToTreeAux(array, beginning, middle - 1));
        if (new_node->left != NULL) {
            new_node->left->parent = new_node;
        }
        new_node->setRight(arrayToTreeAux(array, middle + 1, end));
        if (new_node->right != NULL) {
            new_node->right->parent = new_node;
        }
        updateHeight(new_node);
        new_node->BF = new_node->calculateBF();
        return new_node;
    }

    void mergeTwoTrees(AvlTree<T, K> * first_tree, AvlTree<T, K> * second_tree) {
        Node<T,K> **first_array = new Node <T,K>*[first_tree->size];
        Node<T,K> **second_array = new Node<T,K> *[second_tree->size];
        Node<T,K> **array = new Node<T,K> *[(first_tree->size + second_tree->size)];
        first_tree->treeToArray(first_array);
        second_tree->treeToArray(second_array);
        mergeArrays(first_array, second_array, first_tree->size, second_tree->size, array);
        delete[] first_array;
        delete[] second_array;
        first_tree->Head->setRight(NULL);
        second_tree->Head->setRight(NULL);
        arrayToTree(array, first_tree->size + second_tree->size);
        delete []array;
    }

    void mergeArrays(Node<T,K> *first_array[], Node <T,K>*second_array[], int first_length,
                     int second_length, Node <T,K>*result_array[]) {
        int indexOfArrayOne = 0,
                indexOfArrayTwo = 0,
                indexOfMergedArray = 0;
        Node <T,K>*node_in_first_array, *node_in_second_array;
        while (indexOfArrayOne < first_length
               && indexOfArrayTwo < second_length) {
            node_in_first_array = (first_array)[indexOfArrayOne];
            node_in_second_array = (second_array)[indexOfArrayTwo];
            if (node_in_first_array->getKey() <= node_in_second_array->getKey()) {
                result_array[indexOfMergedArray] = first_array[indexOfArrayOne];
                indexOfArrayOne++;
            } else {
                result_array[indexOfMergedArray] = second_array[indexOfArrayTwo];
                indexOfArrayTwo++;
            }
            indexOfMergedArray++;
        }
        while (indexOfArrayOne < first_length) {
            result_array[indexOfMergedArray] = first_array[indexOfArrayOne];
            indexOfArrayOne++;
            indexOfMergedArray++;
        }
        while (indexOfArrayTwo < second_length) {
            result_array[indexOfMergedArray] = second_array[indexOfArrayTwo];
            indexOfArrayTwo++;
            indexOfMergedArray++;
        }
    }


};




#endif //DS_HW1_AVLTREE_H