#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "employee.h"

class Department{
    public:
        string departmentName;
        Details* HOD;
        Department *next = nullptr;
        int noOfEmployees = 0;

        Department(){}

        Department(string name){departmentName = name;}

        void addEmployee(Employee *emp){
            emp->prev = lastEmployee;
            if(firstEmployee == nullptr){
                firstEmployee = emp;
            }

            else{
                lastEmployee->next = emp;
            }
            lastEmployee = emp;
            lastEmployee->next = nullptr;
            noOfEmployees++;
        }

        void displayEmployees(){
            cout<<"Employees in "<<departmentName<<" are:\n";
            Employee *ptr = firstEmployee;
            int count=1;
            do{
                cout<<count<<") "<<ptr->details->name<<endl;
                count++;
                ptr = ptr->next;
            }while(ptr!=nullptr);
        }

        Employee* getEmployee(Details *deets){
            Employee *ptr = firstEmployee;
            do{
                if(ptr->details==deets) return ptr;
                ptr = ptr->next;
            }while(ptr!=nullptr);
            return nullptr;
        }

    private:
        Employee *firstEmployee = nullptr;
        Employee *lastEmployee = nullptr;
};

#endif