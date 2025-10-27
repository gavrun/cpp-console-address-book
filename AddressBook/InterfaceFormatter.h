#pragma once

#include <string>

class Person;
class Student;
class Teacher;
class Colleague;

namespace InterfaceFormatter
{
    std::string format(const Student& s);
    std::string format(const Teacher& t);
    std::string format(const Colleague& c);

    std::string format(const Person& p);
};

