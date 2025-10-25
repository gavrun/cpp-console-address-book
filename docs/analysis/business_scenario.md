# Scenario: Console Application "Address Book" 

## Overview 

The **Address Book** is a simple console-based application designed to manage contact information. 
It allows users to store, search, edit, and delete contact records. 
This project simulates a real-world scenario of developing a personal information management tool. 
The system will operate in a text-based interface and use a local data file for persistent storage. 

## Subject and Use Case

Managing contact information (names, phone numbers, emails, addresses) is a common task. 
This project uses this idea to demonstrate how data can be structured, stored, and processed programmatically using C++. 
The goal is to provide a simple, self-contained tool. 
The primary user is an individual who wants to store and organize contact information.

## Core Features 

- Add a new contact 
- View all contacts 
- Search for a contact by name or phone number 
- Edit existing contact information 
- Delete a contact 
- Save and load contact data from a file 

## Constraints 

- Console-based user interface (no GUI) 
- Local text file used as storage 

## Outcome 

A console application demonstrating: 
- Data encapsulation and class design 
- GoF design patterns
- STL containers for in-memory data management 
- File input/output for persistence 
- A simple and clear command-driven interface 


## Scenario description (original text)

```
Учебный проект на тему "Консольное приложение «Адресная книга»".
Необходимо создать приложение, позволяющее записывать данные о людях (ФИО, телефон, род занятий и т.д.).
Требуется:
• реализовать иерархию классов;
• должны быть абстрактный класс (например, Person или Human) с общими методами (продумайте самостоятельно, какими методами), производные классы, моделирующие, например, сущности (род занятий): студент, преподаватель, коллега по работе и т.д.;
• применить отношение ассоциации (композиция или агрегации) между объектами (продумайте самостоятельно, какими объектами);
• реализовать запись людей в коллекцию (тип коллекции на усмотрение) и сохранение коллекции в файл на диске в папку с приложением;
• реализовать "интерфейс" взаимодействия в отдельном классе;
• для реализации классов применить шаблоны GoF в тех случаях, где это явно оправдано (кратко обосновать почему).
```

