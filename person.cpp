#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
class ui //user interface class
{
public:
    virtual void fun() = 0;
    virtual void menu() = 0;

    void admin_menu()
    {
        cout << "\n\t\tWelcome to the Admin menu!!";
        cout << "\n1) Sign up\n2) Sign in";
    }
};
class Person : public ui
{
protected:
    int ID;
    string email;
    string username;
    string password;

public:
    Person() { ID = 0; }
    const string get_email() { return email; }
    const string get_username() { return username; }
    const string get_password() { return password; }
    const int get_ID() { return ID; }
    void set_email(const string email) { this->email = email; }
    void set_username(const string username) { this->username = username; }
    void set_password(const string password) { this->password = password; }
    void set_ID(const int ID) { this->ID = ID; }
    void fun() {}
    void output()
    {
        cout << "\nEmail: " << email << endl
             << "Username: " << username << endl
             << "Password: " << password << endl
             << "ID: " << ID << endl;
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
        cout << "Enter designated ID: ";
        cin >> ID;
        fflush(stdin);
        cout << "Enter email: ";
        getline(cin, email);
        fflush(stdin);
    }
};
class Airline : virtual public Person // mohtada
{
protected:
public:
};
class Customer : virtual public Person // hatif
{
private:
protected:
    string f_name, l_name;

public:
    static int c_no;
    void set_fname(string f_name) { this->f_name = f_name; }
    const string get_fname() { return f_name; }
    void set_lname(char l_name) { this->l_name = l_name; }
    const string get_lname() { return l_name; }
    Customer()
    {
        c_no++;
    }
    void output()
    {
        Person::output();
        cout << "First name: " << f_name << "\nLast name: " << l_name;
    }
    void signup()
    {
        Person::signup();
        cout << "Enter first name: ";
        getline(cin, f_name);
        fflush(stdin);
        cout << "Enter last name: ";
        getline(cin, l_name);
        fflush(stdin);
        ofstream fp("customer.txt", ios::app);
        fp << username << "\t" << password << "\t" << f_name << "\t" << l_name << "\t" << email << "\t" << ID << endl;
        fp.close();
    }
    void signin()
    {
        string u, p;
        fflush(stdin);
        cout << "Enter username: ";
        getline(cin, u);
        fflush(stdin);
        cout << "Enter password: ";
        getline(cin, p);
        fflush(stdin);
        ifstream fp("customer.txt", ios::in);
        while (1)
        {
            fp >> username >> password >> f_name >> l_name >> email >> ID;
            if (fp.eof())
            {
                break;
            }
            if (username == u && password == p)
            {
                system("cls");
                cout << "\n\nSign in is Successful";
                break;
            }
        }
        fp.close();
        
    }
    void menu()
    {
        cout << "\n\t\tWelcome to the customer menu!!";
        cout << "\n1) Sign Up\n2) Sign in\n3)Show number of customers\n";
        int choice;
        cout << "\nEnter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            Customer::signup();
            break;
        case 2:
            Customer::signin();
            break;
        case 3:
            cout << "No of customers: " << c_no << endl;
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

class Ticket : protected Person, protected Airline //printing ticket //mohtada
{
};
class HolidayPackage : public Customer
{
    string date;
    int tourcode;
    string departure, arrival;
    int tour;

public:
    void package_details()
    {
        system("CLS");
        cout << "---------------------------------HOLIDAY PACKAGE TOURS-----------------------------------" << endl;
        cout << "Enter a valid date to see available Packages" << endl;
        cin >> date;
        fflush(stdin);
        system("CLS");
        cout << "ENTER DEPARTURE CITY NAME FROM THE FOLLOWING" << endl;
        cout << "1.Karachi(1) \t\t 2.Lahore(2) \t\t 3. Islamabad(3) \t\t  " << endl;
        cin >> departure;
        system("CLS");
        cout << "AVAILABE PACKAGES :" << endl;

        cout << "1. Toronto(1) \t\t 2.Sydney(2) \t\t 3. Paris(3)  \t\t" << endl;
        cout << "ENTER CITY NAME TO VIEW PACKAGE DETAILS" << endl;
        cin >> arrival;

        if ((departure == "Karachi" && arrival == "Toronto") || (departure == "Lahore" && arrival == "Toronto") || (departure == "Islamabad" && arrival == "Toronto"))
        {
            cout << "\t \t \tFlights Found" << endl
                 << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
            cout << "\t 1.Qatar\t08:00\t\t11:05\t\t$.1500\t\tRefundable\t\tThe Pearl Resort\n";
            cout << "\t 2.Fly Dubai\t14:00\t\t17:05\t\t$.1250\t\tRefundable\t\tCountryside View\n";
            cout << "\t 3.Go Air\t19:00\t\t22:05\t\t$.2000\t\tNon-refundable\t\tMarriot\n";
            book_package();
        }
        if ((departure == "Karachi" && arrival == "Sydney") || (departure == "Lahore" && arrival == "Sydney") || (departure == "Islamabad" && arrival == "Sydney"))
        {
            cout << "\t \t \tFlights Found" << endl
                 << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
            cout << "\t 1.Qantas\t08:00\t\t11:05\t\t$.2500\t\tRefundable\t\tKangaroo Resort\n";
            cout << "\t 2.Emirates\t14:00\t\t17:05\t\t$.2750\t\tRefundable\t\tValley Side\n";
            cout << "\t 3.Go Air\t19:00\t\t22:05\t\t$.1900\t\tNon-refundable\t\tSheraton\n";
            book_package();
        }

        if ((departure == "Karachi" && arrival == "Paris") || (departure == "Lahore" && arrival == "Paris") || (departure == "Islamabad" && arrival == "Paris"))
        {
            cout << "\t \t \tFlights Found" << endl
                 << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
            cout << "\t 1.Lufthansa\t08:00\t\t11:05\t\t$.3500\t\tRefundable\t\tThe Eiffel Resort\n";
            cout << "\t 2.Fly Dubai\t14:00\t\t17:05\t\t$.3750\t\tRefundable\t\tShanzay Lezay Motel\n";
            cout << "\t 3.United Air\t19:00\t\t22:05\t\t$.3000\t\tRefundable\t\tMovenpick\n";
            book_package();
        }
    }

    void book_package()
    {

        ofstream file("packages.txt", ios::app);

        cout << "Enter Package number you wish to select" << endl;
        cin >> tour;
        file << "Name:\tID\t:Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";

        if (tour == 1)
        {
            if (arrival == "Toronto")
            {
                file << f_name << "\t" << l_name << "\t" << ID << "\tQatar\t08:00\t\t11:05\t\t$.1500\t\tRefundable\t\tThe Pearl Resort\n"
                     << departure << " to " << arrival << "\n";
                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Sydney")
            {
                file << f_name << "\t" << l_name << ID << "\tQantas\t08:00\t\t11:05\t\t$.2500\t\tRefundable\t\tKangaroo Resort\n"
                     << departure << " to " << arrival << "\n";
                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Paris")
            {
                file << f_name << "\t" << l_name << ID << "\tLufthansa\t08:00\t\t11:05\t\t$.3500\t\tRefundable\t\tThe Eiffel Resort\n"
                     << departure << " to " << arrival << "\n";
                cout << "PACKAGE BOOKED" << endl;
            }
        }

        if (tour == 2)
        {
            if (arrival == "Toronto")
            {
                file << f_name << "\t" << l_name << ID << "\tFly Dubai\t14:00\t\t17:05\t\t$.1250\t\tRefundable\t\tCountryside View\n"
                     << departure << " to " << arrival << "\n";
                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Sydney")
            {
                file << f_name << "\t" << l_name << ID << "\tEmirates\t14:00\t\t17:05\t\t$.2750\t\tRefundable\t\tValley Side\n"
                     << departure << " to " << arrival << "\n";
                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Paris")
            {
                file << f_name << "\t" << l_name << ID << "\tFly Dubai\t14:00\t\t17:05\t\t$.3750\t\tRefundable\t\tShanzay Lezay Motel\n"
                     << departure << " to " << arrival << "\n";
                cout << "PACKAGE BOOKED" << endl;
            }
        }

        if (tour == 3)
        {
            if (arrival == "Toronto")
            {
                file << f_name << "\t" << ID << "\tGo Air\t19:00\t\t22:05\t\t$.2000\t\tNon-refundable\t\tMarriot\n"
                     << departure << " to " << arrival << "\n";
                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Sydney")
            {
                file << f_name << "\t" << ID << "\tGo Air\t19:00\t\t22:05\t\t$.1900\t\tNon-refundable\t\tSheraton\n"
                     << departure << " to " << arrival << "\n";
                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Paris")
            {
                file << f_name << "\t" << ID << "\tUnited Air\t19:00\t\t22:05\t\t$.3000\t\tRefundable\t\tMovenpick\n"
                     << departure << " to " << arrival << "\n";
                cout << "PACKAGE BOOKED" << endl;
            }
        }
        file.close();
    }
};
int Customer::c_no = 0;

int main()
{
    cout << "\t\t\tAIRLINE RESERVATION SYSTEM\t";
    Customer a;
    a.signin();
    a.output();
}
