#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;
class Account {
public:
	string name;
	double amount;
};
class Record {
public:
	string account;
	double income;
	string type;
	string date;
	string time;
};
class Budget {
public:
	string start;
	string end;
	string type;
	double amount;
};
class User {
public:
	string username;
	string name;
	string password;
	vector<Account> account;
	vector<Record> record;
	vector<Budget> budget;
};
bool LoadAll(User&,string,string,string,string);
bool LoadInformation(User&,string);
bool LoadAccount(User&,string);
bool LoadRecord(User&,string);
bool LoadBudget(User&,string);
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
bool LoadInformation(User &user,string info_filename) {
	ifstream info(info_filename);
	string line,field;
	bool found=false;
	if(info.fail()) {
		exit(1);
	}
	while(getline(info,line)) {
		istringstream iss(line);
		iss>>field;
		if(field==user.username) {
			iss>>field;
			if(field==user.password) {
				found=true;
				user.name="";
				while(iss>>field) {
					user.name+=field+" ";
				}
				user.name.pop_back();
				break;
			}
			else {
				return false;
			}
		}
	}
	return found;
}
bool LoadAccount(User &user,string account_filename) {
	ifstream account(account_filename);
	string line,field;
	if(account.fail()) {
		exit(1);
	}
	while(getline(account,line)) {
		istringstream iss(line);
		iss>>field;
		if(field==user.username) {
			Account acc;
			iss>>acc.name;
			iss>>field;
			acc.amount=atof(field.c_str());
			user.account.push_back(acc);
		}
	}
	return true;
}
bool LoadRecord(User &user,string record_filename) {
	ifstream record(record_filename);
	string line,field;
	if(record.fail()) {
		exit(1);
	}
	while(getline(record,line)) {
		istringstream iss(line);
		iss>>field;
		if(field==user.username) {
			Record rd;
			iss>>rd.account;
			iss>>field;
			rd.income=atof(field.c_str());
			iss>>rd.type;
			iss>>rd.date;
			iss>>rd.time;
			user.record.push_back(rd);
		}
	}
	return true;
}
bool LoadBudget(User &user,string budget_filename) {
	ifstream budget(budget_filename);
	string line,field;
	if(budget.fail()) {
		exit(1);
	}
	while(getline(budget,line)) {
		istringstream iss(line);
		iss>>field;
		if(field==user.username) {
			Budget bg;
			iss>>bg.start;
			iss>>bg.end;
			iss>>bg.type;
			iss>>field;
			bg.amount=atof(field.c_str());
			user.budget.push_back(bg);
		}
	}
	return true;
}
bool LoadAll(User &user,string info_filename,string account_filename,string record_filename,string budget_filename) {
	if(!LoadInformation(user,info_filename)) {
		return false;
	}
	if(!LoadAccount(user,account_filename)) {
		return false;
	}
	if(!LoadRecord(user,record_filename)) {
		return false;
	}
	if(!LoadBudget(user,budget_filename)) {
		return false;
	}
	return true;
}
		
			

