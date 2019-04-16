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
			RenewBudget(user.budget);     // Update data for calcualtion
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
				Delete_ACCT(user,database[1]);
				break;
			case 3:
				View_Database(user,database[1]);
				break;
			case 4:
				Add_Record(user,database[2]);
				break;
			case 5:
				Delete_Record(user,database[2]);
				break;
			case 6:
				View_Record(user,database[2]);
				break;
			case 7:
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
		else
			replace=2;
	}
	if (replace==0) {
	cout<<"Write into Account.txt\n";
	fout<<user.username<<' '<<ACCT_type<<' '<<Amount<<endl;
	fout.close();
	fin.close();
  }
}
void Delete_ACCT(User &user,string database) {
	View_Database(user,database);
	int Account;
	cout<<"Please enter your choice : ";
	cin>>Account;
	cout<<"Delete Account "<<Account<<endl;
	Account-=1;
	user.account.erase(user.account.begin()+Account);
	//for (auto i : user.account)
		//cout<<i.name<<' '<<i.amount<<endl;
	Update(user,database);
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
void Add_Record(User &user,string database) {
	string Account,Amount,Category;
	Time date;
	GetCurrentTime(date);
	cout<<"Please enter (Account) (+/-Amount) (Category) : ";
	cin>>Account>>Amount>>Category;
	ofstream fout;
	fout.open(database, ios::app);
	if (fout.fail())
		exit(1);
	fout<<user.username<<' '<<Account<<' '<<Amount<<' '<<Category<<' ';
	fout<<date.timestamp<<endl;
	fout.close();
}
void Delete_Record(User &user,string database) {
	View_Database(user,database);
	int Record;
	cout<<"Please enter your choice : ";
	cin>>Record;
	cout<<"Delete Record "<<Record<<endl;
	Record-=1;
	user.record.erase(user.record.begin()+Record);
	//for (auto i : user.record)
		//cout<<i.account<<' '<<i.income<<' '<<i.type<<' '<<i.date.timestamp<<endl;
	Update(user,database);
}
void View_Record(User &user,string database) {
	int turn=1;
	ifstream fin(database);
	if (fin.fail())
		exit(1);
	cout<<"For Monthly Record: Enter MMYYYY\n";
	cout<<"For Daily Record: Enter DDMMYYYY\n";
	cout<<"Enter : ";
	string date,line,data,weekday;
	Time DATE;
	cin>>date;
	if (date.length()==8) { // Daily
		while (getline(fin,line)) {
			if (turn>3) {
				int pos=line.rfind(" ")+1;
				DATE.timestamp=line.substr(pos);
				data=DATE.timestamp.substr(0,8);
				if (data==date) {
					//cout<<"DATE.timestamp = "<<DATE.timestamp<<endl;
					//cout<<"Matched Date = "<<data<<endl;
					data=DATE.timestamp.substr(0,13);
					//cout<<"data = "<<data<<endl;
					ExtractTime(DATE,true);
					weekday=Identify_Weekday(DATE.wday);
					cout<<left<<setw(30)<<line.substr(0,line.rfind(" "))<<' ';
					cout<<DATE.day<<'/'<<DATE.month<<'/'<<DATE.year<<'-';
					cout<<DATE.minute<<":"<<DATE.hour<<' '<<weekday<<endl;
				}
			}
			turn++;
		}

	}
	fin.close();
	return;
}
void SetBudget(User &user,vector<string> database) {
	int choice,item,count;
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
				cin>>item;
				cout<<"Please enter period, type, amount: ";
				InputBudget(bg);
				user.budget.erase(user.budget.begin()+count-1);
				user.budget.push_back(bg);
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
				cin>>item;
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
	map<string,double> category,account;
	cout<<"Please enter the date (DDMMYYYY/MMYYYY): ";
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
				income+=i.income;
			}
			else {
				if(category.find(i.type)==category.end()) {
					category[i.type]=-i.income;
				}
				else {
					category[i.type]+=-i.income;
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
	cout<<"\nExpense by category:\n";
	if(category.empty()) {
		cout<<"Empty\n";
	}
	else {
		for(auto &i : category) {
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
				if(l==0 && i.period=="Monthly") {
					continue;
				}
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
