#include <cctype>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "Interface.h"
#include "Student.h"
#include "Teacher.h"
#include "Colleague.h"
#include "SearchByName.h"
#include "SearchByPhone.h"

Interface::Interface(AddressBook& addressBook) : book(addressBook) {}

void Interface::run() {
	char choice{};
	bool running = true;

	while (running)
	{
		std::cout << "\n=== Address Book Menu ===\n";
		std::cout << "[S] Add Student\n";
		std::cout << "[T] Add Teacher\n";
		std::cout << "[C] Add Colleague\n";
		std::cout << "[L] List all contacts\n";
		std::cout << "[F] Find (by name/phone)\n";
		std::cout << "[E] Edit by index\n";
		std::cout << "[R] Remove by index\n";
		std::cout << "[Q] Quit\n";
		std::cout << "Enter choice: ";

		if (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Input error. Please try again.\n";
			continue;
		}
		choice = static_cast<char>(std::toupper(static_cast<unsigned char>(choice)));
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice)
		{
		case 'S': addStudent(); break;
		case 'T': addTeacher(); break;
		case 'C': addColleague(); break;
		case 'L': book.listPeople(); break;
		case 'F': findMenu(); break;
		case 'E': editMenu(); break;
		case 'R': removeMenu(); break;
		case 'Q':
			std::cout << "Exiting program...\n";
			running = false;
			break;
		default:
			std::cout << "Invalid option. Please try again.\n";
		}
	}
}

void Interface::addStudent() {
	std::string fn, ln, ph, maj;
	std::cout << "Enter first name: "; std::cin >> fn;
	std::cout << "Enter last name: ";  std::cin >> ln;
	std::cout << "Enter phone: ";      std::cin >> ph;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter major: ";      std::getline(std::cin, maj);

	book.addPerson(std::make_unique<Student>(fn, ln, ph, maj));
	std::cout << "Student added to address book.\n";
}

void Interface::addTeacher() {
	std::string fn, ln, ph, subj;
	std::cout << "Enter first name: "; std::cin >> fn;
	std::cout << "Enter last name: ";  std::cin >> ln;
	std::cout << "Enter phone: ";      std::cin >> ph;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter subject: ";    std::getline(std::cin, subj);

	book.addPerson(std::make_unique<Teacher>(fn, ln, ph, subj));
	std::cout << "Teacher added to address book.\n";
}

void Interface::addColleague() {
	std::string fn, ln, ph, comp;
	std::cout << "Enter first name: "; std::cin >> fn;
	std::cout << "Enter last name: ";  std::cin >> ln;
	std::cout << "Enter phone: ";      std::cin >> ph;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter company: ";    std::getline(std::cin, comp);

	book.addPerson(std::make_unique<Colleague>(fn, ln, ph, comp));
	std::cout << "Colleague added to address book.\n";
}

void Interface::findMenu() {
	char how{};

	std::cout << "Find by [N]ame or [P]hone? ";
	if (!(std::cin >> how))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input error.\n";
		return;
	}
	how = static_cast<char>(std::toupper(static_cast<unsigned char>(how)));
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string query;
	std::cout << "Enter search query: ";
	std::getline(std::cin, query);

	if (how == 'N') book.setStrategy(std::make_unique<SearchByName>());
	else if (how == 'P') book.setStrategy(std::make_unique<SearchByPhone>());
	else
	{
		std::cout << "Unknown option.\n";
		return;
	}

	auto ids = book.find(query);
	if (ids.empty())
	{
		std::cout << "No matches.\n";
		return;
	}

	std::cout << "Matches:\n";
	for (auto idx : ids)
	{
		if (const Person* p = book.get(idx))
		{
			std::cout << "#" << idx << ": ";
			p->printInfo();
		}
	}
}

void Interface::removeMenu() {
	book.listPeople();

	std::cout << "Enter index to remove: ";
	size_t idx{};
	if (!(std::cin >> idx))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input error.\n";
		return;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (book.remove(idx)) std::cout << "Removed.\n";
	else std::cout << "Invalid index.\n";
}

void Interface::editMenu() {
	book.listPeople();

	std::cout << "Enter index to edit: ";
	size_t idx{};
	if (!(std::cin >> idx)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input error.\n";
		return;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (idx >= book.size())
	{
		std::cout << "Invalid index.\n"; 
		return;
	}

	char type{};

	std::cout << "New type: [S]tudent / [T]eacher / [C]olleague ? ";
	if (!(std::cin >> type)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input error.\n";
		return;
	}
	type = static_cast<char>(std::toupper(static_cast<unsigned char>(type)));
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string fn, ln, ph;
	std::cout << "Enter first name: "; std::cin >> fn;
	std::cout << "Enter last name: ";  std::cin >> ln;
	std::cout << "Enter phone: ";      std::cin >> ph;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::unique_ptr<Person> p;

	switch (type)
	{
	case 'S': {
		std::string maj;
		std::cout << "Enter major: ";
		std::getline(std::cin, maj);
		p = std::make_unique<Student>(fn, ln, ph, maj);
		break;
	}
	case 'T': {
		std::string subj;
		std::cout << "Enter subject: ";
		std::getline(std::cin, subj);
		p = std::make_unique<Teacher>(fn, ln, ph, subj);
		break;
	}
	case 'C': {
		std::string comp;
		std::cout << "Enter company: ";
		std::getline(std::cin, comp);
		p = std::make_unique<Colleague>(fn, ln, ph, comp);
		break;
	}
	default:
		std::cout << "Unknown type.\n"; 
		return;
	}

	if (book.edit(idx, std::move(p))) std::cout << "Edited.\n";
	else std::cout << "Invalid index.\n";
 }


