#include <iostream>
#include "company.h"









Employee::Employee(Department *department, Details *d){
    details = d;
    this->department = department;
}
void Employee::makeEmployee(){
    details = Details::getDetails("Employee's");
    while(true){
        cout<<"Enter Employee's department: "; 
        string dName; cin>>dName;
        Department* searchResult = company->getDepartment(dName);
        if (searchResult==nullptr) cout<<"Department Not Found!\n";
        else {
            this->department = searchResult;
            break;
        }
    }
}


class Employer: public Employee{
    public:
        Employer(){}
        Employer(Department *department, Details *d){
            details = d;
            this->department = department;
        }
};



int main(){
    Details Harish = Details("Harish",19,"11 April 2003","Near Gyan Ganga","1234567890");
    Company Harish_Ki_Dukaan = Company("Harish Ki Dukaan", Harish);

    Department* SanitoryDepartment = new Department("Sanitory Department");
    Department* FoodDepartment = new Department("Food Department");
    Department* AccountingDepartment = new Department("Accounting Department");
 
    Harish_Ki_Dukaan.addDepartment(SanitoryDepartment);
    Harish_Ki_Dukaan.addDepartment(FoodDepartment);
    Harish_Ki_Dukaan.addDepartment(AccountingDepartment);


    
    Harish_Ki_Dukaan.displayDepartments();
}