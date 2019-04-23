#include "Accounting_system.h"
using namespace std;
int main() {
	User user;
	vector<string> database={"Information.txt","Account.txt","Record.txt","Budget.txt"};
	LoginScreen(user,database);
	MainMenu(user,database);
	return 0;
}
