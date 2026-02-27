# Client CRM System Documentation

## Contents
- [Overview](#overview)
- [News](#news)
- [Folder content](#folder-content)
- [Project structure](#project-structure)
- [Objects](#objects)
    - [Class CRM](#class-crm)
    - [Class Client](#class-client)
    - [Class Appointment](#class-appointment)
    - [Class Contract](#class-contract)
    - [Functions](#functions)
    - [Main](#main)
- [Compilation and execution](#compilation--execution)

## Overview

This project implements a simple **Client CRM (Customer Relationship Management) System** in C++. It manages client data, appointments and contracts and store all the information in csv files to preserve consistency between sessions. It implements functionality such as adding, editing and deleting clients or adding/viewing appointments and contracts. In the new version there is also a basinc login system and a log system that keeps track of the operations performed by the user.

## News

Following feedback received, the following changes have been made to the software:

- General restructuring of the software: with integration of the file "<i><b>main.h</i></b>" (header) to support "<i><b>main.cpp</i></b>" file (C++ script), as per OOP design best practice;
- Definition of the <i><b>CRM</i></b> "master" class and redefinition of the <i><b>Client</i></b>, <i><b>Appointment</i></b> and<i><b>Contract classes</i></b>: the vectors of the three classes and the unordered_set of IDs are now part of the CRM class, as well as their respective methods of interaction and modification, as per OOP design best practice;
- Fix of the following bugs:
    - <i><b>CRM::loadData()</i></b>: the <i>push_back</i> commands for loading data are now called by referencing the class of belonging (CRM);
    - <i><b>CRM::deleteClient()</i></b>: the process of deleting customers, in addition to customer data, now also removes the data related to appointments and contracts. In addition, an ID deletion system has been integrated from the relevant set once the data associated with it has been deleted;
- The <i><b>isAtLeastOneDayAfter()</i></b> function has been removed: the function was defined but never referenced in the previous version of the software;
- Optimization of the <i><b>isDateInFuture()</i></b> function: resolution of some bugs found during testing;
- Fixed some bugs related to terminal data input by using the <i>cin.ignore()</i> command; 
- Adding more comments to the code to improve readability;
- Optimization of the </i></b>isNumber()<i><b> function: instead of the for loop that performed the input validation one character at a time, the function now integrates a </i></b>try/catch system</i></b> on the <i>stoi()</i> command to convert user input into numerical value;
- "Explicit" function recall: with the code restructuring, functions within the main menu are now invoked by referencing CRM class methods;
- Restructuring of the project folder: csv datasets are now placed in the dedicated "<i>dataset</i>" folder.

## Folder content

The following files and folder are contained in the **CRM.zip** folder:

- **README.md** : Project documentation file;
- **main.cpp**: C++ script;
- **main.h**: Header file;
- **/dataset**: dataset folder;
    - **clients.csv**: Client default dataset;
    - **appointment.csv**: Appointments default dataset;
    - **contract.csv**: Contract default dataset;
    - **ID.csv**: ID dataset;
    - **log.csv**: Log dataset;
    - **user.csv**: User dataset;

## Objects

The software consists of the following components:

### Class CRM

The "master" class for general software administration. It is responsible for starting the program and managing the data collections (vectors and set) by appropriate methods:

```cpp
// CRM "master" class
class CRM {
    public:

        // Data vectors and sets
        std::vector<Client> clients;
        std::vector<Appointment> appointments;
        std::vector<Contract> contracts;
        std::unordered_set<int> usedIDs;
   
        // ==============================
        // CRM - CLIENT METHODS
        // ==============================
        // Methods for client operations
        void addClient();
        void viewClients();
        void editClient();
        void deleteClient();
        void searchClient();
                
        // ==============================
        // CRM - APPOINTMENT METHODS
        // ==============================
        // Methods for appointment operations
        void addAppointment();
        void viewAppointments();
        void searchAppointment();

        // ==============================
        // CRM - CONTRACT METHODS
        // ==============================
        // Methods for contract operations
        void addContract();
        void viewContracts();
        void searchContract();

        // ==============================
        // UTILITY FUNCTION
        // ==============================

        // Generate a unique random ID for clients and interactions
        int generateRandomID();

        // Function to load used IDs from a CSV file
        void loadUsedIDs(const std::string& filename);

        // Save data to csv files
        void saveData();

        // Load data from csv files
        void loadData();

        // Login function 
        bool login();

        // Log function to write operations to log.csv
        void log(const std::string& date, const std::string& time, const std::string& operation, const std::string& id);

        // ==============================
        // MAIN MENU
        // ==============================
        // Main menu set up
        void menu();
};
```

### Class Client

Client class, used to store the general information of each client:

```cpp
// Client class
class Client {
    public:
        int client_ID;
        std::string name;
        std::string surname;
        std::string phone;
        std::string email;
};
```

### Class Appointment

Appointment class, used to store the general information of an appointment referrint to a client:

```cpp
// Appointment class
class Appointment {
    public:
        int appointment_ID;
        int client_ID;
        std::string name;
        std::string surname;
        std::string date;
        std::string time;
};
```

### Class Contract

Contract class, used to store the general information of a contract referrint to a client:

```cpp
// Contract class
class Contract {
    public:
        int contract_ID;
        int client_ID;
        std::string name;
        std::string surname;
        std::string start_date;
        std::string end_date;
        std::string status;
};
```

### Functions

The software includes several utility functions for input validation and data handling:

```cpp
// ==============================
// VALIDITY FUNCTIONS
// ==============================

// Validation functions for client name and surname
bool isValidNameOrSurname(const std::string& text);

// Validation functions for client phone number
bool isValidPhoneNumber(const std::string& phone);

// Validation functions for client email
bool isValidEmail(const std::string& email);

// Validation functions for date
bool isValidDate(const char* dateStr);

// Check if the date is in the future
bool isDateInFuture(const std::string& dateStr);

// Validation functions for time
bool isValidTime(const std::string& timeStr);

// Validation functions for numeric input
bool isNumber(const std::string& str);

// Function to compare two dates in the format DD/MM/YYYY
int compareDates(const std::string& date1, const std::string& date2);
```

### Main

Finally we have the main function that deals with the initialization of objects and the program start:

```cpp
int main();
```

## Compilation and execution

### Requirements
C++ 11 or later.

### Compilation command
```bash
g++ -o main main.cpp
```

### Execution
```bash
./main
```
