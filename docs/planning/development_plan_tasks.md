# Development Plan & Tasks 

This document outlines the main development phases and tasks for creating the working prototype of the **Console Address Book Application**.

## 1. Analysis & Design 

- Define functional and non-functional requirements 
- Identify main use cases (add, delete, edit, search, list contacts) 
- Create conceptual data model (classes, relationships) 
- Define architecture (layered pattern: UI, logic, data access) 
- Plan project file/folder structure 
- Plan project implementation stages 

## 2. Implementation - Bootstrap (Iteration 1)

**Goal:** 
- Project template and environment to start with

**Tasks:** 
- Project scaffolding in C++ (IDE or CMake).
- Baseline build configuration and run target (CMake or IDE project).
- Git repository initialization and README.
- Document initial plan and documentation folder layout.

**Deliverables:** 
- Compilable empty/skeleton project.
- Basic documentation (README, initial plan).

## 3. Implementation - Minimal Viable Prototype (Iteration 2) 

**Goal:** 
- Deliver the first usable prototype that runs entirely in memory and covers core CRUD for contacts.

**Tasks:** 
- Data model
  - Define minimal Contact (first name, last name, phone).
- Business logic
  - Implement AddressBook with vector-based storage (add, list, remove by index).
  - Optional: simple substring find by first/last name.
- Console UI
  - Loop with options: Add, List, Remove, (Find optional), Quit.
  - Input validation (clear and ignore bad input, bounds checking on indices).
- Quality
  - Basic error messages for invalid choices and indices.
  - Consistent, readable output formatting.

**Deliverables:** 
- Compilable prototype executable.
- Source:
  - main.cpp (entry)
  - AddressBook.[h|cpp] (simple implementation)
  - Contact.[h] or inline struct
  - Interface.[h|cpp] (basic menu)
- README updated with build/run instructions.

**Acceptance Criteria:**
- User can add multiple contacts and list them in the same run.
- User can remove by index; invalid index is handled gracefully.
- Program handles invalid input without crashing.
- Optional: basic find returns expected results for substring matches.

## 4. Implementation - Extend Architecture (Iteration 3) 

**Goal:** 
- Evolve the prototype into a modular, extensible architecture with strategies for search, factory-based object creation, and file persistence.

**Tasks:** 
- Core model
  - Implement Person base (virtual dtor, getters, pure virtual: getRole, serialize, printInfo).
  - Implement Student/Teacher/Colleague with extra field (major/subject/company).
  - Implement serialize for each subtype in format:
    - Student: `Student|First|Last|Phone|Major`
    - Teacher: `Teacher|First|Last|Phone|Subject`
    - Colleague: `Colleague|First|Last|Phone|Company`
- Business logic
  - Implement AddressBook:
    - Own contacts via `std::unique_ptr<Person>`.
    - Methods: addPerson, listPeople, edit(index, unique_ptr<Person>), remove(index).
    - Pluggable search: setStrategy(unique_ptr<SearchStrategy>), find(query).
    - Safe getters and size().
- Search strategies
  - Define SearchStrategy interface: `bool matches(const Person&, const std::string&) const`.
  - Implement SearchByName:
    - Case-insensitive substring against first, last, first+space+last, first+last.
  - Implement SearchByPhone:
    - Substring match on phone.
- Factory
  - Implement PersonFactory::create(role, fn, ln, ph, extra):
    - Case-insensitive role handling for "student", "teacher", "colleague".
    - Return correct concrete type or nullptr.
- Persistence
  - Implement FileManager(filePath):
    - load(): read each non-empty line, parse by `|`, use PersonFactory to construct; warn on malformed or unknown types.
    - save(): write each contact via `serialize()`.
  - Ensure robust handling when file does not exist (start with empty dataset).
- Console UI
  - Implement Interface(book) with menu:
    - [S] Add Student, [T] Add Teacher, [C] Add Colleague
    - [L] List
    - [F] Find (choose [N]ame or [P]hone, then query)
    - [E] Edit by index (select new type and fields)
    - [R] Remove by index
    - [Q] Quit
  - Input handling:
    - Use `std::cin.clear()` and `ignore()` on error.
    - Use `std::getline` for fields with spaces (extra fields).
    - Uppercase normalization for commands.
  - Display indices on list and match output.
- Entry point
  - main():
    - Instantiate AddressBook and FileManager("contacts.txt").
    - Load contacts on start.
    - Run Interface loop.
    - Save contacts on exit, report status.
- Quality and robustness
  - Consistent messages on success/failure.
  - Warnings for malformed data lines and unknown types.
  - No leaks; rely on RAII and `unique_ptr`.

**Deliverables:** 
- Source files:
  - main.cpp
  - Interface.[h|cpp]
  - AddressBook.[h|cpp]
  - FileManager.[h|cpp]
  - Person.[h|cpp], Student.[h|cpp], Teacher.[h|cpp], Colleague.[h|cpp]
  - PersonFactory.[h|cpp]
  - SearchStrategy.[h|cpp], SearchByName.[h|cpp], SearchByPhone.[h|cpp]
  - contacts.txt (sample data)
- Updated README with usage, format, and examples.

**Acceptance Criteria:**
- On startup, if contacts.txt exists, contacts are loaded; otherwise start empty.
- User can:
  - Add Student/Teacher/Colleague with appropriate extra field.
  - List all contacts with indices and readable output.
  - Find by name (case-insensitive substring) and by phone (substring).
  - Edit a contact by index, including changing its type.
  - Remove a contact by index.
- On exit, all changes are saved to contacts.txt.
- Program handles invalid inputs and malformed file lines gracefully (with warnings, without crash).

## N. Implementation - N (Iteration N) 

**Goal:** 
- Any number of potential iterations for implementing additional features

## 5. Testing

Manual testing steps: 
- Start the program and ensure the main menu appears  
- Add multiple contacts and verify they display correctly  
- Test deleting and editing contacts  
- Save contacts and restart the program to verify file persistence  
- Try invalid inputs and verify error messages  

## 6. Deployment 

- Package executable with sample data file  
- Include documentation and user manual (README)  
- Verify the application runs correctly on target environment  

## 7. Maintenance 

- Fix bugs reported during testing or usage  
- Refactor and improve code readability  
- Plan future enhancements 

