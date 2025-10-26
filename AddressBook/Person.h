#pragma once

#include <string>

class Person
{
protected:
	std::string firstName;
	std::string lastName;
	std::string phone;

public:
	Person(const std::string& fn, const std::string& ln, const std::string& ph);
	virtual ~Person();

	virtual std::string getRole() const = 0;
	virtual std::string serialize() const = 0;
	virtual void printInfo() const = 0;

	const std::string& getFirstName() const { return firstName; }
	const std::string& getLastName() const { return lastName; }
	const std::string& getPhone() const { return phone; }
};

