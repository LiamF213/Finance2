class student{

  private:
	string name;
	long double bal;
	int pin;
  bool admin;
  bool authorized;

  public:
  void setName(string);
  void setBal(long double);
  void setPin(int);

  string getName();  
  long double getBal();
  int getPin();

  bool login();
  void addMoney(double long);
  void subtractMoney(double long);
}