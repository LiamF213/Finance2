#ifndef STUDENT_H
#define STUDENT_H
#include <string>

class student{

  private:
	std::string name;
	long double bal;
	int pin;
  bool admin;
  bool authorized;

  public:

  student();

  bool setName(std::string);
  bool setBal(long double);
  bool setPin(int);

  std::string getName();  
  long double getBal();
  int getPin();

  int homeAdmin();
  bool login();
  void addMoney(double long);
  void subtractMoney(double long);
  void home();
  void inputFail();
};
#endif
