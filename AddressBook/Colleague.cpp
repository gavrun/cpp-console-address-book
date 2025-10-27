#include <iostream>

#include "Colleague.h"

Colleague::Colleague(const std::string& fn, const std::string& ln, const std::string& ph, const std::string& comp)
    : Person(fn, ln, ph), company(comp) {
}

std::string Colleague::getRole() const { return "Colleague"; }

const std::string& Colleague::getCompany() const { return company; }

std::string Colleague::serialize() const {
    return "Colleague|" + firstName + "|" + lastName + "|" + phone + "|" + company;
}

