#include "AddressBook.h"
#include "Person.h"

#include <iostream>

void AddressBook::addPerson(std::unique_ptr<Person> person) {
	contacts.push_back(std::move(person));
}

bool AddressBook::edit(size_t idx, std::unique_ptr<Person> p) {
	if (idx >= contacts.size()) return false;
	contacts[idx] = std::move(p);
	return true;
}

bool AddressBook::remove(size_t idx) {
	if (idx >= contacts.size()) return false;
	contacts.erase(contacts.begin() + idx);
	return true;
}

void AddressBook::listPeople() const {
	if (contacts.empty())
	{
		std::cout << "Address book is empty.\n";
		return;
	}
	std::cout << "Listing all contacts:\n";
	size_t idx = 0;
	for (const auto& p : contacts)
	{
		std::cout << "#" << idx++ << ": ";
		p->printInfo();
	}
}

