#include <iostream>

#include "Teacher.h"

Teacher::Teacher(const std::string& fn, const std::string& ln, const std::string& ph, const std::string& subj)
	: Person(fn, ln, ph), subject(subj) {
}

std::string Teacher::getRole() const { return "Teacher"; }

const std::string& Teacher::getSubject() const { return subject; }

std::string Teacher::serialize() const {
    return "Teacher|" + firstName + "|" + lastName + "|" + phone + "|" + subject;
}

