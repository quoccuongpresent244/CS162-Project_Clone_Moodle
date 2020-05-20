#include "function.h"

int  Nstaff = 0, Nlecturer = 0, Nstudent = 0, Nclass = 0;
int  staffCapa = 0, lecturerCapa = 0, studentCapa = 0;

classes* lophoc = new classes[100];
staff* giaovu = nullptr;
lecturer* giaovien = nullptr;
student* hocsinh = nullptr;

void firstMenu() {
	int x;
	cout << "1. Login\n";
	cout << "2. Exit\n";
	cout << "What you want: (1-2): \n";
	cin >> x;
	switch (x) {
	case 1: login(); break;
	case 2: break;
	}
}

void login()
{
	string usernameX, passwordX;
	cout << "username: ";
	cin.ignore();
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

void loadStaff() {
	ifstream fin;
	fin.open("staff.txt");
	if (!fin.is_open()) {
		cout << "cannot open file";
	}
	else {
		fin >> Nstaff;
		giaovu = new staff[Nstaff + 10];


		for (int i = 0; i < Nstaff; i++) {
			fin.ignore(1000, '\n');
			fin.get();
			getline(fin, giaovu[i].username);
			getline(fin, giaovu[i].password);
			getline(fin, giaovu[i].fullname);
			fin >> giaovu[i].gender;
		}

		fin.close();
		staffCapa = Nstaff + 10;
	}
}
void loadLecturer() {

	ifstream fin;
	fin.open("lecturer.txt");
	if (!fin.is_open()) {
		cout << "cannot open file";
	}
	else {
		fin >> Nlecturer;
		giaovien = new lecturer[Nlecturer + 10];

		for (int i = 0; i < Nlecturer; i++) {
			fin.ignore(1000, '\n');
			fin.get();
			getline(fin, giaovien[i].username);
			getline(fin, giaovien[i].password);
			getline(fin, giaovien[i].fullname);
			getline(fin, giaovien[i].degree);
			fin >> giaovien[i].gender;
		}

		fin.close();
		lecturerCapa = Nlecturer + 10;
	}
}
void loadStudent() {
	//load data, execute data to calculate number of class? name of class? number of student in each class?

	ifstream fin;
	fin.open("student.txt");
	if (!fin.is_open()) {
		cout << "cannot open file";
	}
	else {
		fin >> Nstudent;
		hocsinh = new student[Nstudent + 10];

		fin.ignore(1000, '\n');
		for (int i = 0; i < Nstudent; i++) {
			fin.get();
			getline(fin, hocsinh[i].id);
			getline(fin, hocsinh[i].password);
			getline(fin, hocsinh[i].fullname);
			getline(fin, hocsinh[i].dob);
			getline(fin, hocsinh[i].clas);

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

		fin.close();
		studentCapa = Nstudent + 10;
	}

	updateAllClassTXT();
}

void updateAllClassTXT() {
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
					fout << hocsinh[j].clas;
				}
			}
		}
		fout.close();
	}
}
void updateAClassTXT(string classname) {

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
				f2 << hocsinh[i].clas;
			}
		}
	}
}
void updateStudentTXT(string filename) {
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
			fout << hocsinh[i].clas;
		}
	}
	fout.close();
	return;
}

void staffMenuShow() {
	cout << "Menu: \n";

	cout <<"------------------------CLASS------------------------";
	cout << "1. Import students of a class\n";
	cout << "2. Add a new student to a class\n";
	cout << "3. Edit an existing student\n";
	cout << "4. Remove a student\n";
	cout << "5. Change student from a class to another class\n";
	cout << "6. View list of classes\n";
	cout << "7. View list of student in a class\n";
	cout << "8. Change your password\n\n";

	cout <<"------------------------COURSE------------------------";
	cout << "9. Create / update / delete / view academic years, and semesters" << endl;
	cout << "10. Import a course" << endl;
	cout << "11. Manually add a new course" << endl;
	cout << "12. Edit an existing course\n";
	cout << "13. Remove a course\n";
	cout << "14. Remove a specific student from a course\n";
	cout << "15. Add a specific student to a course\n";
	cout << "16. View list of courses in the current semester\n"; 

	cout << "Please choose menu (1-8): ";
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

	staffMenuShow();

	int con = 1;
	int t;
	cin >> t;
	while (con == 1) {
		switch (t) {
		case 1: importCSV(); break;
		case 2: addAStudenttoClass(); break;
		case 3: editStudent(); break;
		case 4: break;
		case 5: break;
		case 6: viewListOfClasses(); break;
		case 7: viewListOfStudentsInClass(); break;
		case 8: break;
		case 9: break;
		case 10: break;
		case 11: break;
		case 12: break;
		case 13: break;
		case 14: break;
		case 15: break;
		case 16: break;
		case 17: break;
		case 18: break;
		case 19: break;
		case 20: break;
		default: cout << "Wrong choice\n"; break;
		}

		cout << "Do you want to continue (0.No 1.Yes): ";
		cin >> con;

		if (con == 1) {
			staffMenuShow();
			cin >> t;
		}
		else return;
	}

}
//Function for Staff
///*--------------------------------CLASS--------------------------------*/
void importCSV() {
	// import data from CSV file to program and rewrite file student.txt and student-class.txt

	string no, studentID, fullname, dob, clas;
	int tmp = Nstudent;

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
			getline(fin, clas, '\n');

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
			f2 << hocsinh[i].clas;
		}
	}

	updateStudentTXT("student.txt");      //This function update student.txt file
	cout << "\nImport Successfully\n";

	fin.close();
	f2.close();
	return;
}
void addAStudenttoClass() {
	if (Nstudent == studentCapa) {
		student* tmpHocsinh = new student[Nstudent + 10];                 //increase slots for hocsinh pointer
		for (int i = 0; i < Nstudent; i++)
			tmpHocsinh[i] = hocsinh[i];
		delete[] hocsinh;
		hocsinh = tmpHocsinh;
		studentCapa += 10;
	}

	cout << "Enter student ID: ";
	cin.ignore(1000, '\n');
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

	updateStudentTXT("student.txt");
	updateAClassTXT(tmpclassname);
	return;
}

void editStudent()
{
	string tmpID;
	string tmpClass;
	cout << "Enter Student-ID you want to edit: " << endl;
	getline(cin, tmpID, '\n');

	ifstream fi;
	fi.open("student.txt");
	loadStudent();

	for (int i = 0; i < Nstudent; i++)
	{
		if (tmpID == hocsinh[i].id)
		{
			cout << "Student ID: ";
			getline(cin, hocsinh[i].id, '\n');

			cout << "Password: ";
			getline(cin, hocsinh[i].password, '\n');

			cout << "Full name: ";
			getline(cin, hocsinh[i].fullname, '\n');

			cout << "Date of birth: ";
			getline(cin, hocsinh[i].dob, '\n');

			cout << "Class: ";
			getline(cin, hocsinh[i].clas, '\n'); 

			tmpClass = hocsinh[i].clas;

			break;
		}
	}
	fi.close();
	updateStudentTXT("student.txt");
	updateAClassTXT(tmpClass);
}

void viewListOfClasses() {
	cout << "List of classes: \n";
	for (int i = 0; i < Nclass; i++)
		cout << "Classname: " << lophoc[i].classname << ", Number of students: "
		<< lophoc[i].numofstu << endl;
}
void viewListOfStudentsInClass() {
	string classname;
	cout << "Enter classname you want to view: ";
	cin.ignore(1000, '\n');
	getline(cin, classname, '\n');

	string filename = "student-" + classname + ".txt";
	ifstream fin;
	string id, password, fullname, dob, clas;
	int nstudent;
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "cannot open file";
	}
	else {
		fin >> nstudent;
		fin.ignore(1000, '\n');

		cout << "Students in class of " << classname << " are:" << endl;;
		for (int i = 0; i < nstudent; i++) {
			fin.get();
			getline(fin, id);
			getline(fin, password);
			getline(fin, fullname);
			getline(fin, dob);
			getline(fin, clas);

			cout << endl;
			cout << id << endl;
			cout << fullname << endl;
			cout << dob << endl;
			cout << clas << endl;
		}
	}
}

/*--------------------------------COURSE--------------------------------*/
void importCourseCSV() {
	string acayear, semester, classname, addressCSV;
	string no, courseID, courseName, clas, instructor, instructorUsername, degree, gender, startDate,
		endDate, dayOfWeek, startTime, endTime, room;

	cout << "Enter academic year (yyyy-yyyy): ";
	getline(cin, acayear, '\n');
	cout << "Enter semester: ";
	getline(cin, semester, '\n');
	cout << "Enter class name: ";
	getline(cin, classname, '\n');
	cout << "Enter file csv address: ";
	getline(cin, addressCSV, '\n');

	// C:\\Users\\THINKPAD\\Desktop\\university\\Semester 2\\CS162\\Lab\\Project\\All files\\19APCS1-schedule.csv

	course* khoahoc = new course[10];
	int Ncourse = 0;
	int courseCapa = 10;

	ifstream fin;
	fin.open(addressCSV);
	if (!fin.is_open()) {
		cout << "cannot open file";
	}
	else {
		getline(fin, no, '\n');
		while (fin.good()) {
			getline(fin, no, ',');
			getline(fin, courseID, ',');
			getline(fin, courseName, ',');
			getline(fin, clas, ',');
			getline(fin, instructorUsername, ',');
			getline(fin, instructor, ',');
			getline(fin, degree, ',');
			getline(fin, gender, ',');
			getline(fin, startDate, ',');
			getline(fin, endDate, ',');
			getline(fin, dayOfWeek, ',');
			getline(fin, startTime, ',');
			getline(fin, endTime, ',');
			getline(fin, room, '\n');

			string tmpstartDate = startDate;
			tmpstartDate.replace(4, 1, " ");
			tmpstartDate.replace(7, 1, " ");

			string tmpendDate = endDate;
			tmpendDate.replace(4, 1, " ");
			tmpendDate.replace(7, 1, " ");

			if (Ncourse == courseCapa) {
				course* tmpkhoahoc = new course[Ncourse + 10];
				for (int i = 0; i < Ncourse; i++)
					tmpkhoahoc[i] = khoahoc[i];
				delete[] khoahoc;
				khoahoc = tmpkhoahoc;
				courseCapa += 10;
			}

			khoahoc[Ncourse].courseID = courseID;
			khoahoc[Ncourse].courseName = courseName;
			khoahoc[Ncourse].clas = clas;
			khoahoc[Ncourse].instructor = instructor;
			khoahoc[Ncourse].instructorUsername = instructorUsername;
			khoahoc[Ncourse].degree = degree;
			khoahoc[Ncourse].gender = gender;
			khoahoc[Ncourse].startDate = tmpstartDate;
			khoahoc[Ncourse].endDate = tmpendDate;
			khoahoc[Ncourse].dayOfWeek = dayOfWeek;
			khoahoc[Ncourse].startTime = startTime;
			khoahoc[Ncourse].endTime = endTime;
			khoahoc[Ncourse].room = room;
			khoahoc[Ncourse].status = 1;
			++Ncourse;
		}
	}
	fin.close();


	string coursename = acayear + "-" + semester + "-schedule-" + classname + ".txt";
	updateClassScheduleTXT(khoahoc, Ncourse, coursename);


	for (int i = 0; i < Ncourse; i++) {
		string tmpcourseID = khoahoc[i].courseID;
		string coursestudent = acayear + "-" + semester + "-" + classname + "-" + tmpcourseID + "-student.txt";

		updateCourseStudentTXT(coursestudent, classname);
	}
	delete[]khoahoc;
}
void addANewCourse() {
	string acayear, semester, classname, classcourses;

	cout << "Enter academic year (yyyy-yyyy): ";
	getline(cin, acayear, '\n');
	cout << "Enter semester: ";
	getline(cin, semester, '\n');
	cout << "Enter class name: ";
	getline(cin, classname, '\n');
	classcourses = acayear + "-" + semester + "-schedule-" + classname + ".txt";

	course* khoahoc = nullptr;
	int Ncourse = 0;

	loadClassScheduleTXT(khoahoc, Ncourse, classcourses);


	cout << "New course: \n";
	cout << "Enter courseID: ";				getline(cin, khoahoc[Ncourse].courseID, '\n');
	string courseID = khoahoc[Ncourse].courseID;
	cout << "Enter courseName: ";			getline(cin, khoahoc[Ncourse].courseName, '\n');
	khoahoc[Ncourse].clas = classname;
	cout << "Enter instructor: ";			getline(cin, khoahoc[Ncourse].instructor, '\n');
	cout << "Enter instructorUsername: ";	getline(cin, khoahoc[Ncourse].instructorUsername, '\n');
	cout << "Enter degree: ";				getline(cin, khoahoc[Ncourse].degree, '\n');
	cout << "Enter gender: ";				getline(cin, khoahoc[Ncourse].gender, '\n');
	cout << "Enter startDate(yyyy mm dd): "; getline(cin, khoahoc[Ncourse].startDate, '\n');
	cout << "Enter endDate(yyyy mm dd): ";	getline(cin, khoahoc[Ncourse].endDate, '\n');
	cout << "Enter dayOfWeek: ";			getline(cin, khoahoc[Ncourse].dayOfWeek, '\n');
	cout << "Enter startTime(hh:mm): ";		getline(cin, khoahoc[Ncourse].startTime, '\n');
	cout << "Enter endTime(hh:mm): ";		getline(cin, khoahoc[Ncourse].endTime, '\n');
	cout << "Enter room: ";					getline(cin, khoahoc[Ncourse].room, '\n');
	++Ncourse;

	updateClassScheduleTXT(khoahoc, Ncourse, classcourses);

	string coursestudent = acayear + "-" + semester + "-" + classname + "-" + courseID + "-student.txt";

	updateCourseStudentTXT(coursestudent, classname);

	delete[] khoahoc;
}
void editACourse() {
	string acayear, semester, classname, coursename;

	cout << "Enter academic year (yyyy-yyyy): ";
	getline(cin, acayear, '\n');
	cout << "Enter semester: ";
	getline(cin, semester, '\n');
	cout << "Enter class name: ";
	getline(cin, classname, '\n');
	coursename = acayear + "-" + semester + "-schedule-" + classname + ".txt";

	course* khoahoc = nullptr;
	int Ncourse = 0;

	loadClassScheduleTXT(khoahoc, Ncourse, coursename);


	string courseID;
	cout << "CourseID of the course that you want to modify: ";
	getline(cin, courseID, '\n');
	cout << "Modify: \n";
	for (int i = 0; i < Ncourse; i++) {
		if (khoahoc[i].courseID == courseID) {
			cout << "Enter courseName: ";			getline(cin, khoahoc[i].courseName, '\n');
			khoahoc[i].clas = classname;
			cout << "Enter instructor: ";			getline(cin, khoahoc[i].instructor, '\n');
			cout << "Enter instructorUsername: ";	getline(cin, khoahoc[i].instructorUsername, '\n');
			cout << "Enter degree: ";				getline(cin, khoahoc[i].degree, '\n');
			cout << "Enter gender: ";				getline(cin, khoahoc[i].gender, '\n');
			cout << "Enter startDate(yyyy mm dd): "; getline(cin, khoahoc[i].startDate, '\n');
			cout << "Enter endDate(yyyy mm dd): ";	getline(cin, khoahoc[i].endDate, '\n');
			cout << "Enter dayOfWeek: ";			getline(cin, khoahoc[i].dayOfWeek, '\n');
			cout << "Enter startTime(hh:mm): ";		getline(cin, khoahoc[i].startTime, '\n');
			cout << "Enter endTime(hh:mm): ";		getline(cin, khoahoc[i].endTime, '\n');
			cout << "Enter room: ";					getline(cin, khoahoc[i].room, '\n');
			break;
		}
	}

	updateClassScheduleTXT(khoahoc, Ncourse, coursename);

	delete[] khoahoc;
}

void listofCourse(){
	course* khoahoc = nullptr;
	int Ncourse = 0;  
	string className; 
	cout << "Please enter Class you want to view: ";
	getline(cin, className, '\n');

	string scheduleFileName = "2019-2020-HK2-schedule-" + className + ".txt";
	loadClassScheduleTXT(khoahoc, Ncourse, scheduleFileName);

	cout << left << setw(14) << setfill(' ') << "Course ID";
	cout << left << setw(28) << setfill(' ') << "Course Name";
	cout << left << setw(10) << setfill(' ') << "Class";
	cout << left << setw(20) << setfill(' ') << "Instructor";
	cout << left << setw(25) << setfill(' ') << "Instructor Username";
	cout << left << setw(12) << setfill(' ') << "Degree";
	cout << left << setw(12) << setfill(' ') << "Gender";
	cout << left << setw(16) << setfill(' ') << "Start Date";
	cout << left << setw(14) << setfill(' ') << "End date";
	cout << left << setw(17) << setfill(' ') << "Day Of Week";
	cout << left << setw(16) << setfill(' ') << "Start time";
	cout << left << setw(14) << setfill(' ') << "End time";
	cout << left << setw(10) << setfill(' ') << "Room";
	cout << endl;

	for (int i = 0; i < Ncourse; ++i){
		cout << left << setw(14) << setfill(' ') << khoahoc[i].courseID;
		cout << left << setw(28) << setfill(' ') << khoahoc[i].courseName;
		cout << left << setw(10) << setfill(' ') << khoahoc[i].clas;
		cout << left << setw(20) << setfill(' ') << khoahoc[i].instructor;
		cout << left << setw(25) << setfill(' ') << khoahoc[i].instructorUsername;
		cout << left << setw(12) << setfill(' ') << khoahoc[i].degree;
		cout << left << setw(12) << setfill(' ') << khoahoc[i].gender;
		cout << left << setw(16) << setfill(' ') << khoahoc[i].startDate;
		cout << left << setw(14) << setfill(' ') << khoahoc[i].endDate;
		cout << left << setw(17) << setfill(' ') << khoahoc[i].dayOfWeek;
		cout << left << setw(16) << setfill(' ') << khoahoc[i].startTime;
		cout << left << setw(14) << setfill(' ') << khoahoc[i].endTime;
		cout << left << setw(10) << setfill(' ') << khoahoc[i].room;
		cout << endl;
	}
}

void updateClassScheduleTXT(course* khoahoc, int Ncourse, string classschedule) {
	ofstream f2;

	f2.open(classschedule);
	if (!f2.is_open()) {
		cout << "cannot open file f2";
	}
	else {
		f2 << Ncourse;
		for (int i = 0; i < Ncourse; i++) {
			f2 << endl << endl;
			f2 << khoahoc[i].courseID << endl;
			f2 << khoahoc[i].courseName << endl;
			f2 << khoahoc[i].clas << endl;
			f2 << khoahoc[i].instructor << endl;
			f2 << khoahoc[i].instructorUsername << endl;
			f2 << khoahoc[i].degree << endl;
			f2 << khoahoc[i].gender << endl;
			f2 << khoahoc[i].startDate << endl;
			f2 << khoahoc[i].endDate << endl;
			f2 << khoahoc[i].dayOfWeek << endl;
			f2 << khoahoc[i].startTime << endl;
			f2 << khoahoc[i].endTime << endl;
			f2 << khoahoc[i].room;
		}
	}
	f2.close();
}
void loadClassScheduleTXT(course*& khoahoc, int& Ncourse, string classcourses) {
	ifstream fin;
	fin.open(classcourses);
	if (!fin.is_open()) {
		cout << "cannot open file\n";
		khoahoc = new course[1];
	}
	else {
		fin >> Ncourse;
		fin.ignore(1000, '\n');
		khoahoc = new course[Ncourse + 1];
		for (int i = 0; i < Ncourse; i++) {
			fin.get();
			getline(fin, khoahoc[i].courseID, '\n');
			getline(fin, khoahoc[i].courseName, '\n');
			getline(fin, khoahoc[i].clas, '\n');
			getline(fin, khoahoc[i].instructor, '\n');
			getline(fin, khoahoc[i].instructorUsername, '\n');
			getline(fin, khoahoc[i].degree, '\n');
			getline(fin, khoahoc[i].gender, '\n');
			getline(fin, khoahoc[i].startDate, '\n');
			getline(fin, khoahoc[i].endDate, '\n');
			getline(fin, khoahoc[i].dayOfWeek, '\n');
			getline(fin, khoahoc[i].startTime, '\n');
			getline(fin, khoahoc[i].endTime, '\n');
			getline(fin, khoahoc[i].room, '\n');
		}
	}
	fin.close();
}
void updateCourseStudentTXT(string coursestudent, string classname) {
	stuincourse* hs = nullptr;
	int Nstudent;

	ofstream fo3;

	fo3.open(coursestudent);
	if (!fo3.is_open()) {
		cout << "cannot open file";
	}
	else {
		ifstream fi4;
		fi4.open("student-" + classname + ".txt");
		if (!fi4.is_open()) {
			cout << "cannot open file";
		}
		else {
			fi4 >> Nstudent;
			fo3 << Nstudent;
			hs = new stuincourse[Nstudent + 1];

			fi4.ignore(1000, '\n');
			for (int i = 0; i < Nstudent; i++) {
				fi4.get();
				getline(fi4, hs[i].id, '\n');
				getline(fi4, hs[i].password, '\n');
				getline(fi4, hs[i].fullname, '\n');
				getline(fi4, hs[i].dob, '\n');
				getline(fi4, hs[i].clas, '\n');
				hs[i].midterm = -1;
				hs[i].final = -1;
				hs[i].bonus = -1;
				hs[i].final = -1;

				fo3 << endl << endl;
				fo3 << hs[i].id << endl;
				fo3 << hs[i].password << endl;
				fo3 << hs[i].fullname << endl;
				fo3 << hs[i].dob << endl;
				fo3 << hs[i].clas << endl;
				fo3 << hs[i].midterm << endl;
				fo3 << hs[i].final << endl;
				fo3 << hs[i].bonus << endl;
				fo3 << hs[i].final;
			}
		}
		fi4.close();
		fo3.close();
	}

	delete[]hs;
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

