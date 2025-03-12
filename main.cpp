#include <iostream>
#include <string>

class User
{
    public:
    User(const std::string& username, const std::string& password, const std::string& name) : username(username), password(password),
    name(name) {}

    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getName() const { return name; }

    private:
    std::string username;
    std::string password;
    std::string name;
};

class Message 
{

};

class Chat
{

};