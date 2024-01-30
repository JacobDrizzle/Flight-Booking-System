#ifndef FLIGHTTIME_H
#define FLIGHTTIME_H

#include <string>

class FlightTime {
public:
    // Constructors
    FlightTime();            // Default constructor
    FlightTime(int h, int m); // Parameterized constructor

    // Public methods
    FlightTime readTime(std::string);      // Method to read and validate a FlightTime from user input

    void setHours(int h);     // Setter for hours
    void setMinutes(int m);   // Setter for minutes
    int getHours() const;     // Getter for hours
    int getMinutes() const;   // Getter for minutes

    bool validateFlightTimeFormat() const; // Method to validate the format of FlightTime
    std::string getFlightTimeString() const; // Method to get the FlightTime as a string

private:
    int hours;   // Private member variable for hours
    int minutes; // Private member variable for minutes
};

#endif // FLIGHTTIME_H
