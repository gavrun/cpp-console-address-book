#pragma once

#include <string>

#include "Person.h"

class Teacher : public Person
{
	std::string subject;

public:
    Teacher(const std::string& fn, const std::string& ln, const std::string& ph, const std::string& subj);

    std::string getRole() const override;

    const std::string& getSubject() const;

    std::string serialize() const override;
};

