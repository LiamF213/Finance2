#include "student.h"
#include <iostream>
#include <sstream>
#include <limits>

student::student(){
  name = "";
	bal = 0;
	pin = 0;
  admin = 0;
  authorized = 0;

}

bool student::setName(std::string nameIn){
  name = nameIn;
  return(true);
}

bool student::setBal(long double balIn){
  bal = balIn;
  return(true);  
}

bool student::setPin(int pinIn){
  pin = pinIn;
  return(true);
}

std::string student::getName(){
  return(name);
}

long double student::getBal(){
  return(bal);
}

int student::getPin(){
  return(pin);
}



// Function to add money to an account
void student::addMoney(double long moneyIn) {
	bal += moneyIn;
	std::cout << std::endl << "The new balance in " <<student:: name << "'s account is : $" << bal;
}

// Function to subtract money
void student::subtractMoney(long double moneyIn) {
	bal -= moneyIn;
	std::cout << std::endl << "The new balance in " <<student:: name << "'s account is : $" << bal;
}



// Admin home screen
int student::homeAdmin() {  
	std::cout << std::endl <<"Hello " << student::name <<  " what do you want to do. Options are " << std::endl << "Deposit" << std::endl << "Withdraw" << std::endl << "Reset" << std::endl;
	std::string operationStr;
	std::cin >> operationStr;

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
		std::cout << std::endl << "Invalid operation";
		homeAdmin();
	}
	return(operation);
}

// Function for when the input verifacation fails
void student::inputFail() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << std::endl << "Invalid input" << std::endl;
}