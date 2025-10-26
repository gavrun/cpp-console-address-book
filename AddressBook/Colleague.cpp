#include <iostream>

#include "Colleague.h"

Colleague::Colleague(const std::string& fn, const std::string& ln, const std::string& ph, const std::string& comp)
    : Person(fn, ln, ph), company(comp) {
}

std::string Colleague::getRole() const { return "Colleague"; }

std::string Colleague::serialize() const {
    return "Colleague|" + firstName + "|" + lastName + "|" + phone + "|" + company;
}

void Colleague::printInfo() const {
    std::cout << "Colleague - Name: " << firstName << " " << lastName
        << ", Phone: " << phone
        << ", Company: " << company << std::endl;
}

