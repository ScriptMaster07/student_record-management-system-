This project is a Student Record Management System (SRMS) developed in C. It uses file handling, structures, loops, conditional logic, and modular programming to manage student information stored in external text files.

The system provides the following features:

Login using roll number.

Profile viewing.

Attendance calculation.

Marks display.

Fee tracking.

Daily timetable display based on real-time weekday.

Admin control for managing student records.

FEATURES

Login and Authentication

Accepts roll number as login input.

Credentials are verified from credentials.txt.

Supports ADMIN and STUDENT roles.

System locks after 3 failed login attempts.

Student Profile Module

Reads ID, name, department, and CGPA from students.txt.

Displays the academic profile of the student.

Attendance Module

Reads attendance data from attendance.txt.

Calculates attendance percentage.

Displays present classes, total classes, and percentage.

Marks Module

Reads marks from markss.txt.

Subjects include Maths, DSA, Digital Logic, DBMS, and C Programming.

Fee Module

Reads total fee and paid fee from fees.txt.

Calculates due fee automatically.

Displays all fee-related details.

Timetable Module

Detects the current weekday using system time.

Matches the student's department and day in timetable.txt.

Displays three subjects for the day.

Admin Module

Add new student records.

View all students.

Delete students by ID.

Update CGPA of existing students.

Updated data is saved to students.txt.

FILE STRUCTURE

students.txt - Stores student information
credentials.txt - Stores roll numbers, passwords, and roles
attendance.txt - Stores total and present classes
markss.txt - Stores subject-wise marks
fees.txt - Stores total fee and paid fee
timetable.txt - Stores the daily timetable for each department
main.c - Contains the full program code

HOW TO RUN

Compile the program using: gcc main.c -o project

Run the program using: ./project

Ensure all required .txt files are in the same folder as the executable.

FUTURE ENHANCEMENTS

Password change feature

GUI interface

SQL database integration

Student registration system

Weekly timetable display

AUTHOR
CH. Lakshmi Deepak
CSE Student

