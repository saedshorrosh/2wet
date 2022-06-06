//
// Created by yasmin on 02/05/2022.
//

#ifndef DS_HW1_EMPLOYEE_H
#define DS_HW1_EMPLOYEE_H

#include "AvlTree.h"

class Employee {
public:
    int id;

    int getId() const {
        return id;
    }

    void setId(int id) {
        Employee::id = id;
    }

    Employee(int id) : id(id) {}

    Employee() {}

    Employee(const Employee &employee) = default;

    Employee &operator=(const Employee &employee) = default;

    ~Employee() = default;
};

#endif //DS_HW1_EMPLOYEE_H

