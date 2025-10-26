#include <string>

#include "SearchByPhone.h"
#include "Person.h"

bool SearchByPhone::matches(const Person& p, const std::string& q) const {
	return p.getPhone().find(q) != std::string::npos;
}

