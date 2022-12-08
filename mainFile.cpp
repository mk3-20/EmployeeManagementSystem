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
                cout<<startPadding<<"   Enter "<<person<<" Age: "; cin>>age;
                cout<<startPadding<<"   Enter "<<person<<" Date of Birth: "; cin>>DOB;
                cout<<startPadding<<"   Enter "<<person<<" Address: "; cin>>address;
                cout<<startPadding<<"   Enter "<<person<<" Phone Number: "; cin>>phoneNo;
                return new Details(name,age,DOB,address,phoneNo);
        }
};

class Department;

class Company{
        public:
        Details CEO;
        string companyName;
        int noOfDepartments = 0;
        Company(string companyName, Details Ceo);
        void addDepartment(Department *department);
        void displayDepartments(string startPadding = "   ");
        Department* getDepartment(int index);
        void displayAllEmployees(string startPadding = "   ");

    private:
        Department *firstDepartment = nullptr;
        Department *lastDepartment = nullptr;
};

class Employee{
    public:
            Details *details;
            Company *company;
            Department *department;
            Employee *prev, *next;
            Employee(){}
            Employee(Details *d);
            static Employee* makeEmployee(Company company,string startPadding = "   ");
};

class Employer;


Employee::Employee(Details *d){
    this->department = department;
}

Employee* Employee::makeEmployee(Company companystring,string startPadding){
    cout<<startPadding<<"   --> Make New Employee: \n";
    Employee* newEmp = new Employee();
    newEmp->details = Details::getDetails("Employee's",startPadding);
    return newEmp;
}


class Department{
    public:
        string departmentName;
        Details* HOD;
        Company *company;
        Department *next = nullptr;
        int noOfEmployees = 0;

        Department(){}

        Department(string name){departmentName = name;}

        void makeAndAddEmployee(string startPadding = "   "){
            cout<<startPadding<<"    --> Add an Employee in "<<departmentName<<endl;
            addEmployee(Employee::makeEmployee(*company,"       "),startPadding);
        }

        void addEmployee(Employee *emp,string startPadding = "   "){
            emp->department = this;
            if(firstEmployee == nullptr){
                emp->prev = nullptr;
                firstEmployee = emp;
            }

            else{
                emp->prev = lastEmployee;
                lastEmployee->next = emp;
            }
            lastEmployee = emp;
            lastEmployee->next = nullptr;
            noOfEmployees++;
            cout<<endl<<startPadding<<"! Added "<<emp->details->name<<" in "<<emp->department->departmentName<<" !\n\n";
        }

        void displayEmployees(string startPadding = "   "){
            if(noOfEmployees==0) {
                cout<<endl<<startPadding<<"No Employees in "<<departmentName<<endl<<endl;
                return;
            }
            cout<<startPadding<<"Employees in "<<departmentName<<":\n";
            Employee *ptr = firstEmployee;
            int count=1;
            do{
                cout<<startPadding<<count<<") "<<ptr->details->name<<endl;
                count++;
                ptr = ptr->next;
            }while(ptr!=nullptr);
            cout<<endl;
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



Company::Company(string companyName, Details Ceo){
    this->companyName = companyName;
    this->CEO = Ceo;
}

void Company::addDepartment(Department *department){
    department->company = this;
    if(firstDepartment==nullptr) firstDepartment = department;
    else lastDepartment->next = department;
    
    lastDepartment = department;
    lastDepartment->next = nullptr;
    noOfDepartments++;
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
    cout<<startPadding<<"All Employees at "<<companyName<<" are:";
    Department *ptr = firstDepartment;
    startPadding+="    ";
    while(ptr!=nullptr)
    {
        // cout<<"Employees in "<<ptr->departmentName<<" are: \n";
        ptr->displayEmployees(startPadding);
        ptr = ptr->next;
    }
    cout<<endl;
}

Department* Company::getDepartment(int index){
    Department *ptr = firstDepartment;
    for(int i = 0; i<index; i++){
        ptr = ptr->next;
    }
    return ptr;
}

class Employer: public Employee{
    public:
        Employer(){}
        Employer(Department *department, Details *d){
            details = d;
            this->department = department;
        }
};


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
    if(company==nullptr){

    }
    cout<<"___ Employee Management System ____\n";
    cout<<"    by Mukund Kukreja AIML1\n";
    printOperations(company);

    while(true){
        cout<<"Enter an operation b/w 1 to 10: ";
        int input;
        cin>>input;
        if(input==-1) break;

        switch (input)
        {
        case 1:
            TBI();
            break;
        case 2:
            TBI();
            break;

        case 3:
            cout<<"---> OPER 3: Display Departments in "<<company->companyName<<endl;
            cout<<"Departments in "<<company->companyName<<" are:\n";
            company->displayDepartments();
            break;

        case 4:
            TBI();
            break;
        case 5:
            TBI();
            break;
        case 6:
            TBI();
            break;

        case 7:
            cout<<"---> OPER 7: Display Employees in department...\n\n";
            cout<<"     Departments in "<<company->companyName<<" are:\n";
            company->displayDepartments("     ");
            cout<<"   --> Select a department from above: ";
            int depIndex1;
            cin>>depIndex1;
            company->getDepartment(depIndex1-1)->displayEmployees("       ");
            break;

        case 8:
            cout<<"---> OPER 8: Add a new Employee in department...\n\n";
            cout<<"     Departments in "<<company->companyName<<" are:\n";
            company->displayDepartments("     ");
            cout<<"   --> Select a department from above: ";
            int depIndex2;
            cin>>depIndex2;
            company->getDepartment(depIndex2-1)->makeAndAddEmployee();
            break;

        case 9:
            TBI();
            break;

        case 10:
            cout<<"---> OPER 10: Display all employees in "<<company->companyName<<endl<<endl;
            company->displayAllEmployees();
            break;

        default:
            cout<<"\nEnter a valid command between 1 to 10!\n";
            break;
        }
    }


}

int main(){
    Details Harish = Details("Harish",19,"11 April 2003","Near Gyan Ganga","1234567890");
    Company Harish_Ki_Dukaan = Company("Harish Ki Dukaan", Harish);
    Department* SanitoryDepartment = new Department("Sanitory Department");
    Department* FoodDepartment = new Department("Food Department");
    Department* AccountingDepartment = new Department("Accounting Department");
    

    Employee* A = new Employee();
    A->details = new Details("A",11);
    Employee* B = new Employee();
    B->details = new Details("B",12);
    Employee* C = new Employee();
    C->details = new Details("C",13);
    Employee* D = new Employee();
    D->details = new Details("D",14);

    SanitoryDepartment->addEmployee(A);
    SanitoryDepartment->addEmployee(B);
    FoodDepartment->addEmployee(C);
    AccountingDepartment->addEmployee(D);

    Harish_Ki_Dukaan.addDepartment(SanitoryDepartment);
    Harish_Ki_Dukaan.addDepartment(FoodDepartment);
    Harish_Ki_Dukaan.addDepartment(AccountingDepartment);

    startProgram(&Harish_Ki_Dukaan);

    
    // Harish_Ki_Dukaan.displayDepartments();
    // SanitoryDepartment->displayEmployees();
    // SanitoryDepartment->makeAndAddEmployee();
    // SanitoryDepartment->makeAndAddEmployee();
    // SanitoryDepartment->displayEmployees();
}