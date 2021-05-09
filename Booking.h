#ifndef Final_Project
#define Final_Project

class Booking : protected Airline, public Customer //mohtada
{
    Airline a1;
    int ticket_ID;
    string c_name, c_email, c_airline;
    int c_id;

protected:
    void show()
    {
        cout << "\n\t\tTicket\nName: " << c_name << "Email: " << c_email << "ID: " << c_id << "Airline: " << c_airline << endl;
    }

public:
    static int t_id;
    const int get_ticket_id()
    {
        return ticket_ID;
    }
    Booking()
    {
        t_id++;
        ticket_ID = t_id;
    }

    void get_data()
    {
        c_name = get_fname();
        c_id = get_ID();
        c_email = get_email();
        c_airline = Airline::get_name();
    }
    void menu()
    {
        cout << "___________________________MENU BOOKING_______________________________\n ";
    }
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
        ofstream fp("ticket.dat", ios::app | ios::binary);
        fp.write((char *)&a, sizeof(a));
        fp.close();
    }
    void reading(int c)
    {
        ifstream fpt("airline.dat", ios::in | ios::binary);
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
#endif