#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iomanip>
using namespace std;
class Time {
public:
	string timestamp;
	int year;
	int month;
	int day;
	int hour;
	int minute;
};
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
	Time time;
};
class Budget {
public:
	Time start;
	Time end;
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
void ExtractTime(Time&,bool);
