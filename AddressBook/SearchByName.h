#pragma once

#include "SearchStrategy.h"

struct SearchByName : SearchStrategy
{
	bool matches(const Person& p, const std::string& q) const override;
};

