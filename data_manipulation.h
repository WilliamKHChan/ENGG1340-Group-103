#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iomanip>
#include <algorithm>
#include <map>
#ifndef data_manipulation
#define data_manipulation 1
#endif
using namespace std;
class Time {
public:
	string timestamp;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int wday;
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
	Time date;
};
class Budget {
public:
	string period;
	Time date;
	string type;
	double amount;
	double remain;
};
class User {
public:
	string username;
	string name;
	string password;
	vector<Account> account;
	vector<Record> record;
	vector<Budget> budget;
	vector<Record> auto;
};
bool LoadAll(User&,vector<string>);
bool Load(User&,string);
bool UpdateAll(const User&,vector<string>,string="");
bool Update(const User&,string,string="");
string Identify_Weekday(int);
void Rename(string,string);
void ExtractTime(Time&,bool);
void GetCurrentTime(Time&);
void InputBudget(Budget&);
void RenewBudget(vector<Budget>&);
