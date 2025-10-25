# Conceptual Data Model 

**Project:** Console Application "Address Book"  
**Version:** 1.0  
**Date:** 2025-01-01  
**Author:** Developer  

## 1. Overview

This document defines the conceptual model for the Address Book system.  
It identifies the main entities, their attributes, and relationships between them.

## 2. Main Entities (Simplified)

### 2.1 Contact 

Represents a single person or organization entry in the address book.

**Attributes:**
- `firstName` — string, full name of the contact  
- `lastName` — string
- `phone` — string, phone number  
- `email` — string, email address (optional)  
- `address` — string, physical address (optional)

**Validation Rules:**
- `name` and `phoneNumber` are required (non-empty).
- Combination of (`name`, `phoneNumber`) must be unique.
- `email` and `address` are optional.

### 2.2 AddressBook 

Represents the collection of all contacts managed by the system.

**Attributes:**
- `contacts` — list (vector) of `Contact` objects

**Operations:**
- Add, edit, delete contacts  
- Search by name or phone  
- List all contacts

### 2.3 FileManager 

Responsible for reading and writing contact data to persistent storage.

**Attributes:**
- `filePath` — string, path to the storage file  

**Operations:**
- `load()` – read contacts from file  
- `save()` – write contacts to file  

### 2.4 SearchStrategy 

Pluggable search behavior.

- Implementations:
  - `SearchByName` (case-insensitive substring)
  - `SearchByPhone` (substring)

## 3. Relationships Diagram (Simplified)

```
+------------------+   contains (0..*)   +---------------------+
|   AddressBook    |-------------------->|       Person        |
+------------------+                     +---------------------+
| - contacts       |                     | - firstName         |
| + add/edit/del   |                     | - lastName          |
| + list/search    |                     | - phone             |
+------------------+                     +---------------------+
          |                                        ^
          | uses (0..1)                            | inheritance
          v                                        |
+-------------------+          +---------+----------+-----------+
|  SearchStrategy   |          | Student | Teacher  | Colleague |
+-------------------+          | major   | subject  | company   |
          |                    +---------+----------+-----------+
          | load/save (main)
          v
+------------------+
|   FileManager    |
+------------------+
| - filePath       |
| + load/save      |
+------------------+
```

## 4. Data Persistence Concept 

- Contacts are stored as plain text records in a file (`contacts.txt`).  
- Each record may use a simple separator, e.g. `;` or `|`.  
- Fields must not contain a separator. If entered, it is replaced with ',' on save.
- Encoding: UTF-8.
- One contact per line
- Ignore empty lines; trim leading/trailing spaces on load.
- On program start, all records are loaded into memory.  
- On exit, all updates are saved back to the file.

Example file structure:
```
Student|Al|Tor|1234|Dance
Teacher|Ben|Lock|0974|Math
Colleague|John|Doe|11111|Acme Corp
```

## 5. Future Data Model Enhancements 

- Add unique ID for each contact. 
- Use structured formats (CSV, JSON) for storage. 
- Introduce “Group” entity (e.g., Friends, Work). 
- Add timestamp fields (createdAt, updatedAt).

