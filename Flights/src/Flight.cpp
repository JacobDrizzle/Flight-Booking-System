#include "Flight.h"
#include <iomanip>
#include "InputValidator.h"
#include "Ticket.h"
// Constructor
Flight::Flight() {}

// Parameterized constructor to initialize Flight object
Flight::Flight(const std::string& fClass, const std::string& depAirport, Date& depDate,
               FlightTime& depTime, const std::string& arrAirport, Date& arrDate,
               FlightTime& arrTime, double flightCost) {
    // Initializing member variables with provided values
    flightClass = fClass;
    departureAirport = depAirport;
    arrivalAirport = arrAirport;
    departureDate = depDate;
    departureTime = depTime;
    arrivalDate = arrDate;
    arrivalTime = arrTime;
    cost = flightCost;
}

// Function to finalize booking based on user choice
bool Flight::finalizeBooking(Customer& customer, double cost) {
    std::string finalizeChoice;
    while (true) {
        // Get user choice
        finalizeChoice = InputValidator::validateInput(
            "\nDo you want to finalize the booking? (y/n): ",
            "\nInvalid Choice, please type y or n.\n",
            std::regex("[yYnN]")
        );
         // Compare directly with 'Y' and 'N'
        if (finalizeChoice == "Y" || finalizeChoice == "y") {
            // If user chooses to finalize, process payment and return true
            processPayment(customer, cost);
            return true;
        } else if (finalizeChoice == "N" || finalizeChoice == "n") {
            // If user chooses not to finalize, inform and return false
            std::cout << "\nBooking cancelled.\n" << std::endl;
            return false;
        } else {
            // If an invalid choice is entered, inform and ask again
            std::cout << "\nInvalid Choice, please enter y or n." << std::endl;
        }
    }
}

// Main function with sub-functions to input flight details and finalize booking
bool Flight::inputFlightDetails(Customer& customer) {
    // Get and validate flight class input
    flightClass = InputValidator::validateInput(
        "\nEnter flight class (Economy/Business): ",
        "\nInvalid flight class. Please enter E or B.\n",
        std::regex("[eEbB]")
    );
    std::transform(flightClass.begin(), flightClass.end(), flightClass.begin(), ::toupper);

    // Get and validate departure airport input
    departureAirport = InputValidator::validateInput(
        "\nEnter departure airport (3-letter code): ",
        "\nInvalid input. Please enter a three-letter code e.g. JFK.\n",
       std::regex("[a-z A-Z]{3}")
    );
    std::transform(departureAirport.begin(), departureAirport.end(), departureAirport.begin(), ::toupper);

    // Get and validate arrival airport input
    arrivalAirport = InputValidator::validateInput(
        "\nEnter arrival airport (3-letter code): ",
        "\nInvalid input. Please enter a three-letter code e.g. LAX.\n",
        std::regex("[a-z A-Z]{3}")
    );
    std::transform(arrivalAirport.begin(), arrivalAirport.end(), arrivalAirport.begin(), ::toupper);

    // Get and validate departure date input
    departureDate.readDate("departure");

    // Get and validate departure time input
    departureTime.readTime("departure");

    // Get and validate arrival date input
    arrivalDate.readDate("arrival");

    // Get and validate arrival time input
    arrivalTime.readTime("arrival");

    // Get and validate flight cost input
    cost = std::stod(InputValidator::validateInput(
        "\nEnter flight cost: ",
        "\nInvalid input. Please enter a numeric value.\n",
        std::regex("\\d+")
    ));

    // Finalize booking based on user input
    return finalizeBooking(customer, cost);
}

// Function to process payment for the flight
bool Flight::processPayment(Customer& customer, double flightPrice) {
    // Create a Bank object for payment processing
    Bank bank;
    // Validate the credit card
    if (!bank.validateCreditCard()) {
        return false;
    } else {
        // Check if the customer has sufficient balance
        if(customer.getBalance() < flightPrice){
            // If balance is insufficient, notify the customer and return false
            bank.sendTextMessage("AIB Bank", "Insufficient Balance, Transaction failed");
            std::cout << "\nCustomer Balance: " << customer.getBalance() << "\n" << std::endl;
            return false;
        }
        // If payment is successful, update customer balance and print ticket
        std::cout << "\nBooking finalized successfully!" << std::endl;
        std::cout << "\nCustomer Balance Before: " << customer.getBalance() << std::endl;
        customer.setBalance(-flightPrice);
        std::cout << "\nCustomer Balance After: " << customer.getBalance() << "\n\n";

        // Use the current Flight object's data to create a Ticket
        Ticket ticket(*this);

        // Create a Ticket object and print the ticket details
        ticket.printTicket(customer.getFirstName());
        return true;
    }
}

// Getters for Flight class attributes
std::string Flight::getFlightClass() const {
    return flightClass;
}

std::string Flight::getDepartureAirport() const {
    return departureAirport;
}

std::string Flight::getArrivalAirport() const {
    return arrivalAirport;
}
Date Flight::getDepartureDate() const {
    return departureDate;
}

FlightTime Flight::getDepartureTime() const {
    return departureTime;
}

FlightTime Flight::getArrivalTime() const {
    return arrivalTime;
}

Date Flight::getArrivalDate() const {
    return arrivalDate;
}
double Flight::getCost() const {
    return cost;
}
