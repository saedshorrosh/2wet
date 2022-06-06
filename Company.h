//
// Created by Saed Shorrosh on 05/06/2022.
//

#ifndef INC_2WET_COMPANY_H
#define INC_2WET_COMPANY_H
class Company{
public:
    int id;

    int getId() const {
        return id;
    }

    void setId(int id) {
        Company::id = id;
    }

    Company(int id) : id(id) {}

    Company() {}

    Company(const Company &employee) = default;

    Company &operator=(const Company &employee) = default;

    ~Company() = default;
};
#endif //INC_2WET_COMPANY_H
