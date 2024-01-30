#ifndef BANK_H
#define BANK_H

#include "Customer.h"
#include "InputValidator.h"
#include <vector>

class Bank {
private:
    std::vector<Customer> customers; // Vector to store customer objects

public:
    // Constructor
    Bank();

    // Methods
    void printCustomers(); // Method to print customer details
    void loadCustomersFromFile(const std::string& filename); // Method to load customers from a file
    void saveCustomersToFile(const std::string& filename); // Method to save customers to a file

    void sendTextMessage(const std::string& sender, const std::string& message); // Method to send a text message
    std::string generateVerificationCode(); // Method to generate a verification code

    bool validateCreditCard(); // Method to validate credit card details
    bool checkUserName(const std::string& fName, const std::string& lName); // Method to validate user name
    bool checkCardNumber(const std::string& cardNumber); // Method to validate card number
    void registerUser(); // Method to register a new user

    bool authenticateUser(const std::string& name, const std::string& lName, const std::string& cardNumber); // Method to authenticate a user
    double checkBalance(const Customer& customer); // Method to check customer balance

    std::vector<Customer>& getCustomers(); // Getter for the vector of customers
};
#endif // BANK_H
