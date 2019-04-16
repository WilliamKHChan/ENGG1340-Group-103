#include "data_manipulation.h"
using namespace std;
bool LoadAll(User &user,vector<string> filename) {
	for(auto i : filename) {
		if(!Load(user,i)) {
			return false;
		}
	}
	return true;
}
bool Load(User &user,string filename) {
	ifstream file(filename);
	string line,field;
	bool flag=false;
	if(file.fail()) {
		exit(1);
	}
	file>>line;
	if(line=="Information") {
		while(getline(file,line)) {
			istringstream iss(line);
			iss>>field;
			if(field==user.username) {
				iss>>field;
				if(field==user.password) {
					flag=true;
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
	}
	else if(line=="Account") {
		while(getline(file,line)) {
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
		flag=true;
	}
	else if(line=="Record") {
		while(getline(file,line)) {
			istringstream iss(line);
			iss>>field;
			if(field==user.username) {
				Record rd;
				iss>>rd.account;
				iss>>field;
				rd.income=atof(field.c_str());
				iss>>rd.type;
				iss>>rd.date.timestamp;
				ExtractTime(rd.date,true);
				user.record.push_back(rd);
			}
		}
		flag=true;
	}
	else if(line=="Budget") {
		while(getline(file,line)) {
			istringstream iss(line);
			iss>>field;
			if(field==user.username) {
				Budget bg;
				iss>>bg.period;
				iss>>bg.date.timestamp;
				iss>>bg.type;
				iss>>field;
				bg.amount=atof(field.c_str());
				iss>>field;
				bg.remain=atof(field.c_str());
				ExtractTime(bg.date,true);
				user.budget.push_back(bg);
			}
		}
		flag=true;
	}
	return flag;
	file.close();
}
bool UpdateAll(const User &user,vector<string> filename,string old_username) {
	for(auto i : filename) {
		if(!Update(user,i,old_username)) {
			return false;
		}
	}
	return true;
}
bool Update(const User &user,string filename,string old_username) {
	ifstream file(filename);
	ofstream temp(filename+".temp.txt");
	string line,field,name;
	if(file.fail() || temp.fail()) {
		exit(1);
	}
	file>>name;
	temp<<name;
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
		else if(field!=user.username) {
			temp<<line<<endl;
		}
	}
	// After the while loop
	if(name=="Information") {
		temp<<user.username<<" "<<user.password<<" "<<user.name<<endl;
	}
	else if(name=="Account") {
		for(auto i : user.account) {
			temp<<user.username<<" "<<i.name<<" "<<i.amount<<endl;
		}
	}
	else if(name=="Record") {
		for(auto i : user.record) {
			ExtractTime(i.date,false);
			temp<<user.username<<" "<<i.account<<" "<<i.income<<" "<<i.type<<" "<<i.date.timestamp<<endl;
		}
	}
	else if(name=="Budget") {
		for(auto i : user.budget) {
			ExtractTime(i.date,false);
			temp<<user.username<<" "<<i.period<<" "<<i.date.timestamp<<" "<<i.type<<" "<<i.amount<<" "<<i.remain<<endl;
		}
	}
	file.close();
	temp.close();
	Rename(filename+".temp.txt",filename);
	return true;
}
void Rename(string old_name,string new_name) {
	if (remove(new_name.c_str())!=0)
		cout<<new_name<<" remove fail !\n";
	if (rename(old_name.c_str(),new_name.c_str())!=0)
		cout<<"rename fail !\n";
	//if (remove(old_name.c_str())!=0)
		//cout<<old_name<<" remove fail !\n";
	return;
}
void ExtractTime(Time &time,bool isExtract) { // Convert string into int
	if(isExtract) { // For Data time
		time.year=atoi(time.timestamp.substr(4,4).c_str());
		time.month=atoi(time.timestamp.substr(2,2).c_str());
		time.day=atoi(time.timestamp.substr(0,2).c_str());
		time.hour=atoi(time.timestamp.substr(8,2).c_str());
		time.minute=atoi(time.timestamp.substr(10,2).c_str());
	}
	else { // For Current time
		char temp[12];
		sprintf(temp,"%02d%02d%d%02d%02d",time.day,time.month,time.year,time.hour,time.minute);
		time.timestamp=temp;
	}
	return;
}
void GetCurrentTime(Time &date) {
	time_t now=time(0);
	tm *ltm=localtime(&now);
	date.year=1900+ltm->tm_year;
	date.month=1+ltm->tm_mon;
	date.day=ltm->tm_mday;
	date.hour=ltm->tm_hour;
	date.minute=ltm->tm_min;
	ExtractTime(date,false);
	return;
}
void InputBudget(Budget &budget) {
	cin>>budget.period;
	cin>>budget.type;
	cin>>budget.amount;
	budget.remain=budget.amount;
	GetCurrentTime(budget.date);
	return;
}
void RenewBudget(vector<Budget> &budget) {
	Time date;
	GetCurrentTime(date);
	for(auto &i : budget) {
		if(i.period=="Daily" && i.date.timestamp.substr(0,8)!=date.timestamp.substr(0,8)) {
			i.remain=i.amount;
			i.date.timestamp=date.timestamp;  // Update timestamp
			ExtractTime(i.date,true);
		}
		else if(i.period=="Monthly" && i.date.timestamp.substr(2,6)!=date.timestamp.substr(0,8)) {
			i.remain=i.amount;
			i.date.timestamp=date.timestamp; // Update timestamp
			ExtractTime(i.date,true);
		}
	}
	return;
}
