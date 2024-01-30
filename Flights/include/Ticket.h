#ifndef TICKET_H
#define TICKET_H

#include "Flight.h"
#include <string>

class Ticket : public Flight
{
public:
    Ticket(const Flight& flight); // Constructor that takes a Flight object

    // Member function to print the ticket details
    void printTicket(const std::string& customerName) const;

private:
    // Cost of the flight
};

#endif // TICKET_H
