#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H


#include <iostream>
#include <regex>

class InputValidator {
public:
    // Validate input based on regex pattern
    static std::string validateInput(const std::string& prompt, const std::string& errorMessage, const std::regex& pattern) {
        std::string userInput;
        bool isValid;

        do {
            std::cout << prompt;
            std::cin >> userInput;
            isValid = std::regex_match(userInput, pattern);

            if (!isValid) {
                std::cout << errorMessage;
            }

        } while (!isValid);

        return userInput;
    }
};

#endif // INPUTVALIDATOR_H
