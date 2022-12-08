#ifndef COMPANY_H
#define COMPANY_H

#include "department.h"

class Department;
class Employee;
class Company{
    public:
        Details CEO;
        string companyName;
        int noOfDepartments = 0;

        Company(string companyName, Details Ceo){
            this->companyName = companyName;
            this->CEO = Ceo;
        }

        void addDepartment(Department *department){
            if(firstDepartment==nullptr){
                firstDepartment = department;
                lastDepartment = firstDepartment;
            }
            else{
                lastDepartment->next = department;
                lastDepartment = department;
            }
            lastDepartment->next = firstDepartment;
            noOfDepartments++;
        }

        void displayDepartments(){
            cout<<"Departments in "<<companyName<<" are:\n";
            Department *ptr = firstDepartment;
            int count=1;
            do{
                cout<<count<<") "<<ptr->departmentName<<endl;
                count++;
                ptr = ptr->next;
            }while(ptr!=firstDepartment);
        }

        Department* getDepartment(string dName){
            Department *ptr = firstDepartment;
            do{
                if(ptr->departmentName==dName) return ptr;
                ptr = ptr->next;
            }while(ptr!=firstDepartment);
            return nullptr;
        }

    private:
        Department *firstDepartment = nullptr;
        Department *lastDepartment = nullptr;
};

#endif
