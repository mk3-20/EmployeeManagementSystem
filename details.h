#ifndef DETAILS_H
#define DETAILS_H

#include <iostream>
using namespace std;

class Details{
    public:
        string name;
        int age;
        string DOB;
        string address;
        string phoneNumber;

        Details(){}

        Details(string name, int age, string DOB = "---", string address = "---", string phoneNumber = "---"){
            this->name = name;
            this->age = age;
            this->DOB = DOB;
            this->address = address;
            this->phoneNumber = phoneNumber;
        }

        Details(const Details &d){
            this->name = d.name;
            this->age = d.age;
            this->DOB = d.DOB;
            this->address = d.address;
            this->phoneNumber = d.phoneNumber;
        }

        static Details* getDetails(string person = "Person's"){
                string name,DOB,address,phoneNo;
                int age;
                cout<<"Enter "<<person<<" Name:"; cin>>name;
                cout<<"Enter "<<person<<" Age:"; cin>>name;
                cout<<"Enter "<<person<<" Date of Birth:"; cin>>name;
                cout<<"Enter "<<person<<" Address:"; cin>>name;
                cout<<"Enter "<<person<<" Phone Number:"; cin>>name;
                return new Details(name,age,DOB,address,phoneNo);
        }
};

class Company;
class Department;
class Employee;

#endif