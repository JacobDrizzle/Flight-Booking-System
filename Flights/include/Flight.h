#ifndef FLIGHT_H
#define FLIGHT_H

#include "Date.h"
#include "Bank.h"
#include "FlightTime.h"
#include "Customer.h"
#include "Time.h"
#include "InputValidator.h"

#include <iostream>
#include <string>
#include <regex>

class Flight {
protected:
    // Variables
    std::string flightClass;      // Class of the flight (Economy/Business)
    std::string departureAirport; // Departure airport code
    std::string arrivalAirport;   // Arrival airport code
    Date departureDate;           // Departure date
    Date arrivalDate;             // Arrival date
    FlightTime departureTime;     // Departure time
    FlightTime arrivalTime;       // Arrival time
    double cost;                  // Cost of the flight

public:

    // Default constructor
    Flight();

    // Parameterized constructor to initialize Flight object with specific values
    Flight(const std::string& fClass, const std::string& depAirport, Date& depDate,
           FlightTime& depTime, const std::string& arrAirport, Date& arrDate,
           FlightTime& arrTime, double flightCost);

    // Methods
    // Function to get and validate user input based on a given pattern
    std::string getAndValidateInput(const std::string& prompt, const std::string& errorMessage, const std::string& codePattern);

    bool inputFlightDetails(Customer& customer); // Main function to input flight details and finalize booking
    bool finalizeBooking(Customer& customer, double cost);  // Function to finalize booking based on user choice
    bool processPayment(Customer& customer, double flightCost); // Function to process payment for the flight


    // Getters
    std::string getFlightClass() const; // Getter for flight class
    std::string getDepartureAirport() const; // Getter for departure airport code
    std::string getArrivalAirport() const; // Getter for arrival airport code
    double getCost() const; // Getter for flight cost

    Date getDepartureDate() const; // Getter for departure date
    FlightTime getDepartureTime() const; // Getter for departure time
    Date getArrivalDate() const; // Getter for arrival date
    FlightTime getArrivalTime() const; // Getter for arrival time

};
#endif // FLIGHT_H
