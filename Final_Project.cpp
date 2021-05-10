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
void loading_screen()
{
    cout << "\n\n\t\t\t\t\t ";
    printf("%c", 219);
    for (int a = 1; a < 50; a++)
    {
        Sleep(20);
        printf("%c", 219);
    }
    Sleep(30);
    system("cls");
}
string inputmasking(){
				char c;
				string password;
				
				
				while (1)
				{	
				
					c=getch();
					if (c!='\b'&&c!=13){
						password.push_back(c);
						putch('*');
					}
					else if(c=='\b'){
						if(password.size()!=0){
							password.erase(password.size()-1);
							cout<<"\b \b";
					
					}
			}
					else if (c==13){
						break;
					}
				}
				return password;	
		}
class ui //user interface class
{
public:
    virtual void menu() = 0;
};
class Person : public ui
{
    string username;
    string password;

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
        cout << "---------------------------------------SIGN UP----------------------------------------------------\n\nEnter username: ";
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
    //maybe sign in function to be made for abstraction
};
class Airline : virtual public Person // mohtada
{
protected:
    string name;
    int no_of_planes, rating;
    string sign_u, sign_p;

public:
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
    void menu()
    {
        cout << "::::::::::::::::::::::::::::::::::AIRLINE MENU::::::::::::::::::::::::::::::::::\n";
        cout << "\n\t\tWelcome to the Airline Login/Logout menu!!";
        cout << "\n1) Sign Up\n2) Sign in\n3)Show all airlines\n";
    }
    void signup() 
    {
        fflush(stdin);
        Person::signup();
        srand((unsigned)time(0)); //random rating generator
        rating = 1 + (rand() % 6);
        cout << "Enter name of airline: ";
        getline(cin, name);
        fflush(stdin);
        cout << "Enter no of planes in the fleet: ";
        cin >> no_of_planes;
    }
    void signin(string *u, string *p)
    {
        cout << "---------------------------------------Airline SIGN IN----------------------------------------------------\n\n";
        char c;
        fflush(stdin);
        cout << "Enter username: ";
        getline(cin, sign_u);
        fflush(stdin);
        cout << "Enter password: ";
        sign_p = inputmasking();
        *u = sign_u;
        *p = sign_p;
    }

    void showAirlines()
    {
        Airline a;
        ifstream fp("airline.dat", ios::in | ios::binary);
        fp.read((char *)&a, sizeof(Airline));
        system("cls");
        cout << "\nAirline name:  \tAirline rating: "
                "\tID: "
                "\tEmail: "
             << endl;
        while (1)
        {
            fp.read((char *)&a, sizeof(Airline));
            if (fp.eof())
            {
                break;
            }
            else
            {
                cout << "\t" << a.get_name() << "\t" << a.get_ID() << "\t" << a.get_planes() << "\t" << a.get_email() << "\t" << a.get_rating() << endl;
            }
        }
    }
    void airline_menu() {}
};
class Customer : virtual public Person // hatif
{
private:
protected:
    string f_name, l_name;

public:
    bool is_special = false;
    string u, p;
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
        cout << "\n1) Sign Up\n2) Sign in\n3)EXIT\n";
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
    }

    void signin(string *user, string *pass)
    {
        system("cls");
        cout << "---------------------------------------Customer SIGN IN---------------------------------------\n\n";
        char c;
        fflush(stdin);
        cout << "Enter username: ";
        getline(cin, u);
        fflush(stdin);
        cout << "Enter password: ";
        p = inputmasking();
        *user = u;
        *pass = p;
    }
    void customer_menu()
    {
        cout << "------------------------------------------Customer Main Menu----------------------------\n\n";
        cout << "\n\t1. Refund Booking\n\t2. Book a flight\n\t3. Check flight status\n\t4. Book a Holiday Package";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            refund();
            break;
        case 2:
            book_flight();
            break;
        case 3:
            check_flight();
            break;
        case 4:

            break;
        default:
            cout << "Wrong choice: \nDo you wanna end the program?\n1) Yes\n2) No";
            cin >> choice;
            switch (choice)
            {
            case 1:
                exit(0);
            case 2:
                customer_menu();
                break;
            default:
                break;
            }
            break;
        }
    }
    void check_flight();
    void book_flight();
    void refund();
};
class HolidayPackage : virtual public Person, public Customer
{
    string date;
    int tourcode;
    string departure, arrival;
    int tour;
    int choice;

public:
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
                book_package();
            }
            else if (choice == 1)
            {
                system("PAUSE");
                cout << " 1.Book a Package\t2.Main" << endl;
                cin >> c;
                if (c == 1)
                {
                    book_package();
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
                book_package();
            }
            else if (choice == 1)
            {
                system("PAUSE");
                cout << " 1.Book a Package\t2.Main" << endl;
                cin >> c;
                if (c == 1)
                {
                    book_package();
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
                book_package();
            }
            else if (choice == 1)
            {
                system("PAUSE");
                cout << " 1.Book a Package\t2.Main" << endl;
                cin >> c;
                if (c == 1)
                {
                    book_package();
                }
                else
                {
                    system("CLS");
                    menu();
                }
            }
        }
    }

    void book_package()
    {

        ofstream file("packages.txt", ios::app);

        cout << "Enter Package number you wish to select" << endl;
        cin >> tour;

        if (tour == 1)
        {
            if (arrival == "Toronto")
            {
                file << get_fname() << "\t"
                     << "\t" << ID << "\tQatar\t08:00\t\t11:05\t\t$.1500\t\tRefundable\t\t Pearl\n";

                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Sydney")
            {
                file << get_fname() << "\t" << ID << "\tQantas\t08:00\t\t11:05\t\t$.2500\t\tRefundable\t\tMeriton\n";

                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Paris")
            {
                file << get_fname() << "\t" << ID << "\tLufthansa\t08:00\t\t11:05\t\t$.3500\t\tRefundable\t\tBelvedere\n";

                cout << "PACKAGE BOOKED" << endl;
            }
        }

        if (tour == 2)
        {
            if (arrival == "Toronto")
            {
                file << get_fname() << "\t" << ID << "\tTurkish\t14:00\t\t17:05\t\t$.1250\t\tRefundable\t\tPC\n";
                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Sydney")
            {
                file << get_fname() << "\t" << ID << "\tEmirates\t14:00\t\t17:05\t\t$.2750\t\tRefundable\t\tRaddison\n";

                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Paris")
            {
                file << get_fname() << "\t" << ID << "\tEtihad\t14:00\t\t17:05\t\t$.3750\t\tRefundable\t\tShanzayLezay\n";

                cout << "PACKAGE BOOKED" << endl;
            }
        }

        if (tour == 3)
        {
            if (arrival == "Toronto")
            {
                file << get_fname() << "\t" << ID << "\tKLM\t19:00\t\t22:05\t\t$.2000\t\tNonrefundable\t\tMarriot\n";

                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Sydney")
            {
                file << get_fname() << "\t" << ID << "\tVirgin\t19:00\t\t22:05\t\t$.1900\t\tNonrefundable\t\tSheraton\n";
                cout << "PACKAGE BOOKED" << endl;
            }
            if (arrival == "Paris")
            {
                file << get_fname() << "\t" << ID << "\tNippon\t19:00\t\t22:05\t\t$.3000\t\tRefundable\t\tMovenpick\n";
                cout << "PACKAGE BOOKED" << endl;
            }
        }
        file.close();
    }
};
class Special_customer : public Person //maarij
{
    string u, p;

protected:
    int miles;
    string f_name, l_name;

public:
    bool is_special = true;
    friend class Booking;
    void menu()
    {
        cout << "\n\t\tWelcome to the Special customer Login/Logout menu!!";
        cout << "\n1) Sign Up\n2) Sign in\n3)EXIT\n";
       
    }
    void signup()
    {
        cout << "Enter miles" << endl;
        cin >> miles;
        if (miles >= 10000)
        {
            Person::signup();
            cout << "Enter first name: ";
            getline(cin, f_name);
            fflush(stdin);
            cout << "Enter last name: ";
            getline(cin, l_name);
            fflush(stdin);
        }
        else
        {
            cout << "Not enough miles" << endl
                 << "CONTINUE TRAVELLING WITH US" << endl;
            system("PAUSE");
            menu();
        }
    }
    void signin(string *user, string *pass)
    {
        cout << "---------------------------------------Special Customer SIGN IN----------------------------------------------------\n\n";
        char c;
        fflush(stdin);
        cout << "Enter username: ";
        getline(cin, u);
        fflush(stdin);
        cout << "Enter password: ";
        p = inputmasking();
        *user = u;
        *pass = p;
    }
    void s_customer_menu()
    {
        int c;
        cout << "_______________SPECIAL CUSTOMER MENU_________________" << endl;
        cout << "1.Refund Booking\t\t2.Book a flight\t\t3.Check flight status\t\t4.Book a Holiday Package" << endl;
        cin >> c;
        if (c == 1)
        {
            b_refund();
        }
        else if (c == 2)
        {
            s_customer_menu();
        }
        else if (c == 3)
        {
            s_customer_menu();
        }
        else if (c == 4)
        {
            HolidayPackage h;
            h.menu();
        }
    }
    void b_refund()
    {
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
            cout << "Enter Customer ID" << endl;
            cin >> x;
            while (original >> n >> i >> a >> d >> ar >> p >> c >> h)
            {

                if (i == x)
                {
                    cout << "TICKET REFUNDED" << endl
                         << "FUNDS TRANSFERRED" << endl;
                }
                else if (original.eof())
                {
                    cout << "BOOKING UNAVAILABE" << endl;
                    system("PAUSE");
                    b_refund();
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
    }
};
class Booking : public Airline, public Customer //mohtada
{
    Airline a1;
    int ticket_ID;
    string c_name, c_email, c_airline;
    int c_id;
    float price;
    float prices[3] = {4000, 10000, 15000};

protected:
public:
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
    void get_data()
    {
        int i;
        c_name = get_fname();
        c_id = get_ID();
        c_email = get_email();
        c_airline = Airline::get_name();
        srand((unsigned)time(0)); //random price generator
        i = (rand() % 3);
        price = prices[i];
        if (is_special == true)
        {
            price = price * 0.85;
        }
    }
    void menu();
    void book_tickets()
    {
        Booking a;
        int choice;
        loading_screen();
        cout << "List of airlines: ";
        Airline::showAirlines();
        cout << "Enter ID of the Airline choosen: ";
        cin >> choice;
        reading(choice);
        fstream fp("ticket.dat", ios::app | ios::binary);
        fp.write((char *)&a, sizeof(a));
        fp.close();
        menu();
    }
    void reading(int c)
    {
        Airline a1;
        fstream fpt("airline.dat", ios::in | ios::binary);
        while (1)
        {
            fpt.read((char *)&a1, sizeof(Airline));
            if (a1.get_ID() == c)
            {
                break;
            }
            else if (fpt.eof())
            {
                cout << "\nChoice not found\n";
                break;
            }
        }
        fpt.close();
    }
};

class Ticket : public Booking //printing ticket //mohtada
{
public:
    void menu()
    {
        cout << "\nProcessing ticket";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        printticket();
    }
    void printticket()
    {
        int choice;
        cout << "Enter ID of the ticket to be printed: ";
        cin >> choice;
        Booking t;
        fstream fpt;
        fpt.open("ticket.dat", ios::in | ios::binary);
        while (1)
        {
            fpt.read((char *)&t, sizeof(Ticket));
            if (t.get_ticket_id() == choice)
            {
                system("cls");
                cout << "\n\t\t\t\t\t\t\t\t\t\t\tTICKET ";
                cout << "\tName\tEmail\tAirline\tPrice";
                cout << "\t" << get_c_name() << "\t" << get_c_email() << "\t" << get_c_airline() << "\t" << get_price();
                break;
            }
            else if (fpt.eof())
            {
                cout << "Wrong ID";
                printticket();
            }
        }
    }
};
void Booking::menu()
{

    cout << "___________________________MENU BOOKING_______________________________\n ";
    cout << "\t1) Book a ticket\t2) Print a ticket\t3) Exit\n";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        book_tickets();
    }
    else if (choice == 2)
    {
        Ticket t;
        t.menu();
    }
    else
    {
        exit(0);
    }
}
class Staff : virtual public Person //maarij
{
private:
    string u, p;

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
    }

    void signin(string *username, string *password)
    {
        cout << "---------------------------------------STAFF SIGN IN----------------------------------------------------\n\n";
        char c;
        fflush(stdin);
        cout << "Enter username: ";
        getline(cin, u);
        fflush(stdin);
        cout << "Enter password: ";
        p = inputmasking();
        *username = u;
        *password = p;
    }

    void menu()
    {
        int c;
        cout << "__________________STAFF MENU______________________" << endl;
        cout << "1.SIGN UP\t\t2.SIGN-IN\t\t3.EXIT" << endl;
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
    }

    void refund()
    {
        int ch;
        string x, y;
        string n, i, a, d, ar, p, c, h, l;
        system("CLS");
        ifstream original("packages.txt", ios::out);
        ofstream copy("new.txt", ios::app);

        cout << "1.Ticket Refund\t\t2.Holiday Package Refund\n";
        cin >> ch;
        if (ch == 1)
        {
            cout << "Regular Tickets are Non-refundable" << endl;
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
        staff_menu();
    }

    void verify()
    {
        system("CLS");
        Booking b1;
        int i;
        cout << "Enter Ticket ID" << endl;
        cin>>i;
        fstream fpt;
        fpt.open("ticket.dat", ios::in | ios::binary);
        while (1)
        {
            fpt.read((char *)&t1, sizeof(Ticket));
            if (t1.get_ticket_id()==i)
            {
                Sleep(500);
                loading_screen();
                cout << "TICKET VERIFIED" << endl
                     << "ISSUE BOARDING PASS" << endl;
                break;
            }
        
            else if (fpt.eof())
            {
                cout << "BOOKING UNAVAILABLE" << endl;
            }
        }

        fpt.close();
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
class Admin : public Person //hatif
{
    string u, p;

protected:
    string f_name, l_name;

public:
    Admin() {}
    void set_fname(string f_name) { this->f_name = f_name; }
    const string get_fname() { return f_name; }
    void set_lname(char l_name) { this->l_name = l_name; }
    const string get_lname() { return l_name; }
    void menu()
    {
        cout << "__________________________________________ADMIN MENU__________________________________________\n\n\t1)Sign in\n\t2)Sign up\n\t3)Show admins\n";
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
    }
    void signin(string *user, string *pass)
    {
        cout << "__________________________________ADMIN SIGN IN______________________________________\n\n";
        fflush(stdin);
        cout << "Enter username: ";
        getline(cin, u);
        fflush(stdin);
        cout << "Enter password: ";
        char c;
        p = inputmasking();
        *user = u;
        *pass = p;
    }
    void admin_menu()
    {
        system("cls");
        cout << "__________________________________WELCOME " << f_name << " " << l_name << "______________________________________\n";
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
        Admin a;
        ifstream fp("admin.dat", ios::in | ios::binary);
        fp.read((char *)&a, sizeof(a));
        system("cls");
        cout << "\t\t\t\t\tADMIN LIST";
        cout << "\nFirst name:  \tLast name: "
                "\tID: "
                "\t\tEmail: "
             << endl;
        while (1)
        {
            if (!fp.eof())
            {
                fp.read((char *)&a, sizeof(a));
                cout << a.get_fname() << "\t\t" << a.get_lname() << "\t\t" << a.get_ID() << "\t\t" << a.get_email() << endl;
            }
            else
            {
                break;
            }
        }
    }
};
void Admin::delete_airline()
{
    Airline a;
    int ID;
    cout << "Enter ID of the Airline you want to delete: ";
    cin >> ID;
    loading_screen();
    fstream original("airline.dat", ios::in | ios::binary);
    fstream new_file("new.dat", ios::out | ios::binary);
    while (1)
    {   
        original.read((char *)&a, sizeof(Airline));
        if (a.get_ID() != ID)
        {
            new_file.write((char *)&a, sizeof(Airline));
        }
    }
    new_file.close();
    original.close();
    remove("airline.dat");
    rename("new.dat", "airline.dat");
    admin_menu();
}
void Admin::delete_staff()
{
    Staff a;
    int ID;
    cout << "Enter ID of the Staff you want to delete: ";
    cin >> ID;
    loading_screen();
    fstream original("staff.dat", ios::in | ios::binary);
    fstream new_file("new.dat", ios::out | ios::binary);
    while (1)
    {
        original.read((char *)&a, sizeof(Staff));
        if(original.eof()){
            cout<<"ID not found!";
            break;
        }
        if (a.get_ID() != ID)
        {
            new_file.write((char *)&a, sizeof(Staff));
        }
        
    }
    new_file.close();
    original.close();
    remove("staff.dat");
    rename("new.dat", "staff.dat");
    admin_menu();
}
void Admin::delete_customer()
{
    Customer a;
    int ID;
    cout << "Enter ID of the customer you want to delete: ";
    cin >> ID;
    loading_screen();
    fstream original("customer.dat", ios::in | ios::binary);
    fstream new_file("new.dat", ios::out | ios::binary);
    while (1)
    {
        original.read((char *)&a, sizeof(Customer));
        if(original.eof()){
            cout<<"ID not found!";
            break;
        }
        if (a.get_ID() != ID)
        {
            new_file.write((char *)&a, sizeof(Customer));
        }
    }
    new_file.close();
    original.close();
    remove("customer.dat");
    rename("new.dat", "customer.dat");
    admin_menu();
}

void Customer::book_flight()
{
    Booking a;
    a.menu();
    Customer::menu();
}
void Customer::check_flight()
{
}
void Customer::refund()
{
}
class Payment : protected Booking
{
    string bank;
    long int card_no;
    int cvv, expiry_month, expiry_year;

public:
    void menu()
    {
        cout << "How do you want to pay for your flight MR." << get_fname() << " " << get_lname() << ": ";
        cout << "\n	1) Card Payment\n	2) Online Banking";
        int choice;
        cout << "\n\n\tEnter your choice: ";
        switch (choice)
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
        cout << "Enter expiry month(mm)";
        cin >> expiry_month;
        while (expiry_month <= 12 && expiry_month > 0)
        {
            cout << "Month input is wrong.\nEnter expiry month(mm)";
            cin >> expiry_month;
        }
        cout << "Enter expiry year(yyyy)";
        cin >> expiry_year;
        system("cls");
        cout << "\t\t\t\tProcessing payment";
        Sleep(500);
        loading_screen();
        cout << "\t\t\t\tPayment Successful\n";
        Ticket t;
        t.menu();
    }
    void online_banking()
    {
        char c;
        cout << "Enter bank name: ";
        getline(cin, bank);
        string username, password;
        fflush(stdin);
        cout << "Enter user name: ";
        getline(cin, username);
        fflush(stdin);
        cout << "Enter password: ";

        while (true)
        {
            c = _getch();
            if (c == 13)
            {
                break;
            }
            else if (c == '\b')
            {
                password.pop_back();
                continue;
            }
            password.push_back(c);
            cout << "x";
        }
        fflush(stdin);
        cout << "\t\t\t\tProcessing payment";
        Sleep(500);
        loading_screen();
        cout << "\t\t\t\tPayment Successful\n";
        Ticket t;
        t.menu();
    }
};

void main_screen()
{
    cout << "\n\t\t\t\t\tAIRLINE RESERVATION SYSTEM\n\n\n\t1) Admin\n\t2) Staff\n\t3) Customer\n\t4) Airline\n\t5) Special Customer\n\t6)Book a ticket\n\t7) Print Ticket\n";
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == 1)
    {
        system("cls");
        Admin a;
        while (1)
        {
            a.menu();
            int choice;
            cout << "\nEnter choice: ";
            cin >> choice;
            if (choice == 2)
            {
                system("cls");
                a.signup();
                fstream fp;
                fp.open("admin.dat", ios::binary | ios::app);
                fp.write((char *)&a, sizeof(a));
                fp.close();
                system("cls");
                cout << "\n\n\t\tSIGN UP SUCCESSFUL\n";
            }
            else if (choice == 1)
            {
                system("cls");
                string u, p;
                a.signin(&u, &p);
                fstream fp;
                fp.open("admin.dat", ios::binary | ios::in);
                while (1)
                {
                    fp.read((char *)&a, sizeof(a));
                    if (a.get_username() == u && a.get_password() == p)
                    {
                        system("cls");
                        cout << "\n\n\tSIGN IN SUCCESSFUL\n\n";
                        Sleep(1000);
                        a.admin_menu();
                        break;
                    }
                    else if (fp.eof())
                    {
                        system("cls");
                        cout << "\nWRONG USERNAME OR PASSWORD. \n\n\t\t\tENTER AGAIN\n\n";
                        a.signin(&u, &p);
                    }
                }
                fp.close();
            }
            else
            {
                break;
            }
        }
    }
    else if (choice == 2)
    {
        int c;
        Staff s;
        while (1)
        {
            s.menu();
            cin >> c;
            if (c == 1)
            {
                s.signup();
                fstream f;
                f.open("staff.dat", ios::binary | ios::app);
                f.write((char *)&s, sizeof(s));
                f.close();
                system("CLS");
                cout << endl
                     << "SIGN UP SUCCESSFUL" << endl;
            }
            else if (c == 2)
            {
                string u, p;
                s.signin(&u, &p);
                fstream f;
                f.open("staff.dat", ios::binary | ios::in);
                while (1)
                {
                    f.read((char *)&s, sizeof(s));
                    if (s.get_username() == u && s.get_password() == p)
                    {
                        system("cls");
                        cout << "\nSIGN IN SUCCESSFUL\n";
                        Sleep(1000);
                        s.staff_menu();
                        break;
                    }
                    else if (f.eof())
                    {
                        system("cls");
                        cout << "\nWRONG USERNAME OR PASSWORD" << endl
                             << "TRY AGAIN" << endl;
                        s.signin(&u, &p);
                    }
                }
                f.close();
            }
            else if (c == 3)
            {
                exit(0);
            }
            else
            {
                exit(1);
            }
        }
    }
    else if (choice == 3)
    {
        Customer c;
        while (1)
        {
            c.menu();
            int choice;
            cout << "\nEnter choice: ";
            cin >> choice;
            if (choice == 1)
            {
                c.signup();
                fstream fp;
                fp.open("customer.dat", ios::binary | ios::app);
                fp.write((char *)&c, sizeof(c));
                fp.close();
                system("cls");
                cout << "\nSIGN UP SUCCESSFUL\n";
                Sleep(1000);
                c.menu();
            }
            else if (choice == 2)
            {
                string u, p;
                c.signin(&u, &p);
                fstream fp;
                fp.open("customer.dat", ios::binary | ios::in);
                while (1)
                {
                    fp.read((char *)&c, sizeof(c));
                    if (c.get_username() == u && c.get_password() == p)
                    {
                        system("cls");
                        cout << "\nSIGN IN SUCCESSFUL\n";
                        Sleep(1000);
                        system("cls");
                        c.customer_menu();
                        break;
                    }
                    else if (fp.eof())
                    {
                        system("cls");
                        cout << "\nWRONG USERNAME OR PASSWORD. \n\n\t\t\tENTER AGAIN";
                        c.signin(&u, &p);
                    }
                }
                fp.close();
            }
            else if (choice == 3)
            {
                exit(0);
            }
            else
            {
                exit(1); //wrong input gives return value 1 at end
            }
        }
    }
    else if (choice == 4)
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
                fstream fp;
                fp.open("customer.dat", ios::binary | ios::app);
                fp.write((char *)&a1, sizeof(a1));
                fp.close();
                system("cls");
                cout << "\nSIGN UP SUCCESSFUL\n";
                Sleep(500);
            }
            else if (choice == 2)
            {
                string u, p;
                a1.signin(&u, &p);
                fstream fp;
                fp.open("customer.dat", ios::binary | ios::in);
                while (1)
                {
                    fp.read((char *)&a1, sizeof(a1));
                    if (a1.get_username() == u && a1.get_password() == p)
                    {
                        system("cls");
                        cout << "\nSIGN IN SUCCESSFUL\n";
                        a1.airline_menu();
                        break;
                    }
                    else if (fp.eof())
                    {
                        system("cls");
                        cout << "\nWRONG USERNAME OR PASSWORD. \n\n\t\t\tENTER AGAIN";
                        a1.signin(&u, &p);
                    }
                }
                fp.close();
            }
            else if (choice == 3)
            {
                a1.showAirlines();
            }
            else
            {
                exit(0);
            }
        }
    }
    else if (choice == 5){
        Special_customer s;
        s.menu();
        int c;
        cout << "\nEnter choice: ";
        cin >> c;
        if (c == 1)
        {
            s.signup();
            fstream fp;
            fp.open("special_customer.dat", ios::binary | ios::app);
            fp.write((char *)&s, sizeof(s));
            fp.close();
            system("cls");
            cout << "\nSIGN UP SUCCESSFUL\n";
            Sleep(500);
        }
        else if (c == 2)
        {
            string u, p;
                s.signin(&u, &p);
                fstream fp;
                fp.open("special_customer.dat", ios::binary | ios::in);
                while (1)
                {
                    fp.read((char *)&s, sizeof(s));
                    if (s.get_username() == u && s.get_password() == p)
                    {
                        system("cls");
                        cout << "\nSIGN IN SUCCESSFUL\n";
                        s.s_customer_menu();
                        break;
                    }
                    else if (fp.eof())
                    {
                        system("cls");
                        cout << "\nWRONG USERNAME OR PASSWORD. \n\n\t\t\tENTER AGAIN";
                        s.signin(&u, &p);
                    }
                }
                fp.close();
            }

        else if (c == 3)
        {
            exit(0);
        }

    }
    else if (choice == 6)
    {
        Booking b;
        b.menu();
    }
    else if (choice == 7)
    {
        Ticket t;
        t.menu();
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

int main()
{
    system("cls");
    system("color B0");
    main_screen();
}
