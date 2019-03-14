#include "data_manipulation.h"
using namespace std;
int main() {
	const string info_filename="Information.txt",account_filename="Account.txt",record_filename="Record.txt",budget_filename="Budget.txt";
	User user;
	user.username="JasonChan";
	user.password="jc1234";
	if(LoadAll(user,info_filename,account_filename,record_filename,budget_filename)) {
		cout<<"Name: "<<user.name<<endl<<"\nAccounts:\n";
		for(auto i:user.account) {
			cout<<i.name<<" "<<i.amount<<endl;
		}
		cout<<"\nRecords:\n";
		for(auto i:user.record) {
			cout<<i.account<<" "<<i.type<<" "<<i.income<<" "<<i.date<<" "<<i.time<<endl;
		}
		cout<<"\nBudgets:\n";
		for(auto i:user.budget) {
			cout<<i.start<<" "<<i.end<<" "<<i.type<<" "<<i.amount<<endl;
		}
	}
	return 0;
}
