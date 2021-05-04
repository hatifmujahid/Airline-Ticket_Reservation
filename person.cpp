#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

using namespace std;
void loading_screen()
{
	cout << "\n\n\t\t\t\t\t ";
	printf("%c", 219);
	for (int a = 1; a < 70; a++)
	{
		Sleep(20);
		printf("%c", 219);
	}
}
class ui //user interface class
{
public:
	virtual void menu() = 0;
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
	//make sign up function and store data in file
	// in booking class print all the signed up airlines from which customer can choose which one he likes
public:
};
class Customer : virtual public Person // hatif
{
private:
protected:
	string f_name, l_name;

public:
	Customer(){}
	static int c_no;
	void set_fname(string f_name) { this->f_name = f_name; }
	const string get_fname() { return f_name; }
	void set_lname(char l_name) { this->l_name = l_name; }
	const string get_lname() { return l_name; }
	Customer()
	{
		c_no++;
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
		system("cls");
		cout << "\nSign up successful\n	1) Go back to Customer Menu\n	2) Logout\n    3) ";
	}
	void signin()
	{
		system("cls");
		cout << "---------------------------------------SIGN IN----------------------------------------------------\n\n";
	k:
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
			else
			{
				system("cls");
				cout << "\n\nSign in is unsuccessful";
				goto k;
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
			exit(0);
		}
	}
	~Customer()
	{
		c_no--;
	}
	void output()
	{
		cout << "\nCustomer Details";
		Person::output();
		cout << "\nFirst name: " << f_name << "\nLast name: " << l_name;
	}
};
class Special_customer : protected Person //maarij
{
protected:
public:
};
class admin : protected Person
{
protected:
	string f_name, l_name;

public:
	admin(){}
	void set_fname(string f_name) { this->f_name = f_name; }
	const string get_fname() { return f_name; }
	void set_lname(char l_name) { this->l_name = l_name; }
	const string get_lname() { return l_name; }
	void menu()
	{
		cout << "---------------------------------------ADMIN MENU----------------------------------------------------\n\n     1)Sign in\n    2)Sign up\n    3)Delete Customer\n    ";
	}
	void delete_customer()
	{
	}
	void signup()
	{
	}
	void signin()
	{
		system("cls");
	k:
		cout << "---------------------------------------SIGN IN----------------------------------------------------\n\n";
		string u, p;
		fflush(stdin);
		cout << "Enter username: ";
		getline(cin, u);
		fflush(stdin);
		cout << "Enter password: ";
		getline(cin, p);
		fflush(stdin);
		ifstream fp("admin.txt", ios::out);
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
			else
			{
				system("cls");
				cout << "\n\nSign in is unsuccessful";
				goto k;
			}
		}
		fp.close();
	}
};

class Staff : protected Person
{	//maarij add check ticket function which will
	//check the ticket code from ticket ki file.
public:
};
class Booking : protected Airline, protected Customer //mohtada
{
};
class Payment : protected Booking
{
	string bank;
	long int card_no;
	int cvv, expiry_month, expiry_year;

public:
	void menu()
	{
	wrong_choice:
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
			goto wrong_choice;
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
	}
	void online_banking()
	{
		string username, password;
		fflush(stdin);
		cout << "Enter user name: ";
		getline(cin, username);
		fflush(stdin);
		cout << "Enter password: ";
		getline(cin, password);
		fflush(stdin);
		cout << "\t\t\t\tProcessing payment";
		Sleep(500);
		loading_screen();
	}
};
class Ticket : protected Person, protected Airline //printing ticket //mohtada
{
};
class Ticket : protected Person, protected Airline //printing ticket //mohtada
{
};
class HolidayPackage:virtual public Person, public Customer  
{   string date;
    int tourcode;
    string departure,arrival;
    int tour;
    int choice;
public:
	void menu(){
		cout<<"WELCOME TO THE HOLIDAY TOURS AND PACKAGES MENU"<<endl;
		cout<<" 1.View Packages\t2.Book a Package\t3.Exit to main\n";
		cout<<"Enter choice"<<endl;
		cin>>choice;
		if(choice==1 || choice==2){
			package_details();
		}
		else{
			exit(1);
		}

	}
void package_details(){
	int c;
    system("CLS");
    cout<<"---------------------------------HOLIDAY PACKAGE TOURS-----------------------------------"<<endl;
cout<<"Enter a valid date to see available Packages"<<endl;
cin>>date;
fflush(stdin);
system("CLS");
cout<<"ENTER DEPARTURE CITY NAME FROM THE FOLLOWING"<<endl;
cout<<"1.Karachi(1) \t\t 2.Lahore(2) \t\t 3. Islamabad(3) \t\t  "<<endl;
cin>>departure;
system("CLS");
cout<<"AVAILABE PACKAGES :"<<endl;

cout<<"1. Toronto(1) \t\t 2.Sydney(2) \t\t 3. Paris(3)  \t\t"<<endl;
cout<<"ENTER CITY NAME TO VIEW PACKAGE DETAILS"<<endl;
cin>>arrival;

if((departure=="Karachi"&& arrival=="Toronto") || (departure=="Lahore" && arrival=="Toronto") || (departure=="Islamabad" && arrival=="Toronto")  ){
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
            cout << "\ 1.Qatar\t08:00\t\t11:05\t\t$.1500\t\tRefundable\t\tThe Pearl Resort\n";
            cout << "\ 2.Fly Dubai\t14:00\t\t17:05\t\t$.1250\t\tRefundable\t\tCountryside View\n";
            cout << "\ 3.Go Air\t19:00\t\t22:05\t\t$.2000\t\tNon-refundable\t\tMarriot\n";
            if(choice==2){
            book_package();
			}
			else if(choice==1){
				system("PAUSE");
				cout<<" 1.Book a Package\t2.Main"<<endl;
				cin>>c;
				if(c==1){
				book_package();
				}
				else{
				system("CLS");
				menu();	
				}

			}

}
if((departure=="Karachi"&& arrival=="Sydney") || (departure=="Lahore" && arrival=="Sydney") || (departure=="Islamabad" && arrival=="Sydney")  ){
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
            cout << "\ 1.Qantas\t08:00\t\t11:05\t\t$.2500\t\tRefundable\t\tKangaroo Resort\n";
            cout << "\ 2.Emirates\t14:00\t\t17:05\t\t$.2750\t\tRefundable\t\tValley Side\n";
            cout << "\ 3.Go Air\t19:00\t\t22:05\t\t$.1900\t\tNon-refundable\t\tSheraton\n";
            if(choice==2){
            book_package();
			}
			else if(choice==1){
				system("PAUSE");
				cout<<" 1.Book a Package\t2.Main"<<endl;
				cin>>c;
				if(c==1){
				book_package();
				}
				else{
				system("CLS");
				menu();	
				}

			}

}

if((departure=="Karachi"&& arrival=="Paris") || (departure=="Lahore" && arrival=="Paris") || (departure=="Islamabad" && arrival=="Paris")  ){
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
            cout << "\ 1.Lufthansa\t08:00\t\t11:05\t\t$.3500\t\tRefundable\t\tThe Eiffel Resort\n";
            cout << "\ 2.Fly Dubai\t14:00\t\t17:05\t\t$.3750\t\tRefundable\t\tShanzay Lezay Motel\n";
            cout << "\ 3.United Air\t19:00\t\t22:05\t\t$.3000\t\tRefundable\t\tMovenpick\n";
            if(choice==2){
            book_package();
			}
			else if(choice==1){
				system("PAUSE");
				cout<<" 1.Book a Package\t2.Main"<<endl;
				cin>>c;
				if(c==1){
				book_package();
				}
				else{
				system("CLS");
				menu();	
				}

			}

}

}

void book_package(){

ofstream file("packages.txt",ios::app);

cout<<"Enter Package number you wish to select"<<endl;
cin>>tour;
file << "Name:\tID\t:Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";

if(tour==1) {
    if(arrival=="Toronto"){
    file<<f_name<<"\t"<<ID<<"\tQatar\t08:00\t\t11:05\t\t$.1500\t\tRefundable\t\tThe Pearl Resort\n"<<departure<<" to "<<arrival<<"\n";
    cout<<"PACKAGE BOOKED"<<endl;
    }
    if(arrival=="Sydney"){
    file<<f_name<<"\t"<<ID<<"\tQantas\t08:00\t\t11:05\t\t$.2500\t\tRefundable\t\tKangaroo Resort\n"<<departure<<" to "<<arrival<<"\n";
    cout<<"PACKAGE BOOKED"<<endl;
    }
    if(arrival=="Paris"){
     file<<f_name<<"\t"<<ID<<"\tLufthansa\t08:00\t\t11:05\t\t$.3500\t\tRefundable\t\tThe Eiffel Resort\n"<<departure<<" to "<<arrival<<"\n"; 
     cout<<"PACKAGE BOOKED"<<endl;
    }

}

if(tour==2){
    if(arrival=="Toronto"){
        file<<f_name<<"\t"<<ID<<"\tFly Dubai\t14:00\t\t17:05\t\t$.1250\t\tRefundable\t\tCountryside View\n"<<departure<<" to "<<arrival<<"\n";
        cout<<"PACKAGE BOOKED"<<endl;
    }
    if(arrival=="Sydney"){
        file<<f_name<<"\t"<<ID<<"\tEmirates\t14:00\t\t17:05\t\t$.2750\t\tRefundable\t\tValley Side\n"<<departure<<" to "<<arrival<<"\n";
        cout<<"PACKAGE BOOKED"<<endl;

    }
    if(arrival=="Paris"){
        file<<f_name<<"\t"<<ID<<"\tFly Dubai\t14:00\t\t17:05\t\t$.3750\t\tRefundable\t\tShanzay Lezay Motel\n"<<departure<<" to "<<arrival<<"\n";
        cout<<"PACKAGE BOOKED"<<endl;

    }

}

if(tour==3){
    if(arrival=="Toronto"){
        file<<f_name<<"\t"<<ID<<"\tGo Air\t19:00\t\t22:05\t\t$.2000\t\tNon-refundable\t\tMarriot\n"<<departure<<" to "<<arrival<<"\n";
        cout<<"PACKAGE BOOKED"<<endl;
}
    if(arrival=="Sydney"){
        file<<f_name<<"\t"<<ID<<"\tGo Air\t19:00\t\t22:05\t\t$.1900\t\tNon-refundable\t\tSheraton\n"<<departure<<" to "<<arrival<<"\n";
       cout<<"PACKAGE BOOKED"<<endl;
}
    if(arrival=="Paris"){
       file<<f_name<<"\t"<<ID<<"\tUnited Air\t19:00\t\t22:05\t\t$.3000\t\tRefundable\t\tMovenpick\n"<<departure<<" to "<<arrival<<"\n";
       cout<<"PACKAGE BOOKED"<<endl;
}


}
file.close();


}



};
int Customer::c_no = 0;

int main()
{
	cout << "\t\t\tAIRLINE RESERVATION SYSTEM\n\nThis program has 4 branches: \n    1) Admin\n    2) Staff\n    3)Customer\n    4) Airline\n      5)End program\n";
	int choice;
	cout << "Enter your choice: ";
	cin >> choice;
	if (choice == 1)
	{
		admin a;
		a.menu();
	}
	else if (choice == 2)
	{
		// Staff s;
		// s.menu();
	}
	else if (choice == 3)
	{
		Customer c;
		c.menu();
	}
	else if (choice == 4)
	{
		// Airline a;
		// a.menu();
	}
}
