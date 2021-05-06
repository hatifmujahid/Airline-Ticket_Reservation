#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include<cstdlib>
#include<cstring>
#include<conio.h>
//ios::in input
//ios::out output
//ofstream output to file
//ifstream input from file
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
void menu(){
	cout<<"::::::::::::::::::::::::::::::::::AIRLINE MENU::::::::::::::::::::::::::::\n";
}
};
class Customer : virtual public Person // hatif
{
private:
	string u,p;
protected:
	string f_name, l_name;
	
public:
	friend void delete_customer();
	static int c_no;
	void set_fname(string f_name) { this->f_name = f_name; }
	const string get_fname() { return f_name; }
	void set_lname(char l_name) { this->l_name = l_name; }
	const string get_lname() { return l_name; }
	Customer()
	{
		c_no++;
	}
	void menu()
	{
		cout << "\n\t\tWelcome to the customer Login/Logout menu!!";
		cout << "\n1) Sign Up\n2) Sign in\n3)Show number of customers\n";
		int choice;
		cout << "\nEnter choice: ";
		cin >> choice;
		if(choice==1)
		{
			Customer::signup();
		}
		else if(choice==2){
			Customer::signin();
		}
		else if(choice==3){
			cout << "No of customers: " << c_no << endl;
		}else{
			exit(0);
		}
	}
	void signup()
	{
		Customer a;
		Person::signup();
		cout << "Enter first name: ";
		getline(cin, f_name);
		fflush(stdin);
		cout << "Enter last name: ";
		getline(cin, l_name);
		fflush(stdin);
	}
	void filing(Customer a){
		ofstream fp("customer.dat", ios::app|ios::binary);
		fp.write((char*)&a, sizeof(Customer));
		if(!fp) {
			cout << "Cannot open file!" << endl;
			exit(1);
   		}
		fp.close();
		system("cls");
		cout << "\nSign up successful\n	1) Go back to Customer Login/Logout Menu\n	2) Login\n";
		int choice;
		cin>>choice;
		switch (choice)
		{
		case 1:
			menu();
			break;
		case 2:
			signin();
			break;
		default:
			break;
		}
	}
	void signin()
	{
		cout << "---------------------------------------Customer SIGN IN----------------------------------------------------\n\n";
		char c;
		fflush(stdin);
		cout << "Enter username: ";
		getline(cin, u);
		fflush(stdin);
		cout << "Enter password: ";
		for(int i=0;i<1000;i++)	//input masking
		{
			c=getch();
			if(c=='\r')
				break;
			cout<<"*";
			p+=c;
		}
		fflush(stdin);
	}
	void reading(Customer a1){
		
		ifstream fpt("customer.dat", ios::in|ios::binary);
		while (1)
		{
			fpt.read((char*)&a1, sizeof(Customer));
			if (a1.username == u && a1.password == p)
			{
				system("cls");
				cout << "\n\nSign in is Successful\n";
				customer_menu();
				break;
			}
			else if(fpt.eof())
			{
				system("cls");
				cout << "\n\nSign in is unsuccessful\n";
				signin();
			}
		}
		fpt.close();
	}
	~Customer()
	{
		c_no--;
	} 
	void customer_menu(){
		cout<<"------------------------------------------Customer Main Menu----------------------------\n\n";
		cout<<"\t1) Check Flight\n\t2)	Book Flight\n\t3) Logout";
		int choice;
		cin>>choice;
		switch (choice)
		{
		case 1:
			check_flight();
			break;
		case 2:
			book_flight();
			break;
		default:
			break;
		}
	}
	void check_flight(){
		//ticket class by maaarij
		customer_menu();
	}
	void book_flight(){
		//booking class by mohtada
		customer_menu();
	}
};
class Special_customer : protected Person //maarij
{
protected:
public:
};
class Admin : protected Person //hatif
{
	string u, p;
protected:
	string f_name, l_name;
public:
	Admin(){}
	void delete_customer(){
		Customer a;
		int ID;
		cout<<"Enter ID of the customer you want to delete: ";
		cin>>ID;
		loading_screen();
		ifstream original("customer.dat", ios::out|ios::binary);
		ofstream new_file("new.dat", ios::in|ios::binary);
		original.read((char*)&a, sizeof(Customer));
		while(1){
			if(a.get_ID()!=ID){
				new_file.write((char*)&a, sizeof(Customer));
			}
		}
		new_file.close();
		original.close();
		remove("customer.dat");
		rename("new.dat", "customer.dat");
	}
	friend void delete_staff();
	friend void delete_airline();
	void set_fname(string f_name) { this->f_name = f_name; }
	const string get_fname() { return f_name; }
	void set_lname(char l_name) { this->l_name = l_name; }
	const string get_lname() { return l_name; }
	void menu()
	{
		cout << "__________________________________________ADMIN MENU__________________________________________\n\n\t1)Sign in\n\t2)Sign up\n\t3)Show admins\n";
		int choice;
		cin>>choice;
		switch (choice)
		{
		case 1:
			signin();
			break;
		case 2:
			signup();
			break;
		default: 
			exit(0);
		}
	}	
	void admin_menu(){
		system("cls");
		cout<<"__________________________________WELCOME "<<f_name<<" "<<l_name<<"______________________________________\n";
		cout<<"\t1) Delete a Customer\n\t2) Delete an Airline\n\t3) \n\n\t\tEnter choice: ";
		int choice;
		cin>>choice;
		if(choice==1){
			delete_customer();
		}
	}
	
	void signup()
	{
		Customer a;
		Person::signup();
		cout << "Enter first name: ";
		getline(cin, f_name);
		fflush(stdin);
		cout << "Enter last name: ";
		getline(cin, l_name);
		fflush(stdin);
	}
	void filing(Admin a){
		ofstream fp("admin.dat", ios::app|ios::binary);
		fp.write((char*)&a, sizeof(Admin));
		if(!fp) {
			cout << "Cannot open file!" << endl;
			exit(1);
   		}
		fp.close();
		system("cls");
		cout << "\nSign up successful\n	1) Go back to Customer Login/Logout Menu\n	2) Login\n";
		int choice;
		cin>>choice;
		switch (choice)
		{
		case 1:
			Admin::menu();
			break;
		case 2:
			Admin::signin();
			break;
		default:
			break;
		}
	}
	void signin()
	{
		cout << "__________________________________ADMIN SIGN IN______________________________________\n\n";
		fflush(stdin);
		cout << "Enter username: ";
		getline(cin, u);
		fflush(stdin);
		cout << "Enter password: ";
		char c;
		for(int i=0;i<1000;i++)	//input masking
		{
			c=getch();
			if(c=='\r')
				break;
			cout<<"*";
			p+=c;
		}
		fflush(stdin);
	}
	void reading(Admin a1){
		
		ifstream fpt("admin.dat", ios::in|ios::binary);
		while (1)
		{
			fpt.read((char*)&a1, sizeof(Admin));
			if (a1.username == u && a1.password == p)
			{
				system("cls");
				cout << "\n\nSign in is Successful\n";
				admin_menu();
				break;
			}
			else if(fpt.eof())
			{
				system("cls");
				cout << "\n\nSign in is unsuccessful\n";
				signin();
			}
		}
		fpt.close();
	}
	void show_admin(Admin a){
		ifstream fp("admin.dat", ios::in|ios::binary);
		fp.read((char*)&a, sizeof(a));
		system("cls");
		cout<<"\nFirst name:  \tLast name: ""\tID: ""\tEmail: "<<a.email<<endl;
		while(1){
			if(fp.eof()){
				break;
			}
			else{
				cout<<"\t"<<a.f_name<<"\t"<<a.l_name<<"\t"<<a.ID<<"\t"<<a.email<<endl;
			}
		}

		admin_menu();
	}

};
class Staff : protected Person //maarij
{	 //add check ticket function which will
	//check the ticket code from ticket ki file.
public:
	static int ticket_ID;
	void menu(){
		cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^STAFF MENU^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
	}
};
class Booking : protected Airline, protected Customer //mohtada
{
	public:
		void menu(){
			cout<<"Booking";
		}
};
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
		cin>>card_no;
		cout << "CVV: ";
		cin>>cvv;
		cout << "Enter expiry month(mm)";
		cin>>expiry_month;
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
		cout << "\t\t\t\tPayment Successful";
	}
	void online_banking()
	{
		char c;
		cout<<"Enter bank name: ";
		getline(cin, bank);
		string username, password;
		fflush(stdin);
		cout << "Enter user name: ";
		getline(cin, username);
		fflush(stdin);
		cout << "Enter password: ";
		for(int i=0;i<1000;i++)	//input masking
		{
			c=getch();
			if(c=='\r')
				break;
			cout<<"*";
			password+=c;
		}
		fflush(stdin);
		cout << "\t\t\t\tProcessing payment";
		Sleep(500);
		loading_screen();
		cout << "\t\t\t\tPayment Successful\n\t\t\t\tEnjoy your Flight!!";

	}
};

class Ticket : virtual protected Person, protected Airline //printing ticket //mohtada
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
getline(cin, departure);
system("CLS");
cout<<"AVAILABE PACKAGES :"<<endl;

cout<<"1. Toronto(1) \t\t 2.Sydney(2) \t\t 3. Paris(3)  \t\t"<<endl;
cout<<"ENTER CITY NAME TO VIEW PACKAGE DETAILS"<<endl;
getline(cin, arrival);

if((departure=="Karachi"&& arrival=="Toronto") || (departure=="Lahore" && arrival=="Toronto") || (departure=="Islamabad" && arrival=="Toronto")  ){
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
            cout << "1.Qatar\t08:00\t\t11:05\t\t$.1500\t\tRefundable\t\tThe Pearl Resort\n";
            cout << "2.Fly Dubai\t14:00\t\t17:05\t\t$.1250\t\tRefundable\t\tCountryside View\n";
            cout << "3.Go Air\t19:00\t\t22:05\t\t$.2000\t\tNon-refundable\t\tMarriot\n";
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
            cout << "1.Qantas\t08:00\t\t11:05\t\t$.2500\t\tRefundable\t\tKangaroo Resort\n";
            cout << "2.Emirates\t14:00\t\t17:05\t\t$.2750\t\tRefundable\t\tValley Side\n";
            cout << "3.Go Air\t19:00\t\t22:05\t\t$.1900\t\tNon-refundable\t\tSheraton\n";
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
            cout << "1.Lufthansa\t08:00\t\t11:05\t\t$.3500\t\tRefundable\t\tThe Eiffel Resort\n";
            cout << "2.Fly Dubai\t14:00\t\t17:05\t\t$.3750\t\tRefundable\t\tShanzay Lezay Motel\n";
            cout << "3.United Air\t19:00\t\t22:05\t\t$.3000\t\tRefundable\t\tMovenpick\n";
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
int Staff::ticket_ID=1000;

void main_screen(){
	cout << "\t\t\tAIRLINE RESERVATION SYSTEM\n\n\n\t1) Admin\n\t2) Staff\n\t3)Customer\n\t4)Airline\n\t5)Book a ticket\n\t6)Check ticket\n\t7)Print Ticket\n\t8)Check Flight schedule\n";
	int choice;
	cout << "Enter your choice: ";
	cin >> choice;
	if (choice == 1)
	{
		Admin a;
		a.menu();
		a.filing(a);
		a.reading(a);
	}
	else if (choice == 2)
	{
		Staff s;
		s.menu();
	}
	else if (choice == 3)
	{
		Customer c,c1;
		c.menu();	//goes to menu sign in, sign up
		c.filing(c);	//saves data in file when sign up and re routes to customer login
		c.reading(c);	//retrives data from file logging back in
	}
	else if (choice == 4)
	{
		Airline a1;
		a1.menu();
	}
	else if(choice==5){
		//Ticket t;
	}
	else if(choice ==6){

	}
	else if(choice ==7){

	}
	else if(choice ==8){

	}
	else{
		exit(0);
	}
}
int main()
{
	main_screen();
}
