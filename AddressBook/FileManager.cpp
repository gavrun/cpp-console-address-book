#include <fstream>
#include <sstream>
#include <iostream>

#include "FileManager.h"
#include "PersonFactory.h"
#include "Person.h"

std::vector<std::unique_ptr<Person>> FileManager::load() const {
	std::vector<std::unique_ptr<Person>> out;

	std::ifstream in(filePath);
	if (!in) return out;

	std::string line;
	while (std::getline(in, line))
	{
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string	type, fn, ln, ph, extra;

		bool wellFormed = (
			std::getline(ss, type, '|') &&
			std::getline(ss, fn, '|') &&
			std::getline(ss, ln, '|') &&
			std::getline(ss, ph, '|') &&
			std::getline(ss, extra)
			);

		if (wellFormed)
		{
			auto p = PersonFactory::create(type, fn, ln, ph, extra);
			if (p) out.push_back(std::move(p));
			else std::cerr << "Warning: unknown type '" << type << "'\n";
		}
		else
		{
			std::cerr << "Warning: malformed line: " << line << "\n";
		}
	}
	return out;
}

bool FileManager::save(const std::vector<std::unique_ptr<Person>>& people) const {
	std::ofstream out(filePath);

	if (!out) return false;

	for (const auto& p : people)
	{
		out << p->serialize() << "\n";
	}
	return true;
}

