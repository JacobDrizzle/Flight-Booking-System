#include "Date.h"
#include <iostream>
#include <regex>

Date::Date() {} // Default constructor

Date::Date(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

// Method to validate the date format
bool Date::validateDateFormat() {
    // For simplicity, check that day, month, and year are within reasonable ranges
    return (day >= 1 && day <= 31) && (month >= 1 && month <= 12) && (year >= 2023);
}

// Method to get the date as a string in the format "dd/mm/yyyy"
std::string Date::getDate() const {
    std::string date = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    return date;
}

// Method to print the date to the console
void Date::printDate() const {
    std::cout << this->day << "/" << this->month << "/" << this->year;
}

// Method to read and validate a date from the user input
Date Date::readDate(std::string dateType) {
    std::string date;

    bool dateOK;
    do {
        date = InputValidator::validateInput(
            "\nEnter " + dateType + " date (dd/mm/yyyy): ",
            "\nInvalid date format. Please enter a valid date (dd/mm/yyyy)\n",
            std::regex("\\d{2}/\\d{2}/\\d{4}")
        );


        // Extract day, month, and year from the input
        this->day = stoi(date.substr(0, 2));
        this->month = stoi(date.substr(3, 2));
        this->year = stoi(date.substr(6, 4));

        // Check if the input matches the expected format
        dateOK = validateDateFormat();

        if (!dateOK) {
            std::cout << "\nInvalid date format. Please enter a valid date (dd/mm/yyyy)\n";
            continue;  // Repeat the loop
        }
    } while (!dateOK);

    return *this;
}
