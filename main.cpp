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
#include "main.h"

using namespace std;

// ==============================
// CRM - CLIENT METHODS
// ==============================

// Add a new client
void CRM::addClient() {
    Client newClient;
    newClient.client_ID = CRM::generateRandomID();

    cout << "\nEnter name: ";
    getline(cin, newClient.name);
    // Validate name
    while (!isValidNameOrSurname(newClient.name)) {
        cout << "Name cannot be empty or contain numbers. Try again: ";
        getline(cin, newClient.name);
    }

    cout << "Enter surname: ";
    getline(cin, newClient.surname);
    // Validate surname
    while (!isValidNameOrSurname(newClient.surname)) {
        cout << "Surname cannot be empty or contain numbers. Try again: ";
        getline(cin, newClient.surname);
    }

    cout << "Enter phone number: ";
    getline(cin, newClient.phone);
    // Validate phone number
    while (!isValidPhoneNumber(newClient.phone)) {
        cout << "Phone number must have between 7 and 15 digits and can contain only numbers. Try again: ";
        getline(cin, newClient.phone);
    }

    cout << "Enter email: ";
    getline(cin, newClient.email);
    // Validate email
    while (!isValidEmail(newClient.email)) {
        cout << "Invalid email format. Try again: ";
        getline(cin, newClient.email);
    }

    // Add the new client to the vector
    CRM::clients.push_back(newClient);

    // Log the operation
    CRM::log(__DATE__, __TIME__, "Add client", to_string(newClient.client_ID));

    cout << "Client added successfully!\n\n";
}

// View all clients
void CRM::viewClients() {
    // Print header
    cout << "\nCLIENTS ";
    cout << std::string(110, '-') << endl;
    cout << left << setw(11) << "Client ID" 
         << setw(30) << "Name"
         << setw(30) << "Surname"
         << setw(17) << "Phone number"
         << setw(30) << "Email address" << endl;
    cout << std::string(118, '-') << endl;

    // Iterate through clients and print their details
    for (const auto& c : CRM::clients) {
        cout << left << setw(11) << c.client_ID
             << setw(30) << c.name
             << setw(30) << c.surname
             << setw(17) << c.phone
             << setw(30) << c.email << endl;
    }

    // Print footer
    cout << std::string(118, '-') << "\n" << endl;

    // Log the operation
    CRM::log(__DATE__, __TIME__, "View clients", "-");
}

// Edit an existing client
void CRM::editClient() {
    std::string input_id;
    int id;

    cout << "\nEnter Client ID to edit: ";

    // Validate ID input
    getline(cin, input_id);
    while (!isNumber(input_id) || input_id.length() > 9) {
        cout << "Invalid input. Please enter a valid ID: ";
        getline(cin, input_id);
    }

    id = stoi(input_id);

    // Search for the client by ID
    for (auto& c : CRM::clients) {
        if (c.client_ID == id) {
            cout << "\nCLIENT DATA:\nName: " << c.name << "\nSurname: " << c.surname << "\nPhone number: " << c.phone << "\nEmail address: " << c.email << "\n" << endl;

            std::string input;
            int choice;

            cout << "1. Edit name\n2. Edit surname\n3. Edit phone number\n4. Edit email address\n5. Cancel operation\n"; 
            cout << "\nChoose an option: ";
            
            // Validate choice
            getline(cin, input);
            while (!isNumber(input) || (stoi(input) < 1 || stoi(input) > 5)) {
                cout << "Invalid input. Please enter a valid choice: ";
                getline(cin, input);
            }

            choice = stoi(input);
            
            // Process the choice
            switch (choice) {
                case 1:
                    // Edit name
                    cout << "\nEnter new name: ";
                    getline(cin, c.name);
                    while (!isValidNameOrSurname(c.name)) {
                        cout << "Name cannot be empty or contain numbers. Try again: ";
                        getline(cin, c.name);
                    }
                    break;
                case 2:
                    // Edit surname
                    cout << "\nEnter new surname: ";
                    getline(cin, c.surname);
                    while (!isValidNameOrSurname(c.surname)) {
                        cout << "Surame cannot be empty or contain numbers. Try again: ";
                        getline(cin, c.surname);
                    }
                    break;
                case 3:
                    // Edit phone number
                    cout << "\nEnter new phone number: ";
                    getline(cin, c.phone);
                    while (!isValidPhoneNumber(c.phone)) {
                        cout << "Phone number must have between 7 and 15 digits and can contain only numbers. Try again: ";
                        getline(cin, c.phone);
                    }
                    break;
                case 4:
                    // Edit email address
                    cout << "\nEnter new email address: ";
                    getline(cin, c.email);
                    while (!isValidEmail(c.email)) {
                        cout << "Invalid email format. Try again: ";
                        getline(cin, c.email);
                    }
                    break;
                case 5:
                    // Cancel operation
                    cout << "Operation cancelled.\n\n";
                    return;
            }

            cout << "Client updated successfully.\n\n";

            // Log the operation
            CRM::log(__DATE__, __TIME__, "Edit client", to_string(id));

            return;
        }
    }
    cout << "Client ID not found.\n\n";
}

// Delete a client
void CRM::deleteClient() {
    std::string input_id;
    int id;

    cout << "\nEnter Client ID to delete: ";

    // Validate ID input
    getline(cin, input_id);
    while (!isNumber(input_id) || input_id.length() > 9) {
        cout << "Invalid input. Please enter a valid ID: ";
        getline(cin, input_id);
    }

    id = stoi(input_id);

    // Search for the client by ID
    for (auto it = CRM::clients.begin(); it != CRM::clients.end(); ++it) {
        if (it->client_ID == id) {
            CRM::clients.erase(it);

            // Remove appointments for the client
            for (auto it_appt = CRM::appointments.begin(); it_appt != CRM::appointments.end();) {
                if (it_appt->client_ID == id) {
                    it_appt = CRM::appointments.erase(it_appt);

                    // Erease the appointment ID from used IDs
                    CRM::usedIDs.erase(it_appt->appointment_ID);
                } else {
                    ++it_appt;
                }
            }

            // Remove contracts for the client
            for (auto it_contract = CRM::contracts.begin(); it_contract != CRM::contracts.end();) {
                if (it_contract->client_ID == id) {
                    it_contract = CRM::contracts.erase(it_contract);

                    // Erease the contract ID from used IDs
                    CRM::usedIDs.erase(it_contract->contract_ID);
                } else {
                    ++it_contract;
                }
            }

            // Remove the ID from the used IDs set
            CRM::usedIDs.erase(id);

            // Log the operation
            CRM::log(__DATE__, __TIME__, "Delete client", to_string(id));

            cout << "Client deleted.\n\n";

            return;
        }
    }
    cout << "Client not found.\n";
}

// Search for a client
void CRM::searchClient() {
    std::string keyword;
    std::string input_id;
    int id;

    cout << "\nSearch by:\n1. Name\n2. Surname\n3. Phone number\n4. Email address\n5. Cancel operation\n";

    // Validate choice
    cout << "\nChoose an option: ";
    
    // Get user input for choice
    getline(cin, input_id);
    while (!isNumber(input_id) || stoi(input_id) < 1 || stoi(input_id) > 5) {
        cout << "Invalid input. Please enter a valid ID: ";
        getline(cin, input_id);
    }

    id = stoi(input_id);
    
    // Check if the user wants to cancel the operation
    if (id == 5) {
        cout << "Operation cancelled.\n\n";
        return;
    } else {

        // Get keyword to search 
        cout << "\nEnter search keyword: ";
        getline(cin, keyword);

        // Validate keyword
        while(keyword.empty()) {
            cout << "Keyword cannot be empty. Try again: ";
            getline(cin, keyword);
        }

        // Print header
        cout << "\n" << std::string(118, '-') << endl;
        cout << left << setw(11) << "Client ID" 
        << setw(30) << "Name"
        << setw(30) << "Surname"
        << setw(17) << "Phone number"
        << setw(30) << "Email address" << endl;
        cout << std::string(118, '-') << endl;

        // Search clients based on the selected criteria
        switch (id) {
            case 1:
                // Search by name
                for (const auto& c : CRM::clients) {
                    if (c.name == keyword) {
                        cout << left << setw(11) << c.client_ID
                        << setw(30) << c.name
                        << setw(30) << c.surname
                        << setw(17) << c.phone
                        << setw(30) << c.email << endl;
                    }
                }
                break;
            case 2:
                // Search by surname
                for (const auto& c : CRM::clients) {
                    if (c.surname == keyword) {
                        cout << left << setw(11) << c.client_ID
                        << setw(30) << c.name
                        << setw(30) << c.surname
                        << setw(17) << c.phone
                        << setw(30) << c.email << endl;
                    }
                }
                break;
            case 3:
                // Search by phone number
                for (const auto& c : CRM::clients) {
                    if (c.phone == keyword) {
                        cout << left << setw(11) << c.client_ID
                        << setw(30) << c.name
                        << setw(30) << c.surname
                        << setw(17) << c.phone
                        << setw(30) << c.email << endl;
                    }
                }
                break;
            case 4:
                // Search by email address
                for (const auto& c : CRM::clients) {
                    if (c.email == keyword) {
                        cout << left << setw(11) << c.client_ID
                        << setw(30) << c.name
                        << setw(30) << c.surname
                        << setw(17) << c.phone
                        << setw(30) << c.email << endl;
                    }
                }
                break;
        }
        // Print footer
        cout << std::string(118, '-') << "\n" << endl;
        
        // Log the operation
        CRM::log(__DATE__, __TIME__, "Search client", "-");

        return; 
    }
}

// ==============================
// CRM - APPOINTMENT METHODS
// ==============================

// Add a new appointment
void CRM::addAppointment() {
    Appointment new_appointment;
    cout << "\nEnter Client ID for the appointment: ";
    cin >> new_appointment.client_ID;

    // Verify if client ID exists
    bool exists = false;
    for (auto& c : CRM::clients) {
        if (c.client_ID == new_appointment.client_ID) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        cout << "\nClient ID does not exist.\n\n";
        return;
    }

    // Get client name and surname
    for (const auto& c: CRM::clients) {
        if (c.client_ID == new_appointment.client_ID) {
            new_appointment.name = c.name;
            new_appointment.surname = c.surname;
            break;
        }
    }

    // Clear the input buffer
    cin.ignore();
    
    // Get and validate date
    cout << "Enter date [dd/mm/yyyy]: ";
    getline(cin, new_appointment.date);
    while (!isValidDate(new_appointment.date.c_str()) || !isDateInFuture(new_appointment.date)) {
        cout << "Invalid date format or date is in not in the future. Try again: ";
        getline(cin, new_appointment.date);
    }

    // Get and validate time
    cout << "Enter time [hh:mm] (time must be between 09:00 and 18:00 and in 5-minutes interval): ";
    getline(cin, new_appointment.time);
    while (!isValidTime(new_appointment.time)) {
        cout << "Invalid time format. Try again: ";
        getline(cin, new_appointment.time);
    }

    // Generate a unique appointment ID
    new_appointment.appointment_ID = generateRandomID();

    // Check for duplicate appointments
    for (const auto& a : CRM::appointments) {
        if (a.client_ID == new_appointment.client_ID && a.date == new_appointment.date && a.time == new_appointment.time) {
            cout << "Appointment already exists for this client at this date and time.\n\n";
            return;
        }
    }

    // Add appointment to the list
    CRM::appointments.push_back(new_appointment);

    // Log the operation
    CRM::log(__DATE__, __TIME__, "Add appointment", to_string(new_appointment.appointment_ID));

    cout << "Appointment added.\n\n";
}

// View all appointments
void CRM::viewAppointments() {
    // Print header
    cout << "\nAPPOINTMENTS ";
    cout << std::string(91, '-') << endl;
    cout << left << setw(16) << "Appointment ID" 
         << setw(11) << "Client ID" 
         << setw(30) << "Name"
         << setw(30) << "Surname"
         << setw(12) << "Date"
         << setw(7) << "Time" << endl;
    cout << std::string(104, '-') << endl;

    // Iterate through appointments and print their details
    for (const auto& a : CRM::appointments) {
        cout << left << setw(16) << a.appointment_ID 
             << setw(11) << a.client_ID
             << setw(30) << a.name
             << setw(30) << a.surname 
             << setw(12) << a.date 
             << setw(12) << a.time << endl;
    }

    // Print footer
    cout << std::string(104, '-') << "\n" << endl;

    // Log the operation
    CRM::log(__DATE__, __TIME__, "View appointments", "-");
}

// Search for an appointment
void CRM::searchAppointment() {
    std::string keyword;
    std::string input_id;
    int id;

    cout << "\nSearch by:\n1. Name\n2. Surname\n3. Date\n4. Cancel operation\n";

    // Validate choice
    cout << "\nChoose an option: ";
    
    // Get user input for choice
    getline(cin, input_id);
    while (!isNumber(input_id) || stoi(input_id) < 1 || stoi(input_id) > 4) {
        cout << "Invalid input. Please enter a valid ID: ";
        getline(cin, input_id);
    }

    id = stoi(input_id);
    
    // Check if the user wants to cancel the operation
    if (id == 4) {
        cout << "Operation cancelled.\n\n";
        return;
    } else {
        
        // Get keyword to search 
        cout << "\nEnter search keyword: ";
        getline(cin, keyword);
 
        // Validate keyword
        while(keyword.empty()) {
            cout << "Keyword cannot be empty. Try again: ";
            getline(cin, keyword);
        }

        // Print header
        cout << std::string(104, '-') << endl;
        cout << left << setw(16) << "Appointment ID" 
            << setw(11) << "Client ID" 
            << setw(30) << "Name"
            << setw(30) << "Surname"
            << setw(12) << "Date"
            << setw(7) << "Time" << endl;
        cout << std::string(104, '-') << endl;

        switch (id) {
            case 1:
                // Search by name
                for (const auto& a : CRM::appointments) {
                    if (a.name == keyword) {
                        cout << left << setw(16) << a.appointment_ID
                        << setw(11) << a.client_ID
                        << setw(30) << a.name
                        << setw(30) << a.surname
                        << setw(12) << a.date
                        << setw(7) << a.time << endl;
                    }
                }
                break;
            case 2:
                // Search by surname
                for (const auto& a : CRM::appointments) {
                    if (a.surname == keyword) {
                        cout << left << setw(16) << a.appointment_ID
                        << setw(11) << a.client_ID
                        << setw(30) << a.name
                        << setw(30) << a.surname
                        << setw(12) << a.date
                        << setw(7) << a.time << endl;
                    }
                }
                break;
            case 3:
                // Search by date
                for (const auto& a : CRM::appointments) {
                    if (a.date == keyword) {
                        cout << left << setw(16) << a.appointment_ID
                        << setw(11) << a.client_ID
                        << setw(30) << a.name
                        << setw(30) << a.surname
                        << setw(12) << a.date
                        << setw(7) << a.time << endl;
                    }
                }
                break;
        }

        // Print footer
        cout << std::string(104, '-') << "\n" << endl;

        // Log the operation
        CRM::log(__DATE__, __TIME__, "Search appointment", "-");

        return;
    }
}

// ==============================
// CRM - CONTRACT METHODS
// ==============================

void CRM::addContract() {
    Contract new_contract;
    cout << "\nEnter Client ID for the contract: ";
    cin >> new_contract.client_ID;

    bool exists = false;
    for (auto& c : CRM::clients) {
        if (c.client_ID == new_contract.client_ID) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        cout << "Client ID does not exist.\n\n";
        return;
    }

    // Get client name and surname
    for (const auto& c: CRM::clients) {
        if (c.client_ID == new_contract.client_ID) {
            new_contract.name = c.name;
            new_contract.surname = c.surname;
            break;
        }
    }

    // Clear the input buffer
    cin.ignore();

    // Get and validate start date
    cout << "Enter start date [dd/mm/yyyy]: ";
    getline(cin, new_contract.start_date);
    while (!isValidDate(new_contract.start_date.c_str())) {
        cout << "Invalid date format. Try again: ";
        getline(cin, new_contract.start_date);
    }

    // Get and validate end date
    cout << "Enter end date [dd/mm/yyyy]: ";
    getline(cin, new_contract.end_date);
    while (!isValidDate(new_contract.end_date.c_str())) {
        cout << "Invalid date format. Try again: ";
        getline(cin, new_contract.end_date);
    }
    
    // Check if end date is after start date
    while (compareDates(new_contract.start_date, new_contract.end_date) == 1) {
        cout << "End date must be after start date. Try again: ";
        getline(cin, new_contract.end_date);
    }

    new_contract.contract_ID = CRM::generateRandomID();

    // Check for duplicate contracts
    for (const auto& c : CRM::contracts) {
        if (c.client_ID == new_contract.client_ID && c.start_date == new_contract.start_date && c.end_date == new_contract.end_date) {
            cout << "Contract already exists for this client.\n\n";
            return;
        }
    }

    // Add contract to the list
    CRM::contracts.push_back(new_contract);

    // Log the operation
    CRM::log(__DATE__, __TIME__, "Add contract", to_string(new_contract.contract_ID));

    cout << "Contract added.\n\n";
}

void CRM::viewContracts() {
    cout << "\nCONTRACTS ";
    cout << std::string(100, '-') << endl;
    cout << left << setw(16) << "Contract ID" 
         << setw(11) << "Client ID" 
         << setw(30) << "Name"
         << setw(30) << "Surname"
         << setw(12) << "Start date"
         << setw(7) << "End date" << endl;
    cout << std::string(110, '-') << endl;
    for (const auto& a : CRM::contracts) {
        cout << left << setw(16) << a.contract_ID 
             << setw(11) << a.client_ID
             << setw(30) << a.name
             << setw(30) << a.surname 
             << setw(12) << a.start_date 
             << setw(12) << a.end_date << endl;
    }
    cout << std::string(110, '-') << "\n" << endl;

    // Log the operation
    CRM::log(__DATE__, __TIME__, "View contracts", "-");
}

void CRM::searchContract() {
    std::string keyword;
    std::string input_id;
    int id;

    cout << "\nSearch by:\n1. Name\n2. Surname\n3. Start date\n4. End date\n5. Cancel operation\n";

    // Validate choice
    cout << "\nChoose an option: ";
    
    // Get user input for choice
    getline(cin, input_id);
    while (!isNumber(input_id) || stoi(input_id) < 1 || stoi(input_id) > 5) {
        cout << "Invalid input. Please enter a valid ID: ";
        getline(cin, input_id);
    }

    id = stoi(input_id);
    
    if (id == 5) {
        cout << "Operation cancelled.\n\n";
        return;
    } else {
        
        // Get keyword to search 
        cout << "\nEnter search keyword: ";
        getline(cin, keyword);

        // Validate keyword
        while(keyword.empty()) {
            cout << "Keyword cannot be empty. Try again: ";
            getline(cin, keyword);
        }

        // Print header
        cout << std::string(110, '-') << endl;
        cout << left << setw(16) << "Contract ID" 
            << setw(11) << "Client ID" 
            << setw(30) << "Name"
            << setw(30) << "Surname"
            << setw(12) << "Start date"
            << setw(12) << "End date" << endl;
        cout << std::string(110, '-') << endl;
        
        switch (id) {
            case 1:
                for (const auto& c : CRM::contracts) {
                    if (c.name == keyword) {
                        cout << left << setw(16) << c.contract_ID
                        << setw(11) << c.client_ID
                        << setw(30) << c.name
                        << setw(30) << c.surname
                        << setw(12) << c.start_date
                        << setw(12) << c.end_date << endl;
                    }
                }
                break;
            case 2:
                 for (const auto& c : CRM::contracts) {
                    if (c.surname == keyword) {
                        cout << left << setw(16) << c.contract_ID
                        << setw(11) << c.client_ID
                        << setw(30) << c.name
                        << setw(30) << c.surname
                        << setw(12) << c.start_date
                        << setw(12) << c.end_date << endl;
                    }
                }
                break;
            case 3:
                for (const auto& c : CRM::contracts) {
                    if (c.start_date == keyword) {
                        cout << left << setw(16) << c.contract_ID
                        << setw(11) << c.client_ID
                        << setw(30) << c.name
                        << setw(30) << c.surname
                        << setw(12) << c.start_date
                        << setw(12) << c.end_date << endl;
                    }
                }
                break;
            case 4:
                 for (const auto& c : CRM::contracts) {
                    if (c.end_date == keyword) {
                        cout << left << setw(16) << c.contract_ID
                        << setw(11) << c.client_ID
                        << setw(30) << c.name
                        << setw(30) << c.surname
                        << setw(12) << c.start_date
                        << setw(12) << c.end_date << endl;
                    }
                }
                break;
        }
        cout << std::string(110, '-') << "\n" << endl;

        // Log the operation
        CRM::log(__DATE__, __TIME__, "Search contract", "-");

        return;
    }
}

// ==============================
// CRM - UTILITY FUNCTION
// ==============================

// Generate a unique random ID for clients and interactions
int CRM::generateRandomID() {
    int id;
    do {

        // Generate a random ID between 100000000 and 999999999
        id = 100000000 + rand() % 900000000;
    } while (usedIDs.find(id) != usedIDs.end());

    // Mark ID as used
    CRM::usedIDs.insert(id);  
    return id;
}

// Function to load used IDs from a CSV file
void CRM::loadUsedIDs(const std::string& filename = "dataset/ID.csv") {
    // Check if the file exists and can be opened
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Warning: Could not open " << filename << ". Starting with empty ID set.\n";
        return;
    }
    
    // Read IDs from the file and insert them into the usedIDs set
    std::string line;
    while (getline(file, line)) {
        try {
            int id = stoi(line);
            CRM::usedIDs.insert(id);
        } catch (const exception& e) {
            cerr << "Skipping invalid ID in file: " << line << '\n';
        }
    }
    
    // Close the file after reading
    file.close();
}

// Save data to csv files
void CRM::saveData() {
    // Open files in write mode
    ofstream clientFile("dataset/client.csv"), apptFile("dataset/appointments.csv"), contractFile("dataset/contract.csv"), idFile("dataset/ID.csv");

    // Write data to files
    for (auto& c : CRM::clients)
        clientFile << c.client_ID << "," << c.name << "," << c.surname << "," << c.phone << "," << c.email << "\n";

    for (auto& a : CRM::appointments)
        apptFile << a.appointment_ID << "," << a.client_ID << "," << a.name << "," << a.surname << "," << a.date << "," << a.time << "\n";

    for (auto& c : CRM::contracts)
        contractFile << c.contract_ID << "," << c.client_ID << "," << c.name << "," << c.surname << "," << c.start_date << "," << c.end_date << "\n";

    for (const auto& id : CRM::usedIDs) {
        idFile << id << "\n";
    }
    
    // Close files
    clientFile.close();
    apptFile.close();
    contractFile.close();
    idFile.close();
}

// Load data from csv files
void CRM::loadData() {
    // Check if the files exist and can be opened
    ifstream clientFile("dataset/client.csv"), apptFile("dataset/appointments.csv"), contractFile("dataset/contract.csv");
    std::string line;

    // Load clients from files
    while (getline(clientFile, line)) {
        std::stringstream ss(line);
        Client c;
        getline(ss, line, ','); c.client_ID = stoi(line);
        getline(ss, c.name, ',');
        getline(ss, c.surname, ',');
        getline(ss, c.phone, ',');
        getline(ss, c.email);
        CRM::clients.push_back(c);
    }

    // Load appointments from files
    while (getline(apptFile, line)) {
        std::stringstream ss(line);
        Appointment a;
        std::string id;
        getline(ss, id, ','); a.appointment_ID = stoi(id);
        getline(ss, id, ','); a.client_ID = stoi(id);
        getline(ss, a.name, ',');
        getline(ss, a.surname, ',');
        getline(ss, a.date, ',');
        getline(ss, a.time);
        CRM::appointments.push_back(a);
    }

    // Load contracts from files
    while (getline(contractFile, line)) {
        std::stringstream ss(line);
        Contract c;
        std::string id;
        getline(ss, id, ','); c.contract_ID = stoi(id);
        getline(ss, id, ','); c.client_ID = stoi(id);
        getline(ss, c.name, ',');
        getline(ss, c.surname, ',');
        getline(ss, c.start_date, ',');
        getline(ss, c.end_date);
        CRM::contracts.push_back(c);
    }
}

// Login function 
bool CRM::login() {
    std::string username, password;
    cout << "Welcome to InsuraPro CRM\n";

    cout << "Username: ";
    getline(cin, username);
    // Validate username
    while (username.empty()) {
        cout << "Userame cannot be empty. Try again: ";
        getline(cin, username);
    }
    
    cout << "Password: ";
    getline(cin, password);
    // Validate password
    while (password.empty()) {
        cout << "Password cannot be empty. Try again: ";
        getline(cin, password);
    }

    // Check credentials in user.csv file
    ifstream file("dataset/user.csv");
    if (!file.is_open()) {
        cerr << "Error opening user.csv file.\n";
        return false;
    }

    // Read each line and check if the username and password match
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string fileUsername, filePassword;

        if (getline(ss, fileUsername, ',') && getline(ss, filePassword)) {
            if (fileUsername == username && filePassword == password) {
                return true;
            }
        }
    }

    return false;
}

// Log function to write operations to log.csv
void CRM::log(const std::string& date, const std::string& time, const std::string& operation, const std::string& id) {
    // Open log.csv file in append mode
    ofstream file("dataset/log.csv", ios::app); 
    if (!file.is_open()) {
        cerr << "Error opening log.csv for writing.\n";
        return;
    }

    // Write the log entry
    file << date << ',' << time << ',' << operation << ',' << id << '\n';

    // Close the file
    file.close();
}

// ==============================
// MAIN MENU
// ==============================

// Main menu set up
void CRM::menu() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Load data from files
    loadData();

    // Load used IDs from file
    loadUsedIDs("dataset/ID.csv"); 
    
    std::string input;
    int choice;

    do {
        cout << "========== InsuraPro CRM ==========\n";
        cout << "\nCLIENT OPERATIONS\n1. Add client\n2. View clients\n3. Edit client\n4. Delete client\n5. Search client\n";
        cout << "\nAPPOINTMENT OPERATIONS\n6. Add appointment\n7. View appointments\n8. Search appointment\n";
        cout << "\nCONTRACT OPERATIONS\n9.  Add contract\n10. View contracts\n11. Search contract\n";
        cout << "\n12. SAVE AND EXIT\n\n=====================\nChoose an option: ";

        // Validate choice
        getline(cin, input);
        while (!isNumber(input) || stoi(input) > 12) {
            cout << "Invalid input. Please enter a valid choice: ";
            getline(cin, input);
        }

        choice = stoi(input);

        switch (choice) {
            case 1: CRM::addClient(); break;
            case 2: CRM::viewClients(); break;
            case 3: CRM::editClient(); break;
            case 4: CRM::deleteClient(); break;
            case 5: CRM::searchClient(); break;
            case 6: CRM::addAppointment(); break;
            case 7: CRM::viewAppointments(); break;
            case 8: CRM::searchAppointment(); break;
            case 9: CRM::addContract(); break; 
            case 10: CRM::viewContracts(); break;
            case 11: CRM::searchContract(); break;
            case 12: {CRM::saveData(); cout << "Data saved.\nLoggin out...\n\n"; break;}
        }
    } while (choice != 12);
};

// ==============================
// VALIDITY FUNCTIONS
// ==============================

// Validation functions for client name and surname
bool isValidNameOrSurname(const std::string& text) {
    bool hasLetter = false;
    
    // Check if the text is empty
    if (text.empty()) return false;

    // Check if the text contains only letters and spaces
    for (char c : text) {
        if (isalpha(c)) {
            // At least one letter is present
            hasLetter = true; 
        } else if (isspace(c)) {
            // Spaces are allowed
            continue; 
        } else {
            // Invalid character found
            return false; 
        }
    }

    return hasLetter; // Must contain at least one letter
}

// Validation functions for client phone number
bool isValidPhoneNumber(const std::string& phone) {
    // Check if the phone number is valid (between 7 and 15 digits, only contains numbers)
    if (phone.length() < 7 || phone.length() > 15) return false;
    for (char c : phone) if (!isdigit(c)) return false;
    return true;
}

// Validation functions for client email
bool isValidEmail(const std::string& email) {
    // Check if the email is valid (length, contains '@' and '.', no multiple '@')
    if (email.length() < 5 || email.length() > 50) return false;
    int at_pos = email.find('@');
    int dot_pos = email.find('.', at_pos + 1);
    return (at_pos != -1 && email.find('@', at_pos + 1) == -1 && dot_pos != -1 && dot_pos < email.length() - 1);
}

// Validation functions for date
bool isValidDate(const char* dateStr) {
    // Check if the date std::string is in the format DD/MM/YYYY
    if (!dateStr || strlen(dateStr) != 10 || dateStr[2] != '/' || dateStr[5] != '/')
        return false;
    
    // Check if the date std::string contains only digits and slashes
    for (int i = 0; i < 10; ++i)
        if (i != 2 && i != 5 && !isdigit(dateStr[i])) return false;

    // Extract day, month, and year from the date std::string
    int day = stoi(string(dateStr, 2));
    int month = stoi(string(dateStr + 3, 2));
    int year = stoi(string(dateStr + 6, 4));

    // Validate the extracted day, month, and year
    if (year < 1000 || year > 9999 || month < 1 || month > 12)
        return false;

    // Check if the day is valid for the given month and year
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // Adjust February for leap years
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (isLeap) daysInMonth[1] = 29;

    // Check if the day is valid for the month and year
    return (day >= 1 && day <= daysInMonth[month - 1]);
}

// Check if the date is in the future
bool isDateInFuture(const std::string& dateStr) {
    int d, m, y;
    char dash1, dash2;

    // Parse the date std::string in format DD/MM/YYYY
    if (!(istringstream(dateStr) >> d >> dash1 >> m >> dash2 >> y) || dash1 != '/' || dash2 != '/')
        return false;

    // Get current date
    time_t now = time(0);
    tm nowTm = *localtime(&now);
    nowTm.tm_hour = 0;
    nowTm.tm_min = 0;
    nowTm.tm_sec = 0;
    time_t today = mktime(&nowTm);

    // Construct input date
    tm inputTm = {};
    inputTm.tm_mday = d;
    inputTm.tm_mon = m - 1;
    inputTm.tm_year = y - 1900;
    inputTm.tm_hour = 0;
    inputTm.tm_min = 0;
    inputTm.tm_sec = 0;
    time_t inputDate = mktime(&inputTm);

    // Compare: input date is in the future if it's strictly greater than today
    return difftime(inputDate, today) > 0;
}

// Validation functions for time
bool isValidTime(const std::string& timeStr) {
    // Check if the time std::string is in the format HH:MM
    if (timeStr.length() != 5 || timeStr[2] != ':') return false;

    // Extract hours and minutes from the time std::string
    std::string hStr = timeStr.substr(0, 2);
    std::string mStr = timeStr.substr(3, 2);

    // Check if hours and minutes are valid numbers
    if (!isdigit(hStr[0]) || !isdigit(hStr[1]) || !isdigit(mStr[0]) || !isdigit(mStr[1])) return false;
    int h = stoi(hStr), m = stoi(mStr);
    
    // Time must be between 09:00 and 18:00 and in 5-minute intervals
    return (h >= 9 && h < 18 && m >= 0 && m < 60 && m % 5 == 0);
}

// Validation functions for numeric input
bool isNumber(const std::string& str) {
    // Check if the std::string is empty and contains only digits
    if (str.empty()) return false;
    try {
        stoi(str);
    } catch (const std::exception& e) {
        return false;
    }
    return true;
}

// Function to compare two dates in the format DD/MM/YYYY
int compareDates(const std::string& date1, const std::string& date2) {
    int y1, m1, d1;
    int y2, m2, d2;

    // Parse date1
    char dash; // to skip the dashes
    std::istringstream ss1(date1);
    ss1 >> d1 >> dash >> m1 >> dash >> y1;

    // Parse date2
    std::istringstream ss2(date2);
    ss2 >> d2 >> dash >> m2 >> dash >> y2;

    /* Returns:
        - -1 if date1 < date2
        -  0 if date1 == date2
        - 1 if date1 > date2
    */

    // Compare years
    if (y1 != y2)
        return (y1 < y2) ? -1 : 1;

    // Compare months
    if (m1 != m2)
        return (m1 < m2) ? -1 : 1;

    // Compare days
    if (d1 != d2)
        return (d1 < d2) ? -1 : 1;

    return 0;
}

// ==============================
// MAIN
// ==============================

// Main function to start the CRM application
int main() {
        
    // Initialize CRM
    CRM crm;
    
    // Login (check user.csv file for credentials)
    if (!crm.login()) {
        cout << "Access denied\n\n";
        return 1;
    }
    cout << "Login successful\n\n";


    // Main menu
    crm.menu();
    return 0;
}
