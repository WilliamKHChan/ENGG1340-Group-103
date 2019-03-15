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
bool LoadAll(User&,vector<string>);
bool Load(User&,string);
bool UpdateAll(const User&,vector<string>,string="");
bool Update(const User&,string,string="");
void Rename(string,string);
