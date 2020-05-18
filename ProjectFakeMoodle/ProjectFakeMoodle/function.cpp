#include "function.h"

void firstMenu() {
	/*int x;
	cout << "1. Login\n";
	cout << "2. Exit\n";
	cout << "What you want: (1-2): \n";
	cin >> x;
	switch (x) {
	case 1: login(giaovu, giaovien, hocsinh, Nstaff, Nlecturer, Nstudent); break;
	case 2: break;
	}*/
}

void login(staff* giaovu, lecturer* giaovien, student* hocsinh,
	const int Nstaff, const int Nlecturer, const int Nstudent)
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

void loadStaff(ifstream& fin, staff*& a, const int n) {

	for (int i = 0; i < n; i++) {
		fin.ignore(1000, '\n');
		fin.get();
		getline(fin, a[i].username);
		getline(fin, a[i].password);
		getline(fin, a[i].fullname);
		fin >> a[i].gender;
	}
}

void loadLecturer(ifstream& fin, lecturer*& a, const int n) {

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

void loadStudent(ifstream& fin, student*& hocsinh, const int Nstudent, classes*& lophoc, int& Nclass) {
	//load data, execute data to calculate number of class? name of class? number of student in each class?
	for (int i = 0; i < Nstudent; i++) {
		fin.ignore(1000, '\n');
		fin.get();
		getline(fin, hocsinh[i].id);
		getline(fin, hocsinh[i].password);
		getline(fin, hocsinh[i].fullname);
		getline(fin, hocsinh[i].dob);
		getline(fin, hocsinh[i].clas);
		fin >> hocsinh[i].status;

		if (Nclass == 0) {
			lophoc[0].classname = hocsinh[i].clas;
			lophoc[0].numofstu = 1;
			++Nclass;
		}
		else {
			bool newclass = true;
			int tmp;
			for (int j = 0; j < Nclass; j++) {
				if (hocsinh[i].clas == lophoc[j].classname) {
					newclass = false;
					tmp = j; break;
				}
			}

			if (newclass) {
				lophoc[Nclass].classname = hocsinh[i].clas;
				lophoc[Nclass].numofstu = 1;
				++Nclass;
			}
			else {
				++lophoc[tmp].numofstu;
			}
		}
	}
	updateAllClassTXT(hocsinh, Nstudent, Nclass, lophoc);
}

void updateAllClassTXT(student* hocsinh, const int Nstudent, int Nclass, classes* lophoc) {
	//using for updating all data to file txt (student-19APCS1; student-19APCS2...)

	for (int i = 0; i < Nclass; i++) {
		ofstream fout;
		string filename = "student-" + lophoc[i].classname + ".txt";
		fout.open(filename);
		if (!fout.is_open()) {
			cout << "cannot open file";
		}
		else {
			fout << lophoc[i].numofstu;
			for (int j = 0; j < Nstudent; j++) {
				if (hocsinh[j].clas == lophoc[i].classname) {
					fout << "\n\n";
					fout << hocsinh[j].id << endl;
					fout << hocsinh[j].password << endl;
					fout << hocsinh[j].fullname << endl;
					fout << hocsinh[j].dob << endl;
					fout << hocsinh[j].clas << endl;
					fout << hocsinh[j].status;
				}
			}
		}
		fout.close();
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

	/*int t;
	cin >> t;
	switch (t) {
	case 1:
	}*/




}
//Function for Staff

void importCSV(int& Nstudent, int& studentCapa, student*& hocsinh, classes*& lophoc, int& Nclass) {
	// import data from CSV file to program and rewrite file student.txt and student-class.txt

	string no, studentID, fullname, dob, clas;
	int tmp = Nstudent, status;

	string addressCSV;

	ifstream fin;
	cout << "Enter address of csv file: ";
	getline(cin, addressCSV, '\n');          // You must have file CSV first, then find the address of that file, and modify it to look like the one below
	fin.open(addressCSV);

	// C:\\Users\\THINKPAD\\Desktop\\university\\Semester 2\\CS162\\Lab\\Project\\ProjectFakeMoodle\\19APCS1-student.csv
	if (!fin.is_open()) {
		cout << "cannot open file fin";
	}
	else {
		getline(fin, no, '\n');
		while (fin.good()) {
			getline(fin, no, ',');
			getline(fin, studentID, ',');
			getline(fin, fullname, ',');
			getline(fin, dob, ',');
			getline(fin, clas, ',');
			fin >> status;

			//2001/04/01 20010401 2001 04 01
			string tmpPass = dob;
			tmpPass.erase(tmpPass.begin() + 4);
			tmpPass.erase(tmpPass.begin() + 6);

			string tmpdob = dob;
			tmpdob.replace(4, 1, " ");
			tmpdob.replace(7, 1, " ");

			if (Nstudent == studentCapa) {           //increase slots for hocsinh
				student* tmpHocsinh = new student[Nstudent + 10];
				for (int i = 0; i < Nstudent; i++)
					tmpHocsinh[i] = hocsinh[i];
				delete[] hocsinh;
				hocsinh = tmpHocsinh;
				studentCapa += 10;
			}

			hocsinh[Nstudent].id = studentID;
			hocsinh[Nstudent].password = tmpPass;
			hocsinh[Nstudent].fullname = fullname;
			hocsinh[Nstudent].dob = tmpdob;
			hocsinh[Nstudent].clas = clas;
			hocsinh[Nstudent].status = status;
			++Nstudent;

		}
	}
	string Classname;
	Classname = clas;
	lophoc[Nclass].classname = Classname;             //add new class to class pointer
	++Nclass;

	ofstream f2;
	Classname = "student-" + Classname + ".txt";
	f2.open(Classname);                                // just create new file txt student-[class] to store data.
	if (!f2.is_open()) {
		cout << "cannot open file f2";
	}
	else {
		f2 << Nstudent - tmp;                         //This shows the number of students in Class.... easy to understand, just read line 183
		for (int i = tmp; i < Nstudent; i++) {
			f2 << endl << endl;
			f2 << hocsinh[i].id << endl;
			f2 << hocsinh[i].password << endl;
			f2 << hocsinh[i].fullname << endl;
			f2 << hocsinh[i].dob << endl;
			f2 << hocsinh[i].clas << endl;
			f2 << hocsinh[i].status;
		}
	}

	updateStudentTXT(hocsinh, Nstudent, "student.txt");      //This function update student.txt file
	cout << "\nImport Successfully\n";

	fin.close();
	f2.close();
	return;
}

void addAStudenttoClass(int& Nstudent, int& studentCapa, student*& hocsinh, classes* lophoc, int Nclass) {
	if (Nstudent == studentCapa) {
		student* tmpHocsinh = new student[Nstudent + 10];                 //increase slots for hocsinh pointer
		for (int i = 0; i < Nstudent; i++)
			tmpHocsinh[i] = hocsinh[i];
		delete[] hocsinh;
		hocsinh = tmpHocsinh;
		studentCapa += 10;
	}

	cout << "Enter student ID: ";
	getline(cin, hocsinh[Nstudent].id, '\n');
	cout << "Enter fullname: ";
	getline(cin, hocsinh[Nstudent].fullname, '\n');

	string dob;
	cout << "Enter student date of birth following the format: yyyy/mm/dd: ";
	getline(cin, dob, '\n');

	string tmpPass = dob;
	tmpPass.erase(tmpPass.begin() + 4);
	tmpPass.erase(tmpPass.begin() + 6);

	hocsinh[Nstudent].password = tmpPass;

	string tmpdob = dob;
	tmpdob.replace(4, 1, " ");
	tmpdob.replace(7, 1, " ");

	hocsinh[Nstudent].dob = tmpdob;

	cout << "Enter Class: ";
	getline(cin, hocsinh[Nstudent].clas, '\n');

	string tmpclassname = hocsinh[Nstudent].clas;         //no need to worry about
	++Nstudent;

	for (int i = 0; i < Nclass; i++) {
		if (lophoc[i].classname == tmpclassname) {
			++lophoc[i].numofstu; break;                   //increase number of student in that class
		}
	}

	updateStudentTXT(hocsinh, Nstudent, "student.txt");
	updateAClassTXT(hocsinh, Nstudent, Nclass, lophoc, tmpclassname);
	return;
}

void updateAClassTXT(student* hocsinh, const int Nstudent, int Nclass, classes* lophoc, string classname) {

	// update file txt student-[class] after modifying it

	int tmp;
	ofstream f2;
	string filename = "student-" + classname + ".txt";
	f2.open(filename);
	if (!f2.is_open()) {
		cout << "cannot open file f2";
	}
	else {
		for (int i = 0; i < Nclass; i++) {
			if (lophoc[i].classname == classname) {
				tmp = i; break;
			}
		}
		f2 << lophoc[tmp].numofstu;                            //similarly
		for (int i = 0; i < Nstudent; i++) {
			if (hocsinh[i].clas == classname) {
				f2 << endl << endl;
				f2 << hocsinh[i].id << endl;
				f2 << hocsinh[i].password << endl;
				f2 << hocsinh[i].fullname << endl;
				f2 << hocsinh[i].dob << endl;
				f2 << hocsinh[i].clas << endl;
				f2 << hocsinh[i].status;
			}
		}
	}
}


void updateStudentTXT(student* hocsinh, const int Nstudent, string filename) {
	ofstream fout;
	fout.open(filename);
	if (!fout.is_open()) {
		cout << "cannot open, cannot write fout";
	}
	else {
		fout << Nstudent;
		for (int i = 0; i < Nstudent; i++) {
			fout << endl << endl;
			fout << hocsinh[i].id << endl;
			fout << hocsinh[i].password << endl;
			fout << hocsinh[i].fullname << endl;
			fout << hocsinh[i].dob << endl;
			fout << hocsinh[i].clas << endl;
			fout << hocsinh[i].status;
		}
	}
	fout.close();
	return;
}


void lecturerFeature(lecturer a) {
	if (a.gender == 0)
		cout << "\t \t Xin chao co " << a.fullname << endl;
	else if (a.gender == 1)
		cout << "\t \t Xin chao thay " << a.fullname << endl;
	cout << "Thong tin giang vien: \n";
	cout << "Tai khoan: " << a.username << endl;
	cout << "Ho va ten: " << a.fullname << endl;
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
	cout << "\t \tXin chao ban " << a.fullname << endl;

	cout << "Thong tin sinh vien: \n";
	cout << "Ma so sinh vien: " << a.id << endl;
	cout << "Ho va ten: " << a.fullname << endl;
	cout << "Ngay sinh: " << a.dob << endl;
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

void LoadStudent(student* hocsinh, int numofstu, ifstream& f)
{
	for (int i = 0; i < numofstu; ++i)
	{
		f.ignore(1000, '\n');
		f.get();
		getline(f, hocsinh[i].id);
		getline(f, hocsinh[i].password);
		getline(f, hocsinh[i].fullname);
		getline(f, hocsinh[i].dob);
		getline(f, hocsinh[i].clas);
		f >> hocsinh[i].status;
	}
	f.close();
}

void Remove(student* hocsinh, int numofstu, string tmpID)
{
	for (int i = 0; i < numofstu; ++i)
	{
		if (hocsinh[i].id == tmpID)
		{
			cout << "Student: " << hocsinh[i].fullname << endl;
			cout << "Class: " << hocsinh[i].clas << endl;
			cout << "Do you want to remove this student ? (if yes input 1, else input 0)." << endl;
			int k;
			cin >> k;
			if (k == 0) return;
			hocsinh[i].status = 0;
			cout << "This student has been removed !" << endl;
			break;
		}
	}
}

void RemoveAStudent()
{
	ifstream f;
	string tmpID;
	string tmpClass;
	int numofstu;
	cout << "Enter the class of this student: " << endl;
	getline(cin, tmpClass);
	cout << "ID: " << endl;
	getline(cin, tmpID);
	f.open("student-" + tmpClass + ".txt");
	if (!f.is_open())
		cout << "Can not open file." << endl;
	else
	{
		f >> numofstu;
		student* hocsinh1 = new student[numofstu];
		LoadStudent(hocsinh1, numofstu, f);
		Remove(hocsinh1, numofstu, tmpID);
		updateStudentTXT(hocsinh1, numofstu, "student-" + tmpClass + ".txt");
		delete[]hocsinh1;
	}
}

void DeleteAndAddStudent(student* hocsinh, int& numofstu, string tmpID, string tmpClass)
{
	for (int i = 0; i < numofstu; ++i)
	{
		if (hocsinh[i].id == tmpID)
		{
			cout << "Student: " << hocsinh[i].fullname << endl;
			cout << "Class: " << hocsinh[i].clas << endl;
			cout << "Do you want to change this student's class ? (if yes input 1, else input 0)." << endl;
			int k;
			cin >> k;
			if (k == 0) return;
			ofstream f1, f2;
			f1.open("student-" + tmpClass + ".txt");
			if (!f1.is_open())
				cout << "Can not open file." << endl;
			else
			{
				f1 << (numofstu - 1);
				for (int j = 0; j < numofstu; ++j)
				{
					if (j != i)
					{
						f1 << endl << endl;
						f1 << hocsinh[j].id << endl;
						f1 << hocsinh[j].password << endl;
						f1 << hocsinh[j].fullname << endl;
						f1 << hocsinh[j].dob << endl;
						f1 << hocsinh[j].clas << endl;
						f1 << hocsinh[j].status;
					}
				}
				f1.close();
			}
			cout << "Enter the new class of this student: " << endl;
			string tmpNew;
			cin.get();
			getline(cin, tmpNew);
			ifstream f;
			int numofstu1;
			f.open("student-" + tmpNew + ".txt");
			student* hocsinh1 = nullptr;
			if (!f.is_open())
				cout << "Can not open file." << endl;
			else
			{
				f >> numofstu1;
				hocsinh1 = new student[numofstu1];
				LoadStudent(hocsinh1, numofstu1, f);
			}
			f2.open("student-" + tmpNew + ".txt");
			if (!f2.is_open())
				cout << "Can not open file." << endl;
			else
			{
				f2 << numofstu1 + 1;
				for (int l = 0; l < numofstu1; ++l)
				{
					f2 << endl << endl;
					f2 << hocsinh1[l].id << endl;
					f2 << hocsinh1[l].password << endl;
					f2 << hocsinh1[l].fullname << endl;
					f2 << hocsinh1[l].dob << endl;
					f2 << hocsinh1[l].clas << endl;
					f2 << hocsinh1[l].status;
				}
				f2 << endl << endl;
				f2 << hocsinh[i].id << endl;
				f2 << hocsinh[i].password << endl;
				f2 << hocsinh[i].fullname << endl;
				f2 << hocsinh[i].dob << endl;
				f2 << hocsinh[i].clas << endl;
				f2 << hocsinh[i].status;
				f2.close();
			}
			cout << "The class of this student have been changed !" << endl;
			delete[]hocsinh1;
			break;
		}
	}
}

void ChangeClass()
{
	ifstream f;
	string tmpID;
	string tmpClass;
	int numofstu;
	cout << "Enter the class of this student: " << endl;
	getline(cin, tmpClass);
	cout << "ID: " << endl;
	getline(cin, tmpID);
	f.open("student-" + tmpClass + ".txt");
	if (!f.is_open())
		cout << "Can not open file." << endl;
	else
	{
		f >> numofstu;
		student* hocsinh1 = new student[numofstu];
		LoadStudent(hocsinh1, numofstu, f);
		DeleteAndAddStudent(hocsinh1, numofstu, tmpID, tmpClass);
		delete[]hocsinh1;
	}
}