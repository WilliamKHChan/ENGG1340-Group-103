/* user_interface.h - user interface of the program */

#ifndef data_manipulation
#include "data_manipulation.h"
#endif

/* Function: Show the login screen
   Input   : user - the class of User
   			 database - vector containing the names of all the databases
   Output  : Data stored in user (pass by reference) */
void LoginScreen(User&,vector<string>);

// Login process
void Login(User&,vector<string>);

/* Create new user
   Output: Added new user to database */
void CreateAccount(User&,vector<string>);

/* Function: Show the main menu
   Input   : user - the class of User
   			 database - vector containing the names of all the databases */
void MainMenu(User&,vector<string>);

/* Function: Create an account
   Input   : user - the class of User
   			 database - Account.txt */
void Create_ACCT(User&,string);

/* Function: Delete an account
   Input   : user - the class of User
   			 database - vector containing the names of all the databases */
void Delete_ACCT(User&,vector<string>);

/* Function: Show all the data related to the user in a database
   Input   : user - the class of User
   			 database - vector containing the names of all the databases */
void View_Database(User&,string);

/* Function: Show all the data related to the user in ACcount.txt
   Input   : user - the class of User
   			 database - Account.txt */
void View_ACCT(User&,string);

/* Function: Write the input into Record.txt
             and make deduction to the user's account and budget
   Input   :      user - the class of User
   			      database - vector containing the names of all the databases */
void Add_Record(User&,vector<string>);

/* Function: Delete a record in Record.txt
   Input   : user - the class of User
   			 database - vector containing the names of all the databases */
void Delete_Record(User&,vector<string>);

/* Function: View records in Record.txt
   Input   : user - the class of User
   			 database - vector containing the names of all the databases
             show - if true, called by MainMenu()
                    if false, called by Delete_Record()  */
void View_Record(User&,string,bool);

/* Function: Set an auto-record
   Input   : user - the class of User
   			 database - Record.txt   */
void Set_Auto_Record(User&,string);
void SetBudget(User&,vector<string>);
void ShowReport(User&,vector<string>);
void ChangePassword(User&,vector<string>);
