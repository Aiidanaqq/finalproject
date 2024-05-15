#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Structure representing a single fitness activity record
struct FitnessActivity {
    string date;
    string type;
    int duration; // duration in minutes
};

// Function to add a fitness activity record to the file
void addRecord(ostream& file, const FitnessActivity& activity) {
    file << activity.date << "," << activity.type << "," << activity.duration << "\n";
}

// Function to display all fitness activity records
void displayRecords(const vector<FitnessActivity>& activities) {
    if (activities.empty()) {
        cout << "No records found.\n";
        return;
    }
    for (const auto& activity : activities) {
        cout << "Date: " << activity.date << ", Type: " << activity.type << ", Duration: " << activity.duration << " minutes\n";
    }
}

int main() {
    cout << "Welcome to the Online Gym!\n"; // User greeting

    // Displaying all functions in a beautiful frame
    cout << "************************************************************\n";
    cout << "*                     Description                         *\n";
    cout << "**********************************************************\n";
    cout << "* 1.Logs fitness activities: workouts, runs, and yoga.    *\n";
    cout << "*                                                         *\n";
    cout << "* 2.Selects a suitable workout time: 30, 45 and 60 minutes *\n";
    cout << "*                                                         *\n";
    cout << "* 3. Providing a record of fitness progress over time.    *\n";
    cout << "************************************************************\n\n";

    string username; // Variable to store the user's name
    cout << "Enter your name to save your workouts: ";
    cin >> username;

    // Creating a file name based on the username
    string filename = username + "_fitness_data.txt";

    fstream dataFile(filename, ios::in | ios::out | ios::app);

    if (!dataFile.is_open()) {
        cerr << "Error: Unable to open file for reading and writing.\n";
        return 1;
    }

    cout << "**********************************************************\n";
    cout << "*                   Choose the workout type              *\n";
    cout << "**********************************************************\n";
    cout << "* 1. Workout                                             *\n";
    cout << "* 2. Run                                                 *\n";
    cout << "* 3. Yoga                                                *\n";
    cout << "**********************************************************\n\n";
    cout << "Enter the workout number: ";

    int workoutChoice;
    cin >> workoutChoice;

    string workoutType;
    switch (workoutChoice) {
        case 1:
            workoutType = "Workout";
            break;
        case 2:
            workoutType = "Run";
            break;
        case 3:
            workoutType = "Yoga";
            break;
        default:
            cerr << "Error: Invalid workout choice.\n";
            return 1;
    }

    cout << "**********************************************************\n";
    cout << "*                  Choose the duration                   *\n";
    cout << "**********************************************************\n";
    cout << "* 1. 30 minutes                                          *\n";
    cout << "* 2. 45 minutes                                          *\n";
    cout << "* 3. 60 minutes                                          *\n";
    cout << "**********************************************************\n\n";
    cout << "Enter the duration number: ";

    int durationChoice;
    cin >> durationChoice;

    int duration;
    switch (durationChoice) {
        case 1:
            duration = 30;
            break;
        case 2:
            duration = 45;
            break;
        case 3:
            duration = 60;
            break;
        default:
            cerr << "Error: Invalid duration choice.\n";
            return 1;
    }

    FitnessActivity newActivity = {"2024-04-29", workoutType, duration};
    addRecord(dataFile, newActivity);

    // Move the file pointer to the beginning of the file to read all records
    dataFile.seekg(0);
    vector<FitnessActivity> activities;
    string line;
    // Read each line of the file, parse it, and add to the vector of records
    while (getline(dataFile, line)) {
        istringstream iss(line);
        string date, type;
        int duration;
        char comma;
        if (iss >> date >> comma >> type >> comma >> duration) {
            activities.push_back({date, type, duration});
        }
    }

    // Display all records
    displayRecords(activities);

    // Close the file
    dataFile.close();

    return 0;
}
