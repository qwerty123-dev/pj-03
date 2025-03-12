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
    public:
    Message(const std::string& sender, const std::string& receiver, const std::string& text) : sender(sender), receiver(receiver),
    text(text) {}
    
    std::string getSender() const { return sender; }
    std::string getReceiver() const { return receiver; }
    std::string getText() const { return text; }
   
    private:
    std::string sender;
    std::string receiver;
    std::string text;

};

class Chat
{

};