#ifndef Final_Project
#define Final_Project
#include<string>
class Customer
{
private:
protected:
    std::string f_name, l_name;

public:
    std::string u, p;
    friend class Booking;
    friend class Staff;
    void set_fname(std::string f_name);
    const std::string get_fname();
    void set_lname(char l_name); 
    const std::string get_lname();
    void menu();
    void signup();

    void signin(std::string *user, std::string *pass);
    void customer_menu();
    void check_flight();
    void book_flight();
    void refund();
    
};
#endif