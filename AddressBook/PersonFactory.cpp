#include <algorithm>
#include <cctype>

#include "PersonFactory.h"
#include "Student.h"
#include "Teacher.h"
#include "Colleague.h"

std::unique_ptr<Person> PersonFactory::create(
	const std::string& role,
	const std::string& fn,
	const std::string& ln,
	const std::string& ph,
	const std::string& extra) {
	std::string r = role;
	std::transform(r.begin(), r.end(), r.begin(), 
		[](unsigned char c){ return static_cast<char>(std::tolower(c)); });
	
	if (r == "student")  return std::make_unique<Student>(fn, ln, ph, extra);
	if (r == "teacher")  return std::make_unique<Teacher>(fn, ln, ph, extra);
	if (r == "colleague") return std::make_unique<Colleague>(fn, ln, ph, extra);
	return nullptr;
}

