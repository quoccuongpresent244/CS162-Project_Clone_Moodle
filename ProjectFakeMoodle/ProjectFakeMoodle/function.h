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
	//int type;
};
struct lecturer {
	string username;
	string password;
	string fullname;
	string degree;
	int gender;
};

void loadStaff(ifstream& fin, staff*& a, const int n);
void loadLecturer(ifstream& fin, lecturer*& a, const int n);
void loadStudent(ifstream& fin, student*& hocsinh, const int Nstudent, classes*& lophoc, int& Nclass);
void updateAllClassTXT(student* hocsinh, const int Nstudent, int Nclass, classes* lophoc);

void login(staff giaovu[], lecturer giaovien[], student hocsinh[],
	const int Nstaff, const int Nlecturer, const int Nstudent);

void staffFeature(staff a);
void lecturerFeature(lecturer a);
void studentFeature(student a);

void importCSV(int& Nstudent, int& studentCapa, student*& hocsinh, classes*& lophoc, int& Nclass);
void addAStudenttoClass(int& Nstudent, int& studentCapa, student*& hocsinh, classes* lophoc, int Nclass);

void updateStudentTXT(student* student, const int Nstudent, string filename);
void updateAClassTXT(student* hocsinh, const int Nstudent, int Nclass, classes* lophoc, string classname);

void LoadStudent(student* hocsinh, int numofstu, ifstream& f);
void Remove(student* hocsinh, int numofstu, string tmpID);
void RemoveAStudent(student* hocsinh, classes* lophoc);

void ChangeClass(student* hocsinh, classes* lophoc);
void DeleteAndAddStudent(student* hocsinh, int& numofstu, string tmpID, string tmpClass);

#endif

