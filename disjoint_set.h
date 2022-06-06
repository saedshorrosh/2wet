//
// Created by Saed Shorrosh on 05/06/2022.
//
#ifndef INC_2WET_DISJOINT_SET_H
#define INC_2WET_DISJOINT_SET_H
#include "HashTable.h"
#include "UpTreeNode.h"
template<class T>
class disjoint_set{
public:
    UpTreeNode<T> * arr;
    int findMin(int p,int q){
        if(p<q){
            return p;
        }
        return q;
    }
    int findMax(int p,int q){
        if(p>q){
            return p;
        }
        return q;
    }

    disjoint_set(int k){
        arr=new UpTreeNode<T>[k];
    };

    void makeSet(int i){
        arr[i].setParent(-1);
        arr[i].setSize(1);
    }

    void unionSet(int p, int q){
        int min=findMin(p,q);
        int max= findMax(p,q);
        if(arr[min].getSize()==-1||arr[max].getSize()==-1){
            return;
        }
        arr[min].setParent(max);
        arr[max].setSize(arr[max].getSize()+arr[min].getSize());
        arr[min].setSize(-1);
    }

    int unionFind(int p){
        UpTreeNode<T> node =arr[p];
        if(arr[p].getParent()==-1){
            return p;
        }
        int ans=unionFind(arr[p].getParent());
        node.setParent(ans);
        return ans;
    }


};
#endif //INC_2WET_DISJOINT_SET_H
