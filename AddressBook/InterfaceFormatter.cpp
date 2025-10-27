#include <type_traits>
#include <typeinfo>
#include <sstream>

#include "InterfaceFormatter.h"
#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Colleague.h"

namespace InterfaceFormatter
{
	std::string format(const Student& s) {
		std::ostringstream os;
		os << "" <<  s.getRole() << " - Name: " << s.getFirstName() << ' ' << s.getLastName()
			<< ", Phone: " << s.getPhone()
			<< ", Major: " << s.getMajor() <<  "";
		return os.str();
	}

	std::string format(const Teacher& t) {
		std::ostringstream os;
		os << "Teacher - Name: " << t.getFirstName() << ' ' << t.getLastName()
			<< ", Phone: " << t.getPhone()
			<< ", Subject: " << t.getSubject() << "";
		return os.str();
	}

	std::string format(const Colleague& c) {
		std::ostringstream os;
		os << "Colleague - Name: " << c.getFirstName() << ' ' << c.getLastName()
			<< ", Phone: " << c.getPhone()
			<< ", Company: " << c.getCompany() << "";
		return os.str();
	}

	std::string format(const Person& p) {
		if (auto s = dynamic_cast<const Student*>(&p))   return format(*s);
		if (auto t = dynamic_cast<const Teacher*>(&p))   return format(*t);
		if (auto c = dynamic_cast<const Colleague*>(&p)) return format(*c);

		std::ostringstream os;
		os << "" << p.getRole() << " - Name: " << p.getFirstName() << ' ' << p.getLastName()
			<< ", Phone: " << p.getPhone() << "";
		return os.str();
	}
}

