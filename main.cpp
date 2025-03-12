#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

class User
{
public:
    User() : username(""), password(""), name("") {}

    User(const std::string& username, const std::string& password, const std::string& name)
        : username(username), password(password), name(name) {}

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
    Message() : sender(""), receiver(""), text("") {} 

    Message(const std::string& sender, const std::string& receiver, const std::string& text)
        : sender(sender), receiver(receiver), text(text) {}

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
public:
    Chat() : currentUser("") {}

    void registerUser(const std::string& username, const std::string& password, const std::string& name)
    {
        if (users.find(username) != users.end())
        {
            throw std::runtime_error("User already exists");
        }

        users[username] = User(username, password, name);
    }

    void loginUser(const std::string& username, const std::string& password)
    {
        if (users.find(username) == users.end() || users[username].getPassword() != password)
        {
            throw std::runtime_error("Invalid username or password");
        }

        currentUser = username;
        std::cout << "Logged in as " << username << std::endl;
    }

    void logoutUser()
    {
        if (currentUser.empty())
        {
            throw std::runtime_error("No user is logged in");
        }
        std::cout << "Logged out from " << currentUser << std::endl;
        currentUser.clear();
    }

    void sendMessage(const std::string& receiver, const std::string& text)
    {
        if (currentUser.empty())
        {
            throw std::runtime_error("User not logged in");
        }

        if (users.find(receiver) == users.end()) 
        {
            throw std::runtime_error("Receiver not found");
        }

        messages.push_back(Message(currentUser, receiver, text));
    }

    void showMessages() const
    {
        if (currentUser.empty())
        {
            throw std::runtime_error("No user is logged in");
        }

        bool hasMessages = false;
        for (const auto& message : messages)
        {
            if (message.getReceiver() == currentUser)
            {
                std::cout << message.getSender() << " to " << message.getReceiver() << ": " << message.getText() << std::endl;
                hasMessages = true;
            }
        }

        if (!hasMessages)
        {
            std::cout << "No new messages." << std::endl;
        }
    }

    bool isUserLoggedIn() const
    {
        return !currentUser.empty();
    }

private:
    std::unordered_map<std::string, User> users;
    std::vector<Message> messages;
    std::string currentUser;
};

int main()
{
    Chat chat;
    std::string username, password, name;
    int option;

    try
    {
        while (true)
        {
            if(chat.isUserLoggedIn())
            {
                std::cout << "\nMenu: \n";
                std::cout << "1. Logout\n"; 
                std::cout << "2. Send Message\n"; 
                std::cout << "3. Show Messages\n"; 
                std::cout << "4. Exit\n";
            }
            else
            {
                std::cout << "\nMenu: \n";
                std::cout << "1. Register\n";
                std::cout << "2. Login\n";
                std::cout << "3. Exit\n";
            }

            std::cout << "Choose an option: ";
            std::cin >> option;

            if (option == 1)
            {
                if (!chat.isUserLoggedIn())
                {
                    std::cout << "Enter username: ";
                    std::cin >> username;
                    std::cout << "Enter password: ";
                    std::cin >> password;
                    std::cout << "Enter your name: ";
                    std::cin >> name;

                    chat.registerUser(username, password, name);
                    std::cout << "User registered successfully!" << std::endl;
                }
                else
                {
                    chat.logoutUser();
                }
            }
            else if (option == 2)
            {
                if (!chat.isUserLoggedIn())
                {
                    std::cout << "Enter username to login: ";
                    std::cin >> username;
                    std::cout << "Enter password: ";
                    std::cin >> password;

                    chat.loginUser(username, password);
                }
                else
                {
                    std::string receiver, message;
                    std::cout << "Enter recipient username: ";
                    std::cin >> receiver;
                    std::cout << "Enter message: ";
                    std::cin.ignore();
                    std::getline(std::cin, message);

                    chat.sendMessage(receiver, message);
                }
            }
            else if (option == 3)
            {
                if (!chat.isUserLoggedIn())
                {
                    std::cout << "Exiting program." << std::endl;
                    break;
                }
                else
                {
                    chat.showMessages();
                }
            }
            else if (option == 4 && chat.isUserLoggedIn())
            {
                std::cout << "Exiting program." << std::endl;
                break;
            }
            else
            {
                std::cout << "Invalid option, please try again." << std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
