#include "Person.h"

Person::Person(const std::string& fn, const std::string& ln, const std::string& ph)
	: firstName(fn), lastName(ln), phone(ph) {
}

Person::~Person() = default;

