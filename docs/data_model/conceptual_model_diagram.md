# Conceptual Model Diagram

**Project:** Console Application "Address Book"  
**Version:** 1.0  
**Date:** 2025-01-01  
**Author:** Developer  

## PlantUML 

Paste the following script to `https://www.plantuml.com/plantuml/uml/` and generate a Class Diagram and PNG/SVG:


## Class Diagram (refactored)

```
@startuml
title Address Book – Layered UML Class Diagram (Refactored)

skinparam classAttributeIconSize 0
skinparam shadowing false
skinparam linetype ortho
skinparam packageStyle rectangle
skinparam package {
  BackgroundColor<<Layer>> #F9F9F9
  BorderColor #999999
}
skinparam class {
  BackgroundColor White
  BorderColor #666666
}

package "Application" {
  package "Presentation Layer (UI)" <<Layer>> {
    class Main {
      + main() : int
    }
    class Interface {
      - book : AddressBook&
      + run() : void
      .. helpers ..
      - addStudent() : void
      - addTeacher() : void
      - addColleague() : void
      - findMenu() : void
      - editMenu() : void
      - removeMenu() : void
    }

    class InterfaceFormatter {
      + format(p : Person) : string
      + format(s : Student) : string
      + format(t : Teacher) : string
      + format(c : Colleague) : string
    }
  }

  package "Application (Logic) Layer" <<Layer>> {
    class AddressBook {
      - contacts : vector< unique_ptr<Person> >
      - strategy : unique_ptr<SearchStrategy> [0..1]
      + addPerson(p : unique_ptr<Person>) : void
      + setStrategy(s : unique_ptr<SearchStrategy>) : void
      + find(q : string) : vector<size_t>
      + edit(index : size_t, p : unique_ptr<Person>) : bool
      + remove(index : size_t) : bool
      + get(index : size_t) : const Person*
      + size() : size_t
      + getAll() : const vector< unique_ptr<Person> >&
    }

    interface SearchStrategy {
      + matches(p : Person, q : string) : bool
    }

    class SearchByName {
      + matches(p : Person, q : string) : bool
    }

    class SearchByPhone {
      + matches(p : Person, q : string) : bool
    }

    SearchStrategy <|.. SearchByName
    SearchStrategy <|.. SearchByPhone
  }

  package "Domain Model" <<Layer>> {
    abstract class Person {
      - firstName : string
      - lastName  : string
      - phone     : string
      + getRole() : string <<abstract>>
      + getFirstName() : const string&
      + getLastName()  : const string&
      + getPhone()     : const string&
      + serialize() : string <<abstract>>
    }

    class Student {
      - major : string
      + getRole() : string
      + getMajor() : const string&
      + serialize() : string
    }

    class Teacher {
      - subject : string
      + getRole() : string
      + getSubject() : const string&
      + serialize() : string
    }

    class Colleague {
      - company : string
      + getRole() : string
      + getCompany() : const string&
      + serialize() : string
    }
    
    ' Inheritance
    Person <|-- Student
    Person <|-- Teacher
    Person <|-- Colleague
  }

  package "Data Access (Persistence) Layer" <<Layer>> {
    class FileManager {
      - filePath : string
      + load() : vector< unique_ptr<Person> >
      + save(v : const vector< unique_ptr<Person> >& ) : bool
    }

    class PersonFactory {
      + create(role : string, fn : string, ln : string, ph : string, extra : string) : unique_ptr<Person>
    }
  }

  ' --- Cross-layer relationships (dependencies / uses) ---

  Interface --> AddressBook : uses
  Interface ..> SearchByName : selects
  Interface ..> SearchByPhone : selects
  
  ' Composition / aggregation
  AddressBook ..> SearchStrategy : uses (optional)
  AddressBook "1" *-- "*" Person : owns

  FileManager ..> PersonFactory : uses
  FileManager ..> Person : uses serialize (load/save)

  PersonFactory ..> Person : create

  Interface ..> InterfaceFormatter : uses
  
  InterfaceFormatter ..> Person : formats
  InterfaceFormatter ..> Student
  InterfaceFormatter ..> Teacher
  InterfaceFormatter ..> Colleague

  Main ..> FileManager : load/save
  Main ..> AddressBook : injects data
  Main ..> Interface : runs UI
}

legend left
  Packages denote architectural layers (<<Layer>>).
  Separation of Concerns between UI, Core, I/O, and Search.
  Open/Closed Principle.
  Extensible UI layer decoupled from core logic.
endlegend
@enduml
```
