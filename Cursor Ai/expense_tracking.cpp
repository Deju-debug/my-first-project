/*
 * Expense Tracking System
 * Single-file CLI program using only: arrays, loops, if/switch, strings, variables.
 * No classes, structs, vectors, functions, or file handling.
 */

// iostream  - used for console input (cin) and output (cout)
// string    - used to store text fields like name, category, and date
// iomanip   - used to format amount output to 2 decimal places
// cctype    - used for tolower() when comparing names without caring about case
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

int main() {
    // -------------------------------------------------------------------------
    // STEP 1: Constants
    // Defines the maximum number of expense records the program can hold.
    // All parallel arrays use this same size so every record has one slot
    // in each array at the same index position.
    // -------------------------------------------------------------------------
    const int MAX_EXPENSES = 100;

    // -------------------------------------------------------------------------
    // STEP 2: Parallel arrays (in-memory database)
    // Each expense is split across five arrays. Record #0 uses index 0 in
    // every array, record #1 uses index 1, and so on. This replaces a struct
    // or class while keeping related data aligned by index.
    // -------------------------------------------------------------------------
    int expenseID[MAX_EXPENSES];       // Unique numeric ID for each expense
    string expenseName[MAX_EXPENSES];  // Short title or label (e.g. "Groceries")
    string category[MAX_EXPENSES];     // Group type (e.g. "Food", "Travel")
    double amount[MAX_EXPENSES];       // Money spent for this expense
    string date[MAX_EXPENSES];         // When the expense occurred (user-entered text)

    // -------------------------------------------------------------------------
    // STEP 3: Program state variables
    // expenseCount - how many records are currently stored (0 to MAX_EXPENSES)
    // choice       - menu option the user picked (1 through 7)
    // running      - true while the program should keep showing the menu
    // -------------------------------------------------------------------------
    int expenseCount = 0;
    int choice = 0;
    bool running = true;

    // -------------------------------------------------------------------------
    // STEP 4: Main menu loop
    // Repeats until the user selects Exit (option 7). Each loop iteration shows
    // the menu, reads a choice, and runs the matching case in the switch.
    // -------------------------------------------------------------------------
    while (running) {
        // Display the main menu options
        cout << "\n===== Expense Tracking System =====\n";
        cout << "1. Add Expense\n";
        cout << "2. Display Expenses\n";
        cout << "3. Search Expense\n";
        cout << "4. Update Expense\n";
        cout << "5. Delete Expense\n";
        cout << "6. Generate Report\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        // Validate menu input: if user types letters instead of a number,
        // clear the error flag, discard bad input, and show the menu again.
        if (!(cin >> choice)) {
            cin.clear();
            string junk;
            cin >> junk;
            cout << "Invalid input. Please enter a number (1-7).\n";
            continue;
        }

        // Route the user's choice to the correct feature
        switch (choice) {
            // -----------------------------------------------------------------
            // CASE 1: Add Expense
            // Collects all five fields, stores them at index expenseCount,
            // then increases expenseCount so the next add uses the next slot.
            // -----------------------------------------------------------------
            case 1: {
                cout << "\n----- Add Expense -----\n";

                // Block new records when the arrays are full
                if (expenseCount >= MAX_EXPENSES) {
                    cout << "Cannot add more expenses. Maximum limit (100) reached.\n";
                    break;
                }

                // --- Field 1: Expense ID ---
                // Read a whole number; repeat until input is valid.
                cout << "Enter expense ID: ";
                while (!(cin >> expenseID[expenseCount])) {
                    cin.clear();
                    string junk;
                    cin >> junk;
                    cout << "Invalid ID. Enter a whole number: ";
                }

                // Ensure no two expenses share the same ID (search existing records)
                bool duplicateId = true;
                while (duplicateId) {
                    duplicateId = false;
                    for (int i = 0; i < expenseCount; i++) {
                        if (expenseID[i] == expenseID[expenseCount]) {
                            duplicateId = true;
                            cout << "This ID already exists. Enter a different expense ID: ";
                            while (!(cin >> expenseID[expenseCount])) {
                                cin.clear();
                                string junk;
                                cin >> junk;
                                cout << "Invalid ID. Enter a whole number: ";
                            }
                            break;
                        }
                    }
                }

                // Clear leftover newline after cin >> so getline works for text fields
                cin.ignore(1000, '\n');

                // --- Field 2: Expense name (may contain spaces) ---
                cout << "Enter expense name: ";
                getline(cin, expenseName[expenseCount]);

                // --- Field 3: Category ---
                cout << "Enter category: ";
                getline(cin, category[expenseCount]);

                // --- Field 4: Amount ---
                // Must be a valid number and not negative.
                cout << "Enter amount: ";
                while (!(cin >> amount[expenseCount]) || amount[expenseCount] < 0) {
                    cin.clear();
                    string junk;
                    cin >> junk;
                    cout << "Invalid amount. Enter a positive number: ";
                }

                cin.ignore(1000, '\n');

                // --- Field 5: Date ---
                cout << "Enter date (e.g. DD-MM-YYYY): ";
                getline(cin, date[expenseCount]);

                // Save complete: move to the next free index for future adds
                expenseCount++;

                // Show confirmation using the index we just filled (expenseCount - 1)
                cout << "\nExpense added successfully!\n";
                cout << "  ID       : " << expenseID[expenseCount - 1] << "\n";
                cout << "  Name     : " << expenseName[expenseCount - 1] << "\n";
                cout << "  Category : " << category[expenseCount - 1] << "\n";
                cout << fixed << setprecision(2);
                cout << "  Amount   : " << amount[expenseCount - 1] << "\n";
                cout << "  Date     : " << date[expenseCount - 1] << "\n";
                break;
            }

            // -----------------------------------------------------------------
            // CASE 2: Display Expenses
            // Prints every saved record in a table. Uses a for loop to walk
            // from index 0 up to expenseCount - 1 (only filled slots).
            // -----------------------------------------------------------------
            case 2: {
                cout << "\n----- All Expenses -----\n";

                // No records have been added yet
                if (expenseCount == 0) {
                    cout << "No expense records found. Use option 1 to add an expense.\n";
                    break;
                }

                // Table header row
                cout << left << setw(8) << "ID"
                     << setw(20) << "Name"
                     << setw(15) << "Category"
                     << setw(12) << "Amount"
                     << setw(15) << "Date"
                     << "\n";
                cout << "------------------------------------------------------------------------\n";

                // Loop through each stored record and print one table row
                cout << fixed << setprecision(2);
                for (int i = 0; i < expenseCount; i++) {
                    cout << left << setw(8) << expenseID[i]
                         << setw(20) << expenseName[i]
                         << setw(15) << category[i]
                         << setw(12) << amount[i]
                         << setw(15) << date[i]
                         << "\n";
                }

                cout << "------------------------------------------------------------------------\n";
                cout << "Total records: " << expenseCount << "\n";
                break;
            }

            // -----------------------------------------------------------------
            // CASE 3: Search Expense
            // User picks search by ID or by expense name. A for loop checks
            // each record. Name search ignores upper/lower case letter differences.
            // -----------------------------------------------------------------
            case 3: {
                cout << "\n----- Search Expense -----\n";

                if (expenseCount == 0) {
                    cout << "No expense records found. Use option 1 to add an expense.\n";
                    break;
                }

                int searchChoice = 0;
                cout << "Search by:\n";
                cout << "1. Expense ID\n";
                cout << "2. Expense Name\n";
                cout << "Enter choice: ";
                while (!(cin >> searchChoice) || (searchChoice != 1 && searchChoice != 2)) {
                    cin.clear();
                    string junk;
                    cin >> junk;
                    cout << "Invalid choice. Enter 1 or 2: ";
                }

                bool found = false;

                if (searchChoice == 1) {
                    int searchId = 0;
                    cout << "Enter expense ID to search: ";
                    while (!(cin >> searchId)) {
                        cin.clear();
                        string junk;
                        cin >> junk;
                        cout << "Invalid ID. Enter a whole number: ";
                    }

                    for (int i = 0; i < expenseCount; i++) {
                        if (expenseID[i] == searchId) {
                            found = true;
                            cout << "\nExpense found:\n";
                            cout << "  ID       : " << expenseID[i] << "\n";
                            cout << "  Name     : " << expenseName[i] << "\n";
                            cout << "  Category : " << category[i] << "\n";
                            cout << fixed << setprecision(2);
                            cout << "  Amount   : " << amount[i] << "\n";
                            cout << "  Date     : " << date[i] << "\n";
                            break;
                        }
                    }
                } else {
                    string searchName;
                    cin.ignore(1000, '\n');
                    cout << "Enter expense name to search: ";
                    getline(cin, searchName);

                    for (int i = 0; i < expenseCount; i++) {
                        bool nameMatch = true;

                        // Names must be same length to be equal
                        if (expenseName[i].length() != searchName.length()) {
                            nameMatch = false;
                        } else {
                            // Compare each letter using lowercase form
                            for (int j = 0; j < searchName.length(); j++) {
                                char storedChar = tolower(expenseName[i][j]);
                                char typedChar = tolower(searchName[j]);
                                if (storedChar != typedChar) {
                                    nameMatch = false;
                                    break;
                                }
                            }
                        }

                        if (nameMatch) {
                            found = true;
                            cout << "\nExpense found:\n";
                            cout << "  ID       : " << expenseID[i] << "\n";
                            cout << "  Name     : " << expenseName[i] << "\n";
                            cout << "  Category : " << category[i] << "\n";
                            cout << fixed << setprecision(2);
                            cout << "  Amount   : " << amount[i] << "\n";
                            cout << "  Date     : " << date[i] << "\n";
                        }
                    }
                }

                if (!found) {
                    cout << "Record not found.\n";
                }

                break;
            }

            // -----------------------------------------------------------------
            // CASE 4: Update Expense
            // Find a record by ID, then overwrite name, category, amount, and date.
            // Expense ID itself is not changed (it stays the lookup key).
            // -----------------------------------------------------------------
            case 4: {
                cout << "\n----- Update Expense -----\n";

                if (expenseCount == 0) {
                    cout << "No expense records found. Use option 1 to add an expense.\n";
                    break;
                }

                int updateId = 0;
                cout << "Enter expense ID to update: ";
                while (!(cin >> updateId)) {
                    cin.clear();
                    string junk;
                    cin >> junk;
                    cout << "Invalid ID. Enter a whole number: ";
                }

                bool found = false;
                int index = 0;

                for (int i = 0; i < expenseCount; i++) {
                    if (expenseID[i] == updateId) {
                        found = true;
                        index = i;
                        break;
                    }
                }

                if (!found) {
                    cout << "Record not found.\n";
                    break;
                }

                cout << "\nUpdating expense ID " << expenseID[index] << "\n";
                cout << "(Enter new values for the fields below)\n\n";

                cin.ignore(1000, '\n');

                cout << "Enter new expense name: ";
                getline(cin, expenseName[index]);

                cout << "Enter new category: ";
                getline(cin, category[index]);

                cout << "Enter new amount: ";
                while (!(cin >> amount[index]) || amount[index] < 0) {
                    cin.clear();
                    string junk;
                    cin >> junk;
                    cout << "Invalid amount. Enter a positive number: ";
                }

                cin.ignore(1000, '\n');

                cout << "Enter new date (e.g. DD-MM-YYYY): ";
                getline(cin, date[index]);

                cout << "\nExpense updated successfully!\n";
                cout << "  ID       : " << expenseID[index] << "\n";
                cout << "  Name     : " << expenseName[index] << "\n";
                cout << "  Category : " << category[index] << "\n";
                cout << fixed << setprecision(2);
                cout << "  Amount   : " << amount[index] << "\n";
                cout << "  Date     : " << date[index] << "\n";
                break;
            }

            // -----------------------------------------------------------------
            // CASE 5: Delete Expense
            // Find record by ID, then shift every record after it one index
            // to the left in all five parallel arrays, and reduce expenseCount.
            // -----------------------------------------------------------------
            case 5: {
                cout << "\n----- Delete Expense -----\n";

                if (expenseCount == 0) {
                    cout << "No expense records found. Use option 1 to add an expense.\n";
                    break;
                }

                int deleteId = 0;
                cout << "Enter expense ID to delete: ";
                while (!(cin >> deleteId)) {
                    cin.clear();
                    string junk;
                    cin >> junk;
                    cout << "Invalid ID. Enter a whole number: ";
                }

                bool found = false;
                int index = 0;

                for (int i = 0; i < expenseCount; i++) {
                    if (expenseID[i] == deleteId) {
                        found = true;
                        index = i;
                        break;
                    }
                }

                if (!found) {
                    cout << "Record not found.\n";
                    break;
                }

                // Shift records left from index + 1 to the end of the list
                for (int i = index; i < expenseCount - 1; i++) {
                    expenseID[i] = expenseID[i + 1];
                    expenseName[i] = expenseName[i + 1];
                    category[i] = category[i + 1];
                    amount[i] = amount[i + 1];
                    date[i] = date[i + 1];
                }

                expenseCount--;

                cout << "Expense with ID " << deleteId << " deleted successfully.\n";
                cout << "Total records remaining: " << expenseCount << "\n";
                break;
            }

            // -----------------------------------------------------------------
            // CASE 6: Generate Report
            // One loop reads every amount[] value to compute totals, min, max,
            // and average. Count comes from expenseCount (number of records).
            // -----------------------------------------------------------------
            case 6: {
                cout << "\n----- Expense Report -----\n";

                if (expenseCount == 0) {
                    cout << "No expense records found. Use option 1 to add an expense.\n";
                    break;
                }

                double totalAmount = 0;
                double highest = amount[0];
                double lowest = amount[0];

                for (int i = 0; i < expenseCount; i++) {
                    totalAmount = totalAmount + amount[i];

                    if (amount[i] > highest) {
                        highest = amount[i];
                    }

                    if (amount[i] < lowest) {
                        lowest = amount[i];
                    }
                }

                double average = totalAmount / expenseCount;

                cout << fixed << setprecision(2);
                cout << "\n--- Summary ---\n";
                cout << "Total number of expenses : " << expenseCount << "\n";
                cout << "Total amount spent       : " << totalAmount << "\n";
                cout << "Highest expense amount   : " << highest << "\n";
                cout << "Lowest expense amount    : " << lowest << "\n";
                cout << "Average expense          : " << average << "\n";
                break;
            }

            // CASE 7: Stop the menu loop and end the program
            case 7:
                cout << "\nThank you for using Expense Tracking System. Goodbye!\n";
                running = false;
                break;

            // Any number other than 1-7
            default:
                cout << "\nInvalid choice. Please enter a number between 1 and 7.\n";
                break;
        }
    }

    return 0;
}
