#include <string>

class User {
    private:
        int userID;
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
        User(int id, std::string u, std::string p);
        User(int id, std::string u, std::string p, double m);
        
        /*
        Other methods
        */

        int getID() {return userID;}
        
        std::string getUsername() {return username;}

        std::string getPassword() {return password;}

        double checkBalance() {return money;}

        double withdrawal(double n);

        double deposit(double n);

        void setMoney(double n);
        
        ~User() {};
};

User::User(int id, std::string u, std::string p) {
    userID=id;
    username = u;
    password = p;
    money = 100.00;
}

User::User(int id, std::string u, std::string p, double m) {
    userID=id;
    username=u;
    password=p;
    money=m;
}

double User::withdrawal(double n) {
    money-=n;
    return money;
}

double User::deposit(double n) {
    money+=n;
    return money;
}

void User::setMoney(double n) {
    money=n;
}