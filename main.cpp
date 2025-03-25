#include <iostream>
#include <string>
#include <map>

class User {
    private:
        std::string username;
        std::string password;
        int money;
    
        /*
        Other methods
        */
    
    public:
    
        User() {};
        User(std::string u, std::string p) {
            this->username = u;
            this->password = p;
            this->money = 100;
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

        int checkBalance() {
            return money;
        }

        int withdrawal(int n) {

            money-=n;

            return money;
        }

        int deposit(int n) {
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
                    
                    // need to make getters and setters like checking balance, and adding balance to account aka deposit and withdrawal.
                    char option;
                    std::cout << "Pick an option to navigate the menu (1,2,3,4)"
                            << "\n1) check balance"
                            << "\n2) withdrawal"
                            << "\n3) deposit"
                            << "\n4) logout"
                            << "\n: " << std::endl;
                    std::cin >> option;
                    int amount;
                    switch(option) {
                        case '1':
                            current.checkBalance();
                            break;
                        case '2':
                            std::cout << "Withdrawal amount: ";
                            std::cin >> amount;

                            amount = current.withdrawal(amount);
                            std::cout << "\n\nNew balance: " << amount;
                            break;
                        case '3':
                            std::cout << "Depost amount: ";
                            std::cin >> amount;

                            amount = current.deposit(amount);
                            std::cout << "\n\nNew balance: " << amount;
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
                return User();  // Return a default user or handle error properly
            }
            if(currentUser.getPassword() != pass) {
                std::cerr << "password incorrect" << std::endl;
                return User();
            }

            return currentUser;
        }
        
        //

        ~Bank() {};
};



// void textPrompt() {
//     std::cout << "\nWelcome to the Login screen" << std::endl;
//     std::cout << "Here you will be prompted to login\nor if you do not have an account,\nyou may enter \"signup\" in the username field\n" << std::endl;
// }

// int loginToBank() {
//     std::string tempname;
//     std::string temppass;
//     textPrompt();
//     std::cout << "Username: ";
//     std::cin >> tempname;
//     if (tempname == "signup") {
//         /*
//             call signup function when I make it
//         */
//
//         return 0;
//     }
//     std::cout << "\n\nPassword: ";
//     std::cin >> temppass;
//     return 0;
// }





int main() {

    Bank theBank;

    theBank.loadBank();

    return 0;
}