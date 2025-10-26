#pragma once

#include <memory>
#include <string>

class Person;

class PersonFactory
{
public:
	static std::unique_ptr<Person> create(
		const std::string& role,
		const std::string& fn,
		const std::string& ln,
		const std::string& ph,
		const std::string& extra
	);
};

