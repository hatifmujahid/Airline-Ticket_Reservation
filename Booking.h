#ifndef Final_Project
#define Final_Project
class Airline;
class Customer;
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