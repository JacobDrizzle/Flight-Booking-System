#include "FlightTime.h"
#include <iostream>
#include <regex>
#include <limits>
#include "InputValidator.h"

// Default constructor initializes hours and minutes to 0
FlightTime::FlightTime() : hours(0), minutes(0) {}

// Parameterized constructor to set specific hours and minutes
FlightTime::FlightTime(int h, int m) : hours(h), minutes(m) {}

// Method to read and validate a FlightTime from user input
FlightTime FlightTime::readTime(std::string timeType) {

    bool timeOK;

    do {
        std::string input = InputValidator::validateInput(
            "\nEnter " + timeType + " time (hh:mm): ",
            "\nInvalid time format. Please enter a valid time (hh:mm)\n",
            std::regex("\\d{2}:\\d{2}")
        );

        // Extract hours and minutes from the input
        try {
            this->hours = std::stoi(input.substr(0, 2));
            this->minutes = std::stoi(input.substr(3, 2));
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid time components. Please enter numeric values for hours and minutes: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            timeOK = false;  // Repeat the loop
        } catch (const std::out_of_range& e) {
            std::cout << "Time components out of range. Please enter valid values: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            timeOK = false;  // Repeat the loop
        }

        // Validate the format of FlightTime
        timeOK = validateFlightTimeFormat();

    } while (!timeOK);

    return *this;
}

// Setter for hours
void FlightTime::setHours(int h) {
    hours = h;
}

// Setter for minutes
void FlightTime::setMinutes(int m) {
    minutes = m;
}

// Getter for hours
int FlightTime::getHours() const {
    return hours;
}

// Getter for minutes
int FlightTime::getMinutes() const {
    return minutes;
}

// Method to validate the format of FlightTime
bool FlightTime::validateFlightTimeFormat() const {
    return (hours >= 0 && hours <= 23) && (minutes >= 0 && minutes <= 59);
}

// Method to get the FlightTime as a string in the format "hh:mm"
std::string FlightTime::getFlightTimeString() const {
    return std::to_string(hours) + ":" + (minutes < 10 ? "0" : "") + std::to_string(minutes);
}
