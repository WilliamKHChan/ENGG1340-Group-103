#include "data_manipulation.h"
using namespace std;
int main() {
	User user;
	vector<string> filename={"Information.txt","Account.txt","Record.txt","Budget.txt"};
	
	user.username="JasonChan";
	user.password="jc1234";
	
	if(LoadAll(user,filename)) {
		cout<<"Name: "<<user.name<<endl<<"\nAccounts:\n";
		for(auto i:user.account) {
			cout<<i.name<<" "<<i.amount<<endl;
		}
		cout<<"\nRecords:\n";
		for(auto i:user.record) {	// Or for(int i=0;i<user.record.size();i++) { cout<<user.record[i].account ... ; }
			cout<<i.account<<" "<<i.type<<" "<<i.income<<" "<<i.time.day<<"/"<<i.time.month<<"/"<<i.time.year<<" ";
			cout<<setfill('0')<<setw(2)<<i.time.hour<<":"<<i.time.minute<<endl;
		}
		cout<<"\nBudgets:\n";
		for(auto i:user.budget) {
			cout<<i.start.timestamp<<" "<<i.end.timestamp<<" "<<i.type<<" "<<i.amount<<endl;
		}
	}
	
	// Change data
	user.record[0].type="Game";
	user.record[0].time.year=2020;
	user.record[0].time.hour=7;
	
	// Update all or just one database
	Update(user,filename[2]); // Or Update(user,"Record.txt");
	UpdateAll(user,filename);
	
	//Update username:
	user.username="ABC";
	UpdateAll(user,filename,"JasonChan");
	
	// Change back
	user.username="JasonChan";
	UpdateAll(user,filename,"ABC");
	return 0;
}
