// No longer using

#include <iostream>
#include <string>
#include <map>
#include <iomanip>
//#include <fstream>
#include "user.cpp"

class Bank {
    private:
        std::map<std::string, User> accounts;
    public:
        Bank() {
            User admin("admin", "admin");
            insertUser(admin);

        };

        /*
            Other methods
            Make methods for inserting a user into the vector, and for removing if needed.abort
            To be determined, idk.
        */

        void insertUser(User sigma) {
            accounts.insert({sigma.getUsername(), sigma});
        }

        /*
        
        */

        void loadBank() {
            bool running = true;
            while(running) {
                this->Signup();
                User current = Login();
                bool loggedin = true;
                while(loggedin) {
                    // going back in terminal menus will always be -1
                    // ^ that was hard cap, I did NOT use -1 to go back in terminal menus LOL
                    
                    // need to make getters and setters like checking balance, and adding balance to account aka deposit and withdrawal.
                    char option;
                    std::cout << "\nPick an option to navigate the menu (1,2,3,4)"
                            << "\n1) check balance"
                            << "\n2) withdrawal"
                            << "\n3) deposit"
                            << "\n4) transfer"
                            << "\n5) logout"
                            << "\n6) quit program"
                            << "\n: ";
                    std::cin >> option;
                    double amount;
                    std::string who;
                    User transferie;
                    switch(option) {
                        case '1':
                            std::cout << "\nAccount: " << current.getUsername()
                                      << "\n\nCurrent balance: " << std::fixed << std::setprecision(2) << current.checkBalance() << std::endl;
                            break;
                        case '2':
                            std::cout << "Withdrawal amount: ";
                            std::cin >> amount;

                            std::cout << "\nAccount: " << current.getUsername()
                                      << "\n\nNew balance: " << std::fixed << std::setprecision(2) << current.withdrawal(amount) << std::endl;
                            break;
                        case '3':
                            std::cout << "Deposit amount: ";
                            std::cin >> amount;

                            std::cout << "\nAccount: " << current.getUsername()
                                      << "\n\nNew balance: " << std::fixed << std::setprecision(2) << current.deposit(amount) << std::endl;
                            break;
                        case '4':
                            std::cout << "Who would you like to transfer to?\n: ";
                            std::cin >> who;

                            transferie = userFinder(who);

                            std::cout << "\nHow much would you like to transfer?\n: ";
                            std::cin >> amount;

                            std::cout << "\nAccount: " << current.getUsername()
                                      << "\nTranfering " << amount << " to " << transferie.getUsername();

                            this->moneyTransfer(current, transferie, amount);

                            break;
                        case '5':
                            loggedin = false;
                            break;
                        case '6':
                            loggedin = false;
                            running = false;
                            break;
                        default:
                            std::cout << "\n\nNot an option, ya goober" << std::endl;
                            break;
                    }

                }
            }
        }

        void Signup() {
            
            // if they already have an account and want to login, call Login()
            // this->Login()
            char YN;
            std::cout << "Do you already have an account and need to login? Y/N: ";
            std::cin >> YN;

            if (YN == 'N') {
                std::string name;
                std::string pass;

                std::cout << "\n\nUsername: ";
                std::cin >> name;

                std::cout << "\n\nPassword: ";
                std::cin >> pass;

                User user(name, pass);
                this->insertUser(user);

            } //else if (YN == 'Y') {

            // }

        }

        User Login() {
            // get username and password as inputs and than search the map
            // for a User with the username and than match the password,
            // if correct, the User is "Logged In"
            std::string name;
            std::string pass;
            std::cout << "What is your username?: ";
            std::cin >> name;
            
            auto it = accounts.find(name);
            User currentUser = it->second;
            if (it == accounts.end()) {
                std::cerr << "Username not found" << std::endl;
                return User();  // Return a default user (or handle error properly but I'm too lazy, lowkey)
            }
            std::cout << "\n\nWhat is your password?: ";
            std::cin >> pass;
            if(currentUser.getPassword() != pass) {
                std::cout << "password incorrect" << std::endl;
                return User();
            }
            return currentUser;
        }

        User userFinder(std::string username) {
            auto it = accounts.find(username);
            if (it == accounts.end()) {
                std::cout << "Username not found" << std::endl;
                return User();
            }
            return it->second;
        }

        void moneyTransfer(User from, User to, double amount) {
            from.withdrawal(amount);
            to.deposit(amount);
        }

        void displayListAccounts() {
            for(auto& pair : accounts) {
                User user = pair.second;
                std::cout << "\n\n" << user.getUsername()
                          << "\n" << user.getPassword()
                          << "\n" << user.checkBalance();
            }
        }


        
        // WORK ON ERROR CORRECTION at somepoint ;-;

        ~Bank() {};
};