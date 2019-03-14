#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#define INFORMATION 1
#define ACCOUNT		2
#define RECORD		3
#define BUDGET		4
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
bool UpdateAll(const User&,string,string,string,string,string);
bool Update(const User&,string,int,string);
void Write(const User&,ofstream&,int);
void Rename(string,string);
