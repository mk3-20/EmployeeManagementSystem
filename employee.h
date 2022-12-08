#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "details.h"

class Employee{
    public:
        Details *details;
        Company *company;
        Department *department;
        Employee *prev, *next;
        Employee(){}
        Employee(Department *department, Details *d);
        void makeEmployee();
    private:
};

#endif
