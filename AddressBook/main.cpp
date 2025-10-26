#include <iostream>

#include "Student.h"
#include "Teacher.h"
#include "Colleague.h"
#include "AddressBook.h"
#include "Interface.h"

int main()
{
	std::cout << "Address Book - bootstrap = OK\n" << std::endl;

	Student s("Al", "Tor", "1234", "Dance");
	Teacher t("Ben", "Lock", "0974", "Math");
	Colleague c("Ann", "Lee", "5551", "Biology");

	s.printInfo();
	t.printInfo();
	c.printInfo();

	std::cout << std::endl;

	std::cout << "Address Book - Domain storage + CRUD basic = OK\n" << std::endl;
	
	AddressBook bookTmp;

	bookTmp.addPerson(std::make_unique<Student>("Ban", "Cock", "0666", "Anatomy"));
	bookTmp.listPeople();
	bookTmp.remove(0);
	bookTmp.listPeople();

	std::cout << std::endl;

	std::cout << "Address Book - Strategy search + Interface(UI) = OK\n" << std::endl;

	AddressBook addrBook;
	std::cout << "Welcome to Address Book application!\n"; // move to run()
	Interface ui(addrBook);
	ui.run();

	return 0;
}
