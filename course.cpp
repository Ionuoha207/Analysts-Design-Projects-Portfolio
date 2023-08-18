#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

// Structure to hold information about a course
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Function to sort courses alphanumerically
bool compareCourses(const Course &course1, const Course &course2) {
    return course1.courseNumber < course2.courseNumber;
}

// Class responsible for loading and managing course data
class CoursePlanner {
private:
    map<string, Course> courses;

public:
    // Load course data from a file
    void loadCourseData(const string &filename) {
        ifstream inputFile(filename);
        if (!inputFile) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string courseNumber, name, prereq;
            if (getline(iss, courseNumber, ',') && getline(iss, name, ',')) {
                Course course;
                course.courseNumber = courseNumber;
                course.name = name;

                while (getline(iss, prereq, ',')) {
                    course.prerequisites.push_back(prereq);
                }

                courses[courseNumber] = course;
            } else {
                cerr << "Error: Invalid line format in file " << filename << endl;
            }
        }

        inputFile.close();
        cout << "Course data loaded successfully.\n"; // Provide feedback
    }

    // Print the list of all courses (sorted alphanumerically)
    void printCourseList() {
        if (courses.empty()) {
            cout << "No course data found." << endl;
        } else {
            cout << "Here is a sample schedule:" << endl;

            // Create a vector of courses for sorting
            vector<Course> sortedCourses;
            for (const auto &coursePair : courses) {
                sortedCourses.push_back(coursePair.second);
            }

            // Sort courses alphanumerically using custom compare function
            sort(sortedCourses.begin(), sortedCourses.end(), compareCourses);

            // Print sorted course list
            for (const Course &course : sortedCourses) {
                cout << course.courseNumber << ", " << course.name << endl;
            }
        }
    }

    // ... (Rest of the class methods remain the same)
};

int main() {
    // Create an instance of the CoursePlanner class
    CoursePlanner planner;

    string filename = "/location_of_file/Course_list/course_data.txt"; // Declare filename here

    int choice;
    string courseNumber;
    do {
        cout << "\nWelcome to the Course Planner\n";
        cout << "--------------------------------\n";
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course Details\n";
        cout << "9. Exit\n";
        cout << "--------------------------------\n";
        cout << "Please select an option: ";
        cin >> choice;

        if (cin.fail()) {
            cerr << "\nError: Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                // Check if the file exists before loading course data
                ifstream fileCheck(filename);
                if (!fileCheck) {
                    cerr << "Error: Could not open file " << filename << endl;
                    return 1;
                } else {
                    // Load course data from the file
                    planner.loadCourseData(filename);
                }
                break;
            }
            case 2:
                planner.printCourseList();
                break;
            case 3: {
                cout << "\nEnter the course number: ";
                cin >> courseNumber;
                // Convert course number to uppercase for consistency
                transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
                planner.printCourse(courseNumber);
                break;
            }
            case 9:
                cout << "\nThank you for using the Course Planner!\n";
                break;
            default:
                cout << "\n" << choice << " is not a valid option.\n";
        }
    } while (choice != 9);

    return 0;
}