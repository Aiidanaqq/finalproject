#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct FitnessActivity {
    std::string date;
    std::string type;
    int duration; // in minutes
};

void addRecord(std::ostream& file, const FitnessActivity& activity) {
    file << activity.date << "," << activity.type << "," << activity.duration << "\n";
}

void displayRecords(const std::vector<FitnessActivity>& activities) {
    if (activities.empty()) {
        std::cout << "No records found.\n";
        return;
    }
    for (const auto& activity : activities) {
        std::cout << "Date: " << activity.date << ", Type: " << activity.type << ", Duration: " << activity.duration << " minutes\n";
    }
}

int main() {
    // Open file for reading and writing
    std::fstream dataFile("fitness_data.csv", std::ios::in | std::ios::out | std::ios::app);

    if (!dataFile.is_open()) {
        std::cerr << "Error: Unable to open file for reading and writing.\n";
        return 1;
    }

    // Example: Add a new record
    FitnessActivity newActivity = {"2024-04-29", "Workout", 60};
    addRecord(dataFile, newActivity);

    // Read records from file and display
    dataFile.seekg(0); // Move cursor to the beginning of the file
    std::vector<FitnessActivity> activities;
    std::string line;
    while (std::getline(dataFile, line)) {
        std::istringstream iss(line);
        std::string date, type;
        int duration;
        char comma;
        if (iss >> date >> comma >> type >> comma >> duration) {
            activities.push_back({date, type, duration});
        }
    }

    // Display all records
    displayRecords(activities);

    dataFile.close(); // Close the file

    return 0;
}
