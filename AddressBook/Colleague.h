#pragma once

#include <string>

#include "Person.h"

class Colleague : public Person
{
	std::string company;

public:
    Colleague(const std::string& fn, const std::string& ln, const std::string& ph, const std::string& comp);

    std::string getRole() const override;
    std::string serialize() const override;
    void printInfo() const override;
};

