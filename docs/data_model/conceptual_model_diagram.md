# Conceptual Model Diagram

**Project:** Console Application "Address Book"  
**Version:** 1.0  
**Date:** 2025-01-01  
**Author:** Developer  

## PlantUML Diagram 

Save the following script as `docs/data_model/address_book.puml` and generate PNG/SVG:

```
@startuml
title Address Book – Layered UML Class Diagram (Uniform)

skinparam classAttributeIconSize 0
skinparam shadowing false
skinparam linetype ortho
skinparam packageStyle rectangle

' Optional subtle colors for layers (keep uniform/clean)
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
  }

  package "Application (Logic) Layer" <<Layer>> {
    class AddressBook {
      - contacts : vector< unique_ptr<Person> >
      - strategy : unique_ptr<SearchStrategy> [0..1]
      + addPerson(p : unique_ptr<Person>) : void
      + listPeople() : void
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
      + serialize() : string <<abstract>>
      + printInfo() : void <<abstract>>
      + getFirstName() : const string&
      + getLastName()  : const string&
      + getPhone()     : const string&
    }

    class Student {
      - major : string
      + getRole() : string
      + serialize() : string
      + printInfo() : void
    }

    class Teacher {
      - subject : string
      + getRole() : string
      + serialize() : string
      + printInfo() : void
    }

    class Colleague {
      - company : string
      + getRole() : string
      + serialize() : string
      + printInfo() : void
    }

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

  ' --- Cross-layer relationships (top-down, minimal) ---

  ' UI controls Application
  Interface --> AddressBook : controls

  ' UI selects concrete search strategies
  Interface ..> SearchByName : selects
  Interface ..> SearchByPhone : selects

  ' Application uses strategy (polymorphic)
  AddressBook ..> SearchStrategy : uses (optional)

  ' Composition: AddressBook owns Person entries
  AddressBook "1" *-- "*" Person : owns

  ' Persistence constructs domain objects on load
  FileManager ..> PersonFactory : uses (create on load)
  FileManager ..> Person : reads/writes serialize()

  ' Composition root (startup/shutdown wiring)
  Main ..> FileManager : load/save
  Main ..> AddressBook : injects data
  Main ..> Interface : runs UI
}

legend left
  Packages denote architectural layers (<<Layer>>).
  Allowed directions:
    Presentation -> Application
    Application  -> Domain
    Presentation -> Persistence
    Persistence  -> Domain
  Domain has no upward dependencies.
endlegend

@enduml
```

