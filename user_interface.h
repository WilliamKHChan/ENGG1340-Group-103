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
   			 database - the name of the account database */
void Create_ACCT(User&,string);

/* Function: Delete an account
   Input   : user - the class of User
   			 database - vector containing the names of account and record databases*/
void Delete_ACCT(User&,vector<string>);

/* Function: Show all the data related to the user in a database
   Input   : user - the class of User
   			 database - the name of the database */
void View_Database(User&,string);

/* Function: Show all the data related to the user in the account database
   Input   : user - the class of User
   			 database - the name of the account database */
void View_ACCT(User&,string);

/* Function: Write the input into Record.txt
             and make deduction to the user's account and budget
   Input   : user - the class of User
   			 database - vector containing the names of all the databases */
void Add_Record(User&,vector<string>);

/* Function: Delete a record in Record.txt
   Input   : user - the class of User
   			 database - vector containing the names of the account and record databases */
void Delete_Record(User&,vector<string>);

/* Function: View records in the record database
   Input   : user - the class of User
   			 database - the name of the record database
             show - if true, called by MainMenu()
                    if false, called by Delete_Record()  */
void View_Record(User&,string,bool);

/* Function: Set an auto-record
   Input   : user - the class of User
   			 database - the name of the record database   */
void Set_Auto_Record(User&,string);

/* Function: Add new budget
   Input   : user - the class of User
   			 database - vector containing the names of all the databases
   Output  : Added a budget to user (pass by reference) and updated the database */
void SetBudget(User&,vector<string>);

/* Function: Generate a user report
   Input   : user - the class of User
   			 database - vector containing all the databases' names */
void ShowReport(User&,vector<string>);

/* Function: Change user password
   Input   : user - the class of User
   			 database - the names of all the databases
   Output  : User.password and database updated */ 
void ChangePassword(User&,vector<string>);
