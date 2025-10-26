#pragma once

#include "AddressBook.h"

class Interface
{
	AddressBook& book;

private:
	void addStudent();
	void addTeacher();
	void addColleague();
	void findMenu();
	void removeMenu();
	void editMenu();

public:
	explicit Interface(AddressBook& addressBook);

	void run();
};

