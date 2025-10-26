#include <iostream>

#include "Student.h"

Student::Student(const std::string& fn, const std::string& ln, const std::string& ph, const std::string& maj)
	: Person(fn, ln, ph), major(maj) {
}

std::string Student::getRole() const { return "Student"; }

std::string Student::serialize() const {
	return "Student|" + firstName + "|" + lastName + "|" + phone + "|" + major;
}

void Student::printInfo() const {
	std::cout << "Student - Name: " << firstName << " " << lastName
		      << ", Phone: " << phone
		      << ", Major: " << major << std::endl;
}

