#include <string>

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

