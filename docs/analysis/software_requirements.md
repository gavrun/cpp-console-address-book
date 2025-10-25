# Software Requirements Specification (SRS)

**Project:** Console Application "Address Book"  
**Version:** 1.0  
**Date:** 2025-01-01  
**Author:** Developer  

## 1. Introduction 

### 1.1 Purpose 

This document defines the software requirements for the **Address Book** console application.  
It describes functional and non-functional requirements that guide the design, implementation, and testing phases.

### 1.2 Scope 

The system provides basic contact management capabilities:
- Create, read, update, and delete contact records.
- Store and retrieve data from a local text file.
- Operate via a command-line interface.

The project is educational and aims to practice:
- Object-oriented design (classes, encapsulation, inheritance).
- File input/output.
- Data management with STL containers.
- Simple use of GoF patterns (Strategy, Factory Method) where appropriate.

### 1.3 Definitions 

| Term | Description |
|------|--------------|
| Contact | A record that contains personal information such as name, phone, email, and address. |
| Record | A single data entry stored in memory or file. |
| CLI | Command-Line Interface, text-based user interaction. |

### 1.4 References
- ISO/IEC/IEEE 29148 — Systems and software engineering — Life cycle processes — Requirements engineering.
- C++ standard C++11 or higher.

## 2. Overall Description 

### 2.1 Product Perspective

This is a standalone application with no dependencies on external services.  
It runs locally and stores data in a simple text file (e.g., `contacts.txt`).

### 2.2 Product Functions 

- Display menu with available operations.
- Add new contacts.
- List all existing contacts.
- Search contacts by name or phone number.
- Edit existing contact information.
- Delete contacts.
- Save changes to a text file and load them at startup.

### 2.3 User Characteristics 

- Basic computer literacy.
- Familiarity with command-line interface.
- No programming knowledge required to use the program.

### 2.4 Constraints 

- Implemented in standard **C++11 or higher**.
- Text-based interface.
- Data stored in plain text file.
- No external database 
- No network functionality 
- No multi-user or concurrent access.

### 2.5 Architecture Constraints 

Patterns (GoF) used and rationale:
- Factory Method: centralizes creation of concrete Person types from a textual role (used by loading and editing flows).
- Strategy: pluggable search strategies (SearchByName, SearchByPhone) without changing AddressBook.

### 2.6 Assumptions and Dependencies

- The user runs the program in a console environment.
- The storage file is accessible for reading and writing.
- The default data file is named contacts.txt and located in the same directory as the executable.

### 2.7 System Environment

- Development IDE: Visual Studio / VSCode / CLion 
- Compiler: MSVC supporting C++11 or higher  
- Operating System: Windows

## 3. Specific Requirements 

### 3.1 Functional Requirements 

| ID   | Requirement                                                                                      | Priority |
|------|---------------------------------------------------------------------------------------------------|----------|
| FR-1 | The system shall allow the user to add a new contact.                                            | High     |
| FR-2 | The system shall display all stored contacts with their indices.                                  | High     |
| FR-3 | The system shall search contacts by name or phone using a selectable strategy.                    | Medium   |
| FR-4 | The system shall allow editing of an existing contact by index.                                   | High     |
| FR-5 | The system shall allow deleting a contact by index.                                               | High     |
| FR-6 | The system shall save contact data to a file upon exit.                                           | High     |
| FR-7 | The system shall load contact data from a file at startup if the file exists.                     | High     |
| FR-8 | The system shall support contact roles Student, Teacher, and Colleague with one role-specific field. | High  |
| FR-9 | The system shall store contact records in the format defined in section 3.4.                      | High     |
| FR-10| The system shall skip malformed file lines and unknown contact types, issuing a warning.          | Medium   |
| FR-11| The system shall reject or re-prompt input containing the "pipe" delimiter.                          | Medium   |
| FR-12| The system shall accept spaces in the role-specific field (e.g., major/subject/company).          | Medium   |
| FR-13| The system shall provide confirmation messages for add, edit, and delete operations.              | Low      |
| FR-14| The system shall handle invalid indices gracefully without terminating.                           | High     |
| FR-15| The system shall display a simple text menu and process user commands until quit.                 | High     |

### 3.2 Non-Functional Requirements 

| ID    | Requirement     | Description                                                                                 |
|-------|------------------|---------------------------------------------------------------------------------------------|
| NFR-1 | Usability        | The interface shall be clear and menu-driven with concise prompts and error messages.       |
| NFR-2 | Performance      | File operations shall complete within 1 second for up to 100 contacts (typical workload).   |
| NFR-3 | Portability      | The program should compile and run on Windows; portability to Linux and macOS not covered. |
| NFR-4 | Reliability      | Data shall persist between program runs; malformed file data shall not crash the program.  |
| NFR-5 | Maintainability  | Code shall be modular and commented; components separated by roles.|
| NFR-6 | Memory Safety    | The program shall not leak memory (use RAII and smart pointers).                            |
| NFR-7 | Robustness       | The program shall sanitize user input and recover from basic input errors.                  |

### 3.3 Data Model

- Entity: Contact (abstract base: Person)
  - firstName: string (mandatory; single word recommended)
  - lastName: string (mandatory; single word recommended)
  - phone: string (mandatory; digits and basic symbols allowed; stored as-is)
  - role: enum { Student, Teacher, Colleague } (mandatory)
  - roleSpecific:
    - Student: major (string; may contain spaces)
    - Teacher: subject (string; may contain spaces)
    - Colleague: company (string; may contain spaces)
- Constraints:
  - The delimiter `|` is reserved and shall not appear in any field.
  - Empty mandatory fields are invalid and shall be re-prompted in CLI.
  - Email/address fields are out of scope for v1.1 (future enhancement).

### 3.4 Persistence Format Specification

- File: `contacts.txt` in executable directory.
- Encoding: UTF-8 (plain text).
- Record format (one record per line):
  - Student: `Student|FirstName|LastName|Phone|Major`
- Example:
  - `Student|Al|Tor|1234|Dance`
- Loading rules:
  - Blank lines are ignored.
  - If the first token (type) is unknown, the line is skipped with a warning.
  - If the number of tokens is not 5, the line is considered malformed and skipped with a warning.
- Saving rules:
  - The entire file is overwritten on save.

### 3.5 User Interface Requirements (CLI)
- Menu options:
  - [S] Add Student
  - [T] Add Teacher
  - [C] Add Colleague
  - [L] List all contacts
  - [F] Find (choose by [N]ame or [P]hone)
  - [E] Edit by index
  - [R] Remove by index
  - [Q] Quit
- Feedback:
  - Success confirmation messages for add/edit/remove/save and data load.
  - Warnings for malformed file lines or unknown types during load.

### 3.6 Architectural Overview

- Core components:
  - Person (abstract), Student, Teacher, Colleague (polymorphic domain model).
  - AddressBook (owns collection of contacts).
  - SearchStrategy, SearchByName, SearchByPhone (Strategy pattern).
  - PersonFactory (Factory Method for constructing contacts during load).
  - FileManager (persistence; load/save).
  - ConsoleUI (CLI interaction loop).

- Rationale for patterns:
  - Strategy: Extend search behavior without modifying AddressBook.
  - Factory Method: Centralize object creation based on type tokens from file.

## 4. System Models 

### 4.1 Use Cases 

- UC-1: Add Contact
  - Actor: User
  - Basic Flow: User selects role -> enters first/last/phone -> enters role-specific field -> system creates and stores contact -> confirms success.
  - Alternate: Invalid input (empty/contains `|`) -> re-prompt.
- UC-2: List Contacts
  - Actor: User
  - Basic Flow: User selects List -> system prints contacts with indices.
- UC-3: Search Contacts
  - Actor: User
  - Basic Flow: User selects Find -> chooses Name or Phone -> enters query -> system prints matching contacts with indices.
  - Constraint: Case-insensitive match for name; substring match for phone.
- UC-4: Edit Contact
  - Actor: User
  - Basic Flow: User selects Edit -> enters index -> selects new role -> enters new fields -> system replaces contact -> confirms success.
  - Alternate: Invalid index -> error message, no changes.
- UC-5: Remove Contact
  - Actor: User
  - Basic Flow: User selects Remove -> enters index -> system deletes contact -> confirms success.
  - Alternate: Invalid index -> error message, no changes.
- UC-6: Load/Save
  - Trigger: On startup (Load), On exit (Save).
  - Basic Flow: System loads from file if exists; on exit, overwrites file with current state.
  - Alternate: File missing (start empty); write failure (error message).

## 5. Acceptance Criteria

- The application compiles and runs without errors.
- All menu options function as described and handle invalid inputs gracefully.
- Added/edited/deleted contacts persist after restarting the application.
- Input validation prevents empty mandatory fields and the `|` character.
- Malformed file data and unknown types are skipped with warnings, without terminating the program.
- For up to 100 contacts, load/save operations complete within approximately 1 second on a typical desktop environment.

### 5.1 Acceptance Test Cases (Samples)

- AT-1: Startup with no file
  - Pre: `contacts.txt` absent.
  - Steps: Run app -> List.
  - Expected: “Address book is empty.” No errors.
- AT-2: Add Student and List
  - Steps: Add Student (Al Tor 1234; Major=Dance) -> List.
  - Expected: Entry printed as Student with correct fields and an index.
- AT-3: Search by Name (case-insensitive)
  - Pre: Have entries “Al Tor”, “Ben Lock”.
  - Steps: Find -> Name -> query “al”.
  - Expected: Matches include “Al Tor”.
- AT-4: Edit Contact to Teacher
  - Steps: List -> Edit index 0 -> set Teacher -> enter new fields -> List.
  - Expected: Index 0 shows Teacher with updated fields.
- AT-5: Remove Contact (invalid index)
  - Steps: Remove -> enter out-of-range index.
  - Expected: “Invalid index.” No crash.
- AT-6: Save and Reload
  - Steps: Add some entries -> Quit -> Restart -> List.
  - Expected: Entries are restored.
- AT-7: Malformed Line Handling
  - Pre: Manually add line “UnknownType|A|B|C|X” to file.
  - Steps: Start app -> List.
  - Expected: Warning about unknown type; app continues normally.

## 6. Future Enhancements 

- Sorting and filtering contacts.  
- Improved user interface (TUI).  
- Input validation with formatted phone/email checks.

## 7. Traceability

| FR  | Components Involved                      |
|-----|------------------------------------------|
| FR-1| ConsoleUI, AddressBook, Person subclasses|
| FR-2| ConsoleUI, AddressBook                   |
| FR-3| ConsoleUI, AddressBook, SearchStrategy   |
| FR-4| ConsoleUI, AddressBook, Person subclasses|
| FR-5| ConsoleUI, AddressBook                   |
| FR-6| FileManager, Person::serialize           |
| FR-7| FileManager, PersonFactory               |
| FR-8| Person, Student, Teacher, Colleague      |
| FR-9| Person::serialize, FileManager           |
| FR-10| FileManager, PersonFactory              |
| FR-11| ConsoleUI (input rules)                 |
| FR-12| ConsoleUI (getline for role-specific)   |
| FR-13| ConsoleUI (messages)                    |
| FR-14| ConsoleUI, AddressBook                  |
| FR-15| ConsoleUI                               |

