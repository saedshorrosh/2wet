#include <iostream>
#include "HashTable.h"
#include "disjoint_set.h"
#include "Company.h"
int main() {
    disjoint_set<Company> disjointSet(10);
    disjointSet.makeSet(1);
    disjointSet.makeSet(2);
    disjointSet.makeSet(3);
    disjointSet.makeSet(4);
    disjointSet.unionSet(1,2);
    disjointSet.unionSet(3,4);
    disjointSet.unionSet(2,4);
    disjointSet.unionFind(1);


    return 0;
}
