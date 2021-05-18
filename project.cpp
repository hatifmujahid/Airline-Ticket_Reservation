#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <cstdio>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

//simple fucntion for loading screen
void loading_screen()
{
    cout << "\n\n\t\t\t\t ";
    printf("%c", 219);
    for (int a = 1; a < 50; a++)
    {
        Sleep(20);
        printf("%c", 219);
    }
    Sleep(30);
    system("cls");
}
string pass_encrypt(string password, const string pass)
{
    if(password.empty())
        return password;

    for (int j = 0; j < password.size(); j++)
        password[j] ^= pass[j%pass.size()];
    return password;
}

string pass_decrypt(string password, const string pass)
{
    if(password.empty()){
        return password;
    }
    for (int j = 0; j < password.size(); j++){
        password[j] ^= pass[j%pass.size()];
    }
    return password;
}

//shows *s instead of letters when typing passwords
string inputmasking()
{
    char c;
    string password;

    while (1)
    {

        c = getch();
        if (c != '\b' && c != 13)
        {
            password.push_back(c);
            putch('*');
        }
        else if (c == '\b')
        {
            if (password.size() != 0)
            {
                password.erase(password.size() - 1);
                cout << "\b \b";
            }
        }
        else if (c == 13)
        {
            break;
        }
    }
    return password;
}

class ui //abstract user interface class
{
public:
    virtual void menu() = 0;
};

// Base class containig useful attributes and methods being used in many functions
class Person : public ui
{
    string username;
    string password;
    string key;
protected:
    int ID;
    string email;

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

    // method for  taking input
    void signup()
    {
        fflush(stdin);
        cout << "---------------------------------------SIGN UP----------------------------------------------------\n\nEnter username: ";
        getline(cin, username);
        fflush(stdin);
        cout << "Enter password: ";
        getline(cin, password);
        cout<<"Enter your key(WARNING: THIS KEY IS NOT TO BE FORGOTTEN): ";
        getline(cin,key);
        password = pass_encrypt(password, key);
        fflush(stdin);
        cout << "Enter designated ID: ";
        cin >> ID;
        fflush(stdin);
        cout << "Enter email: ";
        getline(cin, email);
        fflush(stdin);
    }
    
};

// Airline class for registering and viewing available airlines
class Airline: public ui
{
protected:
    string name, airline_email;
    int no_of_planes, rating;
    int airline_id;

public:
    // setters and getters
    int get_airline_id()
    {
        return airline_id;
    }
    string get_airline_email()
    {
        return airline_email;
    }
    Airline()
    {
        no_of_planes = 0;
        rating = 0;
    }
    string get_name()
    {
        return name;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    int get_rating()
    {
        return rating;
    }
    void set_rating(int rating)
    {
        this->rating = rating;
    }
    int get_planes()
    {
        return no_of_planes;
    }
    void set_planes(int no_of_planes)
    {
        this->no_of_planes = no_of_planes;
    }

    //Menu function
    void menu()
    {
        cout << "::::::::::::::::::::::::::::::::::AIRLINE MENU::::::::::::::::::::::::::::::::::\n";
        cout << "\n\t\tWelcome to the Airline Login/Logout menu!!";
        cout << "\n1) Register an Airline\n2) Show all airlines\n3) Back to main menu \n4) Exit";
    }
    void signup()
    {
        fflush(stdin);
        srand((unsigned)time(0)); //random rating generator
        rating = 1 + (rand() % 6);
        fflush(stdin);
        cout << "Enter name of airline: ";
        getline(cin, name);
        cout << "Enter airline email: ";
        getline(cin, airline_email);
        cout << "Enter ID: ";
        cin >> airline_id;
        fflush(stdin);
        cout << "Enter no of planes in the fleet: ";
        cin >> no_of_planes;
        fstream fp;
        fp.open("airline.txt", ios::app);
        fp << name << "#" << airline_email << " " << airline_id << " " << rating << " " << no_of_planes << endl;
        fp.close();
        system("cls");
        cout << "\nAirline Reistered SUCCESSFULLY\n";
        Sleep(500);
    }

    //Function for viewing registered airlines saved in a file
    void showAirlines()
    {
        fstream fp;
        char a = '#';
        fp.open("airline.txt", ios::in);
        if (!fp)
        {
            cout<<"\nFile not opened!\n";
            exit(0);
        }
        cout << "\n\tName\t\tEmail\t\tID\t\trating\n\n";
        while (1)
        {

            
            getline(fp, name, a);
            fp >> airline_email >> airline_id >> rating >> no_of_planes;
            if (fp.eof())
            {
                break;
            }
            cout << endl
                 << "" << name << "\t\t" << airline_email << "\t\t" << airline_id << "\t\t" << rating << "\t" << endl;
        }
        system("PAUSE");
        fp.close();
    }
};

//Customer class for signup or registering a customer
class Customer : public Person
{
private:
    string user, pass, u, p;

protected:
    string f_name, l_name;

public:
    bool is_special;
    Customer()
    {
        is_special = false;
    }
    friend class Booking;
    friend class Staff;
    void set_fname(string f_name) { this->f_name = f_name; }
    const string get_fname() { return f_name; }
    void set_lname(char l_name) { this->l_name = l_name; }
    const string get_lname() { return l_name; }
    void menu()
    {
        system("cls");
        cout << "\n\t\tWelcome to the customer Login/Logout menu!!";
        cout << "\n1) Sign Up\n2) Back to Main screen\n3)EXIT\n";
        cout << "\nEnter choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            signup();
            break;
        case 2:
            break;
        default:
            exit(0);
        }
    }
    void signup()
    {
        system("cls");
        Person::signup();
        cout << "Enter first name: ";
        getline(cin, f_name);
        fflush(stdin);
        cout << "Enter last name: ";
        getline(cin, l_name);
        fflush(stdin);
        fstream fp;
        fp.open("customer.txt", ios::app);
        fp << f_name << "\t" << l_name << "\t" << email << "\t" << ID << "\t" << get_username() << "\t" << get_password() << "\t" << is_special << endl;
        fp.close();
        cout << "\nSIGN UP SUCCESSFUL\n";
        system("PAUSE");
        menu();
    }
    void signin()
    {
        string key;
        system("CLS");
        cout << "---------------------------------------Customer SIGN IN---------------------------------------\n\n";
        char c;
        fflush(stdin);
        cout << "Enter username: ";
        getline(cin, u);
        fflush(stdin);
        cout << "Enter password: ";
        p = inputmasking();
        cout<<"\nEnter Key: ";
        key = inputmasking();
        p = pass_decrypt(p, key);
        fstream fp;
        fp.open("customer.txt", ios::in);
        if (!fp)
        {
            cout << "\nFILE DOES NOT EXIST\n";
            exit(1);
        }
        while (1)
        {
            fp >> f_name >> l_name >> email >> ID >> user >> pass >> is_special;
            if (fp.eof())
            {
                cout << "\nSIGN IN UNSUCCESSFUL\n";
                loading_screen();
                signin();
                break;
            }
            else if (user == u && pass == p)
            {
                fp.close();
                system("cls");
                cout << "\nSIGN IN SUCCESSFUL\n";
                loading_screen();
                break;
            }
        }
        fp.close();
    }
};
//Special Customer class for signup or registering a customer
//a customer is special only when he has miles > 5000
class Special_customer : public Person
{
    string u, p, user, pass;

protected:
    int miles;
    string f_name, l_name;

public:
    bool is_special;
    Special_customer()
    {
        is_special = true;
    }
    void menu()
    {
        system("cls");
        cout << "\n\t\tWelcome to the Special customer Login/Logout menu!!";
        cout << "\n1) Sign Up\n2)Back to Main Menu\n3)EXIT\nEnter choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            signup();
            break;
        case 2:
            break;
        default:
            exit(0);
        }
    }
    void signup()
    {
        cout << "Enter miles" << endl;
        cin >> miles;
        if (miles >= 5000)
        {
            Person::signup();
            cout << "Enter first name: ";
            getline(cin, f_name);
            fflush(stdin);
            cout << "Enter last name: ";
            getline(cin, l_name);
            fflush(stdin);
            fstream fp;
            fp.open("special_customer.txt", ios::app);
            fp << f_name << "\t" << l_name << "\t" << email << "\t" << ID << "\t" << get_username() << "\t" << get_password() << "\t" << is_special << endl;
            fp.close();
            cout << "\nSIGN UP SUCCESSFUL\n";
            system("PAUSE");
            menu();
        }
        else
        {
            cout << "Not enough miles" << endl
                 << "CONTINUE TRAVELLING WITH US" << endl;
            system("PAUSE");
            menu();
        }
    }
    void signin()
    {
        string key;
        system("cls");
        cout << "---------------------------------------Special Customer SIGN IN----------------------------------------------------\n\n";
        char c;
        fflush(stdin);
        cout << "Enter username: ";
        getline(cin, u);
        fflush(stdin);
        cout << "Enter password: ";
        p = inputmasking();
        cout<<"\nEnter Key: ";
        key = inputmasking();
        p = pass_decrypt(p, key);
        fstream fp;
        fp.open("special_customer.txt", ios::in);
        if (!fp)
        {
            cout << "\nFILE DOES NOT EXIST\n";
            exit(1);
        }
        while (1)
        {
            fp >> f_name >> l_name >> email >> ID >> user >> pass >> is_special;
            if (fp.eof())
            {
                cout << "\nSIGN IN UNSUCCESSFUL\n";
                signin();
                break;
            }
            if (user == u && pass == p)
            {
                fp.close();
                system("cls");
                cout << "\nSIGN IN SUCCESSFUL\n";
                loading_screen();
                break;
            }
        }
        fp.close();
    }
    void b_refund()
    {
        Special_customer s;
        s.signin();
        int choice;
        string x;
        string n, i, a, d, ar, p, c, h, l;
        system("CLS");
        ifstream original("packages.txt", ios::out);
        ofstream copy("new.txt", ios::app);

        cout << "1.Holiday Package Refund\t\t2.Ticket Refund" << endl;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter Your Customer ID" << endl;
            cin >> x;
            while (original >> n >> i >> a >> d >> ar >> p >> c >> h)
            {

                if (i == x)
                {
                    cout << "TICKET REFUNDED" << endl
                         << "FUNDS TRANSFERRED" << endl;
                    break;
                }
                else if (original.eof())
                {
                    cout << "BOOKING UNAVAILABE" << endl;
                    system("PAUSE");
                    break;
                }
                else
                {

                    ofstream copy("new.txt", ios::app);

                    copy << n << "\t" << i << "\t" << a << "\t" << d << "\t" << ar << "\t" << p << "\t" << c << "\t" << h << "\n";
                }
            }
            copy.close();
            original.close();
            remove("packages.txt");
            rename("new.txt", "packages.txt");
            system("PAUSE");
            menu();
        }

        else if (choice == 2)
        {
            cout << "Contact Agency or Staff for Refund" << endl;
            system("PAUSE");
            menu();
        }
    }
    void check_flight();
    void book_flight();
    string get_fname()
    {
        return f_name;
    }
};

// Class for viewing packages available and booking them
class HolidayPackage : public ui
{
    string date;
    int tourcode;
    string departure, arrival;
    int tour;
    int choice, c;
    bool special;

public:
    Customer c1;
    Special_customer s1;
    void login()
    {
        cout << "1.Customer\t2.Special Customer" << endl;
        cin >> c;
        if (c == 1)
        {
            c1.signin();
            special = false;
            menu();
        }
        else if (c == 2)
        {
            s1.signin();
            special = true;
            menu();
        }
    }
    void menu()
    {
        cout << "WELCOME TO THE HOLIDAY TOURS AND PACKAGES MENU" << endl;
        cout << " 1.View Packages\t2.Book a Package\t3.Exit to main\n";
        cout << "Enter choice" << endl;
        cin >> choice;
        if (choice == 1 || choice == 2)
        {
            package_details();
        }
        else
        {
            exit(1);
        }
    }
    //showing packages then redirecting to booking methods
    void package_details()
    {
        int c;
        system("CLS");
        cout << "---------------------------------HOLIDAY PACKAGE TOURS-----------------------------------" << endl;
        cout << "Enter a valid date to see available Packages" << endl;
        cin >> date;
        fflush(stdin);
        system("CLS");
        cout << "ENTER DEPARTURE CITY NAME FROM THE FOLLOWING" << endl;
        cout << "1.Karachi(1) \t\t 2.Lahore(2) \t\t 3. Islamabad(3) \t\t  " << endl;
        getline(cin, departure);
        system("CLS");
        cout << "AVAILABE PACKAGES :" << endl;

        cout << "1. Toronto(1) \t\t 2.Sydney(2) \t\t 3. Paris(3)  \t\t" << endl;
        cout << "ENTER CITY NAME TO VIEW PACKAGE DETAILS" << endl;
        getline(cin, arrival);

        if ((departure == "Karachi" && arrival == "Toronto") || (departure == "Lahore" && arrival == "Toronto") || (departure == "Islamabad" && arrival == "Toronto"))
        {
            cout << "\t \t \tFlights Found" << endl
                 << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
            cout << "1.Qatar\t08:00\t\t11:05\t\t$.1500\t\tRefundable\t\tPearl\n";
            cout << "2.Turkish\t14:00\t\t17:05\t\t$.1250\t\tRefundable\t\tPC\n";
            cout << "3.KLM\t\t19:00\t\t22:05\t\t$.2000\t\tNon-refundable\t\tMarriot\n";
            if (choice == 2)
            {
                if (special == true)
                {
                    book_package2();
                }
                else
                {
                    book_package();
                }
            }
            else if (choice == 1)
            {
                system("PAUSE");
                cout << " 1.Book a Package\t2.Main" << endl;
                cin >> c;
                if (c == 1)
                {
                    if (special == true)
                    {
                        book_package2();
                    }
                    else
                    {
                        book_package();
                    }
                }
                else
                {
                    system("CLS");
                    menu();
                }
            }
        }
        if ((departure == "Karachi" && arrival == "Sydney") || (departure == "Lahore" && arrival == "Sydney") || (departure == "Islamabad" && arrival == "Sydney"))
        {
            cout << "\t \t \tFlights Found" << endl
                 << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
            cout << "1.Qantas\t08:00\t\t11:05\t\t$.2500\t\tRefundable\t\tMeriton\n";
            cout << "2.Emirates\t14:00\t\t17:05\t\t$.2750\t\tRefundable\t\tRaddison\n";
            cout << "3.Virgin\t19:00\t\t22:05\t\t$.1900\t\tNon-refundable\t\tSheraton\n";
            if (choice == 2)
            {
                if (special == true)
                {
                    book_package2();
                }
                else
                {
                    book_package();
                }
            }
            else if (choice == 1)
            {
                system("PAUSE");
                cout << " 1.Book a Package\t2.Main" << endl;
                cin >> c;
                if (c == 1)
                {
                    if (special == true)
                    {
                        book_package2();
                    }
                    else
                    {
                        book_package();
                    }
                }
                else
                {
                    system("CLS");
                    menu();
                }
            }
        }
        if ((departure == "Karachi" && arrival == "Paris") || (departure == "Lahore" && arrival == "Paris") || (departure == "Islamabad" && arrival == "Paris"))
        {
            cout << "\t \t \tFlights Found" << endl
                 << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
            cout << "1.Lufthansa\t08:00\t\t11:05\t\t$.3500\t\tRefundable\t\tBelvedere\n";
            cout << "2.Etihad\t14:00\t\t17:05\t\t$.3750\t\tRefundable\t\tShanzayLezay\n";
            cout << "3.Nippon\t19:00\t\t22:05\t\t$.3000\t\tRefundable\t\tMovenpick\n";
            if (choice == 2)
            {
                if (special == true)
                {
                    book_package2();
                }
                else
                {
                    book_package();
                }
            }
            else if (choice == 1)
            {
                system("PAUSE");
                cout << " 1.Book a Package\t2.Main" << endl;
                cin >> c;
                if (c == 1)
                {
                    if (special == true)
                    {
                        book_package2();
                    }
                    else
                    {
                        book_package();
                    }
                }
                else
                {
                    system("CLS");
                    menu();
                }
            }
        }
    }

    //booking packages
    void book_package()
    {

        ofstream file("packages.txt", ios::app);
        if(!file){
            cout<<"file does not exist";
            exit(0);
        }

        cout << "Enter Package number you wish to select" << endl;
        cin >> tour;

        if (tour == 1)
        {
            if (arrival == "Toronto")
            {
                file << c1.get_fname() << "\t" << c1.get_ID() << "\tQatar\t08:00\t\t11:05\t\t$.1500\t\tRefundable\t\t Pearl\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Sydney")
            {
                file << c1.get_fname() << "\t" << c1.get_ID() << "\tQantas\t08:00\t\t11:05\t\t$.2500\t\tRefundable\t\tMeriton\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Paris")
            {
                file << c1.get_fname() << "\t" << c1.get_ID() << "\tLufthansa\t08:00\t\t11:05\t\t$.3500\t\tRefundable\t\tBelvedere\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
        }

        if (tour == 2)
        {
            if (arrival == "Toronto")
            {
                file << c1.get_fname() << "\t" << c1.get_ID() << "\tTurkish\t14:00\t\t17:05\t\t$.1250\t\tRefundable\t\tPC\n";
                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Sydney")
            {
                file << c1.get_fname() << "\t" << c1.get_ID() << "\tEmirates\t14:00\t\t17:05\t\t$.2750\t\tRefundable\t\tRaddison\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Paris")
            {
                file << c1.get_fname() << "\t" << c1.get_ID() << "\tEtihad\t14:00\t\t17:05\t\t$.3750\t\tRefundable\t\tShanzayLezay\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
        }

        if (tour == 3)
        {
            if (arrival == "Toronto")
            {
                file << c1.get_fname() << "\t" << c1.get_ID() << "\tKLM\t19:00\t\t22:05\t\t$.2000\t\tNonrefundable\t\tMarriot\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Sydney")
            {
                file << c1.get_fname() << "\t" << c1.get_ID() << "\tVirgin\t19:00\t\t22:05\t\t$.1900\t\tNonrefundable\t\tSheraton\n";
                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Paris")
            {
                file << c1.get_fname() << "\t" << c1.get_ID() << "\tNippon\t19:00\t\t22:05\t\t$.3000\t\tRefundable\t\tMovenpick\n";
                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
        }
        file.close();
    }
    void book_package2()
    {

        ofstream file("packages.txt", ios::app);

        cout << "Enter Package number you wish to select" << endl;
        cin >> tour;

        if (tour == 1)
        {
            if (arrival == "Toronto")
            {
                file << s1.get_fname() << "\t" << s1.get_ID() << "\tQatar\t08:00\t\t11:05\t\t$.1500\t\tRefundable\t\t Pearl\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Sydney")
            {
                file << s1.get_fname() << "\t" << s1.get_ID() << "\tQantas\t08:00\t\t11:05\t\t$.2500\t\tRefundable\t\tMeriton\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Paris")
            {
                file << s1.get_fname() << "\t" << s1.get_ID() << "\tLufthansa\t08:00\t\t11:05\t\t$.3500\t\tRefundable\t\tBelvedere\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
        }

        if (tour == 2)
        {
            if (arrival == "Toronto")
            {
                file << s1.get_fname() << "\t" << s1.get_ID() << "\tTurkish\t14:00\t\t17:05\t\t$.1250\t\tRefundable\t\tPC\n";
                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Sydney")
            {
                file << s1.get_fname() << "\t" << s1.get_ID() << "\tEmirates\t14:00\t\t17:05\t\t$.2750\t\tRefundable\t\tRaddison\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Paris")
            {
                file << s1.get_fname() << "\t" << s1.get_ID() << "\tEtihad\t14:00\t\t17:05\t\t$.3750\t\tRefundable\t\tShanzayLezay\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
        }

        if (tour == 3)
        {
            if (arrival == "Toronto")
            {
                file << s1.get_fname() << "\t" << s1.get_ID() << "\tKLM\t19:00\t\t22:05\t\t$.2000\t\tNonrefundable\t\tMarriot\n";

                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Sydney")
            {
                file << s1.get_fname() << "\t" << s1.get_ID() << "\tVirgin\t19:00\t\t22:05\t\t$.1900\t\tNonrefundable\t\tSheraton\n";
                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
            if (arrival == "Paris")
            {
                file << s1.get_fname() << "\t" << s1.get_ID() << "\tNippon\t19:00\t\t22:05\t\t$.3000\t\tRefundable\t\tMovenpick\n";
                cout << "PACKAGE BOOKED" << endl;
                system("PAUSE");
            }
        }
        file.close();
    }
};
// Booking flights class
class Booking : public Airline
{
protected:
    int ticket_ID;
    string c_name, c_email, c_airline;
    int c_id;
    float price;
    float prices[3];

public:
    Booking()
    {
        c_id = 0;
        price = 0;
        prices[0] = 4000;
        prices[1] = 10000;
        prices[2] = 15000;
    }
    const int get_ticket_id()
    {
        return ticket_ID;
    }
    const string get_c_email()
    {
        return c_email;
    }
    const string get_c_name()
    {
        return c_name;
    }
    const string get_c_airline()
    {
        return c_airline;
    }
    const int get_price()
    {
        return price;
    }
    void menu()
    {
        cout << "----------------------------------BOOKING MENU---------------------------------------";
        cout << "\n\n1) Customer Ticket\n\n2) Special Customer ticket\n\nEnter choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            n_booking();
            break;
        case 2:
            s_booking();
            break;
        default:
            exit(0);
        }
    }
    void n_booking();
    void s_booking();
};
//printing ticket class
class Ticket : public Booking
{
public:
    void menu()
    {
        system("cls");
        cout << "**************************************TICKET MENU**************************************";
        cout << "\n1) Normal Customer Ticket\n2) Special Customer ticket \n3) Holiday Package\n4) Exit\nEnter choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            n_printticket();
            break;
        case 2:
            s_printticket();
            break;
        case 3:
            print_package();
            break;
        default:
            exit(0);
        }
    }
    void print_package()
    {
        string n, i, a, d, ar, p, c, h;
        system("cls");
        cout << "\nProcessing Package";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        string x;
        cout << "\n\nEnter Customer ID: ";
        cin >> x;
        fstream fpt;
        fpt.open("packages.txt", ios::in);
        if(!fpt){
        cout<<"File not found!";
        exit(0);
    }
        while (1)
        {
            fpt >> n >> i >> a >> d >> ar >> p >> c >> h;
            if (i == x)
            {
                break;
            }
            if (fpt.eof())
            {
                cout << "BOOKING UNAVAILABLE" << endl;
                break;
            }
        }
        fpt.close();
        loading_screen();
        cout << "----------------------------------------------------------------------------------------------\n";
        cout << "-                                         HOLIDAY PACAKGE                                    -\n";
        cout << "----------------------------------------------------------------------------------------------\n";
        cout << "\nCustomer Name: " << n << "\nCustomer ID: " << i << "\nAirline: " << a << "\nDeparture: " << d << "\nArrival: " << ar << "\nCategory :" << c << "\nHotel :" << h << endl;
        system("PAUSE");
    }
    void s_printticket()
    {
        system("cls");
        cout << "\nProcessing ticket";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        int s;
        cout << "\n\nEnter ID of the ticket to be printed: ";
        cin >> s;
        fstream fpt;
        fpt.open("ticket.txt", ios::in);
        if(!fpt){
            cout<<"File not found!";
            exit(0);
        }
        int check = 0;
        while (1)
        {

            fpt >> c_name >> c_email >> c_airline >> c_id >> price >> ticket_ID;
            if (ticket_ID == s)
            {
                check = 1;
                break;
            }
            if (fpt.eof())
            {
                break;
            }
        }
        fpt.close();
        if (check == 1)
        {
            loading_screen();
            cout << "----------------------------------------------------------------------------------------------\n";
            cout << "-                                             Ticket                                         -\n";
            cout << "----------------------------------------------------------------------------------------------\n";
            cout << "\nCustomer Name: " << c_name << "\nCustomer Email: " << c_email << "\nChoosen Airline: " << c_airline << "\nPrice: " << price << endl;
            system("PAUSE");
        }
        if (check == 0)
        {
            cout << "\nTicket not found... exiting";
            exit(1);
        }
    }
    void n_printticket()
    {
        system("cls");
        cout << "\nProcessing ticket";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        int s;
        cout << "\n\nEnter ID of the ticket to be printed: ";
        cin >> s;
        fstream fpt;
        fpt.open("ticket.txt", ios::in);
        if(!fpt){
            cout<<"File not found!";
            exit(0);
        }
        int check = 0;
        while (1)
        {
            fpt >> c_name >> c_email >> c_airline >> c_id >> price >> ticket_ID;
            if (ticket_ID == s)
            {
                check = 1;
                break;
            }
            if (fpt.eof())
            {
                break;
            }
        }
        fpt.close();
        if (check == 1)
        {
            loading_screen();
            cout << "----------------------------------------------------------------------------------------------\n";
            cout << "-                                             Ticket                                         -\n";
            cout << "----------------------------------------------------------------------------------------------\n";
            cout << "\nCustomer Name: " << c_name << "\nCustomer Email: " << c_email << "\nChoosen Airline: " << c_airline << "\nPrice: " << price << endl;
            system("PAUSE");
        }
        if (check == 0)
        {
            cout << "\nTicket not found... Exiting";
            exit(1);
        }
    }
};
// Class for staff sign up, sign in and methods for certain things staff can do
class Staff : virtual public Person
{
private:
    string u, p, user, pass;

protected:
    string f_name, l_name;

public:
    friend class Admin;
    void signup()
    {
        Person::signup();
        cout << "Enter first name: ";
        getline(cin, f_name);
        fflush(stdin);
        cout << "Enter last name: ";
        getline(cin, l_name);
        fflush(stdin);
        fstream fp;
        fp.open("staff.txt", ios::app);
        fp << f_name << "\t" << l_name << "\t" << email << "\t" << ID << "\t" << get_username() << "\t" << get_password() << endl;
        fp.close();
        cout << "\nSIGN UP SUCCESSFUL\n";
        system("PAUSE");
        menu();
    }

    void signin()
    {
        string key;
        cout << "\n\n---------------------------------------STAFF SIGN IN----------------------------------------------------\n\n";
        char c;
        fflush(stdin);
        cout << "Enter username: ";
        getline(cin, u);
        fflush(stdin);
        cout << "Enter password: ";
        p = inputmasking();
        cout<<"\nEnter Key: ";
        key = inputmasking();
        p = pass_decrypt(p, key);
        fstream fp;
        fp.open("staff.txt", ios::in);
        if (!fp)
        {
            cout << "\nFILE DOES NOT EXIST\n";
            exit(0);
        }
        while (1)
        {
            fp >> f_name >> l_name >> email >> ID >> user >> pass;
            if (fp.eof())
            {
                cout << "\nSIGN IN UNSUCCESSFUL\n";
                signin();
                break;
            }
            if (user == u && pass == p)
            {
                fp.close();
                system("cls");
                cout << "\nSIGN IN SUCCESSFUL\n";
                loading_screen();
                staff_menu();
            }
        }
        fp.close();
    }

    void menu()
    {
        int c;
        cout << "\n___________________________STAFF MENU____________________________" << endl;
        cout << "\n1.SIGN UP\t\t2.SIGN-IN\t\t3.EXIT\n"
             << endl;
        int choice;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            signup();
            break;
        case 2:
            signin();
            break;
        default:
            exit(0);
        }
    }

    void staff_menu()
    {
        int i;
        system("CLS");
        cout << "------------------MANAGE VERIFICATION AND REFUND OPERATIONS-------------------" << endl;

        cout << "1.BOOKING REFUND\t2.VERIFY BOOKING\t3.REFUND POLICY\t0.Exit" << endl;
        cin >> i;
        if (i == 1)
        {
            refund();
        }
        else if (i == 3)
        {
            policy();
        }
        else if (i == 2)
        {
            verify();
        }
        else if (i == 0)
        {
            menu();
        }
    }

    void refund()
    {
        int ch;
        string x, y;
        int z, ticket_ID;
        string n, i, a, d, ar, p, c, h, l;
        string c_name, c_email, c_airline, c_id, price;

        system("CLS");
        ifstream original("packages.txt", ios::out);
        ofstream copy("new.txt", ios::app);

        cout << "1.Ticket Refund\t\t2.Holiday Package Refund\n";
        cin >> ch;
        if (ch == 1)
        {
            cout << "Enter Ticket ID for the ticket to be refunded" << endl;
            cin >> z;
            int t=0;

            if(!original){
                cout<<"File not found!";
                exit(0);
            }
            
            while (original >> c_name >> c_email >> c_airline >> c_id >> price >> ticket_ID)
            {
               // fp >> c_name >> c_email >> c_airline >> c_id >> price >> ticket_ID;
                if (ticket_ID == z)
                {
                    cout << "Ticket Refunded" << endl;
                    t=1;
                    
                }
                else 
                {
                    ofstream f("new.txt", ios::app);
                    f << c_name << "\t" << c_email << "\t" << c_airline << "\t" << c_id << "\t" << price << "\t" << ticket_ID << endl;
                }
                
            }
            
            fp.close();
            f.close();
            remove("ticket.txt");
            rename("new.txt", "ticket.txt");
            if(t!=1){
                cout<<"Booking Unavailable"<<endl;
            }
            system("PAUSE");
            staff_menu();
        }

        if (ch == 2)
        {
            cout << "Enter customer ID" << endl;
            cin >> x;
            //system("CLS");

            while (original >> n >> i >> a >> d >> ar >> p >> c >> h)
            {

                if (i == x && c == "Refundable")
                {
                    cout << "TICKET REFUNDED" << endl;
                    // continue;
                }
                else if (i == x && c == "Nonrefundable")
                {
                    cout << "TICKET OF NON-REFUNDABLE CATEGORY" << endl;
                    ofstream copy("new.txt", ios::app);
                    copy << n << "\t" << i << "\t" << a << "\t" << d << "\t" << ar << "\t" << p << "\t" << c << "\t" << h << "\n";
                }

                else
                {

                    ofstream copy("new.txt", ios::app);

                    copy << n << "\t" << i << "\t" << a << "\t" << d << "\t" << ar << "\t" << p << "\t" << c << "\t" << h << "\n";
                }
            }

            copy.close();
            original.close();
            remove("packages.txt");
            rename("new.txt", "packages.txt");
        }
        system("PAUSE");
        staff_menu();
    }

    void policy()
    {
        cout << "->Holiday Packages booked with a refund category are only refundable" << endl;
        cout << "->Non-refundable category packages will not be refunded under any condition" << endl;
        cout << "->Special Customers can refund any package by using the refund option in their menu" << endl;
        cout << "->Refund ensures a 100% money back guarantee" << endl
             << endl
             << endl;
        system("PAUSE");
        staff_menu();
    }

    void verify()
    {   
        system("CLS");
        string c_name, c_email, c_airline, c_id, price;
        int ticket_ID;
        Booking t1;
        int i;
        cout << "Enter Ticket ID" << endl;
        cin >> i;
        
        ifstream fp("ticket.txt", ios::in);
        if(!fp){
        cout<<"File not found!";
        exit(0);
    }
        while (fp >> c_name >> c_email >> c_airline >> c_id >> price >> ticket_ID)
        {
            if (ticket_ID == i)
            {
                Sleep(500);
                loading_screen();
                cout << "TICKET VERIFIED" << endl
                     << "ISSUE BOARDING PASS" << endl;
                break;
            }

            else if (fp.eof())
            {
                cout << "BOOKING UNAVAILABLE" << endl;
            }
        }

        fp.close();
        system("PAUSE");
        staff_menu();
    }

    void set_U(string u)
    {
        this->u = u;
    }

    string get_U()
    {
        return u;
    }

    void set_P(string p)
    {
        this->p = p;
    }

    string get_P()
    {
        return p;
    }
};
// Admin class containing sign up, sign in and methods like deleting a customer, staff or and airline
class Admin : public Person
{
    string user, pass, u, p;

protected:
    string f_name, l_name;

public:
    friend class Airline;
    Admin() {}
    void set_fname(string f_name) { this->f_name = f_name; }
    const string get_fname() { return f_name; }
    void set_lname(char l_name) { this->l_name = l_name; }
    const string get_lname() { return l_name; }
    void menu()
    {
        cout << "\n\n__________________________________________ADMIN MENU__________________________________________\n\n\t1) Sign Up\n\n\t2) Sign in\n\n\t3) Exit";
        cout << "\n\nEnter choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            signup();
            break;
        case 2:
            signin();
            break;
        case 3:
            exit(0);
        default:
            break;
        }
    }

    void signup()
    {
        system("cls");
        Person::signup();
        cout << "Enter first name: ";
        getline(cin, f_name);
        fflush(stdin);
        cout << "Enter last name: ";
        getline(cin, l_name);
        fflush(stdin);
        fstream fp;
        fp.open("admin.txt", ios::app);
        fp << f_name << "\t" << l_name << "\t" << email << "\t" << ID << "\t" << get_username() << "\t" << get_password() << endl;
        fp.close();
        cout << "\nSIGN UP SUCCESSFUL\n";
        admin_menu();
    }
    void signin()
    {
        string key;
        system("cls");
        cout << "__________________________________ADMIN SIGN IN______________________________________\n\n";
        fflush(stdin);
        cout << "Enter username: ";
        getline(cin, u);
        fflush(stdin);
        cout << "Enter password: ";
        p = inputmasking();
        cout<<"\nEnter Key: ";
        key = inputmasking();
        p = pass_decrypt(p, key);
        fstream fp;
        fp.open("admin.txt", ios::in);
        if (!fp)
        {
            cout << "\nFILE DOES NOT EXIST\n";
            exit(1);
        }
        while (1)
        {
            fp >> f_name >> l_name >> email >> ID >> user >> pass;
            if (fp.eof())
            {
                break;
            }
            if (user == u && pass == p)
            {
                fp.close();
                cout << "\nSign in successful\n";
                admin_menu();
            }
        }
        fp.close();
    }
    void admin_menu()
    {
        system("cls");
        cout << "\n\n\n__________________________________WELCOME MR. " << f_name << " " << l_name << "______________________________________\n\n";
        cout << "\t1) Delete a Customer\n\t2) Delete an Airline\n\t3) Delete Staff\n\t4) Show all admins \n\n\t\tEnter choice: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            delete_customer();
        }
        else if (choice == 2)
        {
            delete_airline();
        }
        else if (choice == 3)
        {
            delete_staff();
        }
        else if (choice == 4)
        {
            show_admin();
        }
    }
    void delete_customer();
    void delete_staff();
    void delete_airline();
    void show_admin()
    {
        ifstream fp("admin.txt", ios::in);
        if(!fp){
        cout<<"File not found!";
        exit(0);
    }
        system("cls");
        cout << "\t\t\t\t\tADMIN LIST";
        cout << "\nFirst name  \tLast name \tID \tEmail" << endl;
        while (1)
        {
            fp >> f_name >> l_name >> email >> ID;
            if (fp.eof())
            {
                break;
            }
            else
            {
                cout << f_name << "\t\t" << l_name << "\t\t" << ID << "\t\t" << email << endl;
            }
        }
    }
};
void Admin::delete_airline() //delete airline function in admin
{
    Airline a;
    int ID;
    string n, e;
    int i, r, p;
    cout << "Enter ID of the Airline you want to delete: ";
    cin >> ID;
    loading_screen();
    fstream original("airline.txt", ios::in);
    if(!original){
        cout<<"File not found!";
        exit(0);
    }
    fstream new_file("new.txt", ios::out);
    if (!original)
    {
        exit(1);
    }
    while (1)
    {
        char a = '#';
        getline(original, n, a);
        original >> e >> i >> r >> p;
        if (original.eof())
        {
            break;
        }
        if (i != ID)
        {
            new_file << n << "#" << e << " " << i << " " << r << " " << p << endl;
        }
    }
    new_file.close();
    original.close();
    remove("airline.txt");
    rename("new.txt", "airline.txt");
    admin_menu();
}
void Admin::delete_staff() //delete staff function in admin
{
    string f, l, e, u, p;
    int i;
    bool is;
    int ID;
    fstream original("staff.txt", ios::in);
    if(!original){
        cout<<"File not found!";
        exit(0);
    }
    fstream new_file("new.txt", ios::app);
    if (!original)
    {
        cout << "\nFILE DOES NOT EXIST!\n";
        exit(0);
    }
    cout << "Enter ID of the Staff you want to delete: ";
    cin >> ID;
    loading_screen();
    while (1)
    {
        original >> f >> l >> e >> i >> u >> p >> is;
        if (original.eof())
        {
            cout << "ID not found!";
            break;
        }
        if (i != ID)
        {
            new_file << f << "\t" << l << "\t" << e << "\t" << i << "\t" << u << "\t" << p << "\t" << is << endl;
        }
    }
    new_file.close();
    original.close();
    remove("staff.txt");
    rename("new.txt", "staff.txt");
    admin_menu();
}
void Admin::delete_customer() //delete customer function in admin
{
    Customer a;
    string f, l, e, u, p;
    int i;
    bool is;
    int ID;
    cout << "Enter ID of the customer you want to delete: ";
    cin >> ID;
    loading_screen();
    fstream original("customer.txt", ios::in);
    if(!original){
        cout<<"File not found!";
        exit(0);
    }
    fstream new_file("new.txt", ios::app);
    while (1)
    {
        original >> f >> l >> e >> i >> u >> p >> is;
        if (original.eof())
        {
            cout << "ID not found!";
            break;
        }
        if (i != ID)
        {
            new_file << f << "\t" << l << "\t" << e << "\t" << i << "\t" << u << "\t" << p << "\t" << is << endl;
        }
    }
    new_file.close();
    original.close();
    remove("customer.txt");
    rename("new.txt", "customer.txt");
    admin_menu();
}
int checking(int arr[], int count) //checks ticket id from file to stop repetition
{                                  //basically ticket id is generated using random int genrator. this prevents ovralapping
    srand((unsigned)time(0));
    int u = (rand() % 4000);

    for (int k = 0; k < count; k++)
    {

        if (u == arr[k])
        {
            u = checking(arr, count);
        }
    }
    return u;
}
void Booking::s_booking() //special customer booking
{
    int i;
    Special_customer a;
    a.signin();
    c_name = a.get_fname();
    c_email = a.get_email();
    c_id = a.get_ID();
    int j = 0, count = 0;
    string s;
    fstream file;
    file.open("ticket.txt", ios::in);
    if(file){
    while (getline(file, s))
    {
        count++;
    }
    int arr[count], k = 0;
    file.close();
    fstream file1;
    file1.open("ticket.txt", ios::in);
    while (1)
    {
        file1 >> c_name >> c_email >> c_airline >> c_id >> price >> ticket_ID;
        arr[k] = ticket_ID;
        k++;
        if (file1.eof())
        {
            break;
        }
    }
    i = checking(arr, count);
    ticket_ID = i;
    file1.close();
    fstream fptr;
    fptr.open("ticket.txt", ios::in);
    
    while (1)
    {
        fptr >> c_name >> c_email >> c_airline >> c_id >> price >> ticket_ID;
        if (fptr.eof())
        {
            break;
        }

        if (i == ticket_ID)
        {
            continue;
        }
    }
    fptr.close();
    ticket_ID = i;
    }
    else if(!file){
        srand((unsigned)time(0));
        i = (rand() % 4000);
        ticket_ID = i;
    }
    srand((unsigned)time(0)); //random price generator
    i = (rand() % 3);
    price = prices[i];
    if (a.is_special == true)
    {
        price = price * 0.85;
    }
    cout << "List of airlines: ";
    showAirlines();
    int choice;
    cout << "\nEnter ID of the Airline choosen: ";
    cin >> choice;
    fstream fpt;
    fpt.open("ticket.txt", ios::app);
    if (!fpt)
    {
        cout << "\nFILE DOES NOT EXIST\n";
        exit(1);
    }
    fstream fp;
    fp.open("airline.txt", ios::in);
    if (!fp)
    {
        cout << "\nFILE DOES NOT EXIST\n";
        exit(1);
    }
    while (1)
    {
        fp >> name >> airline_email >> airline_id >> rating >> no_of_planes;
        if (fp.eof())
        {
            break;
        }
        if (airline_id == choice)
        {
            break;
        }
    }
    c_airline = name;
    fpt << c_name << "\t" << c_email << "\t" << c_airline << "\t" << c_id << "\t" << price << "\t" << ticket_ID << endl;
    fpt.close();
    cout << "Ticket is generated.\nID: " << ticket_ID << endl;
    system("PAUSE");
}
void Booking::n_booking() //normal customer booking ticket
{
    int i;
    Customer a;
    a.signin();
    c_name = a.get_fname();
    c_email = a.get_email();
    c_id = a.get_ID();
    int j = 0, count = 0;
    string s;
    fstream file;
    file.open("ticket.txt", ios::out | ios::in);
    if (file)
    {
        while (getline(file, s))
        {
            count++;
        }
        int arr[count], k = 0;
        file.close();
        fstream file1;
        file1.open("ticket.txt", ios::in);
        if (file)
        {
            while (1)
            {
                file1 >> c_name >> c_email >> c_airline >> c_id >> price >> ticket_ID;
                arr[k] = ticket_ID;
                k++;
                if (file1.eof())
                {
                    break;
                }
            }
            i = checking(arr, count);
            ticket_ID = i;
            file1.close();
        }
    }
    else if (!file)
    {
        srand((unsigned)time(0));
        i = (rand() % 4000);
        ticket_ID = i;
    }
    srand((unsigned)time(0)); //random price generator
    i = (rand() % 3);
    price = prices[i];
    if (a.is_special == true)
    {
        price = price * 0.85;
    }
    cout << "List of airlines: ";
    showAirlines(); //shows airline list for selecting airline for ticket
    int choice;
    cout << "\nEnter ID of the Airline choosen: ";
    cin >> choice;
    fstream fpt;
    fpt.open("ticket.txt", ios::app);
    if (!fpt)
    {
        cout << "\nFILE DOES NOT EXIST\n";
        exit(1);
    }
    fstream fp;
    fp.open("airline.txt", ios::in);
    if (!fp)
    {
        cout<<"\nFile not opened!\n";
        exit(0);
    }
    while (1)
    {
        fp >> name >> airline_email >> airline_id >> rating >> no_of_planes;
        if (fp.eof())
        {
            break;
        }
        if (airline_id == choice)
        {
            break;
        }
    }
    c_airline = name;
    fpt << c_name << "\t" << c_email << "\t" << c_airline << "\t" << c_id << "\t" << price << "\t" << ticket_ID << endl;
    fpt.close();
    cout << "Ticket is generated.\nID: " << ticket_ID << endl;
    system("PAUSE");
}

// Class for different payment options available for customers
class Payment //payment class with card payment or online banking
{
    string bank;
    long int card_no;
    int cvv, expiry_month, expiry_year;
    string username, password;

public:
    Payment()
    {
        card_no = 0;
        cvv = 0;
        expiry_month = 0;
        expiry_year = 0;
    }
    void menu()
    {
        Ticket t;
        t.menu();
        cout << "How do you want to pay for your flight: ";
        cout << "\n	1) Card Payment\n	2) Online Banking";
        int c;
        cout << "\n\n\tEnter your choice: ";
        cin >> c;
        switch (c)
        {
        case 1:
            card_payment();
            break;
        case 2:
            online_banking();
            break;
        default:
            system("cls");
            cout << "\nWrong choice. Try Again. \n";
            menu();
            break;
        }
    }
    void card_payment()
    {
        system("cls");
        cout << "Enter card Details: \n\tCard number: ";
        cin >> card_no;
        cout << "CVV: ";
        cin >> cvv;
        cout << "Enter expiry month(mm): ";
        cin >> expiry_month;
        while (1)
        {
            if (expiry_month > 12 && expiry_month <= 0)
            {
                cout << "Month input is wrong.\nEnter expiry month(mm)";
                cin >> expiry_month;
            }
            else
            {
                break;
            }
        }
        cout << "Enter expiry year(yyyy): ";
        cin >> expiry_year;
        system("cls");
        cout << "\t\t\t\tProcessing payment";
        Sleep(500);
        loading_screen();
        cout << "\t\t\t\tPayment Successful\n";
        system("PAUSE");
    }
    void online_banking()
    {
        char c;
        cout << "Enter bank name: ";
        getline(cin, bank);

        fflush(stdin);
        cout << "Enter user name: ";
        getline(cin, username);
        fflush(stdin);
        cout << "Enter password: ";
        password = inputmasking();
        fflush(stdin);
        cout << "\t\t\t\tProcessing payment";
        Sleep(500);
        loading_screen();
        cout << "\t\t\t\tPayment Successful\n";
        system("PAUSE");
    }
};

void names()
{
    cout << "\n--------------------------------------------------------------------------------------------------------------\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                          Welcome to Airline reservation system                             -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                      Developed by:                                         -\n";
    cout << "-                                              Muhammad Hatif Mujahid 20K-0218                               -\n";
    cout << "-                                                 Agha Maarij Amir 20K-0160                                  -\n";
    cout << "-                                                  Mohatada Jokhio 20K-0164                                  -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "--------------------------------------------------------------------------------------------------------------\n";
    system("PAUSE");
}
void main_screen() // main menu screen function
{

    system("cls");
    cout << "\n\t\t\t\t\tAIRLINE RESERVATION SYSTEM\n\n\n\t1) Admin\n\t2) Staff\n\t3) Customer\n\t4) Airline\n\t5) Special Customer\n\t6) Book a ticket\n\t7) Book a Holiday Package\n\t8) Print Ticket\n\t9) Refund Booking\n";
    int choice;
    cout << "\nEnter your choice: ";
    cin >> choice;
    if (choice == 1) //admin
    {
        system("cls");
        Admin a;
        a.menu();
        main_screen();
    }
    else if (choice == 2) //staff
    {
        system("cls");
        Staff s;
        s.menu();
        main_screen();
    }
    else if (choice == 3) //customer
    {
        system("cls");
        Customer c;
        c.menu();
        main_screen();
    }
    else if (choice == 4) //airline
    {
        Airline a1;
        while (1)
        {
            system("cls");
            a1.menu();
            int choice;
            cout << "\nEnter choice: ";
            cin >> choice;
            if (choice == 1)
            {
                a1.signup();
            }
            else if (choice == 2)
            {
                a1.showAirlines();
            }
            else if (choice == 3)
            {
                main_screen();
            }
            else
            {
                exit(1);
            }
        }
        main_screen();
    }
    else if (choice == 5) //special customer
    {
        system("cls");
        Special_customer s;
        s.menu();
        main_screen();
    }
    else if (choice == 6) //booking
    {
        system("cls");

        Booking b;
        b.menu();
        main_screen();
    }
    else if (choice == 7)
    {
        system("CLS");
        HolidayPackage h1;
        h1.login();
        main_screen();
    }
    else if (choice == 8)
    {
        Payment p;
        p.menu();
        main_screen();
    }
    else if (choice == 9)
    {
        int c;
        cout << "1.Customer\t2.SpecialCustomer" << endl;
        cin >> c;
        if (c == 1)
        {
            cout << "Contact Agency or Staff for Refund" << endl;
            system("PAUSE");
            main_screen();
        }
        else if (c == 2)
        {
            Special_customer s1;
            s1.b_refund();
            system("PAUSE");
            main_screen();
        }
    }
    else
    {
        cout << "Do you want to end the program?\n1) Yes \n2)Yesn't";
        cin >> choice;
        if (choice == 2)
        {
            main_screen();
        }
        else
        {
            exit(0);
        }
    }
}
void color() // color function
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    int P;
    P = 10;
    SetConsoleTextAttribute(console_color, P);
}
int main(int argc, char const *argv[])
{
    system("cls");
    color();
    names();
    system("cls");
    main_screen();
    return 0;
}
