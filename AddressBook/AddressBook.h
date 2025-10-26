#pragma once

#include <string>
#include <vector>
#include <memory>

#include "SearchStrategy.h"

class Person;

class AddressBook
{
private:
	std::vector<std::unique_ptr<Person>> contacts;
	std::unique_ptr<SearchStrategy> strategy;

public:
	AddressBook() = default;
	~AddressBook() = default;

	size_t size() const { return contacts.size(); }

	void addPerson(std::unique_ptr<Person> person);
	bool edit(size_t idx, std::unique_ptr<Person> p);
	bool remove(size_t idx);

	const Person* get(size_t idx) const {
		if (idx >= contacts.size()) return nullptr;
		return contacts[idx].get();
	}

	void listPeople() const;

	const std::vector<std::unique_ptr<Person>>& getAll() const { return contacts; }

	void setStrategy(std::unique_ptr<SearchStrategy> s);
	std::vector<size_t> find(const std::string& q) const;
};

