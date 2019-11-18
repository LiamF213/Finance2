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
#include <regex>

#include "student.h"


using namespace std;

// Custom defines
#define infinity (8.5 * pow(10, 307));


// Data Structures

// Data structure used to hold the name and balance of each student
struct student {
	string name;
	long double bal;
	int pin;
};
 
// Prototype Functions
void startbank();
//void addmoney();
//void subtractmoney();
void setflag1();
void save();
void retrive();
void firstSave(int);
bool hasrun();
// bool login();
int homeAdmin();
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
	int operation = homeAdmin();

	switch (operation)
	{
	case 1:
		addmoney();
		break;

	case 2:
		subtractmoney();
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
			cin >> tempstudent.name;
			cout << endl << "Enter the administrator PIN: ";
			cin >> tempstudent.pin;
			tempstudent.bal = infinity;
			bankaccounts.push_back(tempstudent);
		}
		else {
			cout << endl << endl << "Enter student " << (c) << "'s name : ";
			cin >> tempstudent.name;
			cout << endl << "Enter " << tempstudent.name << "'s starting account balance: $";
			string tempBal;
			getline(cin, tempBal);
			while (true)
			{
				getline(cin, tempBal);
				stringstream tempBal2(tempBal);
				if ((tempBal2 >> tempstudent.bal)) {
					break;
				}
				inputFail();
				cout << endl << "Enter " << tempstudent.name << "'s starting account balance: $";

			}
			cout << endl << "Enter " << tempstudent.name << "'s PIN: ";
			cin >> tempstudent.pin;
			bankaccounts.push_back(tempstudent);
			cout << endl << tempstudent.name << "'s account number is : " << c;
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
		accBal = to_string(bankaccounts[c].bal) + ' ';
		accName = bankaccounts[c].name + ' ';
		accPIN = to_string(bankaccounts[c].pin) + ' ';
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
		accBal = to_string(bankaccounts[c].bal) + ' ';
		accName = bankaccounts[c].name + ' ';
		accPIN = to_string(bankaccounts[c].pin) + ' ';
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
		accountBalencesFile >> temp.bal;
		accountNamesFile >> temp.name;
		accountPINsFile >> temp.pin;
		bankaccounts.push_back(temp);
	}
}


// Admin home screen
int homeAdmin() {  
	cout << endl <<"Hello " << bankaccounts[activeAccount].name <<  " what do you want to do. Options are " << endl << "Deposit" << endl << "Withdraw" << endl << "Reset" << endl;
	string operationStr;
	cin >> operationStr;

	int operation;

	if (operationStr == "Deposit" || operationStr == "deposit") {
		operation = 1;
	}
	else if (operationStr == "Withdraw" || operationStr == "withdraw") {
		operation = 2;
	}
	else if (operationStr == "Reset" || operationStr == "reset") {
		operation = 3;
	}
	else {
		cout << endl << "Invalid operation";
		homeAdmin();
	}
	return(operation);
}


// User home screen
void home() {
	string exit;
	cout << endl << endl << "Hello " << bankaccounts[activeAccount].name << " the current account balence for your account is : $" << bankaccounts[activeAccount].bal << endl;
	cout << endl << "Enter anything to close the program" << endl;
	cin >> exit;
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