void package_details()
{
    system("CLS");
    cout << "---------------------------------HOLIDAY PACKAGE TOURS-----------------------------------" << endl;
    cout << "Enter a valid date to see available Packages" << endl;
    cin >> date;
    fflush(stdin);
    system("CLS");
    cout << "SELECT DEPARTURE CITY FROM THE FOLLOWING" << endl;
    cout << "1. KARACHI(1) \t\t 2.LAHORE(2) \t\t 3. ISLAMABAD(3) \t\t  " << endl;
    cin >> departure;
    system("CLS");
    cout << "AVAILABE PACKAGES :" << endl;

    cout << "1. TORONTO(1) \t\t 2.SYDNEY(2) \t\t 3. PARIS(3)  \t\t" << endl;
    cout << "SELECT ANY OF THE ABOVE TO VIEW PACKAGE DETAILS" << endl;
    cin >> arrival;

    if ((departure == 1 && arrival == 1) || (departure == 2 && arrival == 1) || (departure == 3 && arrival == 1))
    {
        cout << "\t \t \tFlights Found" << endl
             << endl;
        cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
        cout << "\1.Qatar(1)\t08:00\t\t11:05\t\t$.1500\t\tRefundable\t\tThe Pearl Resort\n";
        cout << "\2.Fly Dubai(2)\t14:00\t\t17:05\t\t$.1250\t\tRefundable\t\tCountryside View\n";
        cout << "\3.Go Air(3)\t19:00\t\t22:05\t\t$.2000\t\tNon-refundable\t\tMarriot\n";
    }
    if ((departure == 1 && arrival == 2) || (departure == 2 && arrival == 2) || (departure == 3 && arrival == 2))
    {
        cout << "\t \t \tFlights Found" << endl
             << endl;
        cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
        cout << "\1.Qantas(1)\t08:00\t\t11:05\t\t$.2500\t\tRefundable\t\tKangaroo Resort\n";
        cout << "\2.Emirates(2)\t14:00\t\t17:05\t\t$.2750\t\tRefundable\t\tValley Side\n";
        cout << "\3.Go Air(3)\t19:00\t\t22:05\t\t$.1900\t\tNon-refundable\t\tSheraton\n";
    }

    if ((departure == 1 && arrival == 1) || (departure == 2 && arrival == 1) || (departure == 3 && arrival == 1))
    {
        cout << "\t \t \tFlights Found" << endl
             << endl;
        cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\t\tHotel\n";
        cout << "\1.Lufthansa(1)\t08:00\t\t11:05\t\t$.3500\t\tRefundable\t\tThe Eiffel Resort\n";
        cout << "\2.Fly Dubai(2)\t14:00\t\t17:05\t\t$.3750\t\tRefundable\t\tShanzay Lezay Motel\n";
        cout << "\3.United Air(3)\t19:00\t\t22:05\t\t$.3000\t\tRefundable\t\tMovenpick\n";
    }
}