#include <iostream>
#include <string>
#include <vector>



class Bank {
    private:
        std::vector<User> accounts;
    public:
        Bank() {};

        /*
            Other methods
            Make methods for inserting a user into the vector, and for removing if needed.abort
            To be determined, idk.
        */

        void insertUser(User T) {
            accounts.emplace_back(T);
        }

        /*
        
        */

        ~Bank() {};
};

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
    
        ~User() {};
};

void textPrompt() {
    std::cout << "\nWelcome to the Login screen" << std::endl;
    std::cout << "Here you will be prompted to login\nor if you do not have an account,\nyou may enter \"signup\" in the username field\n" << std::endl;
}

int loginToBank() {
    std::string tempname;
    std::string temppass;
    textPrompt();
    std::cout << "Username: ";
    std::cin >> tempname;
    if (tempname == "signup") {
        /*
            call signup function when I make it
        */

        return 0;
    }
    std::cout << "\n\nPassword: ";
    std::cin >> temppass;



    return 0;
}





int main() {

    loginToBank();


    
    return 0;
}