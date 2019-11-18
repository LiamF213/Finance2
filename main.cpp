/* To-do list
	Add support for two party payment
	Input verification
	Add support for interest
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <limits>


#include "student.h"


using namespace std;

// Custom defines
#define infinity (8.5 * pow(10, 307));
 
// Prototype Functions
void startbank();
//void addmoney();
//void subtractmoney();
void setflag1();
void save();
void retrive();
void firstSave(int);
bool hasrun();
bool login();
//int homeAdmin();
void home();
void inputFail();
void reset();

// Global objects
// Global vector used to store the bank information while the program is running
vector<student> bankaccounts;
int activeAccount;



// file opening
fstream runbool("run.txt", ios::in | ios::out);
fstream accountBalencesFile("accountBalences.txt", ios::in | ios::out);
fstream accountNamesFile("accountNames.txt", ios::in | ios::out);
fstream accountPINsFile("accountPINs.txt", ios::in | ios::out);
fstream numberofAccountsFile("numberofAccounts.txt", ios::in | ios::out);

int main() {

	cout << fixed;
	cout << setprecision(2);

	if (hasrun() == false) {
		string x;
		cout << endl << "Setup complete, run the program again to access software, enter anything to exit";
		cin >> x;
		return(0);
	}

	retrive();
	bool accountToken = false;

	while (accountToken == false) {
		accountToken = login();
	}

	if (activeAccount != 0) {
		home();
		return(0); 
	}
// Everything past this point is accessible to the Admin account only
	int operation = bankaccounts[activeAccount].homeAdmin();
  long double temp;
  int activeAccount_temp;
	switch (operation)
	{
	case 1:
    std::cout << std::endl << "Enter the account number for the account you want to modify: ";
    std::cin >> activeAccount_temp;
	  std::cout << std::endl << std::endl << "How much money do you want to add to " << bankaccounts[activeAccount_temp].getName() << "'s account : $";
  	std::cin >> temp;
		bankaccounts[activeAccount_temp].addMoney(temp);
		break;

	case 2:
    std::cout << std::endl << "Enter the account number for the account you want to modify: ";
    std::cin >> activeAccount_temp;
	  std::cout << std::endl << std::endl << "How much money do you want to subtract from " << bankaccounts[activeAccount_temp].getName() << "'s account : $";
  	std::cin >> temp;
	  bankaccounts[activeAccount_temp].subtractMoney(temp);
		break;
	
	case 3:
		reset();
		break;
	}
	save();
}


// Function that gets the names and starting balences the first time the program is run
void startbank() {
	int limit;
	cout << endl << "Enter the number of accounts to open : ";
	cin >> limit;
	if (cin.fail()) {
		inputFail();
		startbank();
	}


	// For loop to inatilize the bankaccounts vector
	int x;
	for (int c = 0; c < limit; c++) {
		student tempstudent;
		if (c == 0) {
			cout << endl << endl << "Enter the administrator account name : ";
      std::string mayflyName;
			cin >> mayflyName;
      tempstudent.setName(mayflyName);
			cout << endl << "Enter the administrator PIN: ";
      int mayflyPin;
			cin >> mayflyPin;
       tempstudent.setPin(mayflyPin);
			tempstudent.setBal((8.5 * pow(10, 307)));
			bankaccounts.push_back(tempstudent);
		}
		else {
			cout << endl << endl << "Enter student " << (c) << "'s name : ";
      std::string tempName;
			cin >> tempName;
      tempstudent.setName(tempName);
			cout << endl << "Enter " << tempstudent.getName() << "'s starting account balance: $";
			std::string tempBal;
			std::getline(std::cin, tempBal);
			while (true)
			{
				std::getline(std::cin, tempBal);
				long double tempBal2 = std::stold(tempBal);
				if ((tempstudent.setBal(tempBal2))) {
					break;
				}
				inputFail();
				cout << endl << "Enter " << tempstudent.getName() << "'s starting account balance: $";

			}
			cout << endl << "Enter " << tempstudent.getName() << "'s PIN: ";
      int tempPin;
			cin >> tempPin;
      tempstudent.setPin(tempPin);
			bankaccounts.push_back(tempstudent);
			cout << endl << tempstudent.getName() << "'s account number is : " << c;
		}
		x = c+1;
		
	}
	numberofAccountsFile << x;
	firstSave(x);
};









// Function to determine if this is the first time something the program is run
bool hasrun() {
	bool run;
	runbool >> run;
	runbool.clear();
	if (run == true) {
		return(true);
	}
	else {
		setflag1();
		startbank();
		return(false);
	}
};


// Function to set a flag when the file is being run the first time
void setflag1() {
	runbool.seekp(0);
	bool runn = true;
	runbool << (runn);
};


// Function to save the account vector to the files the first time
void firstSave(int limit) {
	for (int c = 0; c < limit; c++) {
		string accBal, accName, accPIN;
		accBal = to_string(bankaccounts[c].getBal()) + ' ';
		accName = bankaccounts[c].getName() + ' ';
		accPIN = to_string(bankaccounts[c].getPin()) + ' ';
		accountBalencesFile << accBal;
		accountNamesFile << accName;
		accountPINsFile << accPIN;
	}
};


// Normal Save Function
void save() {
	int limit;
	numberofAccountsFile.clear();
	numberofAccountsFile.seekp(0);
	numberofAccountsFile >> limit;
	accountBalencesFile.clear();
	accountBalencesFile.seekp(0);
	accountNamesFile.clear();
	accountNamesFile.seekp(0);
	accountPINsFile.clear();
	accountPINsFile.seekp(0);
	for (int c = 0; c < limit; c++) {
		string accBal;
    string accName;
    string accPIN;
    stringstream bal;
    stringstream pin;
		accBal = to_string(bankaccounts[c].getBal()) + ' ';
		accName = bankaccounts[c].getName() + ' ';
		accPIN = to_string(bankaccounts[c].getPin()) + ' ';
		accountBalencesFile << accBal;
		accountNamesFile << accName;
		accountPINsFile << accPIN;
	}
};


// Function to retrive data from files and put it into the correct places
void retrive() {
	int limit;
	numberofAccountsFile >> limit;
	for (int c = 0; c < limit; c++) {;
		student temp;
    double long tempBal;
    std::string tempName;
    int tempPin;
		accountBalencesFile >> tempBal ;
		accountNamesFile >> tempName;
		accountPINsFile >> tempPin;
    temp.setBal(tempBal);
    temp.setName(tempName);
    temp.setPin(tempPin);
		bankaccounts.push_back(temp);
	}
}


// Function for when the input verifacation fails
void inputFail() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl << "Invalid input" << endl;
}

// Function to reset the run flag and allow for a data reset of the program
void reset() {
	cout << endl << "THIS WILL PERMANANTLY DELETE ALL USER DATA" << endl << endl << "ARE YOU SURE YOU WANT TO RESET THE PROGRAM?" << endl << endl << "TYPE YES TO RESET THE PROGRAM" << endl;
	string reset;
	cin >> reset;
	if (reset == "YES" || reset == "Yes" || reset == "yes") {
		runbool.seekp(0);
		bool runn = false;
		runbool << (runn);
		cout << endl << "Reset complete, please restart program";
	}
};

// Function to determine which account's data will be able to be modified
bool login() {
  bool authorized = false;
	int temp_pin;
	int temp_activeAccount;
	std::cout << std::endl << std::endl << "Enter the account number : ";
	std::cin >> temp_activeAccount;
	if (std::cin.fail()) {
		inputFail();
		login();
	}
	std::cout << std::endl << "Enter your PIN : ";
	std::cin >> temp_pin;
	if (temp_pin == bankaccounts[temp_activeAccount].getPin()) {
		std::cout << std::endl << "PIN accepted";
		authorized = true;
    activeAccount = temp_activeAccount;
		
	}
	else {
		std::cout << std::endl << "Incorrect PIN";
	}
  return(authorized);
}

// User home screen
void home() {
	std::string exit;
	std::cout << std::endl << std::endl << "Hello " << bankaccounts[activeAccount].getName() << " the current account balence for your account is : $" << bankaccounts[activeAccount].getBal() << std::endl;
	std::cout << std::endl << "Enter anything to close the program" << std::endl;
	std::cin >> exit;
}