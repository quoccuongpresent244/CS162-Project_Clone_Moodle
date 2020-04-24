#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct Date {
	int d, m, y;
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
	Date dob;
	string clas;
	//int type;
};
struct lecturer {
	string username;
	string password;
	string fullname;
	string degree;
	int gender;
};

void loadStaff(ifstream& fin, staff a[], const int n);
void loadLecturer(ifstream& fin, lecturer a[], const int n);
void loadStudent(ifstream& fin, student a[], const int n);

void login(staff giaovu[], lecturer giaovien[], student hocsinh[],
	const int Nstaff, const int Nlecturer, const int Nstudent);

void staffFeature(staff a);
void lecturerFeature(lecturer a);
void studentFeature(student a);

#endif