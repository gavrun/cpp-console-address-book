#include <iostream>

#include "Student.h"
#include "Teacher.h"
#include "Colleague.h"
#include "AddressBook.h"

int main()
{
	std::cout << "Address Book - bootstrap = OK\n" << std::endl;

	Student s("Al", "Tor", "1234", "Dance");
	Teacher t("Ben", "Lock", "0974", "Math");
	Colleague c("Ann", "Lee", "5551", "Biology");

	s.printInfo();
	t.printInfo();
	c.printInfo();

	std::cout << "Address Book - Domain storage + CRUD basic = OK\n" << std::endl;

	AddressBook book;
	book.addPerson(std::make_unique<Student>("Ban", "Cock", "0666", "Anatomy"));
	book.listPeople();
	book.remove(0);
	book.listPeople();

	return 0;
}
