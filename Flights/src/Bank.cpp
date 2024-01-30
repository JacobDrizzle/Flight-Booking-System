#include "Bank.h"
#include "Customer.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <regex>
#include <iostream>
#include <fstream>

Bank::Bank(){
 loadCustomersFromFile("Users.txt");
};

// Validates credit card information, sends a verification code, and prompts for user verification
bool Bank::validateCreditCard() {
    std::string cardNum;

    bool validCard = false;

    do {
        cardNum = InputValidator::validateInput(
            "\nEnter Card Details: ",
            "\nInvalid format. card number must be 16 digits.\n",
            std::regex("\\d{16}")
        );
        validCard = checkCardNumber(cardNum);
        if (!validCard) {
            std::cout << "\nCard Number Does not Exist, please try again\n";
            continue;
        }
    } while (!validCard);

    sendTextMessage("AIB Bank", "Sending verification code please wait.");
    std::string generatedCode = generateVerificationCode();
    std::cout << "\nVerification Code: " << generatedCode << "\n";
    int attempts = 0;
    std::string userCode;

    do{
        if (attempts > 0) {
        std::cout << "\nInvalid code please try again. \n\nAttempts remaining: " << (3 - attempts) << std::endl;
        }
        std::cout << "\nEnter the verification code: ";
        std::cin >> userCode;
        attempts++;
    }
    while(attempts < 3 && userCode != generatedCode);

    if(attempts > 3) {
        std::cout << "\nToo many attempts. Transaction failed.\n" << std::endl;
        return false;
    }
    return true;
}

// Generates a random 4-digit verification code
std::string Bank::generateVerificationCode() {
    // generate a random 4-digit code
    srand(time(0));
    int verificationCode = rand() % 9000 + 1000;
    return std::to_string(verificationCode);
}

// Sends a text message with the sender's name and message content
void Bank::sendTextMessage(const std::string& sender, const std::string& message) {

    // Get the current system date and time
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    // Format the date and time
    std::cout << "\nMessage sent on: " << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
    std::cout << "\nSender: " << sender << std::endl;
    std::cout << "\nMessage: " << message << std::endl;
}

// Checks the balance of a customer account
double Bank::checkBalance(const Customer& customer) {
    return customer.getBalance();
}

// Registers a new user by collecting and validating user details
void Bank::registerUser() {
    std::string fname;
    std::string lname;
    std::string cardNum;

    bool cardExists;

    fname = InputValidator::validateInput(
        "\nEnter Your First Name: ",
        "\nInvalid format. Name can only contain letters (a-z A-Z).\n",
        std::regex("[a-zA-Z]+")
    );

    lname = InputValidator::validateInput(
        "\nEnter Your Last Name: ",
        "\nInvalid format. Name can only contain letters (a-z A-Z).\n",
        std::regex("[a-zA-Z]+")
    );

    do {
        cardNum = InputValidator::validateInput(
            "\nEnter Card Details: ",
            "\nInvalid format. card number must be 16 digits.\n",
            std::regex("\\d{16}")
        );
        cardExists = checkCardNumber(cardNum);
        if (cardExists) {
            std::cout << "\nCard Number Already Exists, please try again\n";
            continue;
        }
    } while (cardExists);

    // Create a new Customer instance and add it to the customers vector
    Customer newCustomer(fname, lname, cardNum, 0.0);  // Replace with actual credit card number
    customers.push_back(newCustomer);

    std::cout << "\nDetails Saved\n\n";

    // Save customers to the file after registration
    saveCustomersToFile("Users.txt");
}

// Prints details of all customers
void Bank::printCustomers() {
    for (Customer& customer : customers) {
        customer.printDetails();
    }
}

// Loads customer data from a file
void Bank::loadCustomersFromFile(const std::string& filename) {
    try {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        std::string fname;
        std::string lname;
        std::string cardNum;
        double balance;

        while (file >> fname >> lname >> cardNum >> balance) {
            Customer customer(fname, lname, cardNum, balance);
            customers.push_back(customer);
        }

        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Returns a reference to the vector of customers
std::vector<Customer>& Bank::getCustomers(){
    return customers;
}

// Validates the existence of a user with the given first name and last name
bool Bank::checkUserName(const std::string& fName, const std::string& lName) {
    for (const Customer& customer : customers) {
        if (customer.getFirstName() == fName && customer.getLastName() == lName) {
            return true;  // USERNAME EXISTS
        }
    }
    return false;  // USEERNAME DOES NOT EXIST
}

// Validates the existence of a user with the given card number
bool Bank::checkCardNumber(const std::string& cardNumber) {
    for (const Customer& customer : customers) {
        if (customer.getCardNumber() == cardNumber) {
            return true;  // USERNAME EXISTS
        }
    }
    return false;  // USEERNAME DOES NOT EXIST
}

// Authenticates a user based on first name, last name, and card number
bool Bank::authenticateUser(const std::string& fName,const std::string& lName, const std::string& cardNumber) {

    for (const Customer& customer : customers) {
        if (customer.getFirstName() == fName && customer.getLastName() == lName && customer.getCardNumber() == cardNumber) {
            return true;  // Authentication successful
        }
    }
    return false;  // Authentication failed
}

// Saves customer data to a file
void Bank::saveCustomersToFile(const std::string& filename) {
    try {
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        for (const Customer& customer : customers) {
            file << customer.getFirstName() << " " << customer.getLastName() << " " << customer.getCardNumber() << " " << customer.getBalance() << std::endl;
        }

        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
