#include <iostream>
#include <string>
#include <cstring>
#include <iterator>

using namespace std;

const int MAX_COURSES = 100;
const int MAX_STUDENTS = 1000;
struct Student;
struct Course {
    string crn;
    string department;
    string number;
    string name;
    Student* enrolled_students[MAX_STUDENTS];
    int num_enrolled_students = 0;
};

struct Student {
    string bnumber;
    string userid;
    string first;
    string last;
};

int num_courses = 0;
Course* courses[MAX_COURSES];

int num_students = 0;
Student* students[MAX_STUDENTS];

bool is_valid_crn(string crn) {
    if (crn.length() != 6) {
        return false;
    }
    for (int i = 0; i < 6; i++) {
        if (!isdigit(crn[i])) {
            return false;
        }
    }
    return true;
}

bool is_valid_department( string department) {
    if (department.length() < 2 || department.length() > 4) {
        return false;
    }
    for (size_t i = 0; i < department.length(); i++) {
        if (!isupper(department[i])) {
            return false;
        }
    }
    return true;
}

bool is_valid_number(string number) {
    if (number.length() != 3) {
        return false;
    }
    int n = stoi(number);
    if (n < 100 || n > 700) {
        return false;
    }
    return true;
}

bool is_valid_bnumber(string bnumber) {
    if (bnumber.length() != 9 || bnumber[0] != 'B') {
        return false;
    }
    for (size_t i = 1; i < bnumber.length(); i++) {
        if (!isdigit(bnumber[i])) {
            return false;
        }
    }
    return true;
}

bool is_valid_userid(string userid) {
    if (userid.length() == 0 || !isalpha(userid[0])) {
        return false;
    }
    for (size_t i = 1; i < userid.length(); i++) {
        if (!isalnum(userid[i])) {
            return false;
        }
    }
    return true;
}

void build(string crn, string department, string number,string name) {
    // Check input validity
    if (!is_valid_crn(crn)) {
        cout << "Input Error: illegal CRN" << endl;
        return;
    }
    if (!is_valid_department(department)) {
        cout << "Input Error: illegal department" << endl;
        return;
    }
    if (!is_valid_number(number)) {
        cout << "Input Error: illegal course number" << endl;
        return;
    }
    if (name.empty()) {
        cout << "Input Error: course name cannot be empty" << endl;
        return;
    }

    // Check if course with the same CRN already exists
    for (int i = 0; i < num_courses; i++) {
        if (courses[i]->crn == crn) {
            cout << "Fail: cannot build course " << department << number << " (CRN: " << crn << "): CRN exists" << endl;
            return;
        }
    }

    // Create new course
    if (num_courses >= MAX_COURSES) {
        cout << "Error: maximum number of courses reached" << endl;
        return;
    }
    Course* course = new Course;
    course->crn = crn;
    course->department = department;
    course->number = number;
    course->name = name;
    courses[num_courses] = course;
    num_courses++;

    // Success message
    cout << "Success: built course " << department << number << " (CRN: " << crn << "): " << name << endl;
}

void cancel_course(string crn) {
    if (!is_valid_crn(crn)) {
        cout << "Input Error: illegal CRN" << endl;
        return;
    }
    bool found = false;
    for (int i = 0; i < num_courses; i++) {
        if (courses[i]->crn == crn) {
            found = true;
            delete courses[i];
            for (int j = i; j < num_courses - 1; j++) {
                courses[j] = courses[j+1];
            }
            num_courses--;
            cout << "Success: cancelled course " << crn << endl;
            break;
        }
    }
    if (!found) {
        cout << "Fail: cannot cancel course, CRN does not exist" << endl;
    }
}

void enroll_student(string bnumber, string userid, string first, string last) {
    if (!is_valid_bnumber(bnumber) || !is_valid_userid(userid)) {
        cout << "Input Error: invalid student information" << endl;
        return;
    }
    for (int i = 0; i < num_students; i++) {
        if (students[i]->bnumber == bnumber) {
            cout << "Fail: cannot enroll student, B Number exists" << endl;
            return;
        }
    }
    if (num_students >= MAX_STUDENTS) {
        cout << "Error: maximum number of students reached" << endl;
        return;
    }
    Student* student = new Student;
    student->bnumber = bnumber;
    student->userid = userid;
    student->first = first;
    student->last = last;
    students[num_students] = student;
    num_students++;
    cout << "Success: enrolled student " << bnumber << " (" << userid << ") " << last << ", " << first << endl;
}
void add(string bnumber, string crn) {
    // Check input validity
    if (!is_valid_bnumber(bnumber)) {
        cout << "Input Error: illegal B Number" << endl;
        return;
    }
    if (!is_valid_crn(crn)) {
        cout << "Input Error: illegal CRN" << endl;
        return;
    }

    // Find student with the given B Number
    Student* student = nullptr;
    for (int i = 0; i < num_students; i++) {
        if (students[i]->bnumber == bnumber) {
            student = students[i];
            break;
        }
    }
    if (student == nullptr) {
        cout << "Fail: cannot add, student " << bnumber << " does not exist" << endl;
        return;
    }

    // Find course with the given CRN
    Course* course = nullptr;
    for (int i = 0; i < num_courses; i++) {
        if (courses[i]->crn == crn) {
            course = courses[i];
            break;
        }
    }
    if (course == nullptr) {
        cout << "Fail: cannot add, course " << crn << " does not exist" << endl;
        return;
    }

    // Check if student is already enrolled in the course
    for (int i = 0; i < course->num_enrolled_students; i++) {
        if (course->enrolled_students[i] == student) {
            cout << "Fail: cannot add, student " << bnumber << " already enrolled in course " << crn << endl;
            return;
        }
    }

    // Enroll student in course
    if (course->num_enrolled_students >= MAX_STUDENTS) {
        cout << "Error: maximum number of enrolled students reached for course " << crn << endl;
        return;
    }
    course->enrolled_students[course->num_enrolled_students] = student;
    course->num_enrolled_students++;

    // Success message
    cout << "Success: added student " << bnumber << " into course " << crn << endl;
}


void drop_student_from_course(string bnumber, string crn) {
    if (!is_valid_bnumber(bnumber) || !is_valid_crn(crn)) {
        cout << "Input Error: invalid B Number or CRN" << endl;
        return;
    }
    bool student_found = false;
    for (int i = 0; i < num_students; i++) {
        if (students[i]->bnumber == bnumber) {
            student_found = true;
            break;
        }
    }
    if (!student_found) {
        cout << "Fail: cannot drop, student " << bnumber << " not enrolled in any course" << endl;
        return;
    }
    bool course_found = false;
    for (int i = 0; i < num_courses; i++) {
        if (courses[i]->crn == crn) {
            course_found = true;
            break;
        }
    }
    if (!course_found) {
        cout << "Fail: cannot drop, course " << crn << " does not exist" << endl;
        return;
    }
    // check if student is enrolled in the course
    bool enrolled = false;
    for (int i = 0; i < num_courses; i++) {
        if (courses[i]->crn == crn) {
            for (int j = 0; j < courses[i]->num_enrolled_students; j++) {
                if (courses[i]->enrolled_students[j]->bnumber == bnumber) {
                    enrolled = true;
                    courses[i]->enrolled_students[j] = nullptr;
                    // move the remaining students down in the array
                    for (int k = j; k < courses[i]->num_enrolled_students - 1; k++) {
                        courses[i]->enrolled_students[k] = courses[i]->enrolled_students[k+1];
                    }
                    courses[i]->num_enrolled_students--;
                    break;
                }
            }
            break;
        }
    }
    if (!enrolled) {
        cout << "Fail: cannot drop, student " << bnumber << " not enrolled in course " << crn << endl;
        return;
    }
    cout << "Success: removed student " << bnumber << " from course " << crn << endl;
}

void roster(string crn) {
    if (!is_valid_crn(crn)) {
        cout << "Input Error: illegal CRN" << endl;
        return;
    }
    int count = 0;
    cout << "CRN: " << crn << endl;
    for (int i = 0; i < num_courses; i++) {
        for (int j = 0; j < courses[i]->num_enrolled_students; j++) {
            if (courses[i]->crn == crn && courses[i]->enrolled_students[j]->bnumber == students[i]->bnumber) {
                count++;
                cout << students[i]->bnumber << " " << students[i]->first << " " << students[i]->last << endl;
                break;
            }
        }
    }
    cout << "Students: " << count << endl;
}

void schedule(string bnumber) {
    // Check if bnumber is valid
    if (!is_valid_bnumber(bnumber)) {
        cout << "Input Error: invalid B Number" << endl;
        return;
    }

    // Find the student with the given bnumber
    Student* student = nullptr;
    for (int i = 0; i < num_students; i++) {
        if (students[i]->bnumber == bnumber) {
            student = students[i];
            break;
        }
    }

    // Check if the student was found
    if (student == nullptr) {
        cout << "Fail: cannot display schedule, student not found" << endl;
        return;
    }

    // Print out the student's name and course schedule
    cout << "Student: " << student->bnumber << ": " << student->first << " " << student->last << endl;
    bool found_courses = false;
    for (int i = 0; i < num_courses; i++) {
        for (int j = 0; j < courses[i]->num_enrolled_students; j++) {
            if (courses[i]->enrolled_students[j] == student) {
                if (!found_courses) {
                    found_courses = true;
                    cout << "Schedule:" << endl;
                }
                cout << courses[i]->crn << " " << courses[i]->department << " " << courses[i]->number << " " << courses[i]->name << endl;
            }
        }
    }
    if (!found_courses) {
        cout << "Fail: cannot display schedule, student is not enrolled in any courses" << endl;
    }
}

int main() {
    string command;

    while (true) {
        cout << "Enter command: ";
        cin >> command;

        if (command == "build") {
	  string crn, department, number, name;
            cin >> crn >> department >> number >> name;
            build(crn, department, number, name);
        } else if (command == "cancel") {
            string crn;
            cin >> crn;
            cancel_course(crn);
        } else if (command == "enroll") {
            string bnumber, userid, first, last;
            cin >> bnumber >> userid >> first >> last;
            enroll_student(bnumber, userid, first, last);
        } else if (command == "add") {
            string bnumber, crn;
            cin >> bnumber >> crn;
            add(bnumber, crn);
        }else if(command == "drop"){ 
            string bnumber, crn;
            cin >> bnumber >> crn;
            drop_student_from_course(bnumber, crn);
        }else if(command == "roster"){
            string crn;
            cin >> crn;
            roster(crn);
        }else if(command == "schedule"){
            string bnumber;
            cin >> bnumber;
            schedule(bnumber);
        }else if (command == "quit") {
            break;
        } else {
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
