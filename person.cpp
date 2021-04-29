#include <iostream>
#include <fstream>

using namespace std;
class Person
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
    void output()
    {
        cout << name << endl
             << email << endl
             << username << endl
             << password;
    }
    void signup()
    {
        fflush(stdin);
        cout << "SIGN UP\n\nEnter username: ";
        cin >> username;
        fflush(stdin);
        cout << "Enter password: ";
        cin >> password;
        fflush(stdin);
        cout << "Enter name: ";
        cin >> name;
        fflush(stdin);
        cout << "Enter designated ID: ";
        cin >> ID;
        cout << "Enter email: ";
        cin >> email;
        fflush(stdin);
    }
};
class Airline : protected Person // mohtada
{
protected:
public:
};
class Customer : protected Person // hatif
{
    private:
        string air_name;

    public:
        void set_airname(string air_name){
            this->air_name= air_name;
        }
        const string get_airname(){
            return air_name;
        }
        Customer(){}
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
    void file(Person b)
    {
        ofstream fp("data.dat", ios::binary | ios::out);
        fp.write((char *)&b, sizeof(b));
        fp.close();
    }
    Person reading()
    {
        Person b1;
        ifstream fptr("data.dat", ios::binary | ios::out);
        fptr.read((char *)&b1, sizeof(b1));
        fptr.close();
        return b1;
    }
};
class Ticket : protected Person, protected Airline //printing ticket //mohtada
{
};
class HolidayPackage : Person, Ticket, Booking //maarij hotels, tour,
{
};
int main()
{
    Person a;
    Filing f;
    a.signup();
    f.file(a);
}
