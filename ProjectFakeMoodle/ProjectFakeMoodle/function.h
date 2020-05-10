#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
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
	string endDate;
	string dayOfWeek;
	string startTime;
	string endTime;
	string room;
	int status;
};

struct stuincourse { //student in course containing student infor, scoreboard and attendance
	string id;
	string password;
	string fullname;
	string dob;
	string clas;
	int status;
	int midterm;
	int final;
	int bonus;
	int total;
					// Tao chua tao attendance
};

void login(staff giaovu[], lecturer giaovien[], student hocsinh[],
	const int Nstaff, const int Nlecturer, const int Nstudent);
void loadStaff(ifstream& fin, staff*& a, const int n);
void loadLecturer(ifstream& fin, lecturer*& a, const int n);
void loadStudent(ifstream& fin, student*& hocsinh, const int Nstudent, classes*& lophoc, int& Nclass);

void updateAllClassTXT(student* hocsinh, const int Nstudent, int Nclass, classes* lophoc);
void updateAClassTXT(student* hocsinh, const int Nstudent, int Nclass, classes* lophoc, string classname);
void updateStudentTXT(student* student, const int Nstudent, string filename);



void staffFeature(staff a);
//CLASS
void importCSV(int& Nstudent, int& studentCapa, student*& hocsinh, classes*& lophoc, int& Nclass);
void addAStudenttoClass(int& Nstudent, int& studentCapa, student*& hocsinh, classes* lophoc, int Nclass);
void viewListOfClasses(classes* lophoc, int Nclass);
void viewListOfStudentsInClass();

//COURSE
void importCourseCSV();
void addANewCourse();
void editACourse();
void updateClassScheduleTXT(course* khoahoc, int Ncourse, string coursename);
void loadClassScheduleTXT(course*& khoahoc, int& Ncourse, string coursename);
void updateCourseStudentTXT(string coursetudent, string classname);


void lecturerFeature(lecturer a);
void studentFeature(student a);



#endif