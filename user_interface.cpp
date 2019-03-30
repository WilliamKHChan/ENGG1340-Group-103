#include "user_interface.h"
void Login(User &user,vector<string> database) {
	bool success;
	do {
		cout<<"Username: ";
		cin>>user.username;
		cout<<"Password: ";
		cin>>user.password;
		success=LoadAll(user,database);
		if(!success) {
			cout<<"Invalid.\n";
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
		getline(cin,user.username);
		cout<<"Password: ";
		cin>>user.password;
		cout<<"Re-type password: ";
		cin>>password;
		cout<<"Name: ";
		cin.clear();
		cin.sync();
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
	cout<<"Welcome!\n\n1. Login\t2. New account\n\nPlease enter your choice: ";
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
void MainMenu(User &user,vector<string> database) {}
