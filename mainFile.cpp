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

        static Details* getDetails(string person = "Person's",string startPadding = "    "){
                string name,DOB,address,phoneNo;
                int age;
                cout<<startPadding<<"   Enter "<<person<<" Name: "; cin>>name;
                cout<<startPadding<<"   Enter "<<name<<"'s Age: "; cin>>age;
                cout<<startPadding<<"   Enter "<<name<<"'s Date of Birth: "; cin>>DOB;
                cout<<startPadding<<"   Enter "<<name<<"'s Address: "; cin>>address;
                cout<<startPadding<<"   Enter "<<name<<"'s Phone Number: "; cin>>phoneNo;
                return new Details(name,age,DOB,address,phoneNo);
        }
};

class Department;
class Company;

class Employee{
    public:
            Details *details;
            Company *company;
            string post;
            string departmentName;
            Employee *prev=nullptr, *next=nullptr;

            Employee(){}

            Employee(const Employee &e){
                details = e.details;
                company = e.company;
                post = e.post;
                departmentName = e.departmentName;
            }

            Employee(Details *d){
                this->details = details;
            }

            Employee(string name, int age, string DOB = "---", string address = "---", string phoneNumber = "---",string post="---",string departmentName="---"){
                details = new Details(name,age,DOB,address,phoneNumber);
                this->post = post;
                this->departmentName = departmentName;
            }

            static Employee* makeEmployee(string startPadding = "   "){
                cout<<startPadding<<"   --> Make New Employee: \n";
                Employee* newEmp = new Employee();
                newEmp->details = Details::getDetails("Employee's",startPadding);
                return newEmp;
            }

            static Employee* getCopyOfEmp(Employee *e){
                Employee* newEmp = new Employee();
                newEmp->details = e->details;
                newEmp->company = e->company;
                newEmp->post = e->post;
                newEmp->departmentName = e->departmentName;
                return newEmp;
            }

            void displayDetails(string heading ="Employee Details:",string startPadding = "     "){
                cout<<"\n"<<startPadding<<heading<<"\n";
                startPadding+="  ";
                cout<<startPadding<<"Name: "<<details->name<<endl;
                cout<<startPadding<<"Department: "<<departmentName<<endl;
                cout<<startPadding<<"Post: "<<post<<endl;
                cout<<startPadding<<"Age: "<<details->age<<endl;
                cout<<startPadding<<"Date of Birth: "<<details->DOB<<endl;
                cout<<startPadding<<"Address: "<<details->address<<endl;
                cout<<startPadding<<"Phone Number: "<<details->phoneNumber<<endl;
                cout<<startPadding<<"Number of Leaves: "<<"--"<<endl;
                cout<<startPadding<<"Salary: "<<"--"<<endl;
            }
};

class Company{
    public:
        int noOfDepartments = 0;
        int noOfEmployees = 0;
        Employee* CEO;
        string companyName;
        Company(string companyName);
        Department* makeAndAddDepartment(string startPadding = "   ");
        Department* addDepartment(Department *department);
        void displayDepartments(string startPadding = "    ");
        Department* getDepartment(int index);
        Employee* getEmployee(int index);
        void displayAllEmployees(string startPadding = "    ");
        void displayAllEmployeesWithDepartments(string startPadding = "    ");
        Department* selectADepartment(string startPadding = "    ");
        Employee* selectAnEmployee(string startPadding = "    ");

    private:
        friend class Department;
        Department *firstDepartment = nullptr;
        Department *lastDepartment = nullptr;
        Employee *firstEmployeeOfCompany = nullptr;
        Employee *lastEmployeeOfCompany = nullptr;
};



class Department{
    public:
        string departmentName = "---";
        Employee* HOD = nullptr;
        Company *company = nullptr;
        Department *next = nullptr;
        int noOfEmployees = 0;

        Department(){}

        Department(string name){departmentName = name;}

        Employee* makeAndAddEmployee(bool makeHOD = false,string startPadding = "   "){
            cout<<startPadding<<"    --> Add an Employee in "<<departmentName<<endl;
            Employee* newEmp = Employee::makeEmployee("       ");
            string post;
            if(makeHOD) post = "HOD";
            else { cout<<startPadding<<"       Enter Employee's post in "<<departmentName<<": "; cin>>post; }
            return addEmployee(newEmp,post,makeHOD,startPadding);
        }

        void setHOD(Employee* emp){
            if(HOD!=nullptr) HOD->post = "---";
            emp->post = "HOD";
            emp->departmentName = departmentName;
            HOD = emp;
        }

        Employee* addEmployee(Employee *emp,string post="--",bool makeHOD = false,string startPadding = "   "){
            emp->departmentName = departmentName;
            emp->company = company;
            emp->post = post;
            emp->prev = lastEmployee;

            if(firstEmployee == nullptr) firstEmployee = emp;
            else lastEmployee->next = emp;

            lastEmployee = emp;
            lastEmployee->next = nullptr;

            if(company!=nullptr){
                
                Employee* empForCompanyLL = Employee::getCopyOfEmp(emp);
                empForCompanyLL->prev = company->lastEmployeeOfCompany;
                if(company->firstEmployeeOfCompany==nullptr) 
                {   
                    company->firstEmployeeOfCompany = empForCompanyLL;
                }
                else company->lastEmployeeOfCompany->next = empForCompanyLL;
                company->lastEmployeeOfCompany = empForCompanyLL;
                (company->noOfEmployees)++;
            }
            
            noOfEmployees++;
            if(makeHOD) setHOD(emp);
            cout<<endl<<startPadding<<"! Added "<<emp->details->name<<" in "<<emp->departmentName<<" !\n\n";
            return emp;
        }

        void displayEmployees(string startPadding = "   "){
            if(noOfEmployees==0) {
                cout<<endl<<startPadding<<"No Employees in "<<departmentName<<endl<<endl;
                return;
            }
            cout<<startPadding<<"Employees in "<<departmentName<<": (Total "<<noOfEmployees<<")\n";
            Employee *ptr = firstEmployee;
            int count=1;
            do{
                cout<<startPadding<<count<<") "<<ptr->details->name<<endl;
                count++;
                ptr = ptr->next;
            }while(ptr!=lastEmployee->next);
        }

        Employee* getEmployee(int index){
            if(index > noOfEmployees) return nullptr;
            Employee *ptr = firstEmployee;
            for(int i = 0; i<index; i++){
                ptr = ptr->next;
            }
            return ptr;
        }

        Employee* selectAnEmployee(string startPadding){
            displayEmployees(startPadding);
            cout<<"\n   --> Select an employee from above: ";
            while(true){
                int empIndexShowEmp;
                cin>>empIndexShowEmp;
                Employee* emp = getEmployee(empIndexShowEmp-1);
                if(emp==nullptr) cout<<"       Select a valid employee: ";
                else return emp;
            }
        }

    private:
        Employee *firstEmployee = nullptr;
        Employee *lastEmployee = nullptr;
};

Company::Company(string companyName){
    this->companyName = companyName;
}




Department* Company::addDepartment(Department *department){
    department->company = this;
    if(firstDepartment==nullptr) firstDepartment = department;
    else lastDepartment->next = department;
    
    lastDepartment = department;
    lastDepartment->next = nullptr;
    noOfDepartments++;
    return department;
}

Department* Company::makeAndAddDepartment(string startPadding = "   "){
    // cout<<startPadding<<"    --> Add an Employee in "<<departmentName<<endl;
    string name;
    cout<<startPadding<<"Enter Department's name: "; cin>>name;
    Department* newDep = new Department(name);
    return addDepartment(newDep);
}

void Company::displayDepartments(string startPadding){
    if(noOfDepartments==0){
        cout<<"No Departments in "<<companyName<<endl<<endl;
        return;
    }
    Department *ptr = firstDepartment;
    int count=1;
    do{
        cout<<startPadding<<count<<") "<<ptr->departmentName<<endl;
        count++;
        ptr = ptr->next;
    }while(ptr!=nullptr);
    cout<<endl;
}

void Company::displayAllEmployees(string startPadding){
    cout<<startPadding<<"All Employees at "<<companyName<<": (Total "<<noOfEmployees<<")\n";
    Employee *ptr = firstEmployeeOfCompany;
    startPadding+="    ";
    int count = 1;
    while(ptr!=nullptr)
    {   
        cout<<startPadding<<count<<") "<<ptr->details->name<<" - "<<ptr->departmentName<<" - "<<ptr->post<<endl;
        count++;
        ptr = ptr->next;
    }
}

void Company::displayAllEmployeesWithDepartments(string startPadding){
    cout<<startPadding<<"All Employees at "<<companyName<<" are:\n";
    Department *ptr = firstDepartment;
    startPadding+="    ";
    while(ptr!=nullptr)
    {
        // cout<<"Employees in "<<ptr->departmentName<<" are: \n";
        ptr->displayEmployees(startPadding);
        cout<<endl;
        ptr = ptr->next;
    }
}

Department* Company::getDepartment(int index){
    if(index>noOfDepartments) return nullptr;
    Department *ptr = firstDepartment;
    for(int i = 0; i<index; i++){
        ptr = ptr->next;
    }
    return ptr;
}

Employee* Company::getEmployee(int index){
    if(index>noOfEmployees) return nullptr;
    Employee *ptr = firstEmployeeOfCompany;
    for(int i = 0; i<index; i++){
        ptr = ptr->next;
    }
    return ptr;
}

Department* Company::selectADepartment(string startPadding){
    cout<<"     Departments in "<<companyName<<" are:\n";
    displayDepartments("     ");
    cout<<"   --> Select a department from above: ";
    while(true){
        int depIndexDisplayEmps;
        cin>>depIndexDisplayEmps;
        Department* dep = getDepartment(depIndexDisplayEmps-1);
        if(dep==nullptr)cout<<"       Select a valid department:";
        else return dep;
    }
}

Employee* Company::selectAnEmployee(string startPadding){
    displayAllEmployees(startPadding);
    cout<<"\n   --> Select an employee from above: ";
    while(true){
        int empIndexShowEmp;
        cin>>empIndexShowEmp;
        Employee* emp = getEmployee(empIndexShowEmp-1);
        if(emp==nullptr)cout<<"       Select a valid employee: ";
        else return emp;
    }
}

void printOperations(Company *company){
    cout<<"\nOPERATIONS:\n";
    
    cout<<"\n --> Company\n";
    cout<<"   1. Display CEO details\n";
    cout<<"   2. Change CEO\n";

    cout<<"\n --> Departments\n";
    cout<<"   3. Display Departments in "<<company->companyName<<endl;
    cout<<"   4. Add a new department\n";
    cout<<"   5. Display HOD details\n";
    cout<<"   6. Change HOD\n";

    cout<<"\n --> Employees\n";
    cout<<"   7. Display Employees in department...\n";
    cout<<"   8. Add a new Employee in department...\n";
    cout<<"   9. Display an Employee details...\n";
    cout<<"  10. Display all employees in "<<company->companyName<<endl;
    cout<<endl;
}

void TBI(){
    cout<<"\n__ TO BE IMPLEMENTED SOON __\n";
}

void startProgram(Company *company=nullptr){
    cout<<"___ Employee Management System ____\n";
    cout<<"    by Mukund Kukreja AIML1\n";
    printOperations(company);

    string spaceA = "    ";
    string space2A = "        ";

    while(true){
        cout<<"Enter an operation b/w 1 to 10: ";
        int input;
        cin>>input;
        if(input==-1) break;

        switch (input)
        {
        case 1: // Display CEO Details
            cout<<"---> OPER 1: Display CEO details\n\n";
            company->CEO->displayDetails();
            break;
            
        case 2: // Change CEO
            TBI();
            break;

        case 3: // Display All Departments
            cout<<"---> OPER 3: Display Departments in "<<company->companyName<<endl;
            cout<<"Departments in "<<company->companyName<<" are:\n";
            company->displayDepartments();
            break;

        case 4: // Add a new department
            cout<<"---> OPER 4: Add a new Deparment in "<<company->companyName<<"\n\n";
            company->makeAndAddDepartment();
            break;

        case 5: // Display HOD Details
            cout<<"---> OPER 5: Display HOD details\n\n";
            if((company->noOfDepartments)>0){
                Department* dep = company->selectADepartment();
                string heading = "HOD of ";
                heading+=dep->departmentName;
                heading+=": ";
                if(dep!=nullptr) dep->HOD->displayDetails(heading,space2A);
            }
            else cout<<"There are no Departments in "<<company->companyName<<" :("<<endl;
            break;

        case 6: // Change HOD
            cout<<"---> OPER 6: Change HOD of department...\n\n";
            if((company->noOfDepartments)>0){
                Department* dep = company->selectADepartment();
                if(dep!=nullptr) cout<<spaceA<<"Current HOD of "<<dep->departmentName<<": "<<dep->HOD->details->name<<endl;
                if((company->noOfEmployees)>0){
                    cout<<spaceA<<" --> Options:\n";
                    cout<<space2A<<"1) Promote pre-exisiting to the post of HOD of "<<dep->departmentName<<endl;
                    cout<<space2A<<"2) Make a new HOD\n";
                    while(true){
                        int makeNewHodInput;
                        cout<<space2A<<"Enter 1 or 2: "; cin>>makeNewHodInput;
                        if(makeNewHodInput == 2){
                            dep->makeAndAddEmployee(true);
                            break;
                        } 
                        else if(makeNewHodInput == 1){
                            Employee* emp = dep->selectAnEmployee(space2A);
                            if(emp!=nullptr) dep->setHOD(emp);
                            break;
                        }
                    }
                    cout<<spaceA<<dep->HOD->details->name<<" is the new HOD of "<<dep->departmentName<<endl;
                }
                else dep->makeAndAddEmployee(true);
            }
            else cout<<"There are no Departments in "<<company->companyName<<" :("<<endl;
            break;

        case 7: // Display Employees in a department
            cout<<"---> OPER 7: Display Employees in department...\n\n";
            if((company->noOfDepartments)>0){
                Department* dep = company->selectADepartment();
                if(dep!=nullptr) dep->displayEmployees("       ");
            }
            else cout<<"There are no Departments in "<<company->companyName<<" :("<<endl;
            break;

        case 8: // Add a new employee 
            cout<<"---> OPER 8: Add a new Employee in department...\n\n";
            if((company->noOfDepartments)>0){
                Department* dep = company->selectADepartment();
                if(dep!=nullptr) dep->makeAndAddEmployee();
            }
            else cout<<"There are no Departments in "<<company->companyName<<" :("<<endl;
            break;

        case 9: // Display An Employee
            cout<<"---> OPER 9: Display an Employee details...\n\n";
            if((company->noOfEmployees)>0){
                Employee* emp = company->selectAnEmployee();
                if(emp!=nullptr) emp->displayDetails("          ");
            }
            else cout<<"There are no Employees in "<<company->companyName<<" :("<<endl;
            break;

        case 10: // Display all employees in the company
            cout<<"---> OPER 10: Display all employees in "<<company->companyName<<endl<<endl;
            company->displayAllEmployees();
            break;

        default:
            cout<<"\nEnter a valid command between 1 to 10!\n";
            break;
        }
        cout<<"_________________________________________________________________\n";
    }


}

int main(){
    // Employee Harish = Employee(new Details("Harish",19,"11 April 2003","Near Gyan Ganga","1234567890"));
    Employee *Harish = new Employee("Harish",19,"11 April 2003","Near Gyan Ganga","1234567890");

    Company Harish_Ki_Dukaan = Company("Harish Ki Dukaan");
    Harish_Ki_Dukaan.CEO = Harish;

    Department* ManagementDepartment = new Department("Management Department");
    Department* SanitoryDepartment = new Department("Sanitory Department");
    Department* FoodDepartment = new Department("Food Department");
    Department* AccountingDepartment = new Department("Accounting Department");
    
    Harish_Ki_Dukaan.addDepartment(ManagementDepartment);
    Harish_Ki_Dukaan.addDepartment(SanitoryDepartment);
    Harish_Ki_Dukaan.addDepartment(FoodDepartment);
    Harish_Ki_Dukaan.addDepartment(AccountingDepartment);

    Employee* A = new Employee("A",11);
    Employee* B = new Employee("B",12);
    Employee* C = new Employee("C",13);
    Employee* D = new Employee("D",14);
    Employee* Hod1 = new Employee("HOD 1",15);
    Employee* Hod2 = new Employee("HOD 2",16);
    Employee* Hod3 = new Employee("HOD 3",17);

    ManagementDepartment->addEmployee(Harish,"CEO",true);

    SanitoryDepartment->addEmployee(Hod1,"HOD",true);
    SanitoryDepartment->addEmployee(A,"Janitor");
    SanitoryDepartment->addEmployee(B,"Washer");

    FoodDepartment->addEmployee(Hod2,"HOD",true);
    FoodDepartment->addEmployee(C,"Chef");

    AccountingDepartment->addEmployee(Hod3,"HOD",true);
    AccountingDepartment->addEmployee(D,"Accountant");

    startProgram(&Harish_Ki_Dukaan);
}



/*     Employee* A = new Employee(new Details("A",11));
    Employee* B = new Employee(new Details("B",12));
    Employee* C = new Employee(new Details("C",13));
    Employee* D = new Employee(new Details("D",14)); */