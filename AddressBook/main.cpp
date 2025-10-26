#include <iostream>
#include <utility>

#include "Student.h"
#include "Teacher.h"
#include "Colleague.h"
#include "AddressBook.h"
#include "Interface.h"
#include "FileManager.h"

int main()
{
	AddressBook addrBook;
	FileManager fm("contacts.txt");

	/*
	Test file already exists
	
	~\contacts.txt
	Student | Al | Tor | 1234 | Dance
	Teacher | Ben | Lock | 0974 | Math
	Bug | Jonhy | Crash | 0666 | Virus

	Colleague | Ann | Lee | 5551 | Biology
	*/

	// Load existing
	auto loaded = fm.load();
	for (auto& person : loaded)
	{
		addrBook.addPerson(std::move(person));
	}

	std::cout << "Welcome to Address Book application!\n";
	Interface ui(addrBook);
	ui.run();

	// Save on exit
	if (fm.save(addrBook.getAll()))
	{
		std::cout << "Contacts saved to contacts.txt\n";
	}
	else
	{
		std::cout << "Error: Failed to save contacts.\n";
	}

	return 0;
}
