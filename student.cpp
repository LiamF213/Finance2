#include student.h

student(bool adminIn){
  name = "";
	bal = 0;
	pin = 0;
  admin = false;
  authorized = false;
}

void setName(string nameIn){
  name = nameIn;
}

void setBal(long double balIn){
  bal = balIn;
}

void setPin(int pinIn){
  pin = pinIn;
}

string getName(){
  return(name);
}

long double getBal(){
  return(bal);
}

int getPin(){
  return(pin);
}

// Function to determine which account's data will be able to be modified
bool login() {
	int temp_pin;
	int temp_activeAccount;
	cout << endl << endl << "Enter the account number : ";
	cin >> temp_activeAccount;
	if (cin.fail()) {
		inputFail();
		login();
	}
	cout << endl << "Enter your PIN : ";
	cin >> temp_pin;
	if (temp_pin == pin) {
		cout << endl << "PIN accepted";
		authorized = true;
		
	}
	else {
		cout << endl << "Incorrect PIN";
	}
  return(authorized);
}

// Function to add money to an account
void addMoney(double long moneyIn) {
	long double temp;
	cout << endl << endl << "How much money do you want to add to " << name << "'s account : $";
	cin >> temp;
	bal += temp);
	cout << endl << "The new balance in " << name << "'s account is : $" << bal;
}

// Function to subtract money
void subtractMoney(long double moneyIn) {
	long double temp;
	cout << endl << endl << "How much money do you want to subtract from " << name << "'s account : $";
	cin >> temp;
	bal += temp;
	cout << endl << "The new balance in " << name << "'s account is : $" << bal;
}