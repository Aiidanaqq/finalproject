#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct FitnessActivity {
    string date;
    string type;
    int duration; // in minutes
};

void addRecord(ostream& file, const FitnessActivity& activity) {
    file << activity.date << "," << activity.type << "," << activity.duration << "\n";
}

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
    string filename;
    cout << "Enter filename to save fitness data: ";
    cin >> filename;

    fstream dataFile(filename, ios::in | ios::out | ios::app);

    if (!dataFile.is_open()) {
        cerr << "Error: Unable to open file for reading and writing.\n";
        return 1;
    }

    string workoutType;
    cout << "Enter workout type: ";
    cin >> workoutType;

    int duration;
    cout << "Enter duration (in minutes): ";
    cin >> duration;

    FitnessActivity newActivity = {"2024-04-29", workoutType, duration};
    addRecord(dataFile, newActivity);

    dataFile.seekg(0);
    vector<FitnessActivity> activities;
    string line;
    while (getline(dataFile, line)) {
        istringstream iss(line);
        string date, type;
        int duration;
        char comma;
        if (iss >> date >> comma >> type >> comma >> duration) {
            activities.push_back({date, type, duration});
        }
    }

    displayRecords(activities);

    dataFile.close();

    return 0;
}
