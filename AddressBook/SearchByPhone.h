#pragma once

#include "SearchStrategy.h"

struct SearchByPhone : SearchStrategy
{
	bool matches(const Person& p, const std::string& q) const override;
};

