#include "user_interface.h"
void Login(User &user,vector<string> database) {
	bool success;
	do {
		cout<<"Username: ";
		cin>>user.username;
		cout<<"Password: ";
		cin>>user.password;
		success=LoadAll(user,database); // True : Get all info of the user
		if(!success) {                  // Login fail
			cout<<"Invalid.\n";
		}
		else {													// Login succeed
			RenewBudget(user,database[3]);     // Update data for calcualtion
			Activate_Auto_Record(user,database); // Decide if auto-record is needed
		}
	}
	while(!success);
}
void CreateAccount(User &user,vector<string> database) {
	string password;
	bool success;
	do {
		cin.clear();
		cin.sync();
		success=true;
		cout<<"Username: ";
		cin>>user.username;
		cout<<"Password: ";
		cin>>user.password;
		cout<<"Re-type password: ";
		cin>>password;
		cout<<"Name: ";
		cin.ignore();
		getline(cin,user.name);
		if(password!=user.password) {
			cout<<"Password not match.\n";
			success=false;
		}
		else if(success) {
			success=Update(user,database[0],user.username);
			if(!success) {
				cout<<"Username is used.\n";
			}
		}
	}
	while(!success);
}
void LoginScreen(User &user,vector<string> database) {
	int choice;
	cout<<"Welcome!\n\n1 Login\t\t2 New account\n\nPlease enter your choice: ";
	do {
		cin>>choice;
		if(choice<1 || choice>2) {
			cout<<"Invalid.\n";
		}
	}
	while(choice<1 || choice>2);
	switch(choice) {
		case 1:
			Login(user,database);
			break;
		case 2:
			CreateAccount(user,database);
			break;
	}
}
void MainMenu(User &user,vector<string> database) {
	int choice;
	do {
		cin.clear();
		cin.sync();
		cout<<"========================================";
		cout<<"\n1 Create Account\t2 Delete Account\n3 View Account\t\t4 Add Record";
		cout<<"\n5 Delete Record\t\t6 View Record\n7 Set Auto-Record";
		cout<<"\t8 Set Budgets\n9 Show Report\t\t10 Change Password\n11 Exit\n";
		cout<<"Please enter your choice : ";
		cin>>choice;
		cout<<"========================================\n";
		switch(choice) {
			case 1:
				Create_ACCT(user,database[1]);
				break;
			case 2:
				Delete_ACCT(user,{database[1],database[2]});
				break;
			case 3:
				View_ACCT(user,database[1]);
				break;
			case 4:
				Add_Record(user,{database[1],database[2]});
				break;
			case 5:
				Delete_Record(user,{database[1],database[2]});
				break;
			case 6:
				View_Record(user,database[2],true);
				break;
			case 7:
				Set_Auto_Record(user,database[2]);
				break;
			case 8:
				SetBudget(user,database);
				Update(user,database[3]);
				break;
			case 9:
				ShowReport(user,database);
				break;
			case 10:
				ChangePassword(user,database);
			case 11:
				break;
			default:
				cout<<"Invalid.\n";
				break;
		}
	}
	while(choice!=11);
	return;
}
void Create_ACCT(User &user,string database) {
	string ACCT_type, line, data, choice;
	double Amount;
	int replace=0;
	cout<<"Please enter (Account type) (Amount): ";
	cin >> ACCT_type >> Amount;
	ifstream fin(database);
	ofstream fout;
	fout.open(database, ios::app);
	if (fout.fail()||fin.fail())
		exit(1);
	while (getline(fin,line)) {
		istringstream iss(line);
		iss>>data;   // data = an username in Account.txt
		if (data==user.username) {
			iss>>data; // data = an account of the user
			cout<<"data :"<<data<<endl;
			if (ACCT_type==data) {
				cout<<"\nAccount already exits. Do you want to replace it ?\n";
				cout<<"1 Yes\t2 No and Exit\nPlease enter your choice : ";
				cin>>choice;
				if (choice=="1") {
					replace=1;
					int pos=0;
					for (auto i : user.account) {
						if (i.name==ACCT_type)
							user.account.erase(user.account.begin()+pos);
						pos++;
					}
					Account ACCT;
					ACCT.name=ACCT_type;
					ACCT.amount=Amount;
					user.account.push_back(ACCT);
					//for (auto i : user.account)
						//cout<<i.name<<' '<<i.amount<<endl;
					fout.close();
					fin.close();
					Update(user,database);
					break;
				}

			}
		}
		else {
			replace=2;
			Account ACCT;
			ACCT.name=ACCT_type;
			ACCT.amount=Amount;
			user.account.push_back(ACCT);
			//for (auto i : user.account)
				//cout<<i.name<<' '<<i.amount<<endl;
			fout.close();
			fin.close();
			Update(user,database);
		}
	}
	if (replace==0) {
	cout<<"Write into Account.txt\n";
	fout<<user.username<<' '<<ACCT_type<<' '<<Amount<<endl;
	fout.close();
	fin.close();
  }
	return;
}
void Delete_ACCT(User &user,vector<string> database) {
	View_Database(user,database[0]);
	int index;
	cout<<"Please enter your choice : ";
	cin>>index;
	cout<<"Delete Account "<<index<<endl;
	index--;
	for(int i=0;i<user.record.size();i++) {
		if(user.record[i].account==user.account[index].name) {
			user.record.erase(user.record.begin()+i);
			i--;
		}
	}
	user.account.erase(user.account.begin()+index);
	for(auto &i : database) {
		Update(user,i);
	}
}
void View_Database(User &user,string database) {
	string line,username;
	int num=1;
	ifstream fin(database);
	if (fin.fail())
		exit(1);
	while (getline(fin,line)){
		istringstream iss(line);
		iss>>username;
		if (username==user.username) {
			cout<<"\t\t"<<num<<" "<<line<<endl;
			num++;
		}
	}
	fin.close();
}
void View_ACCT(User &user,string database) {
	for(auto &i : user.account) {
		cout<<"Name: "<<i.name<<" Amount: $"<<i.amount<<endl;
	}
	return;
}
void Add_Record(User &user,vector<string> database) {
	int element=0;
 	double diff;
	Record rd;
	GetCurrentTime(rd.date);
	cout<<"Please enter (Account) (+/-Amount) (Category) : ";
	cin>>rd.account>>rd.income>>rd.type;
	ofstream fout;
	fout.open(database[1], ios::app);
	if (fout.fail())
		exit(1);
	fout<<user.username<<' '<<rd.account<<' '<<rd.income<<' '<<rd.type<<' ';
	fout<<rd.date.timestamp<<endl;
	fout.close();
	for (auto i : user.budget) {
		if (i.type==rd.type) {
			diff=i.remain+rd.income;
			user.budget[element].remain=diff;
			if (diff>=0)
				cout<<rd.type<<"-"<<i.period<<" budget remaining : "<<diff<<endl;
			else
				cout<<rd.type<<"-"<<i.period<<" budget overspent : "<<diff<<endl;
			break;
		}
		element++;
	}
	element=0;
	for (auto i : user.account) {
		if (i.name==rd.account) {
			diff=i.amount+rd.income;
			cout<<"Account - "<<i.name<<" : $"<<diff<<endl;
			user.account[element].amount=diff;
			break;
		}
		element++;
	}
	user.record.push_back(rd);
	for(auto &i : database) {
		Update(user,i);
	}
}
void Delete_Record(User &user,vector<string> database) {
	int choice,index,begin,end;
	string date,DDMMYYYY;
	int pos=0;
	bool first=true;
	cout<<"\t1 Delete records of the entire day\n";
	cout<<"\t2 Delete a single record in a day\n";
	cout<<"\tPlease enter your choice : ";
	cin>>choice;
	if (choice==2) {
		View_Record(user,database[1],false);
		//for (auto i : user.record)
			//cout<<i.account<<' '<<i.income<<' '<<i.type<<' '<<i.date.timestamp<<endl;
		cout<<"\tPlease enter the index : ";
		cin>>index;
		for(auto &i : user.account) {
			if(i.name==user.record[index].account) {
				i.amount-=user.record[index].income;
			}
		}
		for(auto &i : user.budget) {
			if(i.type==user.record[index].type) {
				i.remain-=user.record[index].income;
			}
		}
		user.record.erase(user.record.begin()+index);
	}
	else if (choice==1) {
		for (auto i : user.record)
			cout<<i.account<<' '<<i.income<<' '<<i.type<<' '<<i.date.timestamp<<endl;
		cout<<"\tPlease enter the date (DDMMYYYY) : ";
		cin>>date;
		for (auto i : user.record) {
			DDMMYYYY=i.date.timestamp.substr(0,8);
			if (date==DDMMYYYY) {
				if (first) {
					first=false;
					begin=pos;
				}
				else
					end=pos+1;
				//cout<<"Deleted !\n";
			}
			pos++;
		}
		for(int i=begin;i<end;i++) {
			for(auto &j : user.account) {
				if(j.name==user.record[i].account) {
					j.amount-=user.record[i].income;
				}
			}
			for(auto &k : user.budget) {
				if(k.type==user.record[index].type) {
					k.remain-=user.record[index].income;
				}
			}
		}
		user.record.erase(user.record.begin()+begin,user.record.begin()+end);
		//for (auto i : user.record)
			//cout<<i.account<<' '<<i.income<<' '<<i.type<<' '<<i.date.timestamp<<endl;
	}
	for(auto &i : database) {
		Update(user,i);
	}
	return;
}
void View_Record(User &user,string database,bool show) {
	int turn=1;
	//int index=1;
	int length=-1;
	ifstream fin(database);
	if (fin.fail())
		exit(1);
	if (show) {
		cout<<"For Monthly Record: Enter MMYYYY\n";
		cout<<"For Daily Record: Enter DDMMYYYY\n";
		cout<<"Enter : ";
	}
	else
		cout<<"Please enter the date (DDMMYYYY) : ";
	string date,line,data,weekday,name;
	Time DATE;
	cin>>date;
	if (date.length()==8) { // Daily
		while (getline(fin,line)) {
			istringstream iss(line);
			iss>>name;
			if (turn>3 && name==user.username) {
				length++;
				int pos=line.rfind(" ")+1;
				DATE.timestamp=line.substr(pos);
				data=DATE.timestamp.substr(0,8);
				if (data==date) {
					data=DATE.timestamp.substr(0,13);
					ExtractTime(DATE,true);
					weekday=Identify_Weekday(DATE.wday);
					if (!show) {
						cout<<left<<setw(2)<<length<<" - ";
					}
					cout<<left<<setw(35)<<setfill(' ')<<line.substr(0,line.rfind(" "))<<' ';
					cout<<right<<setw(2)<<setfill('0')<<DATE.day<<'/'<<setw(2)<<setfill('0')<<DATE.month<<'/'<<DATE.year<<'-';
					cout<<setw(2)<<setfill('0')<<DATE.hour<<":"<<setw(2)<<setfill('0')<<DATE.minute<<' '<<weekday<<endl;
				}
			}
			turn++;
		}
	}
	else if (date.length()==6) {
		while (getline(fin,line)) {
			istringstream iss(line);
			iss>>name;
			if (turn>3 && name==user.username) {
				int pos=line.rfind(" ")+1;
				DATE.timestamp=line.substr(pos);
				data=DATE.timestamp.substr(2,6);
				if (data==date) {
					data=DATE.timestamp.substr(0,13);
					ExtractTime(DATE,true);
					weekday=Identify_Weekday(DATE.wday);
					if (!show) {
						cout<<left<<setw(2)<<length<<" - ";
					}
					cout<<left<<setw(35)<<setfill(' ')<<line.substr(0,line.rfind(" "))<<' ';
					cout<<right<<setw(2)<<setfill('0')<<DATE.day<<'/'<<setw(2)<<setfill('0')<<DATE.month<<'/'<<DATE.year<<'-';
					cout<<setw(2)<<setfill('0')<<DATE.hour<<":"<<setw(2)<<setfill('0')<<DATE.minute<<' '<<weekday<<endl;
				}
			}
			turn++;
		}
	}
	fin.close();
	return;
}
void Set_Auto_Record(User &user,string database) {
	int choice,turn,index;
	Time date;
	GetCurrentTime(date);
	cout<<"\t1 Set an auto-record\t2 Cancel an auto-record\n";
	cout<<"Enter your choice : ";
	cin>>choice;
	if (choice==1) {
			ofstream fout,fout2;
			fout.open(database,ios::app);
			fout2.open("Auto_"+database,ios::app);
			if (fout.fail()||fout2.fail())
				exit(1);
			string Account,Amount,Category,days;
			cout<<"Enter record (Account) (Amount) (Category) : ";
			cin>>Account>>Amount>>Category;
			cout<<"For every 1: Mon  2: Tue  3: Wed  4: Thu\n";
			cout<<"          5: Fri  6: Sat  0: Sun\n";
			cout<<"You may select multiple days (i.e. 12345)\nEnter : ";
			cin>>days;
			cout<<"The Auto-Record is activated.\n";
			fout<<user.username<<' '<<Account<<' '<<Amount<<' '<<Category<<' ';
			fout<<date.timestamp<<"-Auto:"<<days<<endl;
			fout2<<user.username<<' '<<Account<<' '<<Amount<<' '<<Category<<' ';
			fout2<<date.timestamp<<"-Auto:"<<days<<endl;
			fout.close();
			fout2.close();
	}
	else if (choice==2) {
		ifstream fin("Auto_Record.txt");
		ofstream fout;
		fout.open("Auto_Record.txt.temp.txt",ios::app);
		string line;
		if (fin.fail()||fout.fail()) {
			exit(1);
		}
		turn=1;
		index=-1;
		while(getline(fin,line)) {
			if (turn>3) {
				int pos=line.rfind(" ");
				int day=atoi((line.substr(pos+13,1)).c_str());
				string d=Identify_Weekday(day);
				cout<<"\t"<<turn<<" "<<line.substr(0,pos)<<" ";
				cout<<line.substr(pos+1,2)<<"/"<<line.substr(pos+3,2)<<"/";
				cout<<line.substr(pos+5,4)<<"-"<<line.substr(pos+9,2)<<":";
				cout<<line.substr(pos+11,2)<<" "<<d<<" "<<line.substr(pos+14)<<endl;
				cout<<"Please select the index : ";
				cin>>index;
			}
			if (turn!=index) {
				fout<<line<<endl;
			}
			turn++;
		}
		fin.close();
		fout.close();
		Rename("Auto_Record.txt.temp.txt","Auto_Record.txt");
  }
	else if (choice<1||choice>2) {
		cout<<"Invalid\n";
	}
	return;
}
void SetBudget(User &user,vector<string> database) {
	int choice,count,index;
	Budget bg;
	do {
		cout<<"\n1 View budgets\t\t2 Add budget\t3 Change budget";
		cout<<"\n4 Delete budget\t\t5 Save & back\n\n";
		cout<<"Please enter your choice: ";
		cin>>choice;
		switch(choice) {
			case 1:
				cout.setf(ios::fixed,ios::floatfield);
				cout.setf(ios::showpoint);
				cout<<setprecision(1);
				cout<<endl;
				if(user.budget.empty()) {
					cout<<"Empty budget.";
					break;
				}
				for(auto i:user.budget) {
					cout<<i.type<<" ("<<i.period<<"): $"<<i.amount<<" Remain: $"<<i.remain<<endl;
				}
				break;
			case 2:
				cout<<"Please enter (Daily/Monthly) (Category) (Amount): ";
				InputBudget(bg);
				user.budget.push_back(bg);
				break;
			case 3:
				if(user.budget.empty()) {
					cout<<"\nEmpty budget.\n";
					break;
				}
				count=1;
				cout<<endl;
				for(auto &i:user.budget) {
					cout<<count<<". "<<i.type<<" ("<<i.period<<"): $"<<i.amount<<endl;
					count++;
				}
				cout<<"\nPlease choose: ";
				cin>>index;
				cout<<"Please enter (Daily/Monthly) (Category) (Amount): ";
				InputBudget(user.budget[index-1]);
				break;
			case 4:
				if(user.budget.empty()) {
					cout<<"\nEmpty budget.\n";
					break;
				}
				count=1;
				cout<<endl;
				for(auto i:user.budget) {
					cout<<count<<". "<<i.period<<" "<<i.type<<" "<<i.amount<<endl;
					count++;
				}
				cout<<"\nPlease choose: ";
				cin>>index;
				user.budget.erase(user.budget.begin()+count-1);
				break;
			case 5:
				sort(user.budget.begin(),user.budget.end(),[](Budget &x,Budget &y) {
					return x.period<y.period;
				});
				Update(user,database[3]);
				break;
			default:
				break;
		}
	}
	while(choice!=5);
	return;
}
void ShowReport(User &user,vector<string> database) {
	string date;
	Time now;
	int l,u;
	bool showBudget=false;
	double income=0,expense=0;
	map<string,double> map_expense,map_income,account;
	cout<<"For Monthly Report: Enter MMYYYY \n";
	cout<<"For Daily Report: Enter DDMMYYYY \nEnter : ";
	cin>>date;
	if(date.length()==8) {
		l=0;
		u=8;
	}
	else {
		l=2;
		u=6;
	}
	for(auto &i : user.record) {
		if(i.date.timestamp.substr(l,u)==date) {
			if(i.income>=0) {
				if(map_income.find(i.type)==map_income.end()) {
					map_income[i.type]=i.income;
				}
				else {
					map_income[i.type]+=i.income;
				}
				income+=i.income;
			}
			else {
				if(map_expense.find(i.type)==map_expense.end()) {
					map_expense[i.type]=-i.income;
				}
				else {
					map_expense[i.type]+=-i.income;
				}
				expense+=-i.income;
			}
		}
	}
	cout<<"\nDate: ";
	cout<<date.substr(0,2)<<"/";
	if(l==0) {
		cout<<date.substr(2,2)<<"/"<<date.substr(4,4);
	}
	else {
		cout<<date.substr(2,4);
	}
	cout<<"\n\n";
	cout.setf(ios::fixed,ios::floatfield);
	cout.setf(ios::showpoint);
	cout<<setprecision(1);
	cout<<"Accounts:\n";
	for(auto &i : user.account) {
		cout<<i.name<<": $"<<i.amount<<endl;
	}
	cout<<"\nSummary:\nTotal income: $"<<income<<endl;
	cout<<"Total expense: $"<<expense<<endl;
	cout<<"Net income: $"<<income-expense<<endl;
	cout<<"\nIncome by category:\n";
	if(map_income.empty()) {
		cout<<"Empty\n";
	}
	else {
		for(auto &i : map_income) {
			cout<<i.first<<": $"<<i.second<<" ("<<(i.second/income*100)<<"%)"<<endl;
		}
	}
	cout<<"\nExpense by category:\n";
	if(map_expense.empty()) {
		cout<<"Empty\n";
	}
	else {
		for(auto &i : map_expense) {
			cout<<i.first<<": $"<<i.second<<" ("<<(i.second/expense*100)<<"%)"<<endl;
		}
	}
	cout<<endl;
	GetCurrentTime(now);
	if(now.timestamp.substr(l,u)==date) {
		cout<<"Budgets:\n";
		if(user.budget.empty()) {
			cout<<"Empty\n";
		}
		else {
			for(auto &i : user.budget) {
				cout<<i.type<<" ("<<i.period<<"): $"<<i.amount<<" Remain: $"<<i.remain;
				if(i.remain<0) {
					cout<<" Overspent warning!";
				}
				cout<<endl;
			}
		}
	}
	return;
}
void ChangePassword(User &user,vector<string> database) {
	string password,confirm;
	do {
		cout<<"Enter new password: ";
		cin>>password;
		cout<<"Re-enter new password: ";
		cin>>confirm;
		if(confirm!=password) {
			cout<<"Not match.\n";
		}
	}
	while(password!=confirm);
	user.password=password;
	Update(user,database[0]);
	return;
}
