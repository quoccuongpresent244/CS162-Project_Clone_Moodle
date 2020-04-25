#include <iostream>
#include "function.h"

using namespace std;

int main()
{
	int Nstaff, Nlecturer, Nstudent;

	staff giaovu[100];
	lecturer giaovien[100];
	student hocsinh[600];

	ifstream fin1;
	fin1.open("staff.txt");
	if (!fin1.is_open()) {
		cout << "cannot open file";
	}
	else {
		fin1 >> Nstaff;
		loadStaff(fin1, giaovu, Nstaff);
		fin1.close();
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
		loadLecturer(fin2, giaovien, Nlecturer);
		fin2.close();
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
		loadStudent(fin3, hocsinh, Nstudent);
		fin3.close();
	}

	for (int i = 0; i < Nstudent; i++) {
		cout << hocsinh[i].id << endl;
		cout << hocsinh[i].password << endl;
		cout << hocsinh[i].fullname << endl;
		cout << hocsinh[i].dob.y << " " << hocsinh[i].dob.m << " " << hocsinh[i].dob.d << endl;
		cout << hocsinh[i].clas << endl;
		cout << endl;
	}

	//studentFeature(hocsinh[0]);
    //check git pull

	return  0;
}