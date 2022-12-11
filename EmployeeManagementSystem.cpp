#include <iostream>
#include <string>
using namespace std;

class Details{
    public:
        string name;
        int age;
        string DOB;
        string address;
        string phoneNumber;

        Details(string name, int age, string DOB = "---", string address = "---", string phoneNumber = "---"){
            this->name = name;
            this->age = age;
            this->DOB = DOB;
            this->address = address;
            this->phoneNumber = phoneNumber;
        }

        static Details* getDetailsFromUser(string person = "Person's",string startPadding = "    "){
                string name,DOB,address,phoneNo;
                int age;
                cout<<startPadding<<"   Enter "<<person<<" Name: "; getline(std::cin >> std::ws,name);
                cout<<startPadding<<"   Enter "<<name<<"'s Age: "; cin>>age;
                cout<<startPadding<<"   Enter "<<name<<"'s Date of Birth: "; getline(std::cin >> std::ws,DOB);
                cout<<startPadding<<"   Enter "<<name<<"'s Address: "; getline(std::cin >> std::ws,address);
                cout<<startPadding<<"   Enter "<<name<<"'s Phone Number: "; getline(std::cin >> std::ws,phoneNo);
                return new Details(name,age,DOB,address,phoneNo);
        }
};

class Department;
class Company;

class Employee{
    public:
        Details *details;
        string companyName = "---", departmentName = "---", post = "---";
        string id, password = "abcd";
        float annualSalary;
        int leaveCount = 0;
        Employee *prev=nullptr, *next=nullptr;

        Employee(){}

        Employee(string name, int age,float salary,int leaves=0, string DOB = "---", string address = "---", string phoneNumber = "---",string post="---",string departmentName="---"){
            details = new Details(name,age,DOB,address,phoneNumber);
            this->post = post;
            this->leaveCount = leaves;
            this->annualSalary = salary;
            this->departmentName = departmentName;
        }

        static Employee* makeEmployee(string startPadding = "   "){
            cout<<startPadding<<"   --> Make New Employee: \n";
            Employee* newEmp = new Employee();
            newEmp->details = Details::getDetailsFromUser("Employee's",startPadding);
            cout<<startPadding<<"   Enter "<<newEmp->details->name<<"'s Annual Salary: ";cin>>(newEmp->annualSalary);
            return newEmp;
        }

        void displayDetails(int curSalary,string heading ="Employee Details:",string startPadding = "     "){
                cout<<startPadding<<heading<<"\n";
                startPadding += "  ";
                cout<<startPadding<<"Name: "<<details->name<<endl;
                cout<<startPadding<<"Department: "<<departmentName<<endl;
                cout<<startPadding<<"Post: "<<post<<endl;
                cout<<startPadding<<"Age: "<<details->age<<endl;
                cout<<startPadding<<"Date of Birth: "<<details->DOB<<endl;
                cout<<startPadding<<"Address: "<<details->address<<endl;
                cout<<startPadding<<"Phone Number: "<<details->phoneNumber<<endl;
                cout<<startPadding<<"Number of Leaves: "<<leaveCount<<endl;
                cout<<startPadding<<"Total Annual Salary: "<<annualSalary<<endl;
                cout<<startPadding<<"Current Salary: "<<to_string(curSalary)<<endl;
            }
};

class Company{
    public:
        Employee* CEO=nullptr;
        string companyName="---";
        Department* ManagementDepartment = nullptr;
        Company *prev=nullptr, *next=nullptr;

        Company(string companyName);

        string getSalaryPolicy(string startPadding = "        "){

            string salaryPolicy = "\n";
            salaryPolicy += startPadding;
            salaryPolicy += "---> ";
            salaryPolicy += companyName;
            salaryPolicy += "'s Salary Policy <---\n\n";

            salaryPolicy += startPadding;
            salaryPolicy += " * Salary of an employee is affected by the number of leaves they've taken.\n";

            salaryPolicy += startPadding;
            salaryPolicy += " * The number of paid leaves allowed in ";
            salaryPolicy += companyName;
            salaryPolicy += " are ";
            salaryPolicy += to_string(noOfLeavesAllowed);
            salaryPolicy += " in ";
            salaryPolicy += to_string(workingDays);
            salaryPolicy += " working days.\n";

            salaryPolicy += startPadding;
            salaryPolicy += " * Any more leaves than that will result in ";
            salaryPolicy += to_string(salaryReductionPercentage);
            salaryPolicy += "% salary reduction for each leave.";

            return salaryPolicy;
        }

        Department* makeAndAddDepartment(string startPadding = "   ");
        Department* addDepartment(Department *department,string startPadding = "   ");
        Department* getDepartment(int index);
        Department* selectADepartment(string startPadding = "    ");

        void displayDepartments(string startPadding = "    ");
        void displayAllEmployees(string startPadding = "    ");
        void displayAllEmployeesWithDepartments(string startPadding = "    ");

        Employee* setCEO(Employee* emp);
        Employee* makeAndAddCEO(string startPadding = "    ");

        Employee* getEmployeeFromIndex(int index){
            if(index>noOfEmployees) return nullptr;
            Employee *ptr = firstEmployeeOfCompany;
            for(int i = 0; i<index; i++){
                ptr = ptr->next;
            }
            return ptr;
        }

        Employee* selectAnEmployee(string startPadding = "    "){
            displayAllEmployees(startPadding);
            cout<<"\n   --> Select an employee from above: ";
            while(true){
                int empIndexShowEmp;
                cin>>empIndexShowEmp;
                Employee* emp = getEmployeeFromIndex(empIndexShowEmp-1);
                if(emp==nullptr)cout<<"       Select a valid employee: ";
                else return emp;
            }
        }

        Employee* getEmployeeFromId(string id){
            Employee* ptr = firstEmployeeOfCompany;
            while(ptr!=nullptr && ptr->id!=id){
                ptr = ptr->next;
            }
            return ptr;
        }

        float getEmployeeSalary(Employee *emp){
            if((emp->leaveCount)<=noOfLeavesAllowed) return emp->annualSalary;
            float oneDaySalary = (emp->annualSalary)/workingDays;
            float oneDayReduction = (oneDaySalary * salaryReductionPercentage)/100;
            float amountToBeReducted = oneDayReduction * ((emp->leaveCount)-noOfLeavesAllowed);
            return ((emp->annualSalary) - amountToBeReducted);
        }

    private:
        Department *firstDepartment = nullptr, *lastDepartment = nullptr;
        Employee *firstEmployeeOfCompany = nullptr, *lastEmployeeOfCompany = nullptr;
        string adminPassword = "MakaM";
        int noOfDepartments = 0, noOfEmployees = 0;
        int noOfLeavesAllowed = 3, workingDays = 200;
        float salaryReductionPercentage = 69;

        friend class Department;

        friend bool startProgramForEmployee(Company *company,Employee *emp);
        friend bool startProgramForAdmin(Company *company);
        friend bool login(Company *company);

        friend Company* makeANewCompany(Company *lastCompany);
};

class Department{
    public:
        string departmentName = "---";
        Employee* HOD = nullptr;
        Company *company = nullptr;
        Department *next = nullptr;
        Department *prev = nullptr;
        int noOfEmployees = 0;

        Department(string name){departmentName = name;}

        Employee* makeAndAddEmployee(bool makeHOD = false,string startPadding = "   "){
            cout<<startPadding<<"    --> Add an Employee in "<<departmentName<<endl;
            Employee* newEmp = Employee::makeEmployee("       ");
            string post;
            if(makeHOD) post = "HOD";
            else { 
                cout<<startPadding<<"       Enter Employee's post in "<<departmentName<<": "; 
                getline(cin>>ws,post);
            }
            startPadding += "       ";
            cout << startPadding << newEmp->details->name << "'s ID: "<< getEmployeeId(newEmp)<<endl;
            cout << startPadding << newEmp->details->name << "'s Password: "<< newEmp->password<<endl;
            return addEmployee(newEmp,post,makeHOD,startPadding);
        }

        void setHOD(Employee* emp){
            if(HOD!=nullptr) HOD->post = "---";
            if(emp->post!="---" && emp->post!="HOD") emp->post += ", HOD";
            else emp->post = "HOD";
            emp->departmentName = departmentName;
            HOD = emp;
        }

        string getEmployeeId(Employee* emp){
            string id = company->companyName.substr(0,3);
            id += departmentName.substr(0,3);
            id += to_string(company->noOfEmployees);
            return id;
        }

        Employee* addEmployee(Employee *emp,string post="---",bool makeHOD = false,string startPadding = "   "){
            emp->departmentName = departmentName;
            emp->id = getEmployeeId(emp);
            emp->companyName = company->companyName;
            emp->post = post;

            if(noOfEmployees==0){
                emp->next = nullptr;
                while(this->prev!=nullptr && this->prev->lastEmployee==nullptr) {
                    Department *temp = this->prev;
                    if(temp->prev!=nullptr) temp->prev->next = this;
                    else company->firstDepartment = this;
                    if(this->next!=nullptr) this->next->prev = temp;
                    else company->lastDepartment = temp;
                    temp->next = this->next;
                    this->prev = temp->prev;
                    temp->prev = this;
                    this->next = temp;
                    if(this==company->lastDepartment) company->lastDepartment = temp;
                }
                if(this->prev != nullptr && this->prev->lastEmployee != nullptr){
                    this->prev->lastEmployee->next = emp;
                    emp->prev = this->prev->lastEmployee;
                }
                else emp->prev = nullptr;
                if(this->next != nullptr && this->next->firstEmployee != nullptr) {
                    this->next->firstEmployee->prev = emp;
                    emp->next = this->next->firstEmployee; 
                }
                else emp->next = nullptr;
                this->firstEmployee = emp;
                this->lastEmployee = emp;
            }
            else{
                emp->prev = lastEmployee;
                emp->next = lastEmployee->next;
                lastEmployee->next = emp;
                lastEmployee = emp;
            }

            if(emp->next == nullptr) company->lastEmployeeOfCompany = emp;
            
            if(this==company->firstDepartment && company->noOfEmployees == 0) company->firstEmployeeOfCompany = emp;
            if(this==company->lastDepartment) company->lastEmployeeOfCompany = emp; 

            noOfEmployees++;
            (company->noOfEmployees)++;
            if(makeHOD) setHOD(emp);
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

        Employee* getEmployeeByIndex(int index){
            if(index > noOfEmployees) return nullptr;
            Employee *ptr = firstEmployee;
            for(int i = 0; i<index; i++){
                ptr = ptr->next;
            }
            return ptr;
        }

        Employee* selectAnEmployee(string startPadding){
            if(noOfEmployees==0) return nullptr;
            displayEmployees(startPadding);
            cout<<"\n   --> Select an employee from above: ";
            while(true){
                int empIndexShowEmp;
                cin>>empIndexShowEmp;
                Employee* emp = getEmployeeByIndex(empIndexShowEmp-1);
                if(emp==nullptr) cout<<"       Select a valid employee: ";
                else return emp;
            }
        }

    private:
        Employee *firstEmployee = nullptr, *lastEmployee = nullptr;
};

Company::Company(string companyName){
    ManagementDepartment = new Department("Management Department");
    addDepartment(ManagementDepartment);
    this->companyName = companyName;
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
}

void Company::displayAllEmployees(string startPadding){
    cout<<startPadding<<"All Employees at "<<companyName<<": (Total "<<noOfEmployees<<")\n";
    Employee *ptr = firstEmployeeOfCompany;
    startPadding+="    ";
    int count = 1;
    while(ptr!=nullptr)
    {   
        cout<<startPadding<<count<<") "<<ptr->id<<" - "<<ptr->details->name<<" - "<<ptr->departmentName<<" - "<<ptr->post<<endl;
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

Employee* Company::setCEO(Employee* emp){
    if(CEO!=nullptr) CEO->post = "---";
    emp->departmentName = ManagementDepartment->departmentName;
    if(emp->post!="---" && emp->post!="CEO") emp->post += ", CEO";
    else emp->post = "HOD";
    CEO = emp;
    return CEO;
}

Employee* Company::makeAndAddCEO(string startPadding){
    cout<<startPadding<<"Enter "<<companyName<<"'s CEO's Details: \n";
    Employee* newCEO = Employee::makeEmployee(startPadding);
    startPadding += "   ";
    cout << startPadding << newCEO->details->name << "'s ID: "<< ManagementDepartment->getEmployeeId(newCEO)<<endl;
    cout << startPadding << newCEO->details->name << "'s Password: "<< newCEO->password<<endl;
    ManagementDepartment->addEmployee(newCEO,"CEO",true,startPadding);
    return setCEO(newCEO);
}

Department* Company::makeAndAddDepartment(string startPadding){
    string name;
    while(true){
        cout<<startPadding<<"Enter Department's name: "; 
        getline(cin >> std::ws,name);    
        if(name.length()<3) cout<<startPadding<<"Department's name cannot be less than 3 characters...\n\n";
        else break;
    }
    Department* newDep = new Department(name);
    return addDepartment(newDep);
}

Department* Company::addDepartment(Department *department,string startPadding){
    department->company = this;
    if(firstDepartment==nullptr) {
            firstDepartment = department;
        }
    else {
            lastDepartment->next = department;
        }
    department->prev = lastDepartment;
    lastDepartment = department;
    lastDepartment->next = nullptr;
    noOfDepartments++;
    return department;
}

Department* Company::getDepartment(int index){
    if(index>noOfDepartments) return nullptr;
    Department *ptr = firstDepartment;
    for(int i = 0; i<index; i++){
        ptr = ptr->next;
    }
    return ptr;
}

Department* Company::selectADepartment(string startPadding){
    cout<<"     Departments in "<<companyName<<" are:\n";
    displayDepartments("     ");
    cout<<endl<<startPadding<<"--> Select a department from above: ";
    while(true){
        int depIndexDisplayEmps;
        cin>>depIndexDisplayEmps;
        Department* dep = getDepartment(depIndexDisplayEmps-1);
        if(dep==nullptr)cout<<startPadding<<"Select a valid department:";
        else return dep;
    }
}


Company* getExampleCompany(){
    Employee *Harish = new Employee("Harish",19,100000,0,"11 April 2003","Near Gyan Ganga","1234567890");

    Company* Harish_Ki_Dukaan = new Company("Harish Ki Dukaan");

    Department* SanitoryDepartment = new Department("Sanitory Department");
    Department* FoodDepartment = new Department("Food Department");
    Department* AccountingDepartment = new Department("Accounting Department");
    
    Harish_Ki_Dukaan->addDepartment(SanitoryDepartment);
    Harish_Ki_Dukaan->addDepartment(FoodDepartment);
    Harish_Ki_Dukaan->addDepartment(AccountingDepartment);

    Employee* Manish = new Employee("Manish",11,19219,3,"20 Nov 2003","Near Falana","1234658972");
    Employee* B = new Employee("B",12,21342,4);
    Employee* C = new Employee("C",13,34523,5);
    Employee* D = new Employee("D",14,213,6);
    Employee* Hod1 = new Employee("HOD 1",15,13321,7);
    Employee* Hod2 = new Employee("HOD 2",16,342523,8);
    Employee* Hod3 = new Employee("HOD 3",17,32435,9);

    Harish_Ki_Dukaan->ManagementDepartment->addEmployee(Harish,"---",true);
    Harish_Ki_Dukaan->setCEO(Harish);
    
    SanitoryDepartment->addEmployee(Hod1,"HOD",true);
    SanitoryDepartment->addEmployee(Manish,"Janitor");
    SanitoryDepartment->addEmployee(B,"Washer");

    FoodDepartment->addEmployee(Hod2,"HOD",true);
    FoodDepartment->addEmployee(C,"Chef");

    AccountingDepartment->addEmployee(Hod3,"HOD",true);
    AccountingDepartment->addEmployee(D,"Accountant");

    return Harish_Ki_Dukaan;
}

Company* makeANewCompany(Company *lastCompany){
    string companyName;
    cout<<"\n--> Make a new Company\n";
    while(true){
        cout<<"    Enter Company's name: ";
        getline(cin>>ws,companyName);
        if(companyName.length()<3) cout<<"    Company's name cannot be less than 3 characters...\n\n";
        else break;
    }
    Company* newCompany = new Company(companyName);
    cout<<endl;
    newCompany->makeAndAddCEO("    ");
    cout<<"    Default Admin Password: "<<newCompany->adminPassword<<endl;
    cout<<"    Default Employee Password: "<<newCompany->CEO->password<<endl;
    cout<<"    Login as Employee or Admin to change their respective passwords..\n";
    
    newCompany->prev = lastCompany;
    if(lastCompany != nullptr) lastCompany->next = newCompany;
    lastCompany = newCompany;

    return newCompany;
}

Company* getCompanyByIndex(Company* firstCompany,int index){
    Company* ptr = firstCompany;
    int count = 1;
    while(count<index){
        ptr = ptr->next;
        count++;
    }
    return ptr;
}


void printAdminOperations(Company *company){
    cout<<"\nAdmin Operations:\n";
    
    cout<<"   0. Print Operations\n";

    cout<<"\n --> Company\n";
    cout<<"   1. Display CEO details\n";
    cout<<"   2. Change CEO\n";

    cout<<"\n --> Department\n";
    cout<<"   3. Display Departments in "<<company->companyName<<endl;
    cout<<"   4. Add a new department\n";
    cout<<"   5. Display HOD details\n";
    cout<<"   6. Change HOD\n";

    cout<<"\n --> Employee\n";
    cout<<"   7. Display Employees in department...\n";
    cout<<"   8. Add a new Employee in department...\n";
    cout<<"   9. Display an Employee details...\n";
    cout<<"  10. Display all employees in "<<company->companyName<<endl;

    cout<<"\n --> Salary\n";
    cout<<"  11. View "<< company->companyName <<"'s Salary Policy\n";
    cout<<"  12. Change "<< company->companyName <<"'s Salary Policy\n";
    

    cout<<"\n --> Other\n";
    cout<<"  13. Change Admin Password"<<endl;
    cout<<"  14. Logout"<<endl;
    cout<<"  15. Exit"<<endl;
}

void printEmployeeOperations(Company* company){
    cout<<"\n Employee Operations:\n";
    cout<<"0. Display Operations\n";
    cout<<"1. View your current salary status\n";
    cout<<"2. View "<<company->companyName<<"'s salary policy\n";
    cout<<"3. Change your password\n";
    cout<<"4. Logout\n";
    cout<<"5. Exit\n";
}

int printCompanies(Company *firstCompany){
    cout<<"\nCOMPANIES: \n";
    Company* ptr = firstCompany;
    int count = 1;
    while(ptr!=nullptr){
        cout<<count<<") "<<ptr->companyName<<endl;
        ptr = ptr->next;
        count++;
    }
    return count;
}


bool startProgramForAdmin(Company *company){
    cout<<"\nLogged in as Admin..\n";

    printAdminOperations(company);

    string spaceA = "    ";
    string space2A = "        ";

    while(true){
        cout<<"\nEnter an operation b/w 1 to 15: ";
        int input;
        cin>>input;
        if(input==15) return false;
        switch (input){
            case 0: // Display Operations
            {
                printAdminOperations(company);
                break;
            } 
            case 1: // Display CEO Details
            {
                cout<<"---> OPER 1: Display CEO details\n\n";
                company->CEO->displayDetails(company->getEmployeeSalary(company->CEO),"CEO Details:");
                break;
            }
                
            case 2: // Change CEO
            {
                cout<<"---> OPER 6: Change CEO of "<<company->companyName<<"\n\n";
                if(company->CEO!=nullptr) cout<<spaceA<<"Current CEO of "<<company->companyName<<": "<<company->CEO->details->name<<endl;
                if((company->noOfEmployees)>0){
                    cout<<spaceA<<" --> Options:\n";
                    cout<<space2A<<"1) Promote pre-exisiting employee to the post of CEO of "<<company->companyName<<endl;
                    cout<<space2A<<"2) Make a new CEO\n";
                    while(true){
                        int makeNewHodInput;
                        cout<<space2A<<"Enter 1 or 2: "; cin>>makeNewHodInput;
                        if(makeNewHodInput == 2){
                            company->makeAndAddCEO();
                            break;
                        } 
                        else if(makeNewHodInput == 1){
                            Employee* emp = company->selectAnEmployee(space2A);
                            if(emp!=nullptr) company->setCEO(emp);
                            break;
                        }
                    }
                }
                else company->makeAndAddCEO();
                cout<<spaceA<<company->CEO->details->name<<" is the new CEO of "<<company->companyName<<endl;
                break;
            }

            case 3: // Display All Departments
                {
                    cout<<"---> OPER 3: Display Departments in "<<company->companyName<<endl;
                    cout<<space2A<<"Departments in "<<company->companyName<<" are:\n";
                    company->displayDepartments(space2A);
                    break;
                }

            case 4: // Add New department
                {
                    cout<<"---> OPER 4: Add a new Deparment in "<<company->companyName<<"\n\n";
                    Department* department = company->makeAndAddDepartment(spaceA);
                    cout<<spaceA<<"! Added "<<department->departmentName<<" to "<<company->companyName<<" !"<<endl;
                    break;
                }

            case 5: // Display HOD Details
                {
                    cout<<"---> OPER 5: Display HOD details\n\n";
                    if((company->noOfDepartments)>0){
                        Department* dep = company->selectADepartment("     ");
                        string heading = "HOD of ";
                        heading+=dep->departmentName;
                        heading+=": ";
                        if(dep!=nullptr){
                            if(dep->HOD==nullptr) cout<<space2A<<" "<<dep->departmentName<<" has no HOD :(\n";
                            else dep->HOD->displayDetails(company->getEmployeeSalary(dep->HOD),heading,space2A);
                        }
                    }
                    else cout<<space2A<<"There are no Departments in "<<company->companyName<<" :("<<endl;
                    break;
                }

            case 6: // Change HOD
            {
                cout<<"---> OPER 6: Change HOD of department...\n\n";
                if((company->noOfDepartments)>0){
                    Department* dep = company->selectADepartment();
                    if(dep!=nullptr && dep->HOD!=nullptr) cout<<spaceA<<"Current HOD of "<<dep->departmentName<<": "<<dep->HOD->details->name<<endl;
                    if((dep->noOfEmployees)>0){
                        cout<<spaceA<<" --> Options:\n";
                        cout<<space2A<<"1) Promote pre-exisiting employee to the post of HOD of "<<dep->departmentName<<endl;
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
                    }
                    else dep->makeAndAddEmployee(true);
                    cout<<spaceA<<dep->HOD->details->name<<" is the new HOD of "<<dep->departmentName<<endl;
                }
                else cout<<"There are no Departments in "<<company->companyName<<" :("<<endl;
                break;
            }

            case 7: // Display Employees in department
            {
                cout<<"---> OPER 7: Display Employees in department...\n\n";
                if((company->noOfDepartments)>0){
                    Department* dep = company->selectADepartment();
                    if(dep!=nullptr) dep->displayEmployees("       ");
                }
                else cout<<"There are no Departments in "<<company->companyName<<" :("<<endl;
                break;
            }

            case 8: // Add New employee 
            {
                cout<<"---> OPER 8: Add a new Employee in department...\n\n";
                if((company->noOfDepartments)>0){
                    Department* dep = company->selectADepartment();
                    if(dep!=nullptr) {
                        Employee* emp = dep->makeAndAddEmployee();
                        cout<<endl<<spaceA<<"! Added "<<emp->details->name<<" in "<<emp->departmentName<<" !\n\n";
                    }
                }
                else cout<<"There are no Departments in "<<company->companyName<<" :("<<endl;
                break;
            }

            case 9: // Display An Employee
            {
                cout<<"---> OPER 9: Display an Employee details...\n\n";
                if((company->noOfEmployees)>0){
                    Employee* emp = company->selectAnEmployee();
                    if(emp!=nullptr) emp->displayDetails(company->getEmployeeSalary(emp),"Employee Details:","          ");
                }
                else cout<<"There are no Employees in "<<company->companyName<<" :("<<endl;
                break;
            }

            case 10: // Display All Employees in Company
            {
                cout<<"---> OPER 10: Display all employees in "<<company->companyName<<endl<<endl;
                company->displayAllEmployees();
                break;
            }

            case 11: // View Salary Policy
            {  
                cout<<"---> OPER 11: View "<<company->companyName<<"'s Salary Policy"<<endl<<endl;
                cout<<company->getSalaryPolicy()<<endl;
                break;
            }

            case 12: // Change Salary Policy
            {   
                cout<<"---> OPER 12: Change "<<company->companyName<<"'s Salary Policy"<<endl<<endl;
                cout<<spaceA<<"Current Salary Policy: ";
                cout<<company->getSalaryPolicy()<<endl<<endl;
                int input;
                cout<<space2A<<"1. Change reduction percentage..\n";
                cout<<space2A<<"2. Change number of paid leaves..\n";
                cout<<space2A<<"3. No further changes to be done\n";
                while(true){
                    cout<<endl<<space2A<<"Enter from 1 to 3: "; cin>>input;
                    if(input==1){
                        cout<<endl<<space2A<<"Current reduction percentage: "<<company->salaryReductionPercentage<<endl;
                        cout<<space2A<<"New reduction percentage: "; cin >> (company->salaryReductionPercentage);
                        cout<<space2A<<(company->salaryReductionPercentage)<<" is the new salary reduction percentage for "<<company->companyName<<"!!\n";
                    }
                    else if(input == 2){
                        cout<<endl<<space2A<<"Current number of paid leaves: "<<company->noOfLeavesAllowed<<endl;
                        cout<<space2A<<"New number of paid leaves: "; cin >> (company->noOfLeavesAllowed);
                        cout<<space2A<<(company->noOfLeavesAllowed)<<" is the new number of paid leaves allowed in "<<company->companyName<<"!!\n";
                    }
                    else if(input == 3) break;
                    else cout<<space2A<<"Invalid input..\n";
                }
                break;
            }

            case 13:
            {   
                cout<<"---> OPER 11: Change Admin Password\n";
                string curPassword;
                while(true){
                    cout<<space2A<<"Enter current admin password: "; getline(cin>>ws,curPassword);
                    if(curPassword!=company->adminPassword) cout<<space2A<<"Wrong password.. Try again\n\n";
                    else {
                        cout<<space2A<<"Enter new admin password: "; getline(cin>>ws,(company->adminPassword));
                        cout<<space2A<<"Admin Password successfully changed!!\n";
                        break;
                    }
                }
                break;
            }
            case 14: // Logout
            {
                return true;
            }
            default: // Invalid Input
            {
                cout<<"\nEnter a valid command between 1 to 10!\n";
                break;
            }
        }
        cout<<"_________________________________________________________________\n";
    }


}

bool startProgramForEmployee(Company *company,Employee *emp){
    cout<<"\nLogged in as "<<emp->details->name<<"..\n\n";
    emp->displayDetails(company->getEmployeeSalary(emp),"Your Details: ","");
    printEmployeeOperations(company);

    int input;
    while (true)
    {   
        cout<<"\nEnter from 0 to 5: ";
        cin>>input;
        if(input==5) return false;
        switch (input)
        {   
            case 0: // Display Employee Operations
            {
                printEmployeeOperations(company);
                break;
            }
            case 1: // Employee's Salary Status
            {
                cout<<"\n       ---> Your Salary Status <---\n"<<endl;
                cout<<"Your annual salary is "<<to_string(emp->annualSalary)<<endl;
                cout<<"The company allowes "<<to_string(company->noOfLeavesAllowed)<<" paid leaves in "<<to_string(company->workingDays)<<" working days."<<endl;
                cout<<"You've taken "<<to_string(emp->leaveCount)<<" leaves so far.." <<endl;
                string extraLeaves = "0";
                if((emp->leaveCount) > (company->noOfLeavesAllowed)) extraLeaves = to_string((emp->leaveCount) - (company->noOfLeavesAllowed));
                cout<<"After "<<to_string(company->salaryReductionPercentage)<<"% salary reduction for your "<<extraLeaves<<" extra leaves, your salary for this year comes out to be: "<<company->getEmployeeSalary(emp)<<endl;
                break;
            }                
            case 2: // Company's Salary Policy
            {
                cout<<company->getSalaryPolicy()<<endl;
                break;
            }          
            case 3: // Change Password
            {
                cout<<"--> Change your password\n";
                string curPassword;
                while(true){
                    cout<<"    Enter your current password: "; getline(cin>>ws,curPassword);
                    if(curPassword!=emp->password) cout<<"    Wrong password.. Try again\n\n";
                    else {
                        cout<<"    Enter new password: "; getline(cin>>ws,(emp->password));
                        cout<<"    Password successfully changed!!\n";
                        break;
                    }
                }
                break;
            }      
            case 4: // Logout
            {
                return true;
            }                
            default: // Invalid Input
            {
                cout<<"Enter a valid operation!\n";
                break;
            }
        }
        cout<<"_______________________________________________________________________________________________\n";
    }
    
}

bool login(Company *company){
    bool keepRunning = true;
        while(keepRunning){
        cout<<"\n       ----------------------------\n\n" ;
        cout<<"             "<<company->companyName<<"\n\n" ;
        cout<<"       ----------------------------\n\n" ;
        
        cout<<"[ Press -1 to exit program OR 0 to go back to all companies ]\n";
        cout<<"1) Admin\n";
        cout<<"2) Employee\n";
        cout<<"--> You are: ";
        int input;
        string userId = "admin";
        string password;
        while(true){
            cin>>input;
            if(input == -1) return false;
            if(input == 0) return true;
            if(input == 1){
                cout<<"\n   Login as Admin\n\n";
                cout<<"Welcome Admin..\n";
                cout<<"Enter your Password: ";
                getline(cin>>ws,password);
                while(password!=company->adminPassword){
                    cout<<"Incorrect password! Enter a valid password: ";
                    getline(cin>>ws,password);
                }
                keepRunning = startProgramForAdmin(company);
                cout<<"Logging out...\n\n\n";
                break;
            }
            else if(input == 2){
                cout<<"\n   Login as Employee\n\n";
                cout<<"Enter your ID: ";
                getline(cin>>ws,userId);
                Employee *emp = company->getEmployeeFromId(userId);
                while(emp==nullptr){
                    cout<<"ID not found.. Enter a valid ID: ";
                    getline(cin>>ws,userId);
                    emp=company->getEmployeeFromId(userId);
                }
                cout<<"Welcome "<<emp->details->name<<"..\n";
                cout<<"Enter your Password: ";
                getline(cin>>ws,password);
                while(emp->password!=password){
                    cout<<"Incorrect password! Enter a valid password: ";
                    getline(cin>>ws,password);
                }
                keepRunning = startProgramForEmployee(company,emp);
                cout<<"Logging out...\n\n\n";
                break;
            }
            cout<<"Select a valid option: ";
        }
    }
}

void startProgram(){
    cout<<"__ Employee Management System __\n";
    cout<<"    by Team MakaM AIML1\n"; 

    Company *firstCompany = getExampleCompany();
    Company *lastCompany = firstCompany;

    int input;
    bool keepRunning = true;
    while(keepRunning)
    {   
        cout<<"\n[ Enter -1 to exit program. ]";
        int count = printCompanies(firstCompany);
        cout<<(count)<<") Make a new Company\n";
        cout<<"\nSelect a company: ";
        cin>>input;
        if(input == -1) return;
        else if(input<=count && input>0){
            if(input==count) {
                lastCompany = makeANewCompany(lastCompany);
                input = count;
            }
            keepRunning = login(getCompanyByIndex(firstCompany,input));
        }
        else cout<<"Enter between 1 to "<<count<<" please: \n";
        cout<<"_________________________________________________________________\n";
    }

}

int main(){
    startProgram();
    cout<<"\n       ---------------------------------\n";
    cout<<"\n       !! Ending Program !! Thank You :)\n";
    cout<<"\n       ---------------------------------\n";
}

/* 
1) display posts in ---> OPER 7: Display Employees in department...
2) COMMENTSSSSS
 */