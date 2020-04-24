#include "function.h"

void firstMenu(){
	int x;
	cout << "1. Login\n";
	cout << "2. Exit\n";
	cout << "What you want: (1-2): \n";
	cin >> x;
	switch (x) {
	case 1: 
	case 2: break;
	}
}

void login(staff giaovu[], lecturer giaovien[], student hocsinh[],
	const int Nstaff,const int Nlecturer,const int Nstudent) 
{
	string usernameX, passwordX;
	cout << "username: ";
	getline(cin, usernameX);
	cout << "password: ";
	getline(cin, passwordX);
	for (int i = 0; i < Nstaff; i++) {
		if (giaovu[i].username == usernameX && giaovu[i].password == passwordX) {
			staffFeature(giaovu[i]);
			return;
		}
	}
	for (int i = 0; i < Nlecturer; i++) {
		if (giaovien[i].username == usernameX && giaovien[i].password == passwordX) {
			lecturerFeature(giaovien[i]);
			return;
		}
	}
	for (int i = 0; i < Nstudent; i++) {
		if (hocsinh[i].id == usernameX && hocsinh[i].password == passwordX) {
			studentFeature(hocsinh[i]);
			return;
		}
	}
}

void loadStaff(ifstream& fin, staff a[], const int n) {

	for (int i = 0; i < n; i++) {
		fin.ignore(1000, '\n');
		fin.get();
		getline(fin, a[i].username);
		getline(fin, a[i].password);
		getline(fin, a[i].fullname);
		fin >> a[i].gender;
	}
}

void loadLecturer(ifstream& fin, lecturer a[], const int n) {

	for (int i = 0; i < n; i++) {
		fin.ignore(1000, '\n');
		fin.get();
		getline(fin, a[i].username);
		getline(fin, a[i].password);
		getline(fin, a[i].fullname);
		getline(fin, a[i].degree);
		fin >> a[i].gender;
	}
}

void loadStudent(ifstream& fin, student a[], int n) {
	fin.ignore(1000, '\n');
	for (int i = 0; i < n; i++) {
		fin.get();
		getline(fin, a[i].id);
		getline(fin, a[i].password);
		getline(fin, a[i].fullname);
		fin >> a[i].dob.y >> a[i].dob.m >> a[i].dob.d;
		fin.ignore(1000, '\n');
		getline(fin, a[i].clas);
	}
}


void staffFeature(staff a) {
	if (a.gender == 0)
		cout << "\t \t Xin chao co " << a.fullname << endl;
	else if (a.gender == 1)
		cout << "\t \t Xin chao thay " << a.fullname << endl;

	cout << "Thong tin giao vu:\n";
	cout << "Tai khoan: " << a.username << endl;
	cout << "Ho va ten: " << a.fullname << endl;
	if (a.gender == 0)
		cout << "Gioi tinh: Nu\n";
	else if (a.gender == 1)
		cout << "Gioi tinh: Nam\n";
	cout << endl << endl;


	cout << "Menu: \n";

	cout << "1. Import students of a class\n";
	cout << "2. Add a new student to a class\n";
	cout << "3. Edit an existing student\n";
	cout << "4. Remove a student\n";
	cout << "5. Change student from a class to another class\n";
	cout << "6. View list of classes\n";
	cout << "7. View list of student in a class\n\n";

	cout << "8. Change your password\n";

	cout << "Please choose menu (1-8)\n";
	//int t;
	//cin >> t;
	//switch (t) {
	//case 1:

	//}




}

void lecturerFeature(lecturer a) {
	if (a.gender == 0)
		cout << "\t \t Xin chao co " << a.fullname << endl;
	else if (a.gender == 1)
		cout << "\t \t Xin chao thay " << a.fullname << endl;
	cout << "Thong tin giang vien: \n";
	cout << "Tai khoan: " << a.username << endl;
	cout << "Ho va ten: " << a.fullname<<endl;
	cout << "Hoc vi: " << a.degree << endl;
	if (a.gender == 0)
		cout << "Gioi tinh: Nu\n";
	else if (a.gender == 1)
		cout << "Gioi tinh: Nam\n";
	cout << endl << endl;

	cout << "Menu: \n";

	cout << "1. View list of courses in the current semester\n";
	cout << "2. View list of students of a course\n";
	cout << "3. View attendance list of a course\n";
	cout << "4. Edit an attendance\n";
	cout << "5. Import scoreboard of a course\n";
	cout << "6. Edit grade of a student\n";
	cout << "7. View a scoreboard\n";
	cout << "8. Change your password\n";

	cout << "Please choose menu (1-8)\n";
	//int t;
	//cin >> t;
	//switch (t) {
	//case 1:

	//}

}

void studentFeature(student a) {
	cout << "\t \tXin chao ban " << a.fullname<<endl;

	cout << "Thong tin sinh vien: \n";
	cout << "Ma so sinh vien: " << a.id << endl;
	cout << "Ho va ten: " << a.fullname << endl;
	cout << "Ngay sinh: " << a.dob.d << "/" << a.dob.m << "/" << a.dob.y<<endl;
	cout << "Lop: " << a.clas << endl;
	cout << "\n\n";

	cout << "Menu: \n";
	cout << "1. Check in \n";
	cout << "2. View check-in result\n";
	cout << "3. View Schedules\n";
	cout << "4. View score of a course\n";
	cout << "5. Change your password\n";

	cout << "Please choose menu (1-5)\n";
	//int t;
	//cin >> t;
	//switch (t) {
	//case 1:

	//}
}