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
void Create_ACCT(User&,string);
void Delete_ACCT(User&,vector<string>);
void View_Database(User&,string);
void View_ACCT(User&,string);
void Add_Record(User&,vector<string>);
void Delete_Record(User&,vector<string>);
void View_Record(User&,string,bool);
void Set_Auto_Record(User&,string);
void SetBudget(User&,vector<string>);
void ShowReport(User&,vector<string>);
void ChangePassword(User&,vector<string>);
