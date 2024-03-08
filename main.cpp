#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to prompt user for student details and save them to a file
void saveStudentDetails() {
    string name, admNumber;
    int marks, units;

    // Prompt user for student details
    cout << "Enter student name: ";
    getline(cin, name);
    cout << "Enter admission number: ";
    getline(cin, admNumber);
    cout << "Enter marks: ";
    cin >> marks;
    cout << "Enter number of units: ";
    cin >> units;
system("cls");

    // Prompt user for unit marks
    vector<int> unitMarks(units);
    for (int i = 0; i < units; ++i) {
        cout << "Enter marks for unit " << i + 1 << ": ";
        cin >> unitMarks[i];
    }

    // Save student details to file
    ofstream outputFile("studentmarks.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << name << "," << admNumber << "," << marks;
        for (int mark : unitMarks) {
            outputFile << "," << mark;
        }
        outputFile << endl;
        outputFile.close();
        cout << "Student details saved successfully." << endl;
    } else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
}

// Function to read student details from file and display in terminal
void displayStudentDetails() {
    ifstream inputFile("studentmarks.txt");
    string line;

    cout << "Student details:" << endl;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
}

// Function to edit student details in the file
void editStudentDetails() {
    string studentName;
    cout << "Enter the name of the student whose details you want to edit: ";
    getline(cin, studentName);

    ifstream inputFile("studentmarks.txt");
    ofstream tempFile("temp.txt");

    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        size_t pos = line.find(studentName);
        if (pos != string::npos) {
            found = true;
            string newName, newAdmNumber;
            int newMarks, newUnits;

            cout << "Enter new name: ";
            getline(cin, newName);
            cout << "Enter new admission number: ";
            getline(cin, newAdmNumber);
            cout << "Enter new marks: ";
            cin >> newMarks;
            cout << "Enter new number of units: ";
            cin >> newUnits;

            vector<int> newUnitMarks(newUnits);
            for (int i = 0; i < newUnits; ++i) {
                cout << "Enter new marks for unit " << i + 1 << ": ";
                cin >> newUnitMarks[i];
            }

            line = newName + "," + newAdmNumber + "," + to_string(newMarks);
            for (int mark : newUnitMarks) {
                line += "," + to_string(mark);
            }
        }
        tempFile << line << endl;
    }

    inputFile.close();
    tempFile.close();

    remove("studentmarks.txt");
    rename("temp.txt", "studentmarks.txt");

    if (found) {
        cout << "Student details updated successfully." << endl;
    } else {
        cout << "Student not found." << endl;
    }
}

// Function to display results in sorted manner
void displaySortedResults() {
    ifstream inputFile("studentmarks.txt");
    vector<string> lines;

    string line;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }

    sort(lines.begin(), lines.end());

    cout << "Student details (sorted):" << endl;
    for (const string& sortedLine : lines) {
        cout << sortedLine << endl;
    }

    inputFile.close();
}

// Function to search and display results of specific student
void searchAndDisplayResults(const string& studentName) {
    ifstream inputFile("studentmarks.txt");
    string line;
    bool found = false;

    cout << "Results for student '" << studentName << "':" << endl;
    while (getline(inputFile, line)) {
        size_t pos = line.find(studentName);
        if (pos != string::npos) {
            cout << line << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Student '" << studentName << "' not found." << endl;
    }
    inputFile.close();
}

int main() {
    int choice;
    string studentName;
    do {
        cout << "\n1. Save student details\n"
                "2. Display all student details\n"
                "3. Edit student details\n"
                "4. Display results in sorted manner\n"
                "5. Search and display results of specific student\n"
                "6. Exit\n"
                "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Consume the newline character left in the buffer

        switch (choice) {
            case 1:
                saveStudentDetails();
                break;
            case 2:
                displayStudentDetails();
                break;
            case 3:
                editStudentDetails();
                break;
            case 4:
                displaySortedResults();
                break;
            case 5:
                cout << "Enter student name to search: ";
                getline(cin, studentName);
                searchAndDisplayResults(studentName);
                break;
            case 6:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }

    } while (choice != 6);
    return 0;
}
