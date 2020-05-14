#include <iostream>
#include "function.h"

using namespace std;

int main()
{
	int Nstaff, Nlecturer, Nstudent;
	int staffCapa, lecturerCapa, studentCapa;

	classes* lophoc = new classes[100];
	int Nclass=0;

	/*int courseCapa = 20;
	course* khoahoc = new course[20];
	int Ncourse = 0;*/


	staff* giaovu=nullptr;
	lecturer* giaovien = nullptr;
	student* hocsinh = nullptr;

	ifstream fin1;
	fin1.open("staff.txt");
	if (!fin1.is_open()) {
		cout << "cannot open file";
	}
	else {
		fin1 >> Nstaff;
		giaovu = new staff[Nstaff+10];
		loadStaff(fin1, giaovu, Nstaff);
		fin1.close();
		staffCapa = Nstaff + 10;
	}

	for (int i = 0; i < Nstaff; i++) {
		cout << giaovu[i].username << endl;
		cout << giaovu[i].password << endl;
		cout << giaovu[i].fullname << endl;
		cout << giaovu[i].gender << endl;
		cout << endl;
	}

	ifstream fin2;
	fin2.open("lecturer.txt");
	if (!fin2.is_open()) {
		cout << "cannot open file";
	}
	else {
		fin2 >> Nlecturer;
		giaovien = new lecturer[Nlecturer + 10];
		loadLecturer(fin2, giaovien, Nlecturer);
		fin2.close();
		lecturerCapa = Nlecturer + 10;
	}

	for (int i = 0; i < Nlecturer; i++) {
		cout << giaovien[i].username << endl;
		cout << giaovien[i].password << endl;
		cout << giaovien[i].fullname << endl;
		cout << giaovien[i].gender << endl;
		cout << endl;

	}

	ifstream fin3;
	fin3.open("student.txt");
	if (!fin3.is_open()) {
		cout << "cannot open file";
	}
	else {
		fin3 >> Nstudent;
		hocsinh = new student[Nstudent + 10];
		loadStudent(fin3, hocsinh, Nstudent, lophoc, Nclass);
		fin3.close();
		studentCapa = Nstudent + 10;
	}

	for (int i = 0; i < Nstudent; i++) {
		cout << hocsinh[i].id << endl;
		cout << hocsinh[i].password << endl;
		cout << hocsinh[i].fullname << endl;
		cout << hocsinh[i].dob << endl;
		cout << hocsinh[i].clas << endl;
		cout << endl;
	}

	//viewListOfClasses(lophoc, Nclass);
	

	//importCSV(Nstudent, studentCapa, hocsinh, lophoc ,Nclass);
	//addAStudenttoClass(Nstudent, studentCapa, hocsinh, lophoc, Nclass);

	//login(giaovu, giaovien, hocsinh, Nstaff, Nlecturer, Nstudent);

	//viewListOfStudentsInClass();

	//importCourseCSV(lophoc, Nclass);
	addANewCourse();
	//editACourse();

	delete[]lophoc;
	delete[]giaovu;
	delete[]giaovien;
	delete[]hocsinh;
	return 0;
}