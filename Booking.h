#ifndef Final_Project
#define Final_Project
class Airline;
class Customer : virtual public Person // hatif
{
private:
protected:
    string f_name, l_name;

public:
    string u, p;
    friend class Booking;
    friend class Staff;
    void set_fname(string f_name);
    const string get_fname();
    void set_lname(char l_name);
    const string get_lname();
    void menu();
    void signup();

    void signin(string *user, string *pass);
    void customer_menu();
    void check_flight();
    void book_flight();
    void refund();
};
class Booking: protected Airline, public Customer
{
    int ticket_ID;
    //string c_name, c_email, c_airline;
    int c_id;

protected:
    void show();

public:
    static int t_id;
    const int get_ticket_id();
    Booking();

    void get_data();
    void menu();
    void book_tickets();
    void reading(int c);
};
#endif