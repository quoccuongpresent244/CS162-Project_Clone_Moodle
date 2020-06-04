#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <Windows.h>
#include <conio.h>

using namespace std;

extern int  Nstaff, Nlecturer, Nstudent, Nclass, Nleave;
extern int  staffCapa, lecturerCapa, studentCapa;
extern string a[10];


struct date{
	int year, month, day;
};
struct classes {
	string classname;
	int numofstu;
};

struct staff {
	string username;
	string password;
	string fullname;
	int gender;
};
struct student {
	string id;
	string password;
	string fullname;
	string dob;
	string clas;
	int status;
};
struct lecturer {
	string username;
	string password;
	string fullname;
	string degree;
	int gender;
};

struct course {
	string courseID;
	string courseName;
	string clas;
	string instructor;
	string instructorUsername;
	string degree;
	string gender;
	string startDate;
	//date startDate;
	string endDate;
	//date endDate;
	string dayOfWeek;
	string startTime;
	string endTime;
	string room;
	//int status;
};
struct stuincourse { //student in course containing student infor, scoreboard and attendance
	string id;
	string password;
	string fullname;
	string dob;
	string clas;
	int status;

	float midterm;
	float final;
	float bonus;
	float total;

	string attendance[10];

	int statusCourse;
};

extern classes* lophoc;
extern staff* giaovu;
extern lecturer* giaovien;
extern student* hocsinh;

void firstMenu();
void login();
void loadStaff();
void loadLecturer();
void loadStudent();

void updateAllClassTXT();
void updateAClassTXT(string classname);
void updateStudentTXT(string filename);
void updatePosition(string filename);

//CLASS
void importCSV();
void addAStudenttoClass();
void editStudent();
//task 9
void RemoveAStudent();
void ChangeClass();
void viewListOfClasses();
void viewListOfStudentsInClass();

//COURSE
void importCourseCSV();
void addANewCourse();
void editACourse();
void removeACourse();
void RemoveASpecificStu();
void AddASpecificStu();
void listofCourse(); //task 20: view List of Course
void listofStuinCourse(); //task21: view student in a course
void listofAttendance(); //task 23: view attendance list
void viewLecturer(); //task 23: view all lecturer

void updateClassScheduleTXT(course* khoahoc, int Ncourse, string classScheduleTXT);
void loadClassScheduleTXT(course*& khoahoc, int& Ncourse, string classScheduleTXT);
void loadStuinCourseTXT(stuincourse*& stuinCourse, int& NstuinCourse, int& NstuinCourseLeave, string stuinCourseTXT);
void setupCourseStudentTXT(string stuinCourseTXT, string classname);
void updateStuinCourseTXT(stuincourse* stuinCourse, int NstuinCourse, int NstuinCourseLeave, string stuinCourseTXT);
//for attendance 
bool nhuan(int y);
void plus7days(int &y, int &m, int &d);
void createAttendance(course khoahoc);

void staffMenuShow();
void staffFeature(staff a);
void lecturerMenuShow();
void lecturerFeature(lecturer a);
void studentFeature(student a);


//Function for lecturer
void importScoreboardCSV();
void editGradeOfStu();

#endif