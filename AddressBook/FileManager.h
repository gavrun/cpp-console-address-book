#pragma once

#include <memory>
#include <string>
#include <vector>

class Person;

class FileManager
{
	std::string filePath;
public:
	explicit FileManager(std::string path) : filePath(std::move(path)) {}

	std::vector<std::unique_ptr<Person>> load() const;
	bool save(const std::vector<std::unique_ptr<Person>>& people) const;
};

