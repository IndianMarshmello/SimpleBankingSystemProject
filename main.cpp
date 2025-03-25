#include <iostream>
#include <string>
#include <map>
#include <iomanip>
//#include <cmath> // might need

class User {
    private:
        std::string username;
        std::string password;
        double money; //should use double instead of int
                   // I have to figure out how to make the double stop after two decimals (because thats how MONEY WORKS!!!)
                   // I should probably get started ;-;
        /*
        Other methods
        */
    
    public:
    
        User() {};
        User(std::string u, std::string p) {
            this->username = u;
            this->password = p;
            this->money = 100.00;
        }
    
        /*
        Other methods
        */

        std::string getUsername() {
            return username;
        }

        std::string getPassword() {
            return password;
        }

        double checkBalance() {
            return money;
        }


        // withdrawing or depositing more than 2 decimals places (i.e. 0.001) adds up still,
        // it just doesn't display on the "Bank terminal"
        // fix maybe, at some point.
        double withdrawal(double n) {

            money-=n;

            return money;
        }

        double deposit(double n) {
            money+=n;

            return money;
        }
    
        ~User() {};
};

class Bank {
    private:
        std::map<std::string, User> accounts;
    public:
        Bank() {};

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
            while(true) {
                this->Signup();
                User current = Login();
                bool gay = true;
                while(gay) {
                    // going back in terminal menus will always be -1
                    // ^ that was hard cap, I did NOT use -1 to go back in terminal menus LOL
                    
                    // need to make getters and setters like checking balance, and adding balance to account aka deposit and withdrawal.
                    char option;
                    std::cout << "Pick an option to navigate the menu (1,2,3,4)"
                            << "\n1) check balance"
                            << "\n2) withdrawal"
                            << "\n3) deposit"
                            << "\n4) logout"
                            << "\n: ";
                    std::cin >> option;
                    double amount;
                    switch(option) {
                        case '1':
                            std::cout << "\n\nCurrent balance: " << std::fixed << std::setprecision(2) << current.checkBalance() << std::endl;
                            break;
                        case '2':
                            std::cout << "Withdrawal amount: ";
                            std::cin >> amount;

                            std::cout << "\n\nNew balance: " << std::fixed << std::setprecision(2) << current.withdrawal(amount) << std::endl;
                            break;
                        case '3':
                            std::cout << "Deposit amount: ";
                            std::cin >> amount;

                            std::cout << "\n\nNew balance: " << std::fixed << std::setprecision(2) << current.deposit(amount) << std::endl;
                            break;
                        case '4':
                            gay = false;
                            break;
                        default:
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
            std::cout << "\n\nWhat is your password?: ";
            std::cin >> pass;
            auto it = accounts.find(name);
            User currentUser = it->second;
            if (it == accounts.end()) {
                std::cerr << "Username not found" << std::endl;
                return User();  // Return a default user (or handle error properly but I'm too lazy, lowkey)
            }
            if(currentUser.getPassword() != pass) {
                std::cerr << "password incorrect" << std::endl;
                return User();
            }

            return currentUser;
        }
        
        // WORK ON ERROR CORRECTION at somepoint ;-;

        ~Bank() {};
};


int main() {

    Bank theBank;

    theBank.loadBank();

    return 0;
}