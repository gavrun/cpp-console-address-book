# Architecture Overview

**Project:** Console Application "Address Book"  
**Version:** 1.0  
**Date:** 2025-01-01  
**Author:** Developer  

## 1. Architectural Patterns

The system follows a **Layered Architecture (3-layer pattern)**:

1. **Presentation Layer (UI Layer)**  
- Component: ConsoleUI  
- Responsibilities:
  - Render console menu and prompts
  - Collect and validate user input
  - Invoke application services 
  - Display results and error messages

2. **Application (Logic) Layer**  
- Components: AddressBook, SearchStrategy (interface), SearchByName, SearchByPhone  
- Responsibilities:
  - Orchestrate operations: add, edit, list, search, remove
  - Maintain in-memory collection of contacts (composition/ownership)
  - Select and apply search strategies 
  - Collaborate with persistence and factory to load/save/create entities

3. **Data Access Layer (Persistence)**  
- Components: FileManager, PersonFactory  
- Responsibilities:
  - Read/write records to a local text file 
  - Parse and serialize records using a simple delimiter-based format
  - Construct concrete Person objects based on record type 

## 2. Design Patterns

Design patterns:
- Strategy: pluggable search behavior (SearchStrategy with SearchByName/SearchByPhone)
- Factory Method: centralized construction of Student/Teacher/Colleague from type token

Ownership model:
- AddressBook holds contacts via std::unique_ptr<Person> (composition and RAII)

## 4. Design Principles

- Separation of Concerns: UI, application logic, and persistence are isolated.
- Single Responsibility: each class has a focused purpose (e.g., FileManager only I/O).
- Encapsulation: internal state hidden behind class interfaces.
- RAII & Memory Safety: std::unique_ptr for ownership, no manual delete.
- Open/Closed: strategies and person types can be extended without modifying core flows.
- Simplicity: straightforward data format, minimal dependencies.

## 3. Technology Stack 

| Component | Technology |
|------------|-------------|
| Language | C++ (C++11 or higher) |
| Compiler | MSVC |
| Build system | Manual compilation or simple Makefile |
| Data storage | Local text file (`contacts.txt`) |
| Libraries | Standard C++ STL |

## 4. Project Structure 

```
address_book/
│
├── src/
│   ├── main.cpp                  # Entry point (creates AddressBook, loads/saves, runs ConsoleUI)
│   ├── AddressBook.cpp           # Application logic (CRUD, search integration, ownership)
│   ├── Interface.cpp             # ConsoleUI (menu, input handling)
│   ├── FileManager.cpp           # Persistence (load/save)
│   ├── Person.cpp                # Base abstract class impl (ctor/dtor)
│   ├── Student.cpp               # Derived type (serialize/printInfo)
│   ├── Teacher.cpp
│   ├── Colleague.cpp
│   ├── PersonFactory.cpp         # Factory Method (create by type)
│   ├── SearchStrategy.cpp        # Interface TU
│   ├── SearchByName.cpp          # Strategy: name searching
│   └── SearchByPhone.cpp
│
├── include/
│   ├── AddressBook.h
│   ├── Interface.h               # ConsoleUI
│   ├── FileManager.h
│   ├── Person.h                  # Abstract base
│   ├── Student.h
│   ├── Teacher.h
│   ├── Colleague.h
│   ├── PersonFactory.h
│   ├── SearchStrategy.h
│   ├── SearchByName.h
│   └── SearchByPhone.h
│
├── data/
│   └── contacts.txt              # Flat data file
│
├── docs/
│   ├── analysis/
│   │   ├── business_scenario.md
│   │   └── software_requirements.md
│   ├── architecture/
│   │   └── architecture_overview.md
│   ├── data_model/
│   │   ├── conceptual_model.md
│   │   └── conceptual_model_diagram.md
│   └── planning/
│       └── development_plan_tasks.md
│
├── CMakeLists.txt (optional)
└── README.md
```

## 5. Key Components and Responsibilities

- Person (abstract)
  - Fields: firstName, lastName, phone
  - API: virtual getRole(), serialize(), printInfo()
- Student / Teacher / Colleague
  - Role-specific field: major / subject / company
  - Implement getRole()/serialize()/printInfo()
- AddressBook
  - Owns std::vector
  - CRUD: addPerson, edit, remove, listPeople
  - Search: setStrategy, find(query) → vector<size_t>
  - Safe access: get(index), size()
- SearchStrategy (interface)
  - matches(const Person&, const std::string&) → bool
  - Implementations: SearchByName (case-insensitive), SearchByPhone (substring)
- PersonFactory (Factory Method)
  - create(role, fn, ln, ph, extra) → std::unique_ptr<Person>
- FileManager (Persistence)
  - load() → vector (skips malformed/unknown with warnings)
  - save(const vector&) → bool (overwrites file)
- ConsoleUI (Presentation)
  - run(): menu loop
  - Operations: add student/teacher/colleague, list, find, edit, remove, quit
  - Validates input; never crashes on invalid data; re-prompts as needed

## 9. Extensibility 

- New role type:
  - Add subclass (e.g., Friend), update PersonFactory::create()
  - Ensure serialize()/printInfo() implemented
- New search behavior:
  - Implement new SearchStrategy (e.g., SearchByEmail), use via setStrategy()
- Alternate storage:
  - Replace FileManager with CSV/JSON version with the same API
- Additional fields:
  - Extend domain classes and serialization format (versioning out of current scope)

## 7. Example Workflows

Add Contact (Student):
1) User selects [S] Add Student in ConsoleUI
2) ConsoleUI gathers firstName, lastName, phone (token inputs) and major (getline)
3) AddressBook.addPerson(std::make_unique<Student>(...))
4) ConsoleUI prints confirmation

Search by Name:
1) User selects [F], chooses [N]ame, enters query
2) ConsoleUI sets strategy = SearchByName
3) AddressBook.find(query) applies strategy over all Person entries
4) ConsoleUI prints matches with indices

Load/Save:
- At startup: FileManager.load() → vector of unique_ptr<Person>, each created via PersonFactory; AddressBook takes ownership
- At exit: FileManager.save(AddressBook.getAll())

## 11. Component Interaction (High-Level)

Data flow for typical operations:

```
User → ConsoleUI → AddressBook → (SearchStrategy or CRUD) → [FileManager on load/save] → contacts.txt
```

