#include <algorithm>
#include <string>

#include "SearchByName.h"
#include "Person.h"

static std::string toLower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return static_cast<char>(std::tolower(c)); });
	return s;
}

bool SearchByName::matches(const Person& p, const std::string& q) const {
	std::string first = toLower(p.getFirstName());
	std::string last = toLower(p.getLastName());
	std::string full = first + " " + last;
	std::string fullNoSpace = first + last;

	std::string query = toLower(q);

	return (!query.empty()) && (
		first.find(query) != std::string::npos ||
		last.find(query) != std::string::npos ||
		full.find(query) != std::string::npos ||
		fullNoSpace.find(query) != std::string::npos
		);
}

