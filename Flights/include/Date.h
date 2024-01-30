#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include "InputValidator.h"
class Date
{
public:
    // Constructors
    Date();                 // Default constructor
    Date(int, int, int);    // Parameterized constructor

    Date readDate(std::string); // Method to read and validate a date from user input
    void printDate() const;       // Method to print the date to the console
    bool validateDateFormat(); // Method to validate the date format
    std::string getDate() const;   // Method to get the date as a string

private:
    // Member variables
    int day, month, year;

};

#endif // DATE_H
