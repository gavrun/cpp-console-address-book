#pragma once

#include <string>

#include "Person.h"

class Student : public Person
{
	std::string major;

public:
	Student(const std::string& fn, const std::string& ln, const std::string& ph, const std::string& maj);

	std::string getRole() const override;
	std::string serialize() const override;
	void printInfo() const override;
};

