#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>
#include "user.cpp"

class Bank {
private:
    int currentID = 9999;
public:

    Bank();

    // some if not most of these functions
    // will not be return type 'void'
    // maybe they will, Idk.

    void loadBank();

    void landing();

    void setup();

    void insUser();

    void retUser();

    void login();

    void latestID();

    void transferMoney();

    void displayAccounts();

};

Bank::Bank() {
    // constructor for Bank
}

void Bank::loadBank() {
    

    // runs the banks
}

void Bank::landing() {
    // First thing that should happen
    // ask if user wants to login or sign up
}

void Bank::setup() {
    // setup an account.
    // add the account to the database (i.e. "users.csv")
    // using LatestID() make sure the correct ID is given to the newest entry 
    // also make sure that the private "currentID" variable is correctly instantiated
    // during the runtime so that when multiple accounts are setup it stays consistent
        // (I.E. there are already 0-5 accounts make sure the newest entry starts at ID 6)
}

void Bank::insUser() { // insert user into database (lowkey, might be setup..... LOL)

}

void Bank::retUser() { // retrieve user (from database) (In hindsight, this might be just logging in, but we will see.)

}

void Bank::login() {
    // get a username
    // get a password

    // search the database
    // for a row where the username and password match
        // that would mean this is the "logged in" account, set it as the current user.

}

void Bank::latestID() {
    // search the database for the final entry
    // return the last ID
        // run on startup to update the private "currentID" variable
        // when program starts

    // change return type to int
}

void Bank::transferMoney() {
    // for transferring money
    // between users/accounts (users or accounts, call it what you like :P)

}

void Bank::displayAccounts() {
    // display all account information
        // username
        // password
        // money
}
