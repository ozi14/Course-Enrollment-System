# Course Enrollment System

This repository contains a C++ implementation of a simple course enrollment system. The program allows users to build courses, enroll students, add students to courses, drop students from courses, and view course rosters and student schedules. It provides a command-line interface to interact with the system.

## Table of Contents
- [Overview](#overview)
- [Installation](#installation)
- [Usage](#usage)
- [Commands](#commands)
- [Contributing](#contributing)


## Overview

The course enrollment system is implemented in C++ and uses basic data structures like structs and arrays to manage courses and students. Each course has a unique Course Reference Number (CRN), a department, a course number, and a name. Students are identified by their B Number and have a user ID, first name, and last name. The system provides various functionalities to build courses, enroll students, add students to courses, drop students from courses, and view course rosters and student schedules.

## Installation

1. Clone the repository to your local machine:

```bash
git clone https://github.com/your_username/your_repository.git
```

2. Compile the C++ program using your preferred C++ compiler. For example, with g++, run:

```bash
g++ -o course_enrollment course_enrollment.cpp
```

## Usage

1. Run the compiled program:

```bash
./course_enrollment
```

2. The program will prompt you to enter commands. Follow the instructions to interact with the system.

## Commands

The course enrollment system supports the following commands:

- `build <CRN> <Department> <Number> <Name>`: Build a new course with the given CRN, department, course number, and name.

- `cancel <CRN>`: Cancel a course with the given CRN.

- `enroll <BNumber> <UserID> <First> <Last>`: Enroll a new student with the given B Number, user ID, first name, and last name.

- `add <BNumber> <CRN>`: Add a student with the given B Number to a course with the given CRN.

- `drop <BNumber> <CRN>`: Drop a student with the given B Number from a course with the given CRN.

- `roster <CRN>`: View the roster of students enrolled in a course with the given CRN.

- `schedule <BNumber>`: View the schedule of a student with the given B Number.

- `quit`: Exit the program.

## Contributing

Contributions to the course enrollment system are welcome! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

