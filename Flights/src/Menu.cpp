#include "Menu.h"
#include <iostream>
#include <regex>

// Enumeration to represent menu options
enum MenuOptions {
    SIGN_UP = 1,
    LOGIN,
    ADD_CREDIT,
    BOOK_FLIGHT,
    PRINT_USER,
    EXIT,
    LOGOUT
};

// Constructor initializes the Menu object
Menu::Menu() : bank() {}

// Run the main menu loop
void Menu::run() {
    while (true) {
        displayMenu();
        int choice;
        std::cout << "\nEnter your choice: ";

        std::cin >> choice;

        // Clear input buffer in case of non-numeric input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }

        switch (static_cast<MenuOptions>(choice)) {
            case SIGN_UP:
                bank.registerUser();
                break;
            case LOGIN:
                login();
                break;
            case ADD_CREDIT:
                updateBalance(authenticatedUser);
                break;
            case BOOK_FLIGHT:
                if (authenticatedUser.getFirstName().empty()) {
                    std::cout << "\nYou are not logged in. Please log in first.\n\n";
                    break;
                } else {
                    bookFlight(authenticatedUser);
                    break;
                }
            case PRINT_USER:
                printUser();
                break;
            case EXIT:
                std::cout << "Exiting the program.\n";
                return;
            case LOGOUT:
                logout();
                break;
            default:
                std::cout << "\nPlease enter a valid number\n\n";
                break;
        }
    }
}

// Perform user login
void Menu::login() {
    if (!authenticatedUser.getFirstName().empty()) {
        std::cout << "\nAlready Logged In.\n\n";
    } else {
        std::string fName = InputValidator::validateInput("\nEnter Your First Name: ",
                                                           "\nInvalid format. First Name can only contain letters (a-z A-Z).",
                                                           std::regex("[a-zA-Z]+"));

        std::string lName = InputValidator::validateInput("\nEnter Your Last Name: ",
                                                           "\nInvalid format. Last Name can only contain letters (a-z A-Z).",
                                                           std::regex("[a-zA-Z]+"));

        if (!bank.checkUserName(fName, lName)) {
            std::cout << "\nNo account with name: " << fName << " " << lName << ".\n\nPlease try again.\n\n";
            return;
        }

        std::string cardNum = InputValidator::validateInput("\nEnter Card Details: ",
                                                            "\nInvalid format. Card number must be 16 digits.",
                                                            std::regex("\\d{16}"));

        if (!bank.checkCardNumber(cardNum) || !bank.authenticateUser(fName, lName, cardNum)) {
            std::cout << "\nInvalid Card Number or authentication failed. Please try Again.\n";
            return;
        }

        // Find the existing user from the loaded customer data
        for (const Customer &customer : bank.getCustomers()) {
            if (customer.getFirstName() == fName && customer.getLastName() == lName &&
                customer.getCardNumber() == cardNum) {
                authenticatedUser = customer;
                std::cout << "\nLogged in as: " << customer.getFirstName() << std::endl;
                std::cout << "\nBalance: " << customer.getBalance() << "\n" << std::endl;
                break;
            }
        }
    }
}

// Perform user logout
void Menu::logout() {
    if (authenticatedUser.getFirstName().empty()) {
        std::cout << "\nPlease log in first.\n\n";
    } else {
        std::cout << "\n" << authenticatedUser.getFirstName() << " Logged out.\n\n";
        authenticatedUser = Customer();
    }
}

// Display the main menu options
void Menu::displayMenu() {
    std::cout << "====== Main Menu ======\n";
    std::cout << "1. Sign Up\n";
    std::cout << "2. Login\n";
    std::cout << "3. Add Credit\n";
    std::cout << "4. Book Flight\n";
    std::cout << "5. Print Logged in user\n";
    std::cout << "6. Exit\n";
    std::cout << "7. Logout\n";
}

// Print details of the authenticated user
void Menu::printUser() {
    if (authenticatedUser.getFirstName().empty()) {
        std::cout << "\nNo active user, Please log in to print details.\n\n";
        return;
    } else {
        authenticatedUser.printDetails();  // Print details of the logged-in user
    }
}

// Update the balance of the authenticated user
void Menu::updateBalance(Customer &customer) {
    if (authenticatedUser.getFirstName().empty()) {
        std::cout << "\nPlease log in to add credit.\n\n";
        return;
    } else {
        std::string amount;
        std::regex amountPattern("\\d+");

        do {
            std::cout << "\nPlease enter an amount to top up: ";
            std::cin >> amount;
            if (!regex_match(amount, amountPattern)) {
                std::cout << "\nInvalid Amount, please enter numeric values only.\n";
                continue;
            }
        } while (!regex_match(amount, amountPattern));

        double amountInt = std::stod(amount);
        customer.setBalance(amountInt);  // Update the balance of the logged-in user
        std::cout << "\nBalance: " << customer.getBalance() << "\n\n";
    }
}

// Book a flight for the authenticated user
void Menu::bookFlight(Customer &user) {
    flight.inputFlightDetails(user);  // Take input for flight details and payment
}
