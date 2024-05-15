#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Structure representing a single fitness activity record
struct FitnessActivity {
    string date;
    string type;
    int duration; // duration in minutes
    vector<string> exercises; // set of exercises
};

// Function to add a fitness activity record to the file
void addRecord(ostream& file, const FitnessActivity& activity) {
    file << "Date: " << activity.date << ", Type: " << activity.type << ", Duration: " << activity.duration << " minutes\n";
    file << "Exercises:\n";
    for (const auto& exercise : activity.exercises) {
        file << "- " << exercise << endl;
    }
    file << endl;
}

// Function to display all fitness activity records
void displayRecords(const vector<FitnessActivity>& activities) {
    if (activities.empty()) {
        cout << "No records found.\n";
        return;
    }
    for (const auto& activity : activities) {
        cout << "Date: " << activity.date << ", Type: " << activity.type << ", Duration: " << activity.duration << " minutes\n";
        cout << "Exercises:\n";
        for (const auto& exercise : activity.exercises) {
            cout << "- " << exercise << endl;
        }
        cout << endl;
    }
}

// Function to get current date in string format
string getCurrentDate() {
    time_t now = time(nullptr);
    tm* current_time = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", current_time);
    return string(buffer);
}

// Function to check if the user wants to finish the workout
bool finishWorkout() {
    char choice;
    cout << "Would you like to finish the workout and save it? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

int main() {
    cout << "Welcome to the Online Gym!\n"; // User greeting

    // Displaying all functions in a beautiful frame
    cout << "************************************************************\n";
    cout << "*                      Description                         *\n";
    cout << "************************************************************\n";
    cout << "* 1.Logs fitness activities: workouts, runs, and yoga.     *\n";
    cout << "*                                                          *\n";
    cout << "* 2.Selects a suitable workout time: 30, 45 and 60 minutes *\n";
    cout << "*                                                          *\n";
    cout << "* 3. Providing a record of fitness progress over time.     *\n";
    cout << "************************************************************\n\n";

    string username; // Variable to store the user's name
    cout << "Enter your name to save your workouts: ";
    cin >> username;

    // Creating a file name based on the username
    string filename = username + "_fitness_data.txt";

    // Create a new file for the user's fitness data
    ofstream dataFile(filename, ios::app);
    if (!dataFile.is_open()) {
        cerr << "Error: Unable to create file for writing.\n";
        return 1;
    }

    while (true) {
        // Ask the user to choose workout type
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

        // Ask the user to choose workout duration
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

        // Create a new fitness activity record
        FitnessActivity newActivity;
        newActivity.date = getCurrentDate(); // Set current date
        newActivity.type = workoutType;
        newActivity.duration = duration;

        // Open the file containing exercise set for the chosen workout type and duration
        ifstream exercisesFile(workoutType + "_" + to_string(duration) + ".txt");
        if (exercisesFile.is_open()) {
            string exercise;
            while (getline(exercisesFile, exercise)) {
                newActivity.exercises.push_back(exercise);
            }
            exercisesFile.close();
        } else {
            cerr << "Error: Unable to open " << workoutType << " exercise file.\n";
            return 1;
        }

        // Display all records
        cout << "\nYour workout:\n";
        displayRecords({newActivity});

        // Check if the user wants to finish the workout
        if (finishWorkout()) {
            // Append the new activity record to the file
            addRecord(dataFile, newActivity);
            cout << "\nYour workout has been saved.\n";
        }

        // Check if the user wants to continue
        char continueChoice;
        cout << "Do you want to log another workout? (Y/N): ";
        cin >> continueChoice;
        if (continueChoice != 'Y' && continueChoice != 'y') {
            cout << "See you, " << username << "!\n";
            break; // Exit the loop if the user doesn't want to continue
        }
    }

    // Close the file
    dataFile.close();

    return 0;
}
