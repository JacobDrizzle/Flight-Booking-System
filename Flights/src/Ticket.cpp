#include "Ticket.h"
#include <iomanip>
// Constructor implementation
Ticket::Ticket(const Flight& flight) : Flight(flight){}

// Member function to print the ticket details
void Ticket::printTicket(const std::string& customerName) const {
    // Format the date and time for booking code
    std::string formattedTime = this->departureDate.getDate();
    size_t slashPosition = formattedTime.find('/');
    while (slashPosition != std::string::npos) {
        formattedTime.replace(slashPosition, 1, ""); // Remove slashes from the date
        slashPosition = formattedTime.find('/');
    }

    std::cout << "Booking Confirmation Message.\n";
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    // Print booking confirmation details
    std::cout << "\nMessage sent on: " << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
    std::cout << "\nSender: Morrison's Island Getaways\n";
    std::cout << "\nBooking Code: MIG" << formattedTime << this->getDepartureAirport() << this->arrivalAirport << "\n";
    std::cout << "\nNAME:<" << customerName << ">\tCLASS:<" << this->flightClass << ">\t\tCOST:<" << this->cost << ">\n";
    std::cout << "\nDEPARTING" << "\tDATE" << "\t\t\tTIME\n";
    std::cout << "\n<" << this->departureAirport << ">\t\t<" << this->departureDate.getDate() << ">\t\t<" << this->departureTime.getFlightTimeString() << ">\n";
    std::cout << "\nARRIVING" << "\tDATE" << "\t\t\tTIME\n";
    std::cout << "\n<" << this->arrivalAirport << ">\t\t<" << this->arrivalDate.getDate() << ">\t\t<" << this->arrivalTime.getFlightTimeString() << ">\n\n";
}
