#pragma once

#include <string>

class Person;

struct SearchStrategy
{
	virtual bool matches(const Person& p, const std::string& q) const = 0;

	virtual ~SearchStrategy() = default;
};

