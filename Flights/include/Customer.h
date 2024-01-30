#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    std::string FirstName;   // First name of the customer
    std::string LastName;    // Last name of the customer
    std::string CardNumber;  // Credit card number of the customer
    double Balance;          // Balance in the customer's account

public:
    // Constructor
    Customer();
    Customer(const std::string& fname, const std::string& lname, const std::string& cardNumber, double customerBalance);

    // Methods
    void printDetails();             // Method to print customer details

    // Setters
    void updateBalanceInFile();    // Method to update the balance in the file
    void setBalance(double amount); // Setter for balance

    // Getters
    double getBalance() const;         // Getter for balance
    std::string getFirstName() const;  // Getter for first name
    std::string getLastName() const;   // Getter for last name
    std::string getCardNumber() const; // Getter for card number
};

#endif // CUSTOMER_H
