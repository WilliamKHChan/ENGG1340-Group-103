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
int Identify_Month(int MM) {
	int days;
	switch (MM) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days=31;
			return days;
			break;
		case 2:
			days=28;
			return days;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days=30;
			return days;
			break;
	}
}
int Day_passed(int MM,int current_month,int DD) {
	int days,days_elapsed;
	int months_elasped=current_month-MM;
	days=Identify_Month(MM);
	days_elapsed=days-DD;
	return days_elapsed;
}
void Auto_insert_time(Time &date,string Timestamp) {
	date.year=atoi(Timestamp.substr(4,4).c_str());
	date.month=atoi(Timestamp.substr(2,2).c_str());
	date.day=atoi(Timestamp.substr(0,2).c_str());
	date.hour=atoi(Timestamp.substr(8,2).c_str());
	date.minute=atoi(Timestamp.substr(10,2).c_str());
	return;
}
bool should_Update(User &user,string record_time,string line) {
	ofstream fout;
	fout.open("Record.txt",ios::app);
	if (fout.fail())
		exit(1);
	Time time;
	GetCurrentTime(time);
	//int current_month=5;
	int current_month=time.month;
	Record rd;
	string D,data,Timestamp,date1,date2,date3,tail,name;
	tail=record_time.substr(13);
	istringstream iss(line);
	iss>>name;
	iss>>rd.account;
	iss>>data;
	rd.income=atof(data.c_str());
	iss>>rd.type;
	int original_wday,days_in_month,d;
	string user_input_days=record_time.substr(19);
	int weekday=atoi((record_time.substr(12,1)).c_str());
	int DD=atoi((record_time.substr(0,2)).c_str());
	int dd=DD;
	int MM=atoi((record_time.substr(2,2)).c_str());
	int days_elapsed;
	d=atoi((time.timestamp.substr(0,2)).c_str());
	if (current_month-MM==0)
		days_elapsed=d-DD;
	else
		days_elapsed=d+Day_passed(MM,current_month,DD);
	int total_days=days_elapsed;
	int update=-1;
	int count_days=0;
	//(time.timestamp.substr(0,2)
	while (count_days+1<=total_days) {
		if (weekday==6) {
			weekday=-1;
		}
		count_days++;
		weekday++;
		D=to_string(weekday);
		//cout<<"count_days = "<<count_days<<endl;
		//cout<<"weekday = "<<weekday<<endl;
		if (user_input_days.find(D)!=string::npos) {
			days_in_month=Identify_Month(MM);
			update=0;
			if (DD+count_days>days_in_month)
				date1=to_string(DD+count_days-days_in_month);
			else
				date1=to_string(DD+count_days);
			date2=to_string(current_month);
			if (date2.length()==1)
				date2="0"+date2;
			date3=D;
			Timestamp=date1+date2+record_time.substr(4,8)+date3+tail;
			//cout<<"Timestamp = "<<Timestamp<<endl;
			rd.date.timestamp=Timestamp;
			rd.date.wday=atoi(D.c_str());
			Auto_insert_time(rd.date,Timestamp);
			user.record.insert(user.record.begin(),rd);
			fout<<name<<" "<<rd.account<<" "<<rd.income<<" "<<rd.type;
			fout<<" "<<rd.date.timestamp<<endl;
		}
	}
if (update!=0)
	return false;
else
	return true;
}
void Activate_Auto_Record(User &user,vector<string> database) {
	int turn=1;
	int num,pos;
	string line,info,user_data,str_num;
	ifstream fin("Auto_Record.txt");
	reverse(user.record.begin(), user.record.end());
	if (fin.fail())
		exit(1);
	while (getline(fin,line)) {
		if (turn>3) {
			for (auto i : user.record) {
				pos=line.rfind(" ");
				info=line.substr(0,pos);
				num=i.income;
				str_num=to_string(num);
				user_data=user.username+" "+i.account+" "+str_num+" "+i.type;
				if (i.date.timestamp.find("Auto")!=string::npos && user_data==info) {
					if (should_Update(user,i.date.timestamp,line))
						cout<<"There is a Auto-Record \n";
					reverse(user.record.begin(), user.record.end());
					break;
					//Update(user,"Record.txt");
				}
			}
		}
		turn++;
	}
	//for (auto i : user.record)
		//cout<<i.account<<" "<<i.income<<" "<<i.type<<" "<<i.date.timestamp<<endl;
	fin.close();
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
	if(file.fail() || temp.fail())
		exit(1);
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
		for(auto i : user.account)
			temp<<user.username<<" "<<i.name<<" "<<i.amount<<endl;
	}
	else if(name=="Record") {
		for(auto i : user.record) {
			//ExtractTime(i.date,false);
			temp<<user.username<<" "<<i.account<<" "<<i.income<<" "<<i.type<<" "<<i.date.timestamp<<endl;
			//Update_Record();
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
	if(isExtract) {
		time.year=atoi(time.timestamp.substr(4,4).c_str());
		time.month=atoi(time.timestamp.substr(2,2).c_str());
		time.day=atoi(time.timestamp.substr(0,2).c_str());
		time.hour=atoi(time.timestamp.substr(10,2).c_str());
		time.minute=atoi(time.timestamp.substr(8,2).c_str());
		time.wday=atoi(time.timestamp.substr(12,1).c_str());
	}
	else {
		char temp[12];
		sprintf(temp,"%02d%02d%d%02d%02d%01d",time.day,time.month,time.year,time.hour,time.minute,time.wday);
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
	date.wday=ltm->tm_wday;
	ExtractTime(date,false);
	return;
}
string Identify_Weekday(int day) {
	switch (day) {
		case 0:
			return "Sun";
			break;
		case 1:
			return "Mon";
			break;
		case 2:
			return "Tue";
			break;
		case 3:
			return "Wed";
			break;
		case 4:
			return "Thu";
			break;
		case 5:
			return "Fri";
			break;
		case 6:
			return "Sat";
			break;
	}
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
