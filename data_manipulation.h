/* data_manipulation.h - Manipulation on the user data */

/* This program uses vector to store all the data. Its flexibility improves the ease of loading
   data from the databases. The user does not need to worry that the number of records is larger
   than the array size. He or she needs not to reallocate memory to the array */

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
#include <functional>
#ifndef data_manipulation
#define data_manipulation 1
#endif
using namespace std;

// class Time - Stores the date
class Time {
public:
	string timestamp;	// In the format of DDMMYYHHMMW (Day/Month/Year Hour:Minute Weekday)
	int year;			// Year
	int month;			// Month
	int day;			// Day
	int hour;			// Hour
	int minute;			// Minute
	int wday;			// Weekday
};

// class Account - Stores the account information
class Account {
public:
	string name;		// Account name
	double amount;		// Amount of money
};

// class Record - Stores a record information
class Record {
public:
	string account;		// Account responsible for the transaction
	double income;		// Amount of money involved (+/-)
	string type;		// Category of the transaction
	Time date;			// Date of the transaction made
};

// class Budget - Stores a bugdet information
class Budget {
public:
	string period;		// Daily or monthly
	Time date;			// Date to check for renewal
	string type;		// Category to be budgeted
	double amount;		// Budget amount
	double remain;		// Budget amount left
};

// class User - Stores all the account data of a user
class User {
public:
	string username;			// The username of the user
	string name;				// The full name of the user
	string password;			// Login password
	vector<Account> account;	// Accounts that a user has
	vector<Record> record;		// Transaction records
	vector<Budget> budget;		// Budgets set by user
};

/* Function: Load the data from all the databases
   Input   : user - the class of User
   			 filename - vector containing the names of the databases
   Output  : user with updated member variables (pass by reference) */
bool LoadAll(User&,vector<string>);

/* Function: Load the data from a database
   Input   :     user - the class of User
   			     filename - the name of the database
   Output  : user with updated member variables related to that database (pass by reference) */
bool Load(User&,string);

/* Function: count the number of days in a month
   Input   : month in number
	 Output  : the number of days in a month*/
int Identify_Month(int);

/* Function: Get the number of days elapsed since the record time
   Input   : 					  MM - month of the record time
	 					 current_month - current month
						            DD - days of the record time
	 Output  : number of days elapsed since the record time*/
int Day_passed(int,int,int);

/* Function: Get the number of days elapsed since the record time
   Input   : 					  MM - month of the record time
	 					 current_month - current month
						            DD - days of the record time
	 Output  : number of days elapsed since the record time*/

/* Function: Check whether there should be autu-records
   Input   : 			User - all information about the user
	 	 					database - all .txt file
	 Output  : if true, update the information vector of the user*/
void Activate_Auto_Record(User&,vector<string>);

/* Function: Wrtite the auto-records into the database
   Input   : 				  User - all information about the user
	 					   record time - record time of a record
						          line - auto-record
										 Count - number of auto-records
	 Output  : number of auto-records*/
bool should_Update(User&,string,string,int&);

/* Function: Complete a Time class
   Input   : 				  date - all information about the user
	 					     timestamp - all string elements of time
	 Output  : a Completed Time class*/
void Auto_insert_time(Time&,string);

/* Function: Update the data in all the databases
   Input   : user - the class of User
   			 filename - vector containing the names of the databases
   			 old_username - (Optional) the old username that will be replaced
   Output  : Content in the databases updated */
bool UpdateAll(const User&,vector<string>,string="");

/* Function: Update the data in a database
   Input   : user - the class of User
   			 filename - the name of the database
   			 old_username - (Optional) the old username that will be replaced
   Output  : Content in the database updated */
bool Update(const User&,string,string="");

/* Function: Identif Weekday according to number
   Input   : day - a number representing the weekday
	 Output  : weekday in string */
string Identify_Weekday(int);

/* Function: Rename a file
   Input   : old_name - old name of the file
   		   : new_name - new name of the file
   Output  : The old filename is replaced by the new name */
void Rename(string,string);

/* Function: Manipulation on the class Time
   Input   : time - the class of Time
   			 isExtract - true for converting timestamp to integers, false for converting integers to timestamp
   Output  : Updated time (pass by reference) */
void ExtractTime(Time&,bool);

/* Function: Get current time
   Input   : time - the class of Time
   Output  : Updated time (pass by reference) */
void GetCurrentTime(Time&);

/* Function: User input on the budget
   Input   : budget - the class of Budget
   Output  : budget with the user input stored (pass by reference) */
void InputBudget(Budget&);

/* Function: Renew daily or monthly budgets
   Input   : user - the class of User
			 database - the name of the budget database
   Output  : User.Budget and budget database updated */
void RenewBudget(User&,string);

/* Function: Validate input. Input until valid
   Input   : Lambda function with bool as return value */
void Validate(function<bool()>);
