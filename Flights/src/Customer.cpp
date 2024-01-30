#include <iostream>
#include <string>
#include "Customer.h"
#include <regex>
#include <fstream>

Customer::Customer() {}

// Constructor
Customer::Customer(const std::string& fname, const std::string& lname, const std::string& cardNumber, double balance) {
    this->FirstName = fname;
    this->LastName = lname;
    this->CardNumber = cardNumber;
    this->Balance = balance;
}

void Customer::setBalance(double amount) {
    this->Balance += amount;
    updateBalanceInFile();
}

void Customer::updateBalanceInFile() {
    std::fstream file("Users.txt", std::ios::in | std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file Users.txt" << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> fileContent;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string fname, lname, cardNum;
        double balance;

        if (iss >> fname >> lname >> cardNum >> balance) {
            if (fname == this->FirstName && lname == this->LastName && cardNum == this->CardNumber) {
                // Update the balance for the current customer
                balance = this->Balance;
            }
            fileContent.push_back(fname + " " + lname + " " + cardNum + " " + std::to_string(balance));
        }
    }

    // Clear the file content and rewrite it with the updated balances
    file.close();
    file.open("Users.txt", std::ios::out | std::ios::trunc);

    for (const std::string& content : fileContent) {
        file << content << '\n';
    }

    file.close();
}

void Customer::printDetails() {
    std::cout << "\nName: " << this->FirstName << " " << this->LastName << "\tCardNumber: " << this->CardNumber << "\tBalance: " << this->Balance << "\n\n";
}

// Getters
std::string Customer::getFirstName() const {
    return FirstName;
}

std::string Customer::getLastName() const {
    return LastName;
}

std::string Customer::getCardNumber() const {
    return CardNumber;
}

double Customer::getBalance() const {
    return Balance;
}
