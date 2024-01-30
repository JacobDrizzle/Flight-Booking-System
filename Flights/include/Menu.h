#ifndef MENU_H
#define MENU_H

#include "Bank.h"
#include "Flight.h"
#include "Customer.h"
#include "InputValidator.h"

#include <vector>

class Menu {
public:
    // Constructor initializes the Menu object
    Menu();

    // Authenticated user for the current session
    Customer authenticatedUser;

    // Run the main menu loop
    void run();

    // Perform user login
    void login();

    // Perform user logout
    void logout();

private:
    // Bank object to manage customer data and transactions
    Bank bank;

    // Flight object to manage flight-related operations
    Flight flight;

    // Display the main menu options
    void displayMenu();

    // Perform user registration
    void signUp();

    // Print details of the authenticated user
    void printUser();

    // Update the balance of the authenticated user
    void updateBalance(Customer& customer);

    // Book a flight for the authenticated user
    void bookFlight(Customer& user);
};

#endif // MENU_H
