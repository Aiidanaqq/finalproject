# Online Fitness Activity Logger

## Purpose
The Online Fitness Activity Logger is a console-based application designed to help users log their fitness activities, including different types of workouts, running sessions, and yoga practices. The application allows users to select the type and duration of their workouts, review their exercise details, and save their logs to a file for future reference.

## Design Decisions 
-**Simple Console Interface:**

The application uses a simple console interface to interact with the user, making it accessible without requiring a graphical user interface.
- **File-Based Storage:**

 Each user's workout data is stored in a separate text file named after the user, allowing for easy data retrieval and management.
- **Modular Structure:**

 The application is designed with a modular structure, using functions to handle specific tasks like displaying records, adding new records, and checking user input.
- **Flexibility and Extensibility:**

   The program is designed to be easily extensible, allowing for new types of workouts and durations to be added by simply creating new exercise files.
## Algorithms and Data Structures
- **Vector for Storing Exercises:**

   The vector container from the C++ Standard Library is used to store the list of exercises for each workout.
- **Struct for Fitness Activities:**

   A struct named FitnessActivity is used to encapsulate the details of each workout, including the date, type, duration, and exercises.
- **File I/O Operations:**

   The application uses file input/output streams (ifstream and ofstream) for reading exercise details from predefined files and writing workout logs to the user's file.
## Functions/Modules
- **addRecord:**

   Adds a new fitness activity record to the specified output stream (file).
- **displayRecords:**

   Displays the details of the provided fitness activity records.
getCurrentDate: Retrieves the current date in string format.
- **finishWorkout:**

   Asks the user if they want to finish and save the workout.
- **main:**

   The main function that drives the application, handling user input and coordinating the workflow.

