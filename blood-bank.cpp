#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <windows.h>
#include <fstream>
using namespace std;

#define MAX_CAPACITY 100
///Date class
class Date
{
public:
    int day;
    int month;
    int year;

    Date(int a,int b,int c);
    void InputDate();
    void displayDate();
};
Date::Date(int a=1,int b=1,int c = 2021)
{
    day = a;
    month = b;
    year = c;
}
void Date::InputDate()
{
    cout << "\t\t\t\tDAY : "<<endl<<"\t\t\t\t\t";
    cin >> day;
    cout << "\t\t\t\tMONTH : "<<endl<<"\t\t\t\t\t";
    cin >> month;
    cout << "\t\t\t\tYEAR : "<<endl<<"\t\t\t\t\t";
    cin >> year;
}
void Date::displayDate()
{
    cout << day <<"/"<<month<<"/"<<year<<endl;
}
///date class

///time class
class Time
{
public:
    int hours;
    int minutes;
    int seconds;

    Time()
    {
        hours = minutes = seconds = 1;
    }
    void inputTime()
    {
        cout << "\t\t\t\tHOURS : "<<endl<<"\t\t\t\t\t";
        cin >> hours;
        cout << "\t\t\t\tMINUTES : "<<endl<<"\t\t\t\t\t";
        cin >> minutes;
        cout << "\t\t\t\tSECONDS : "<<endl<<"\t\t\t\t\t";
        cin >> seconds;
    }
    void displayTime()
    {
        cout << hours <<":"<<minutes<<":"<<seconds<<endl;
    }
};
///time class
class Donor;
///user class
class User
{
public:
    int ID;
    Date DOB;
    int age;
    string name;
    string address;
    string email_id;
    string gender;
    char choice;
    static int userNo;
    static User* ptr;

    operator Donor();
    char addUser(User user[],int search_id,int j);
    void deleteUser(User user[],int search_id);
    void editUser(User user[],int search_id);
    int searchUser(User user[],int search_id);
    void displayAllUsers(User user[]);
    ~User()
    {
        delete ptr;
    }
};
int User::userNo = 1;
User* User::ptr = 0;
///user class
class Donor;
///blood class
class Blood
{
public:
    int donor_id;
    int patient_id;
    string donor_name;
    string patient_name;
    string patient_blood;

    int searchBlood(User don[],string patient_blood,int patient_id);
    void addBlood(int donor_id,int patient_id);
};
///blood class
class Stock;
///order class
class Order
{
public :
    Stock* stk;
    Blood b;
    int blood_amt;
    string blood_type;
    Time due_time;

    void connectToStock(Stock* stock);
    void addOrder(int patient_id,string blood_group,int amt,Time& time);
    void editOrder(int patient_id,string blood_group,int amt,Time& time);
};
///order class

///stock class
class Stock
{
public:
    Order* orde;
    Blood b;
    string blood_type[8];
    static int blood_qty[8];
    Time refill_time;

    Stock()
    {
        blood_type[0] = "O+ve";
        blood_type[1] = "O-ve";
        blood_type[2] = "A+ve";
        blood_type[3] = "A-ve";
        blood_type[4] = "B+ve";
        blood_type[5] = "B+ve";
        blood_type[6] = "AB+ve";
        blood_type[7] = "AB+ve";
    }
    void connectToOrder(Order* ord)
    {
        orde = ord;
    }
    void addStock(string bType,int amt);
    void editStock(string bType,int amt);
    void searchStock(string bTYpe,int amt);
    void viewStock();
};
int Stock::blood_qty[8] = {0,0,0,0,0,0,0,0};
///stock class

///donor class
class Donor:public User
{
public:
    Stock stc;
    Time donate_time;
    int donor_id;
    int blood_amt;
    float weight;
    int age;
    static int donorNo;
    char eligibility[5];
    string blood_type;

    void donorDetails();
    bool donorEligibility();
};
int Donor::donorNo = 1;
///donor class

///patient class
class Patient
{
public :
    Order ord;
    Time order_time;
    int patient_id;
    int blood_amt;
    string blood_type;
    static int patientNo;

    void patientDetails(User don[],int c);
    int searchPatient(Patient patient[],int search_id);
};
int Patient::patientNo = 1;
///patient class

///function definitions
///User
char User::addUser(User user[],int search_id,int j)
{
    if(j<=userNo+1)
    {
        int result = searchUser(user,search_id);
        if(result)
        {
            cout << "\n\n\n\n\n\t\t\t\tACCOUNT ALREADY EXISTS"<<endl<<"\t\t\t\t\t";
        }
        else
        {
            //input details
            user[j].ID = search_id;
            userNo++;
            cout << "\n\n\t\t\t\tENTER YOUR NAME :"<<endl<<"\t\t\t\t\t";
            cin >> user[j].name;
            cout << "\t\t\t\tENTER YOUR DATE OF BIRTH :"<<endl;
            user[j].DOB.InputDate();
            cout << "\t\t\t\tENTER YOUR ADDRESS :"<<endl<<"\t\t\t\t\t";
            cin >> user[j].address;
            cout << "\t\t\t\tENTER YOUR EMAIL ID :"<<endl<<"\t\t\t\t\t";
            cin >> user[j].email_id;
            cout << "\t\t\t\tENTER YOUR GENDER :"<<endl<<"\t\t\t\t\t";
            cin >> user[j].gender;
            cout << "\t\t\t\tDO YOU WISH TO BE A DONOR OR A RECEPIENT (D/R) ?"<<endl<<"\t\t\t\t\t";
            cin >> user[j].choice;
            char Choice = user[j].choice;
        }
        j++;
    }
    else
    {
        cout << " \n\n\n\n\t\t\t\tMAXIMUM CAPACITY EXCEEDED "<<endl<<"\t\t\t\t\t";
    }
}
void User::deleteUser(User user[],int search_id)
{
   int j = 0;
   cout << userNo <<endl;
    if (userNo>=1)
    {
        if(searchUser(user,search_id))
        {
            while (j < userNo)
            {
                if (search_id == (user[j]).ID)
                    break;
                j++;
            }
            while(j < userNo-1)
            {
                user[j] = user[j+1];
            }
            ptr = &user[userNo-1];
            user[userNo].~User();
            cout << "\n\n\n\n\t\t\t\tDELETED"<<endl<<"\t\t\t\t\t";
            userNo--;
        }
        else
        {
            cout << "\n\n\n\n\t\t\t\tUSER NOT FOUND"<<endl<<"\t\t\t\t\t";
        }
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\tNO USERS YET" << endl<<"\t\t\t\t\t";
    }
}

int User::searchUser(User user[],int search_id)
{
    int i=1;
    int f = 0;
    while (i < userNo)
    {
        cout << user[i].ID<<endl;
        if (search_id == user[i].ID)
        {
            f++;
           return f;
           break;
        }

        i++;
    }
    return f;
}
void User::editUser(User user[],int search_id)
{
    int j = 0;
    int choice;
    if(userNo>=1 && userNo<=MAX_CAPACITY)
    {
        if(searchUser(user,search_id))
        {
            while (j < userNo)
            {
                if (search_id == user[j].ID)
                    break;
                j++;
            }
            cout << "\n\n\n\n\t\t\t\tENTER\n\t\t\t\t1.NAME\n\t\t\t\t2.ADDRESS\n\t\t\t\t3.MAIL ID\n\t\t\t\t"<<endl<<"\t\t\t\t\t";
            cin >> choice;
            switch(choice)
            {
                case 1:
                    {
                        cout << "\n\t\t\t\tNAME:"<<endl<<"\t\t\t\t\t";
                        cin >> name;
                        this->name = name;
                    }
                    break;
                case 2:
                    {
                        cout << "\n\t\t\t\tADDRESS:"<<endl<<"\t\t\t\t\t";
                        cin >> address;
                        this->address = address;
                    }
                    break;
                case 3:
                    {
                        cout << "\n\t\t\t\tMAIL ID:"<<endl<<"\t\t\t\t\t";
                        cin >> email_id;
                        this->email_id = email_id;
                    }
                    break;
                default:
                    cout << "\n\t\t\t\tINVALID CHOICE"<<endl<<"\t\t\t\t\t";
                    break;
            }
        }
    }
}
void User::displayAllUsers(User user[])
{
    int i = 1;
    if(userNo>1)
    {
        while(i < userNo)
        {
            cout << "\n\n\n\n\t\t\t\tUSER DATABASE"<<endl;
            cout <<"\t\t\t\tID:"<<user[i].ID;
            cout <<"\t\t\t\tNAME : "<<user[i].name<<endl<<"\t\t\t\t\t";
            i++;
        }
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\tNO USERS YET"<<endl;
    }

}
///User
///blood
int Blood::searchBlood(User don[],string patient_blood,int patient_id)
{
    int i = 0;
    int match = 0;
    while (i <= Donor::donorNo)
    {
        Donor d;
        d = don[i];
        if(patient_blood == d.blood_type)
        {
            match = d.donor_id;
            return match;
            break;
        }
    }
    return match;
}
void Blood::addBlood(int donor_id,int patient_id)
{
    fstream record;
    record.open("Blood Records.txt",ios::app);
    record << patient_id << "-----" << donor_id << endl;
    record.close();
}
///blood
///order
void Order::addOrder(int patient_id,string blood_group,int amt,Time& time)
{
    Stock s;
    char choice;
    cout << "\t\t\t\tORDER OF PATIENT               :"  << patient_id<<endl;
    cout << "\t\t\t\tBLOOD GROUP                    : " << blood_group <<endl ;
    cout << "\t\t\t\tAMOUNT OF BLOOD NEEDED (IN ML) : " << amt<< endl;
    cout << "\t\t\t\tDUE TIME                       :";
    time.displayTime();
    cout << "\n\t\t\t\tDO YOU WISH TO PROCEED WITH THE ORDER (Y/E/N) ?"<<endl<<"\t\t\t\t\t";
    cin >> choice;
    if(choice=='y' || choice=='Y')
    {
        Order::connectToStock(&s);
        stk->searchStock(blood_group,amt);
        stk->editStock(blood_group,amt);
    }
    else if(choice=='E' || choice=='e')
    {
        Order::editOrder(patient_id,blood_group,amt,time);
    }
    else
    {
        cout << "\t\t\t\tYOUR ORDER HAS BEEN CANCELLED "<<endl<<"\t\t\t\t\t";
    }

}

void Order::editOrder(int patient_id,string blood_group,int amt,Time& time)
{
    int ch;
    cout << "\t\t\t\tIN ORDER TO EDIT,ENTER\t\t\t\t1.BLOOD GROUP\nt\t\t\t2.QUANTITY REQUIRED"<<endl<<"\t\t\t\t\t";
    cin >> ch;
    cout << "\t\t\t\tPLEASE VERIFY YOUR DETAILS BEFORE ENTERING THEM"<<endl<<"\t\t\t\t\t";
    switch(ch)
    {
        case 1:
            {
                cout << "\t\t\t\tENTER YOUR BLOOD GROUP : "<<endl<<"\t\t\t\t\t";
                cin >> blood_type;
                this->blood_type = blood_type;
                Order::addOrder(patient_id,blood_type,amt,time);
            }
             break;
        case 2:
            {
                cout << "\t\t\t\tENTER THE QUANTITY REQUIRED : "<<endl<<"\t\t\t\t\t";
                cin >> blood_amt;
                this->blood_amt = blood_amt;
                Order::addOrder(patient_id,blood_group,blood_amt,time);
            }
            break;
        default:
            break;
    }
}
///order
///stock
void Order::connectToStock(Stock* stock)
{
   stk = stock;
}
void Stock::addStock(string bType,int amt)
{
    int i;
    for(i=0;i<8;i++)
    {
        if(bType == blood_type[i])
            break;
    }
    blood_qty[i] += amt;
    cout << "\t\t\t\tADDED TO STOCK"<<endl<<"\t\t\t\t\t";
}
void Stock::editStock(string bType,int amt)
{
    int i;
    for(i=0;i<8;i++)
    {
        if(bType == blood_type[i])
            break;
    }
    if(blood_qty[i]>=amt)
    {
        blood_qty[i] -= amt;
        cout << "\t\t\t\tDONATED FROM STOCK";
    }
    else
    {
        cout << "\t\t\t\tLOOKS LIKE WE ARE OUT OF SUPPLIES"<<endl;
    }

}
void Stock::searchStock(string bType,int amt)
{
    int i;

        for(i=0;i<8;i++)
        {
            if(bType==blood_type[i])
                break;
        }
        if(blood_qty[i]>0 && amt<=blood_qty[i])
        {
            cout << "\t\t\t\tBLOOD AVAILABLE IN STOCK" << endl<<"\t\t\t\t\t";
        }
        else
        {
            cout << "\t\t\t\tOOPS! WE RAN OUT OF STOCK "<<endl;
            cout << "\t\t\t\tAPPROXIMATE REFILL TIME : ";
            refill_time.displayTime();
            cout <<endl;
            Stock::viewStock();
        }

}
void Stock::viewStock()
{
    int i;
    cout << "\t\t\t\tAMOUNT AVAILABLE IN STOCK"<<endl;
    for (i=0;i<8;i++)
    {
        cout <<"\t\t\t\t"<<blood_type[i]<<" --- "<<blood_qty[i]<<" ML\t\t\t\t"<<endl;
    }
}
///stock
///Donor
User::operator Donor()
{
    Donor d;
    d.donor_id = ID;
    return d;
}
void Donor::donorDetails()
{
    cout<<"\t\t\t\tENTER BLOOD GROUP : "<<endl<<"\t\t\t\t\t";
    cin>>blood_type;
    cout<<"\t\t\t\tENTER THE AMOUNT OF BLOOD YOU WISH TO DONATE (IN ML) :"<<endl<<"\t\t\t\t\t";
    cin>>blood_amt;
    cout<<"\t\t\t\tENTER THE TIME OF DONATION : "<<endl;
    donate_time.inputTime();
    stc.addStock(blood_type,blood_amt);
    stc.viewStock();
}
bool Donor::donorEligibility()
{
    cout << "\n\n\n\n\t\t\t\tYOU ARE REQUESTED TO ANSWER THE FOLLOWING QUESTIONS "<<endl<<"\t\t\t\t";
    cout << "ENTER YOUR AGE : "<<endl<<"\t\t\t\t\t";
    cin >> age;
    cout << "\t\t\t\tENTER YOUR WEIGHT : "<<endl<<"\t\t\t\t\t";
    cin >>weight;
    cout << "\t\t\t\tDO YOU HAVE ANY INFECTIONS/ALLERGIES (Y/N) ?"<<endl<<"\t\t\t\t\t";
    cin >> eligibility[0];
    cout << "\t\t\t\tARE YOU SUFFERING FROM ANY BLEEDING PROBLEMS (Y/N) ?"<<endl<<"\t\t\t\t\t";
    cin >> eligibility[1];
    cout << "\t\t\t\tARE YOU SUFFERING FROM ANY OTHER DISEASES/DISORDERS (Y/N) ?"<<endl<<"\t\t\t\t\t";
    cin >> eligibility[2];
    cout << "\t\t\t\tHAVE YOU UNDERGONE A RECENT VACCINATION OR AN ORGAN TRANSPLANTATION (Y/N) ?"<<endl<<"\t\t\t\t\t";
    cin >> eligibility[3];
    cout << "\t\t\t\tHAVE YOU CONSUMED ALCOHOL IN THE PAST 24 HOURS (Y/N) ?"<<endl<<"\t\t\t\t\t";
    cin >> eligibility[4];
    int check = 0;
    if((eligibility[0]=='n'||eligibility[0]=='N') && (eligibility[1]=='n'||eligibility[1]=='N')&& (eligibility[2]=='n'||eligibility[2]=='N')&& (eligibility[3]=='n'||eligibility[3]=='N')&&(eligibility[4]=='n'||eligibility[4]=='N'))
    {
        check =1;
    }
    if(age>=18 && age<=65 && weight >=60 && check==1)
       {
           cout << "\t\t\t\tYOU ARE AN ELIGIBLE DONOR"<<endl;
           return true;
       }
    else
        {
            cout << "\t\t\t\tSORRY, YOU CANNOT DONATE BLOOD"<<endl;
            return false;
        }
}
///Donor
///patient
void Patient::patientDetails(User don[],int c)
{
    int choice;
    char ch;
    Blood b1;
    cout<<"\t\t\t\tENTER THE PATIENT'S BLOOD GROUP :\n\t\t\t\t1.O+ve\n\t\t\t\t2.O-ve\n\t\t\t\t3.A+ve\n\t\t\t\t4.A-ve\n\t\t\t\t5.B+ve\n\t\t\t\t6.B-ve\n\t\t\t\t7.AB+ve\n\t\t\t\t8.AB-ve"<<endl<<"\t\t\t\t\t";
    cin>>blood_type;
    cout<<"\t\t\t\tENTER THE AMOUNT OF BLOOD THE PATIENT REQUIRES (IN ML) : "<<endl<<"\t\t\t\t\t";
    cin>>blood_amt;
    cout<<"\t\t\t\tENTER THE AMOUNT OF TIME THE PATIENT NEEDS THE BLOOD BY : "<<endl;
    order_time.inputTime();
    cout <<"\n\t\t\t\tDO YOU WISH TO"<<endl;
    cout <<"\t\t\t\t1.RECEIVE BLOOD RIGHT AWAY\n\t\t\t\t2.FIND A MATCH FOR A LATER TIME"<<endl<<"\t\t\t\t\t";
    cin >> choice;
    if(choice==1)
    {
        system("CLS");
        cout << endl << "\t\t\t\tHERE'S YOUR ORDER"<<endl;
        ord.addOrder(patient_id,blood_type,blood_amt,order_time);
        Sleep(1500);
        system("CLS");
    }
    else if(choice==2)
    {
        system("CLS");
        cout << "\n\n\n\n\t\t\t\tDO YOU KNOW OF ANY DONORS (Y/N) ?"<<endl<<"\t\t\t\t\t";
        cin >>ch;
        if(ch=='Y' || ch=='y')
        {
            int donor_id;
            cout << "\t\t\t\tENTER DONOR ID"<<endl<<"\t\t\t\t\t";
            cin >> donor_id;
            if(don[c].searchUser(don,donor_id))
            {
                cout << "\t\t\t\tMATCHING DONOR FOUND"<<endl;
                b1.addBlood(donor_id,patient_id);
            }
            else
                cout <<"\t\t\t\tNO SUCH DONOR"<<endl;
        }
        else
        {
            int match = ord.b.searchBlood(don,blood_type,patient_id);
            cout << "\n\n\n\n\t\t\t\tHERE'S A PROSPECTIVE DONOR"<<endl<<"\t\t\t\t\t";
            cout <<match;
            b1.addBlood(match,patient_id);
        }
    }
    else
    {
        cout << "\n\t\t\t\tINVALID CHOICE";
    }

}

int Patient::searchPatient(Patient patient[],int search_id)
{
    int i=0;
    int f = 0;
    while (i < patientNo)
    {
        if (search_id == patient[i].patient_id)
        {
            f++;
           return f;
           break;
        }

        i++;
    }
    return f;
}

///main function
int main()
{
    int val1 = MAX_CAPACITY / 2;
    int val2 = MAX_CAPACITY / 2;
    int* capacityd = &val1;
    int* capacityp = &val2;
    User* u = new User[MAX_CAPACITY];
    Donor* d = new Donor[*capacityd];
    Patient* p = new Patient[*capacityp];
    int current_user = 1;
    int current_donor = 1;
    int current_patient = 1;
    char ch;
    int choice;


    do
    {
        cout << "\n\n\n\n\n\n\t\t\t\t---------------------------------------------------------------------------------"<<endl<<endl;
        cout << "\t\t\t\t----------------------------------BLOOD BANK---------------------------------------"<<endl<<endl;
        cout << "\t\t\t\t-----------------------------------------------------------------------------------"<<endl;
        cout << "\t\t\t\t-----------------------------------MAIN MENU---------------------------------------"<<endl;
        cout << "\t\t\t\tTHE BLOOD BANK FUNCTIONS ONLY WHEN THERE ARE EQUAL NUMBER OF DONORS AND RECEPIENTS"<<endl;
        cout << "\t\t\t\t1.ADD USER"<<endl;
        cout << "\t\t\t\t2.SEARCH USER"<<endl;
        cout << "\t\t\t\t3.EDIT USER DETAILS"<<endl;
        cout << "\t\t\t\t4.DELETE USER" << endl;
        cout << "\t\t\t\t5.VIEW ALL USERS"<<endl;

        cout <<endl;
        cout << "\t\t\t\tENTER YOUR CHOICE:";
        cin >> choice;

        switch(choice)
        {
            case 1:
                {
                    int search_id;
                    cout << "\t\t\t\tENTER THE USER'S ID TO BE ADDED:"<<endl<<"\t\t\t\t\t";
                    cin >> search_id;
                    char Choice = u[current_user].addUser(u,search_id,current_user);
                        current_user++;
                    if(Choice=='D'||Choice=='d')
                    {
                        if(Donor::donorNo <= *capacityd)
                        {
                            system("cls");
                            if(d[current_donor].donorEligibility())
                            {
                                u[current_user] = d[current_donor];
                                d[current_donor].donor_id = u[current_user].ID;
                                d[current_donor].donorDetails();
                                Sleep(1500);
                                current_donor++;
                                Donor::donorNo++;
                            }

                        }
                        else
                        {
                            cout << "\t\t\t\tOOPS! WE ARE RUNNING OUT OF STORAGE SPACE" << endl<<"\t\t\t\t\t";
                        }
                    }
                   else if(Choice == 'R' || Choice=='r')
                    {
                        int choice;
                        if(Patient::patientNo <= *capacityd)
                        {
                            system("cls");
                            p[current_patient].patient_id = u[current_user].ID;

                            {
                                system("cls");
                                p[current_patient].patientDetails(u,current_patient);
                                Sleep(1500);
                            }

                            current_patient++;
                            Patient::patientNo++;
                        }
                        else
                        {
                            cout << "\t\t\t\tOOPS! WE ARE RUNNING OUT OF SPACE" << endl<<"\t\t\t\t\t";
                        }
                    }
                }
                break;
            case 2:
                {
                    int search_id;
                    system("CLS");
                    cout << "\n\n\n\n\n\t\t\t\tENTER THE USER'S ID TO BE SEARCHED:"<<endl<<"\t\t\t\t\t";
                    cin >> search_id;
                    if(u[current_user].searchUser(u,search_id))
                        cout << "\t\t\t\tUSER FOUND"<<endl;
                }
                break;
            case 3:
                {
                    int search_id;
                    system("CLS");
                    cout << "\n\n\n\n\n\t\t\t\tENTER THE USER'S ID WHOSE DETAILS NEED TO BE EDITED:"<<endl<<"\t\t\t\t\t";
                    cin >> search_id;
                    u[current_user].editUser(u,search_id);

                }
                break;
            case 4:
                {
                    int search_id;
                    cout << "\n\n\n\n\n\t\t\t\tENTER THE USER'S ID WHOSE ACCOUNT NEEDS TO BE DELETED:"<<endl<<"\t\t\t\t\t";
                    cin >> search_id;
                    u[current_user].deleteUser(u,search_id);
                }
                break;
            case 5:
                {
                    system("CLS");
                    u[current_user].displayAllUsers(u);
                }
                break;
            default:
                {
                    cout << "\n\n\n\n\t\t\t\tEXIT";
                }
                break;

        }
       cout << "\n\n\n\n\t\t\t\tDO YOU WANT TO RETURN TO THE MAIN MENU ,ELSE YOU CAN EXIT (Y/N) ?";
       cin >> ch;
       Sleep(150);
       system("CLS");
    }while(ch=='Y'||ch=='y' && User::userNo<=MAX_CAPACITY);

    return 0;
}
