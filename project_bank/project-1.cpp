#include<iostream>
#include<cmath>
#include<iomanip>
#include<ctime>
#include<string>
#include<ctime>
#include<windows.h>
#include<sstream>
#include<stdlib.h>
#include <cctype>
#include <fstream>
#include<conio.h>
using namespace std;

template<typename T>//use of generic class
class NumToString {
	public:
	    static string Convert(T num) {
	        stringstream ss;
	        ss << num;
	        return ss.str();
	    }
};


const int interest_rate=1.2;//the interst rate per month


string date()//to store the current date we have used this function whenever a transaction is made this is uploaded to the file
{
    // Get the current system time
    time_t currentTime = time(0);
    // Convert the current time to a tm structure
    tm* now = localtime(&currentTime);

    // Create a string stream to format the date and time
    stringstream ss;
    ss << setfill('0');
    ss << setw(4) << (now->tm_year + 1900) << "-"; // Year
    ss << setw(2) << (now->tm_mon + 1) << "-";     // Month
    ss << setw(2) << now->tm_mday << " ";          // Day
    ss << setw(2) << now->tm_hour << ":";          // Hour
    ss << setw(2) << now->tm_min << ":";           // Minute
    ss << setw(2) << now->tm_sec;                  // Second
    return ss.str();
}


class Account {
	static int users; // count the total number of users 
	string accountnum; // to hold the account number of the user
	char accountname[100]; // name of the user
	string phone; // phone for sending informations
	long balance; // balance in the account
	bool c; // if c==0 then the user has not taken other banking facilities so no charge   
	string date; // to store the date of the transaction		
	long aq_intr;
	public:
	// Default constructor
	Account()
	{
		accountnum = NumToString<int>::Convert(600000 + users + 1); // Convert int to string using generic class NumToString
		strcpy(accountname," "); //'=' can't be used in character array
		phone = "";
		balance = 0;
		c = 0;
	}
	
	
	// Parameterized constructor
	Account(char* name, string phoney, bool s)
	{
		balance=0;
		accountnum = NumToString<int>::Convert(600000 + users + 1); // Convert int to string using generic class NumToString
		strcpy(accountname,name); //'=' can't be used in character array
		phone = phoney;
		c = s;
	}

	// Member function to display account information
	void displayinfo()
	{
		cout << "Account Name: " << setw(16) << accountname << endl;
		cout << "Account Number: " << setw(14) << accountnum << endl;
		cout << "Balance: " << setw(14) << balance << endl;
		cout << "Phone: " << setw(12) << phone << endl;
		cout << "Other facilities status: " << setw(12) << c << endl;
	}

	void writeTransaction(const string& transactionDetails) {
	    ofstream outFile((accountnum + ".txt").c_str(), ios::app); // Convert std::string to const char* using c_str()
	    if (outFile.is_open()) {
	        outFile << transactionDetails << endl; // Write transaction details to file
	        outFile.close();
	    }
	}

    void viewStatement() {
        ifstream inFile((accountnum + ".txt").c_str()); // Convert std::string to const char* using c_str()
        if (inFile.is_open()) {
            string line;
            cout << "Transaction details for Account Number: " << accountnum << endl;
            while (getline(inFile, line)) {
                cout << line << endl; // Print transaction details from file
            }
            inFile.close();
        }
        getch();
    }
    
    void aquried_interest()
    {
    	aq_intr+=aq_intr*interest_rate;
    	cout<<aq_intr;
    	getch();
	}

    // Member function to make a deposit
    void deposit(long amount) {
        tryagain:
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << " Successfully!" << endl;
            date = ::date(); // Update transaction date	
			string  numstr = NumToString<long>::Convert(amount);
            string transactionDetails = "Transaction: Deposit $" + numstr; // Transaction details
            writeTransaction(transactionDetails); // Write transaction details to file
        }
        else {
            cout << "Invalid amount. Please enter a positive value." << endl;
            cout << "Enter 1 to exit and 2 to try again: ";
            if (getch() == '2')
                goto tryagain;
        }
        getch();
    }

    // Member function to make a withdrawal
    void withdraw(long amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << " Successfully!" << endl;
            date = ::date(); // Update transaction date
            string  numstr = NumToString<long>::Convert(amount);
            string transactionDetails = "Transaction: Withdraw $" + numstr; // Transaction details
            writeTransaction(transactionDetails); // Write transaction details to file
        }
        else if (amount > balance) {
            cout << "Insufficient balance. Please enter a valid amount." << endl;
        }
        else {
            cout << "Invalid amount. Please enter a positive value." << endl;
        }
        getch();
    }

    // Member function to view statements
    void viewStatements() {
    cout << left << setw(20) << "Account Number: " << accountnum << endl;
    cout << left << setw(20) << "Account Name: " << accountname << endl;
    cout << left << setw(20) << "Phone: " << phone << endl;
    cout << left << setw(20) << "Balance: $" << balance << endl;
    cout << left << setw(20) << "Transaction Date: " << date << endl;
    getch();
    }

	// Member function to display account information
	void displayAccountInfo()
	{
		cout << "Account Number: " << accountnum << endl;
		cout << "Account Name: " << accountname << endl;
		cout << "Phone: " << phone << endl;
		cout << "Balance: $" <<balance << endl;
		cout << "Other facilities status: " << c << endl;
		getch();
	}
	
	
	void applyForLoan(long amount)
{
    cout << "Loan application submitted successfully!" << endl;
    // Additional code to write the loan application to a file
    ofstream file;
    string fileName = accountnum + "_loan.txt"; // File name based on account number
    file.open(fileName.c_str(), ios::app); // Convert string to const char* using c_str()
    if (file.is_open())
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        file << "Loan Application Date: " << dt << endl;
        file << "Account Number: " << accountnum << endl;
        file << "Account Name: " << accountname << endl;
        file << "Phone: " << phone << endl;
        file << "Loan Amount: $" << amount << endl; // Loan amount is entered by the user
        file << "Loan Status: Pending" << endl;
        file << "------------------------------------------" << endl;
        file.close();
        cout << "Loan application has been written to file: " << fileName << endl;
    }
    else
    {
        cout << "Error: Unable to write loan application to file." << endl;
    }
    getch();
}
	static int getTotalUsers()
	{
		return users;
	}
	
	// Static member function to get the total number of users
	static void setTotalUsers(int count)
	{
		users = count;
	}
};

int Account::users = 0;

main()
{
	//top:

	char accountname[100];//name of the user
	string phone;//phone for sending informations
	bool c1;
	char c2;
	cout << "Enter account name: ";
    cin.getline(accountname, sizeof(accountname)); // Read input with spaces
	
	cout<<"Enter phone number:";
	cin>>phone;
	
	cout<<"Do you want to have our other facilities(SMS banking/ Mobile banking /ATM)(y/n)";
	cin>>c2;
	if (c2=='y') 
		c1=1;
	else 
	 	c1=0;
	Account a1(accountname,phone,c1);
	
	int choice;
    do
	{
		//clear the contents each time
		system("cls");
        
		// Display menu options
        cout << "Bank Account Menu:" << endl;
        cout << "1. Make a deposit" << endl;
        cout << "2. Make a withdrawal" << endl;
        cout << "3. View statements" << endl;
        cout << "4. Display account information" << endl;
        cout << "5. View acquired interest" << endl;
		cout << "6. Apply for a loan"<<endl;
		cout << "Any ohter Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
		long amount;   
		system("cls");	
        // Process user choice
        switch (choice) {
			case 1:
            	
                // Make a deposit
                cout<<"enter amount to deposit";
                cin>>amount;
                a1.deposit(amount);
                break;

            case 2:
                // Make a withdrawal
                cout<<"enter amount to withdraw";
                cin>>amount;
                a1.withdraw(amount);
				break;

            case 3:
                // Process monthly transactions
                a1.viewStatements();
                break;

            case 4:
                a1.displayinfo();
				// Display account information
                break;
			
			case 5:
				//view interst
				a1.aquried_interest();
				break;
			
			case 6:
				cout<<"enter loan amount";
				cin>>amount;
				a1.applyForLoan(amount);
            
			default:
                // Quit
                cout << "Thank you for banking with us. Goodbye" << endl;
                break;
		}
	}while(choice<7);
}
