#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "user.cpp"

class Bank {
private:
    int currentID = 9999;
    bool running = true;
public:

    Bank();

    // some if not most of these functions
    // will not be return type 'void'
    // maybe they will, Idk.

    void loadBank();

    User* landing();

    User* setup();

    void insUser();

    User* retUser(std::string username);

    User* login();

    int latestID();

    void homepage(User* userPtr);

    User* parseLine(const std::string &line);

    void updateMoney(User* userPtr);

    void transferMoney(User* userPtr);

    void displayAccounts();

    ~Bank();
};

Bank::Bank() {
    // constructor for Bank
    currentID=latestID();
}

void Bank::loadBank() {
    while(running) {
        User* currentUserPtr = landing();
        if (currentUserPtr == nullptr) {
            break;
        }
        bool Logged_In = true;
        while(Logged_In) {
            homepage(currentUserPtr);
            break;
        }
    }
    // runs the banks
}

User* Bank::landing() {
    // First thing that should happen
    // ask if user wants to login or sign up
    char option;
    std::cout << "\n\nWelcome to Sigma Bank"
              << "\nWould you like to log in"
              << "\nOr sign up?"
              << "\n1) log in"
              << "\n2) sign up"
              << "\n3) quit program"
              << "\n: ";
    std::cin >> option;

    switch(option) {
        case '1':
            return login();
        case '2':
            return setup();
        case '3':
            return nullptr;
        default:
            return landing();

    }
}

User* Bank::setup() {
    // setup an account.
    std::string username, password;
    std::cout << "\n\nAccount Setup"
              << "\nUsername: ";
    std::cin >> username;
    std::cout << "\nPassword: ";
    std::cin >> password;
    
    // check for accounts existence in database (for now, just don't allow two accounts with the same username)
    std::ifstream check("users.csv");

    if (check.is_open()) {
        std::string line;
        getline(check, line);
        while (getline(check, line)) {
            std::stringstream ss(line);
            std::string dUsername;
            getline(ss, dUsername);
            getline(ss, dUsername);
            if (dUsername == username) {
                std::cout << "\nAccount with the username " << username << " already exists!"
                          << "\nReturning to landing" << std::endl;
                return landing();
            }
        }
    }

    // add the account to the database (i.e. "users.csv")
    std::ofstream file("users.csv", std::ios::app);
    
    if (file.is_open()) {
        file << currentID << ','
             << username << ','
             << password
             << ",100\n";
        file.close();
        std::cout << "New account added with username: " << username << std::endl;
        std::cout << "You will now be returned to the Landing menu"
                  << "\nchoose to Log in, to Log in to your newly created account.";
        currentID++;
        return landing();
    } else {
        std::cerr << "Error opening file for writing!\n";
        return landing();
    }

    // using LatestID() make sure the correct ID is given to the newest entry // used to set the "currentID" inside this class.(Bank class)
    // also make sure that the private "currentID" variable is correctly instantiated
    // during the runtime so that when multiple accounts are setup it stays consistent
        // (I.E. there are already 0-5 accounts make sure the newest entry starts at ID 6)
}

void Bank::insUser() { // insert user into database (lowkey, might be setup..... LOL)

}

User* Bank::retUser(std::string username) { // retrieve user (from database) (In hindsight, this might be just logging in, but we will see.)
    // search the database
    std::ifstream file("users.csv");
    if (!file.is_open()) {
        std::cerr << "\nError opening file!";
        return nullptr;
    }
    std::string line;
    getline(file, line);
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string ID, dUsername, dPassword, dMoney;
        
        if(std::getline(ss, ID, ',')&&
           std::getline(ss, dUsername, ',')&&
           std::getline(ss, dPassword, ',')&&
           std::getline(ss, dMoney)) {
            if((dUsername==username)) {
                User* userPtr = new User(std::stoi(ID), dUsername, dPassword, std::stod(dMoney));
                file.close();
                return userPtr;
            }
        }
    }
    file.close();
    return nullptr;
}

User* Bank::login() {
    // get a username
    // get a password
    std::string username;
    std::string password;

    std::cout << "\nEnter Username: ";
    std::cin >> username;
    std::cout << "\nEnter Password: ";
    std::cin >> password;

    // search the database
    // for a row where the username and password match
        // that would mean this is the "logged in" account, set it as the current user.
    std::ifstream file("users.csv");
    if (!file.is_open()) {
        std::cerr << "\nError opening file!";
        return landing();
    }
    std::string line;
    getline(file, line);
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string ID, dUsername, dPassword, dMoney;
        
        if(std::getline(ss, ID, ',')&&
           std::getline(ss, dUsername, ',')&&
           std::getline(ss, dPassword, ',')&&
           std::getline(ss, dMoney)) {
            if((dUsername==username)&&(dPassword==password)) {
                std::cout << "\nLogged In" << std::endl;
                User* userPtr = new User(std::stoi(ID), dUsername, dPassword, std::stod(dMoney));
                file.close();
                return userPtr;
            }
        }
    }
    std::cout << "\nCouldn't find account matching those credentials" << std::endl;
    return landing();
    

}

int Bank::latestID() {
    // search the database for the final entry
    // return the last ID
        // run on startup to update the private "currentID" variable
        // when program starts

    std::ifstream file("users.csv");
    if(!file.is_open()) {
        std::cerr << "\nError opening file!\n";
        return -1;
    }

    std::string line;
    int lastID = -1; // Start with -1 to account for increment
    getline(file, line);

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr;

        getline(ss, idStr, ',');

        try {
            int id = stoi(idStr);
            if (id > lastID) {
                lastID = id;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid ID format in line: " << line << "\n";
        }
    }

    file.close();
    return lastID + 1;

    // change return type to int
}

void Bank::homepage(User* userPtr) {
    // create the terminal menu
    // after the user is 'logged in'
    // provide options like 'view balance', 'deposit', 'withdrawal', and 'transfer'
    char option;
    std::cout << "\n\nPick an option to navigate the menu (1,2,3,4)"
            << "\n1) check balance"
            << "\n2) withdrawal"
            << "\n3) deposit"
            << "\n4) transfer"
            << "\n5) logout"
            << "\n6) quit program"
            << "\n: ";
    std::cin >> option;
    double amount;
    switch(option) {
        case '1':
            std::cout << "\nAccount: " << userPtr->getUsername()
                    << "\nCurrent balance: " << std::fixed << std::setprecision(2) << userPtr->checkBalance();
            
            homepage(userPtr);
            break;
        case '2':
            std::cout << "\nAccount: " << userPtr->getUsername()
                    << "\nWithdrawal amount: ";
            std::cin >> amount;

            std::cout << "\nAccount: " << userPtr->getUsername()
                    << "\nNew balance: " << userPtr->withdrawal(amount);
            updateMoney(userPtr);
            homepage(userPtr);
            break;
        case '3':
            std::cout << "\nAccount: " << userPtr->getUsername()
                    << "\nDeposit amount: ";
            std::cin >> amount;

            std::cout << "\n\nAccount: " << userPtr->getUsername()
                    << "\nNew balance: " << userPtr->deposit(amount);
            updateMoney(userPtr);
            homepage(userPtr);
            break;
        case '4':
            transferMoney(userPtr);
            break;
        case '5':
            break;
        case '6':
            running = false;
            break;
        default:
            std::cout << "\n\nINVALID OPTION" << std::endl;
            homepage(userPtr);
            break;

    }
    

}

User* Bank::parseLine(const std::string &line) {
    std::stringstream ss(line);
    std::string ID, dUsername, dPassword, dMoney;

    std::getline(ss, ID, ',');
    std::getline(ss, dUsername, ',');
    std::getline(ss, dPassword, ',');
    std::getline(ss, dMoney);
    User* entry = new User(std::stoi(ID), dUsername, dPassword, std::stod(dMoney));
    return entry;
}

void Bank::updateMoney(User* userPtr) {
    int targetID=userPtr->getID();
    double newMoney = userPtr->checkBalance();
    std::ifstream file("users.csv");
    if (!file.is_open()) {
        std::cerr << "\nError opening file!\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    if (std::getline(file, line)) {
        lines.push_back(line);
    }

    while (std::getline(file, line)) {
        User* entryPtr = parseLine(line);
        if (entryPtr->getID() == targetID) {
            entryPtr->setMoney(newMoney);
        }

        std::ostringstream updateLine;
        updateLine << entryPtr->getID() << ',' << entryPtr->getUsername() << ',' << entryPtr->getPassword() << ',' << entryPtr->checkBalance();
        lines.push_back(updateLine.str());
        delete entryPtr;
    }

    file.close();

    std::ofstream outFile("users.csv");
    if (!outFile.is_open()) {
        std::cerr << "\nError writing file!\n";
        return;
    }

    for (const auto &l:lines) {
        outFile << l << "\n";
    }

    outFile.close();
}

void Bank::transferMoney(User* userPtr) {
    std::string who;
    std::cout << "\n\nWho are you transferring money to? (username only)\n: ";
    std::cin >> who;

    if (who == userPtr->getUsername()) {
        std::cout << "\n\nYou can't transfer money to yourself" << std::endl;
        return transferMoney(userPtr);
    }
    double amount;
    while(true) {
        std::cout << "\n\nHow much would you like to transfer?\n: ";
        std::cin >> amount;

        if(amount < 0) {
            std::cout << "\n\nCannot transfer negative number" << std::endl;
            continue;
        }
        break;
    }

    if(userPtr->checkBalance() < amount) {
        std::cout << "\n\nInsufficient funds";
        return homepage(userPtr);
    }
    
    User* transferiePtr = retUser(who);
    if (transferiePtr == nullptr) {
        std::cout << "\n\nCould not transfer money, try again later.";
        return homepage(userPtr);
    }

    userPtr->withdrawal(amount);
    transferiePtr->deposit(amount);
    updateMoney(userPtr);
    updateMoney(transferiePtr);
    std::cout << "\n\nMoney transfer successful" << std::endl;
    delete transferiePtr;
    return homepage(userPtr);
    // for transferring money
    // between users/accounts (users or accounts, call it what you like :P)
}

void Bank::displayAccounts() {
    // display all account information
        // username
        // password
        // money
}

Bank::~Bank() {
    // I do not fully understand destructors, or when/how to use them
    // Learn.... lol
}