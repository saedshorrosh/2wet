//
// Created by Saed Shorrosh on 03/06/2022.
//

#ifndef INC_2WET_HASHTABLE_H
#define INC_2WET_HASHTABLE_H
#include "DynamicArray.h"
#include "AvlTree.h"
#include "Employee.h"
void rehash();
class HashTable{
public:
    int hash_size=0;
    DynamicArray<AvlTree<Employee,int>> array;
    int hash(int input){
        return input%array.max;
    }

    void insert(Employee& t){
        if(double(hash_size)/double(array.max)>=1){
            rehash();
        }
        int newIndex=hash(t.getId());
        if(array[newIndex].insert(t,t.getId())!=NULL){
            hash_size++;
        }
    }

    void remove(int key){
        int id= hash(key);
        AvlTree<Employee,int> & tree=array[id];
        tree.remove(key);
        hash_size--;
        if(double(hash_size)/double(array.max)<=0.25){
            rehash();
        }
    }

    void rehash(){
        int oldSize=array.max;
        array.max=array.max*2;
        AvlTree<Employee,int> * newArr= new AvlTree<Employee,int> [array.max];
        AvlTree<Employee,int> * temp=array.arr;
        array.arr=newArr;
        hash_size=0;
        for(int i=0;i<oldSize;i++){
            AvlTree<Employee,int>::iterator iterator=temp[i].begin();
            for(int j=0;j<temp[i].size;j++){
                insert(iterator.nodePtr->getData());
                ++iterator;
            }
        }
        delete [] temp;
    }

    void shrink(){
        int oldSize=array.max;
        array.max=array.max/2;
        AvlTree<Employee,int> * newArr = new AvlTree<Employee,int> [array.max];
        AvlTree<Employee,int> * temp = array.arr;
        array.arr = newArr;
        hash_size = 0;
        for(int i=0;i<oldSize;i++){
            AvlTree<Employee,int>::iterator iterator=temp[i].begin();
            for(int j=0;j<temp[i].size;j++){
                insert(iterator.nodePtr->getData());
                ++iterator;
            }
        }
        delete temp;
    }

    friend HashTable operator + (HashTable const &obj1,HashTable const &obj2) ;

    HashTable& operator=(const HashTable & t){
        if(this==&t){
            return *this;
        }
        delete[]array.arr;
        array.max=t.array.max;
        hash_size=t.hash_size;
        array.arr=new AvlTree<Employee,int> [array.max];
        for(int i=0;i<array.max;i++){
            array.arr[i]=t.array.arr[i];
        }
        return *this;
    };

    HashTable(const HashTable& t){
        array.max=t.array.max;
        hash_size=t.hash_size;
        array.arr=new AvlTree<Employee,int> [array.max];
        for(int i=0;i<array.max;i++){
            array.arr[i]=t.array.arr[i];
        }
    }

    HashTable(){}
};

HashTable operator + (HashTable const &obj1,HashTable const &obj2){
    HashTable  hashTable;
    hashTable.hash_size= 0;
    hashTable.array.max= obj1.array.max+obj2.array.max;
    AvlTree<Employee,int> * newArr= new AvlTree<Employee,int> [hashTable.array.max];
    hashTable.array.arr=newArr;

    for(int i=0;i< obj1.array.max;i++){
        AvlTree<Employee,int>::iterator iterator=obj1.array[i].begin();
        for(int j=0;j<obj1.array[i].size;j++){
            hashTable.insert(iterator.nodePtr->getData());
            ++iterator;
        }
    }

    for(int i=0;i< obj2.array.max;i++){
        AvlTree<Employee,int>::iterator iterator=obj2.array[i].begin();
        for(int j=0;j<obj2.array[i].size;j++){
            hashTable.insert(iterator.nodePtr->getData());
            ++iterator;
        }
    }
    return hashTable;
}


#endif //INC_2WET_HASHTABLE_H
