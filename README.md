# cpp-console-address-book

## Address Book

The **Address Book** is a simple console-based application designed to manage contact information. 
It allows users to store, search, edit, and delete contact records. 
This project simulates a real-world scenario of developing a personal information management tool. 
The system will operate in a text-based interface and use a local data file for persistent storage. 

### Features 

- Add a new contact 
- View all contacts 
- Edit existing contact information 
- Delete a contact 
- Search for a contact by name or phone number 
- Save and load contact data from a file 

### User Interface

Text-based menu with interactive options (no TUI/GUI).

* Add / Edit / Remove contact
* Search (by name or phone)
* List all contacts
* Exit with auto-save

### Design

* **Polymorphism** unified handling of all contact types via virtual methods.
* **Strategy Pattern** modular search algorithms without changing the `AddressBook` core.
* **Factory Pattern** dynamic creation of objects from file data.
* **RAII** and **Smart Pointers** unique_ptr ensures safe memory management.
* **STL Containers** vector used for flexible and efficient contact storage.

### Structure

```
AddressBook/
├── AddressBook.h/.cpp          # Core contact storage logic
├── FileManager.h/.cpp          # File input/output layer
├── Interface.h/.cpp            # Console UI controller
├── Person.h/.cpp               # Abstract base for contacts
├── Student.h/.cpp              # Derived contact type: Student
├── Teacher.h/.cpp		        
├── Colleague.h/.cpp	        
├── SearchStrategy.h/.cpp       # Search Strategy
├── SearchByName.h/.cpp         # Search implementation
├── SearchByPhone.h/.cpp        
├── PersonFactory.h/.cpp        # Factory for creating contacts
|
├── contacts.txt                # Example data file
└── main.cpp                    # Program entry point
```

### Build 

1. Open Visual Studio 2022 (with MSVC)

2. Clone 

```
git clone https://github.com/gavrun/cpp-console-address-book.git
cd cpp-console-address-book
```

3. Open the project in VS

4. Build Solution (Debug)

5. Run


