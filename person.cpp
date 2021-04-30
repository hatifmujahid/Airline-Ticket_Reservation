#include <iostream>
#include <fstream>

using namespace std;
class ui{                               //user interface class
    public:
        virtual void fun()=0;
        void main_page(){
            int choice;
            cout<<"\n\t\tWelcome to main page!!";
            cout<<"\n1) Customer Page\n2) Admin Page\n3) Staff Page\n4) Airline Page\n";
        }
        void airline_menu(){
            cout<<"\n\t\tWelcome to Airline menu page!!";
        }
        void customer_menu(){
            cout<<"\n\t\tWelcome to the customer menu!!";
            cout<<"\n1) Sign Up\n2) Sign in\n3)Show number of customers\n";
        }

};
class Person:public ui
{
protected:
    string name;
    int ID;
    string email;
    string username;
    string password;

public:
    Person() { ID = 0; }
    const string get_name() { return name; }
    const string get_email() { return email; }
    const string get_username() { return username; }
    const string get_password() { return password; }
    const int get_ID() { return ID; }
    void set_name(const string name) { this->name = name; }
    void set_email(const string email) { this->email = email; }
    void set_username(const string username) { this->username = username; }
    void set_password(const string password) { this->password = password; }
    void set_ID(const int ID) { this->ID = ID; }
    void fun(){}
    void output()
    {
        cout << name << endl
             << email << endl
             << username << endl
             << password<<endl;
    }
    void signup()
    {
        fflush(stdin);
        cout << "SIGN UP\n\nEnter username: ";
        getline(cin, username);
        fflush(stdin);
        cout << "Enter password: ";
        getline(cin, password);
        fflush(stdin);
        cout << "Enter name: ";
        getline(cin, name);
        fflush(stdin);
        cout << "Enter designated ID: ";
        cin >> ID;
        cout << "Enter email: ";
        getline(cin, email);
        fflush(stdin);
    }
};
class Airline :virtual public Person // mohtada
{
protected:
public:
};
class Customer :virtual public Person // hatif
{
    private:
        string air_name;
        char air_type;
    public:
        static int c_no;
        void set_airname(string air_name){this->air_name= air_name;}
        const string get_airname(){return air_name;}
        void set_airtype(char air_type){this->air_type=air_type;}
        Customer(){
            c_no++;
        }
        void output(){
            Person::output();
            cout<<"Airline name: "<<air_name;
        }
        void signup(){
            Person::signup();
        }
        void signin(){
            string u,p;
            cout<<"Enter User name: ";
            getline(cin, u);
            cout<<"Enter password: ";
            getline(cin, p);
        }
        void customer_menu(){
            ui::customer_menu();
            int choice;
            cout<<"\nEnter choice: ";
            cin>>choice;
            switch (choice)
            {
            case 1:
                Customer::signup();
                break;
            case 2:
                Customer::signin();
                break;
            case 3:
                cout<<"No of customers= "<<c_no;
                break;
            default:
                break;
            }
        }
};
class Special_customer : protected Person //maarij
{
protected:
public:
};
class Staff : protected Person //maarij
{
public:
};
class Booking : protected Airline, protected Customer //mohtada
{
};
class Filing
{
public:
    
    
};
class Ticket : protected Person, protected Airline //printing ticket //mohtada
{
};
class HolidayPackage : Person, Ticket, Booking //maarij hotels, tour,
{
};
int Customer::c_no = 0;
int main()
{
    Customer a;
    a.main_page();
}
