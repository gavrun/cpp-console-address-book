#pragma once

#include <string>

#include "Person.h"

class Colleague : public Person
{
	std::string company;

public:
    Colleague(const std::string& fn, const std::string& ln, const std::string& ph, const std::string& comp);

    std::string getRole() const override;

    const std::string& getCompany() const;

    std::string serialize() const override;
};

