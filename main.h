#pragma once

#include <unordered_set>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <limits>
#include <cstdlib>
#include <ctime>

// ==============================
// CLASS DEFINITIONS
// ==============================

// Client class
class Client {
    public:
        int client_ID;
        std::string name;
        std::string surname;
        std::string phone;
        std::string email;
};

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

// ==============================
// MAIN
// ==============================

// Main function to start the CRM application
int main();