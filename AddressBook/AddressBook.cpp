#include <iostream>

#include "Student.h"
#include "Teacher.h"
#include "Colleague.h"

int main()
{
	std::cout << "Address Book - bootstrap OK\n" << std::endl;

	Student s("Al", "Tor", "1234", "Dance");
	Teacher t("Ben", "Lock", "0974", "Math");
	Colleague c("Ann", "Lee", "5551", "Biology");

	s.printInfo();
	t.printInfo();
	c.printInfo();
}

