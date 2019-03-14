#include "data_manipulation.h"
using namespace std;
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
bool UpdateAll(const User &user,string info_filename,string account_filename,string record_filename,string budget_filename,string old_username="") {
	if(!Update(user,info_filename,1,old_username)) {
		return false;
	}
	if(!Update(user,account_filename,2,old_username)) {
		return false;
	}
	if(!Update(user,record_filename,3,old_username)) {
		return false;
	}
	if(!Update(user,budget_filename,4,old_username)) {
		return false;
	}
	return true;
}
bool Update(const User &user,string filename,int database,string old_username="") {
	ifstream file(filename);
	ofstream temp(filename+".temp.txt");
	string line,field;
	if(file.fail() || temp.fail()) {
		exit(1);
	}
	while(getline(file,line)) {
		istringstream iss(line);
		iss>>field;
		if(!old_username.empty()) {
			if(field==user.username) {
				return false;
			}
			else if(field!=old_username) {
				temp<<line<<endl;
			}
		}
	}
	Write(user,temp,database);
	file.close();
	temp.close();
	Rename(filename+".temp.txt",filename);
	return true;
}
void Write(const User &user,ofstream &file,int database) {
	switch(database) {
		case INFORMATION:
			file<<user.username<<" "<<user.password<<" "<<user.name<<endl;
			break;
		case ACCOUNT:
			for(auto i : user.account) {
				file<<user.username<<" "<<i.name<<" "<<i.amount<<endl;
			}
			break;
		case RECORD:
			for(auto i : user.record) {
				file<<user.username<<" "<<i.account<<" "<<i.income<<" "<<i.type<<" "<<i.date<<" "<<i.time<<endl;
			}
			break;
		case BUDGET:
			for(auto i : user.budget) {
				file<<user.username<<" "<<i.start<<" "<<i.end<<" "<<i.type<<" "<<i.amount<<endl;
			}
			break;
		default:
			break;
	}
	return;
}
void Rename(string old_name,string new_name) {
	remove(new_name.c_str());
	rename(old_name.c_str(),new_name.c_str());
	remove(old_name.c_str());
	return;
}
