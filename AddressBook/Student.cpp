#include <iostream>

#include "Student.h"

Student::Student(const std::string& fn, const std::string& ln, const std::string& ph, const std::string& maj)
	: Person(fn, ln, ph), major(maj) {
}

std::string Student::getRole() const { return "Student"; }

const std::string& Student::getMajor() const { return major; }

std::string Student::serialize() const {
	return "Student|" + firstName + "|" + lastName + "|" + phone + "|" + major;
}

