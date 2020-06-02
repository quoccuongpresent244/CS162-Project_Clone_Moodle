#include "function.h"

int Nstaff = 0, Nlecturer = 0, Nstudent = 0, Nclass = 0, Nleave = 0;
int staffCapa = 0, lecturerCapa = 0, studentCapa = 0;
string a[10];

classes *lophoc = new classes[100];
staff *giaovu = nullptr;
lecturer *giaovien = nullptr;
student *hocsinh = nullptr;

void firstMenu()
{
	int color[] = { 10, 12 };
	int index[] = { 1, 0};
	int ptr = 0;
	int keystroke = 0;
	while (keystroke != 13) { // 13: enter
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[0]]);
		cout << "1. LOGIN" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[1]]);
		cout << "2. LOG OUT." << endl;

		keystroke = _getch();
		fflush(stdin);
        
        //UP_ARROW: 72
		if (keystroke == 72) {
			index[ptr] = 0;
			if (ptr == 0)
				ptr = 1;
			else
				ptr--;
			index[ptr] = 1;
		}

        //DOWN_ARROW: 80
		else if (keystroke==80) {
			index[ptr] = 0;
			if (ptr == 1)
				ptr = 0;
			else
				ptr++;
			index[ptr] = 1;
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	switch (ptr) {
	case 0:
		login();
		break;
	case 1:
		cout << "See you later!" << endl;
		break;
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
	//system("cls");
	for (int i = 0; i < Nstaff; i++)
	{
		if (giaovu[i].username == usernameX && giaovu[i].password == passwordX)
		{
			cout << "CUA STAFF" << endl;
			staffFeature(giaovu[i]);
			return;
		}
	}
	for (int i = 0; i < Nlecturer; i++)
	{
		if (giaovien[i].username == usernameX && giaovien[i].password == passwordX)
		{
			cout << "CUA LECTURER" << endl;
			lecturerFeature(giaovien[i]);
			return;
		}
	}
	for (int i = 0; i < Nstudent; i++)
	{
		if (hocsinh[i].id == usernameX && hocsinh[i].password == passwordX)
		{
			cout << "CUA HOC SINH" << endl;
			studentFeature(hocsinh[i]);
			return;
		}
	}
	cout << "ERROR!!!!!!!!!!!!" << endl;
}

void loadStaff()
{
	ifstream fin;
	fin.open("staff.txt");
	if (!fin.is_open())
	{
		cout << "cannot open file";
	}
	else
	{
		fin >> Nstaff;
		giaovu = new staff[Nstaff + 10];
		fin.ignore(1000, '\n');

		for (int i = 0; i < Nstaff; i++)
		{
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
void loadLecturer()
{

	ifstream fin;
	fin.open("lecturer.txt");
	if (!fin.is_open())
	{
		cout << "cannot open file";
	}
	else
	{
		fin >> Nlecturer;
		giaovien = new lecturer[Nlecturer + 10];

		for (int i = 0; i < Nlecturer; i++)
		{
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
void loadStudent()
{
	//load data, execute data to calculate number of class? name of class? number of student in each class?

	ifstream fin;
	fin.open("student.txt");
	if (!fin.is_open())
	{
		cout << "cannot open file";
	}
	else
	{
		fin >> Nstudent >> Nleave;
		hocsinh = new student[Nstudent + 10];

		fin.ignore(1000, '\n');
		for (int i = 0; i < Nstudent + Nleave; i++)
		{
			fin.get();
			getline(fin, hocsinh[i].id);
			getline(fin, hocsinh[i].password);
			getline(fin, hocsinh[i].fullname);
			getline(fin, hocsinh[i].dob);
			getline(fin, hocsinh[i].clas);
			fin >> hocsinh[i].status;
			fin.get();

			if (Nclass == 0)
			{
				lophoc[0].classname = hocsinh[i].clas;
				if (hocsinh[i].status == 1)
					lophoc[0].numofstu = 1;
				else
					lophoc[0].numofstu = 0;
				++Nclass;
			}
			else
			{
				bool newclass = true;
				int tmp;
				for (int j = 0; j < Nclass; j++)
				{
					if (hocsinh[i].clas == lophoc[j].classname)
					{
						newclass = false;
						tmp = j;
						break;
					}
				}
				if (newclass)
				{
					lophoc[Nclass].classname = hocsinh[i].clas;
					if (hocsinh[i].status == 1)
						lophoc[Nclass].numofstu = 1;
					else
						lophoc[Nclass].numofstu = 0;
					++Nclass;
				}
				else
				{
					if (hocsinh[i].status == 1)
						++lophoc[tmp].numofstu;
				}
			}
		}
		fin.close();
		studentCapa = Nstudent + 10;
	}
	updateAllClassTXT();
}

void updateAllClassTXT()
{
	//using for updating all data to file txt (student-19APCS1; student-19APCS2...)

	for (int i = 0; i < Nclass; i++)
	{
		ofstream fout;
		string filename = "student-" + lophoc[i].classname + ".txt";
		fout.open(filename);
		if (!fout.is_open())
		{
			cout << "cannot open file";
		}
		else
		{
			fout << lophoc[i].numofstu;
			for (int j = 0; j < Nstudent; j++)
			{
				if (hocsinh[j].clas == lophoc[i].classname)
				{
					fout << "\n\n";
					fout << hocsinh[j].id << endl;
					fout << hocsinh[j].password << endl;
					fout << hocsinh[j].fullname << endl;
					fout << hocsinh[j].dob << endl;
					fout << hocsinh[j].clas << endl;
					fout << hocsinh[j].status;
				}
			}
			for (int t = Nstudent; t < Nstudent + Nleave; ++t)  //viet nhung thang co status = 0 vao file student class
			{
				if (hocsinh[t].clas == lophoc[i].classname)
				{
					fout << "\n\n";
					fout << hocsinh[t].id << endl;
					fout << hocsinh[t].password << endl;
					fout << hocsinh[t].fullname << endl;
					fout << hocsinh[t].dob << endl;
					fout << hocsinh[t].clas << endl;
					fout << hocsinh[t].status;
				}
			}
		}
		fout.close();
	}
}
void updateAClassTXT(string classname)
{

	// update file txt student-[class] after modifying it

	int tmp = -1;
	ofstream f2;
	string filename = "student-" + classname + ".txt";
	f2.open(filename);
	if (!f2.is_open())
	{
		cout << "cannot open file f2";
	}
	else
	{
		for (int i = 0; i < Nclass; i++)
		{
			if (lophoc[i].classname == classname)
			{
				tmp = i;
				break;
			}
		}
		f2 << lophoc[tmp].numofstu; //similarly
		for (int i = 0; i < Nstudent + Nleave; i++)
		{
			if (hocsinh[i].clas == classname && hocsinh[i].status == 1)
			{
				f2 << endl
					<< endl;
				f2 << hocsinh[i].id << endl;
				f2 << hocsinh[i].password << endl;
				f2 << hocsinh[i].fullname << endl;
				f2 << hocsinh[i].dob << endl;
				f2 << hocsinh[i].clas << endl;
				f2 << hocsinh[i].status;
			}
		}
		for (int i = 0; i < Nstudent + Nleave; i++)
		{
			if (hocsinh[i].clas == classname && hocsinh[i].status == 0)
			{
				f2 << endl
					<< endl;
				f2 << hocsinh[i].id << endl;
				f2 << hocsinh[i].password << endl;
				f2 << hocsinh[i].fullname << endl;
				f2 << hocsinh[i].dob << endl;
				f2 << hocsinh[i].clas << endl;
				f2 << hocsinh[i].status;
			}
		}
	}
	f2.close();
}

void updateStudentTXT(string filename)
{
	ofstream fout;
	fout.open(filename);
	if (!fout.is_open())
	{
		cout << "cannot open, cannot write fout";
	}
	else
	{
		fout << Nstudent << " " << Nleave;
		for (int i = 0; i < Nstudent + Nleave; i++)
		{
			if (hocsinh[i].status == 1)
			{
				fout << endl
					<< endl;
				fout << hocsinh[i].id << endl;
				fout << hocsinh[i].password << endl;
				fout << hocsinh[i].fullname << endl;
				fout << hocsinh[i].dob << endl;
				fout << hocsinh[i].clas << endl;
				fout << hocsinh[i].status;
			}
		}
		for (int i = 0; i < Nstudent + Nleave; i++)
		{
			if (hocsinh[i].status == 0)
			{
				fout << endl
					<< endl;
				fout << hocsinh[i].id << endl;
				fout << hocsinh[i].password << endl;
				fout << hocsinh[i].fullname << endl;
				fout << hocsinh[i].dob << endl;
				fout << hocsinh[i].clas << endl;
				fout << hocsinh[i].status;
			}
		}
	}
	fout.close();
}

void updatePosition(string filename)
{
	ifstream fin;

	fin.open(filename);
	if (!fin.is_open())
		cout << "Can not open file." << endl;
	else
	{
		fin >> Nstudent >> Nleave;
		fin.ignore(1000, '\n');
		for (int i = 0; i < Nstudent + Nleave; ++i)
		{
			fin.get();
			getline(fin, hocsinh[i].id);
			getline(fin, hocsinh[i].password);
			getline(fin, hocsinh[i].fullname);
			getline(fin, hocsinh[i].dob);
			getline(fin, hocsinh[i].clas);
			fin >> hocsinh[i].status;
			fin.get();
		}
		fin.close();


		/*fout.open(filename);
		if(!fout.is_open())
			cout << "Can not open file." << endl;
		else
		{
			fout << Nstudent << " " << Nleave;
			for (int i = 0; i < Nstudent + Nleave; i++)
			{
				fout << endl
					<< endl;
				fout << hocsinh[i].id << endl;
				fout << hocsinh[i].password << endl;
				fout << hocsinh[i].fullname << endl;
				fout << hocsinh[i].dob << endl;
				fout << hocsinh[i].clas << endl;
				fout << hocsinh[i].status;
			}
			fout.close();
		}*/
	}
}

void staffMenuShow()
{
	cout << "Menu: \n";

	cout << "------------------------CLASS------------------------\n";
	cout << "1. Import students of a class\n";
	cout << "2. Add a new student to a class\n";
	cout << "3. Edit an existing student\n";
	cout << "4. Remove a student\n";
	cout << "5. Change student from a class to another class\n";
	cout << "6. View list of classes\n";
	cout << "7. View list of student in a class\n";
	cout << "8. Change your password\n\n";

	cout << "------------------------COURSE------------------------\n";
	cout << "9. Create / update / delete / view academic years, and semesters" << endl;
	cout << "10. Import a course" << endl;
	cout << "11. Manually add a new course" << endl;
	cout << "12. Edit an existing course\n";
	cout << "13. Remove a course\n";
	cout << "14. Remove a specific student from a course\n";
	cout << "15. Add a specific student to a course\n";
	cout << "16. View list of courses in the current semester\n";
	cout << "17. View list students of a course\n";
	cout << "18. View attendance list of a course\n";
	cout << "19. View list of lecturer\n";

	cout << "Please choose menu (1-19): ";
}
void staffFeature(staff a)
{
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
	cout << endl
		 << endl;

	staffMenuShow();

	int con = 1;
	int t;
	cin >> t;
	system("cls");
	while (con == 1)
	{
		switch (t)
		{
		case 1:
			importCSV();
			break;
		case 2:
			addAStudenttoClass();
			break;
		case 3:
			editStudent();
			break;
		case 4:
			RemoveAStudent();
			break;
		case 5:
			ChangeClass();
			break;
		case 6:
			viewListOfClasses();
			break;
		case 7:
			viewListOfStudentsInClass();
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			importCourseCSV();
			break;
		case 11:
			addANewCourse();
			break;
		case 12:
			editACourse();
			break;
		case 13:
			removeACourse();
			break;
		case 14:
			break;
		case 15:
			break;
		case 16:
			listofCourse();
			break;
		case 17:
			listofStuinCourse();
			break;
		case 18:
			listofAttendance();
			break;
		case 19:
			viewLecturer();
			break;
		case 20:
			break;
		default:
			cout << "Wrong choice\n";
			break;
		}

		cout << "Do you want to continue (0.No 1.Yes): ";
		cin >> con;

		if (con == 1)
		{
			staffMenuShow();
			cin >> t;
		}
		else
			return;
	}
}
//Function for Staff
/*--------------------------------CLASS--------------------------------*/
void importCSV()
{
	// import data from CSV file to program and rewrite file student.txt and student-class.txt

	string no, studentID, fullname, dob, clas;

	string addressCSV;

	ifstream fin;
	cout << "Enter address of csv file: ";
	cin.ignore(1000, '\n');
	getline(cin, addressCSV, '\n'); // You must have file CSV first, then find the address of that file, and modify it to look like the one below
	fin.open(addressCSV);

	// C:\\Users\\THINKPAD\\Desktop\\university\\Semester 2\\CS162\\Lab\\Project\\ProjectFakeMoodle\\19APCS1-student.csv
	if (!fin.is_open())
	{
		cout << "cannot open file fin";
	}
	else
	{
		getline(fin, no, '\n');
		while (fin.good())
		{
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

			if (Nstudent == studentCapa)
			{ //increase slots for hocsinh
				student *tmpHocsinh = new student[Nstudent + 10];
				for (int i = 0; i < Nstudent; i++)
					tmpHocsinh[i] = hocsinh[i];
				delete[] hocsinh;
				hocsinh = tmpHocsinh;
				studentCapa += 10;
			}

			hocsinh[Nstudent+Nleave].id = studentID;
			hocsinh[Nstudent + Nleave].password = tmpPass;
			hocsinh[Nstudent + Nleave].fullname = fullname;
			hocsinh[Nstudent + Nleave].dob = tmpdob;
			hocsinh[Nstudent + Nleave].clas = clas;
			hocsinh[Nstudent + Nleave].status = 1;
			++Nstudent;

			bool newclass = true;
			int tmp;
			for (int j = 0; j < Nclass; j++)
			{
				if (lophoc[j].classname == clas)
				{
					newclass = false;
					tmp = j;
					break;
				}
			}
			if (newclass)
			{
				lophoc[Nclass].classname = clas;
				lophoc[Nclass].numofstu = 1;
				++Nclass;
			}
			else {
				++lophoc[tmp].numofstu;
			}
		}
	}

	updateStudentTXT("student.txt");
	updatePosition("student.txt");
	updateAllClassTXT();

	cout << "\nImport Successfully\n";
	fin.close();
	return;
}
void addAStudenttoClass()
{
	if (Nstudent + Nleave == studentCapa)
	{
		student *tmpHocsinh = new student[Nstudent + Nleave + 10]; //increase slots for hocsinh pointer
		for (int i = 0; i < Nstudent + Nleave; i++)
			tmpHocsinh[i] = hocsinh[i];
		delete[] hocsinh;
		hocsinh = tmpHocsinh;
		studentCapa += 10;
	}

	cout << "Enter student ID: ";
	cin.ignore(1000, '\n');
	getline(cin, hocsinh[Nstudent + Nleave].id, '\n');
	cout << "Enter fullname: ";
	getline(cin, hocsinh[Nstudent + Nleave].fullname, '\n');

	string dob;
	cout << "Enter student date of birth following the format: yyyy/mm/dd: ";
	getline(cin, dob, '\n');

	string tmpPass = dob;
	tmpPass.erase(tmpPass.begin() + 4);
	tmpPass.erase(tmpPass.begin() + 6);

	hocsinh[Nstudent + Nleave].password = tmpPass;

	string tmpdob = dob;
	tmpdob.replace(4, 1, " ");
	tmpdob.replace(7, 1, " ");

	hocsinh[Nstudent + Nleave].dob = tmpdob;

	cout << "Enter Class: ";
	getline(cin, hocsinh[Nstudent + Nleave].clas, '\n');

	hocsinh[Nstudent + Nleave].status = 1;

	string tmpclassname = hocsinh[Nstudent + Nleave].clas; //no need to worry about
	++Nstudent;

	for (int i = 0; i < Nclass; i++)
	{
		if (lophoc[i].classname == tmpclassname)
		{
			++lophoc[i].numofstu;
			break; //increase number of student in that class
		}
	}

	updateStudentTXT("student.txt");
	updateAClassTXT(tmpclassname);
	updatePosition("student.txt");
}

void editStudent()
{
	string tmpID;
	string tmpClass;
	cout << "Enter Student-ID you want to edit: ";
	cin.ignore(1000, '\n');
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

void RemoveAStudent()
{
	string tmpID;
	string tmpClass;
	cout << "Enter the class of this student: ";
	cin.ignore();
	getline(cin, tmpClass);
	cout << "ID: ";
	getline(cin, tmpID);
	for (int i = 0; i < Nstudent; ++i)
	{
		if (hocsinh[i].id == tmpID && hocsinh[i].clas == tmpClass)
		{
			cout << "----------INFORMATION---------" << endl;
			cout << "Student: " << hocsinh[i].fullname << endl;
			cout << "Class: " << hocsinh[i].clas << endl;
			cout << "Do you want to remove this student ? (0.No 1.Yes).";
			int k;
			cin >> k;
			if (k == 0) return;
			hocsinh[i].status = 0;
			++Nleave;
			--Nstudent;
			for (int j = 0; j < Nclass; ++j)
			{
				if (lophoc[j].classname == tmpClass)
				{
					--lophoc[j].numofstu;
					break;
				}
			}
			break;
		}
	}
	cout << "This student has been removed !" << endl;
	updateStudentTXT("student.txt");
	updateAClassTXT(tmpClass);
}

void ChangeClass()
{
	string tmpID;
	string tmpClass;
	string tmpNew;
	cout << "Enter the class of this student: ";
	cin.ignore();
	getline(cin, tmpClass);
	cout << "ID: ";
	getline(cin, tmpID);
	for (int i = 0; i < Nstudent; ++i)
	{
		if (hocsinh[i].id == tmpID && hocsinh[i].clas == tmpClass)
		{
			cout << "----------INFORMATION---------" << endl;
			cout << "Student: " << hocsinh[i].fullname << endl;
			cout << "Class: " << hocsinh[i].clas << endl;
			cout << "Do you want to change this student's class ? (0.No 1.Yes).";
			int k;
			cin >> k;
			if (k == 0) return;
			cout << "Enter the new class of this student: ";
			cin.get();
			getline(cin, tmpNew);
			hocsinh[i].clas = tmpNew;
			
			bool newclass = true;
			for (int j = 0; j < Nclass; ++j) {
				if (lophoc[j].classname == tmpNew)
					newclass = false;
				break;
			}

			if (newclass) {
				lophoc[Nclass].classname = tmpNew;
				lophoc[Nclass].numofstu = 1;
				++Nclass;
			}

			for (int j = 0; j < Nclass; ++j)
			{
				if (lophoc[j].classname == tmpClass)
					--lophoc[j].numofstu;

				if (!newclass && lophoc[j].classname == tmpNew)
					++lophoc[j].numofstu;
			}
			cout << "The class of this student have been changed !" << endl;
			break;
		}
	}
	updateStudentTXT("student.txt");
	/*updateAClassTXT(tmpClass);
	updateAClassTXT(tmpNew);*/

	updateAllClassTXT();
}

void viewListOfClasses()
{
	cout << left << setw(15) << setfill(' ') << "Class name";
	cout << left << setw(19) << setfill(' ') << "Number of student";
	cout << endl;

	for (int i = 0; i < Nclass; i++)
	{
		cout << left << setw(15) << setfill(' ') << lophoc[i].classname;
		cout << left << setw(19) << setfill(' ') << lophoc[i].numofstu;
	}
}
void viewListOfStudentsInClass()
{
	string classname;
	cout << "Enter classname you want to view: ";
	cin.ignore(1000, '\n');
	getline(cin, classname, '\n');

	string filename = "student-" + classname + ".txt";
	ifstream fin;
	string id, password, fullname, dob, clas;
	int status;
	int nstudent;
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "cannot open file";
	}
	else
	{
		fin >> nstudent;

		cout << "Students in class of " << classname << " are:" << endl;
		for (int i = 0; i < nstudent; i++)
		{
			fin.ignore(1000, '\n');
			fin.get();
			getline(fin, id);
			getline(fin, password);
			getline(fin, fullname);
			getline(fin, dob);
			getline(fin, clas);
			fin >> status;

			cout << endl;
			cout << id << endl;
			cout << fullname << endl;
			cout << dob << endl;
			cout << clas << endl;
			cout << status << endl;
		}
	}
}

/*--------------------------------COURSE--------------------------------*/
void importCourseCSV()
{
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

	course *khoahoc = new course[10];
	int Ncourse = 0;
	int courseCapa = 10;

	ifstream fin;
	fin.open(addressCSV);
	if (!fin.is_open())
	{
		cout << "cannot open file";
	}
	else
	{
		getline(fin, no, '\n');
		while (fin.good())
		{
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

			if (Ncourse == courseCapa)
			{
				course *tmpkhoahoc = new course[Ncourse + 10];
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
			//khoahoc[Ncourse].status = 1;
			++Ncourse;
		}
	}
	fin.close();

	string coursename = acayear + "-" + semester + "-schedule-" + classname + ".txt";
	updateClassScheduleTXT(khoahoc, Ncourse, coursename);

	for (int i = 0; i < Ncourse; i++)
	{
		string tmpcourseID = khoahoc[i].courseID;
		string coursestudent = acayear + "-" + semester + "-" + classname + "-" + tmpcourseID + "-student.txt";

		createAttendance(khoahoc[i]);
		updateCourseStudentTXT(coursestudent, classname);
	}
	delete[] khoahoc;
}

bool nhuan(int y)
{
	bool c;
	if ((y % 4 == 0) && (y % 100 != 0) || (y % 400 == 0))
		c = true;
	return c;
}

void plus7days(int &y, int &m, int &d)
{
	if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
	{
		if (d > 24)
		{
			if (m == 12)
			{
				d = 7 - (31 - d);
				m = 1;
				y += 1;
			}
			else
			{
				d = 7 - (31 - d);
				m += 1;
			}
		}
		else
		{
			d += 7;
		}
	}
	else
	{
		if (m == 2)
		{
			if (nhuan(y))
			{
				if (d > 22)
				{
					d = 7 - (29 - d);
					m = 3;
				}
				else
					d += 7;
			}
			else if (d > 21)
			{
				d = 7 - (28 - d);
				m = 3;
			}
			else
				d += 7;
		}
		else
		{
			if (d > 23)
			{
				d = 7 - (30 - d);
				m += 1;
			}
			else
				d += 7;
		}
	}
}

void createAttendance(course khoahoc)
{

	string tmpY, tmpM, tmpD;
	int y, m, d;
	for (int i = 0; i < 4; ++i)
		tmpY += khoahoc.startDate[i];
	for (int i = 5; i < 7; ++i)
		tmpM += khoahoc.startDate[i];
	for (int i = 8; i < 10; ++i)
		tmpD += khoahoc.startDate[i];
	y = stoi(tmpY);
	m = stoi(tmpM);
	d = stoi(tmpD);

	for (int i = 0; i < 10; i++)
	{
		a[i] = tmpY + " " + tmpM + " " + tmpD + " " + khoahoc.startTime + " " + khoahoc.endTime + " " + "-1";
		plus7days(y, m, d);
		tmpY = to_string(y);
		if (m < 10)
			tmpM ="0" + to_string(m);
		else tmpM = to_string(m);
		if (d < 10)
			tmpD = "0" + to_string(d);
		else tmpD = to_string(d);
	}
}


void addANewCourse()
{
	string acayear, semester, classname, classcourses;

	cout << "Enter academic year (yyyy-yyyy): ";
	getline(cin, acayear, '\n');
	cout << "Enter semester: ";
	getline(cin, semester, '\n');
	cout << "Enter class name: ";
	getline(cin, classname, '\n');
	classcourses = acayear + "-" + semester + "-schedule-" + classname + ".txt";

	course *khoahoc = nullptr;
	int Ncourse = 0;

	loadClassScheduleTXT(khoahoc, Ncourse, classcourses);

	cout << "New course: \n";
	cout << "Enter courseID: ";
	getline(cin, khoahoc[Ncourse].courseID, '\n');
	string courseID = khoahoc[Ncourse].courseID;
	cout << "Enter courseName: ";
	getline(cin, khoahoc[Ncourse].courseName, '\n');
	khoahoc[Ncourse].clas = classname;
	cout << "Enter instructor: ";
	getline(cin, khoahoc[Ncourse].instructor, '\n');
	cout << "Enter instructorUsername: ";
	getline(cin, khoahoc[Ncourse].instructorUsername, '\n');
	cout << "Enter degree: ";
	getline(cin, khoahoc[Ncourse].degree, '\n');
	cout << "Enter gender: ";
	getline(cin, khoahoc[Ncourse].gender, '\n');
	cout << "Enter startDate(yyyy mm dd): ";
	getline(cin, khoahoc[Ncourse].startDate, '\n');
	cout << "Enter endDate(yyyy mm dd): ";
	getline(cin, khoahoc[Ncourse].endDate, '\n');
	cout << "Enter dayOfWeek: ";
	getline(cin, khoahoc[Ncourse].dayOfWeek, '\n');
	cout << "Enter startTime(hh:mm): ";
	getline(cin, khoahoc[Ncourse].startTime, '\n');
	cout << "Enter endTime(hh:mm): ";
	getline(cin, khoahoc[Ncourse].endTime, '\n');
	cout << "Enter room: ";
	getline(cin, khoahoc[Ncourse].room, '\n');
	++Ncourse;

	updateClassScheduleTXT(khoahoc, Ncourse, classcourses);
	createAttendance(khoahoc[Ncourse-1]);

	string coursestudent = acayear + "-" + semester + "-" + classname + "-" + courseID + "-student.txt";

	updateCourseStudentTXT(coursestudent, classname);

	delete[] khoahoc;
}
void editACourse()
{
	string acayear, semester, classname, coursename;

	cout << "Enter academic year (yyyy-yyyy): ";
	getline(cin, acayear, '\n');
	cout << "Enter semester: ";
	getline(cin, semester, '\n');
	cout << "Enter class name: ";
	getline(cin, classname, '\n');
	coursename = acayear + "-" + semester + "-schedule-" + classname + ".txt";

	course *khoahoc = nullptr;
	int Ncourse = 0;

	loadClassScheduleTXT(khoahoc, Ncourse, coursename);

	string courseID;
	cout << "CourseID of the course that you want to modify: ";
	getline(cin, courseID, '\n');
	cout << "Modify: \n";
	for (int i = 0; i < Ncourse; i++)
	{
		if (khoahoc[i].courseID == courseID)
		{
			cout << "Enter courseName: ";
			getline(cin, khoahoc[i].courseName, '\n');
			khoahoc[i].clas = classname;
			cout << "Enter instructor: ";
			getline(cin, khoahoc[i].instructor, '\n');
			cout << "Enter instructorUsername: ";
			getline(cin, khoahoc[i].instructorUsername, '\n');
			cout << "Enter degree: ";
			getline(cin, khoahoc[i].degree, '\n');
			cout << "Enter gender: ";
			getline(cin, khoahoc[i].gender, '\n');
			cout << "Enter startDate(yyyy mm dd): ";
			getline(cin, khoahoc[i].startDate, '\n');
			cout << "Enter endDate(yyyy mm dd): ";
			getline(cin, khoahoc[i].endDate, '\n');
			cout << "Enter dayOfWeek: ";
			getline(cin, khoahoc[i].dayOfWeek, '\n');
			cout << "Enter startTime(hh:mm): ";
			getline(cin, khoahoc[i].startTime, '\n');
			cout << "Enter endTime(hh:mm): ";
			getline(cin, khoahoc[i].endTime, '\n');
			cout << "Enter room: ";
			getline(cin, khoahoc[i].room, '\n');

			createAttendance(khoahoc[i]);
			
			string filename = acayear + "-" + semester + "-" + classname + "-" + courseID + ".txt";
			updateCourseStudentTXT(filename, classname);

			break;
		}
	}

	updateClassScheduleTXT(khoahoc, Ncourse, coursename);

	delete[] khoahoc;
}

void listofCourse()
{
	course *khoahoc = nullptr;
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

	for (int i = 0; i < Ncourse; ++i)
	{
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

void listofStuinCourse()
{
	stuincourse *khoahoc = nullptr;
	int NstuinCourse = 0;
	string courseID, classname;
	cin.ignore(1000, '\n');
	cout << "Choose class do you want to view: ";
	getline(cin, classname, '\n');
	cout << "Choose course do you want to view: ";
	getline(cin, courseID, '\n');
	string filename = "2019-2020-HK2-" + classname + "-" + courseID + "-student.txt";

	loadStudentOfCourseTXT(khoahoc, NstuinCourse, filename);

	cout << left << setw(14) << setfill(' ') << "Student ID";
	cout << left << setw(28) << setfill(' ') << "Student Full Name";
	cout << left << setw(12) << setfill(' ') << "DOB";
	cout << left << setw(10) << setfill(' ') << "Class";
	cout << left << setw(10) << setfill(' ') << "Mid Term";
	cout << left << setw(9) << setfill(' ') << "Final";
	cout << left << setw(9) << setfill(' ') << "Bonus";
	cout << left << setw(9) << setfill(' ') << "Total";
	cout << endl;

	for (int i = 0; i < NstuinCourse; i++)
	{
		cout << left << setw(14) << setfill(' ') << khoahoc[i].id;
		cout << left << setw(28) << setfill(' ') << khoahoc[i].fullname;
		cout << left << setw(12) << setfill(' ') << khoahoc[i].dob;
		cout << left << setw(10) << setfill(' ') << khoahoc[i].clas;
		cout << left << setw(10) << setfill(' ') << khoahoc[i].midterm;
		cout << left << setw(9) << setfill(' ') << khoahoc[i].final;
		cout << left << setw(9) << setfill(' ') << khoahoc[i].bonus;
		cout << left << setw(9) << setfill(' ') << khoahoc[i].total;
		cout << endl;
	}
	delete[] khoahoc;
}

void listofAttendance(){
	stuincourse *khoahoc = nullptr;
	int NstuinCourse = 0;
	string courseID, classname;
	cout << "Choose class do you want to view: ";
	getline(cin, classname, '\n');
	cout << "Choose course do you want to view: ";
	getline(cin, courseID, '\n');
	string filename = "2019-2020-HK2-" + classname + "-" + courseID + "-student.txt";

	loadStudentOfCourseTXT(khoahoc, NstuinCourse, filename);
	for (int i = 0; i < NstuinCourse; ++i){
		for (int j = 0; j < 10; ++j)
			cout << khoahoc[i].attendance[j] << endl;
		cout << endl;
	}
	delete [] khoahoc;
}

void loadStudentOfCourseTXT(stuincourse *&stuinCourse, int &NstuinCourse, string coursename)
{
	ifstream fin;
	fin.open(coursename);
	if (!fin.is_open())
	{
		cout << "Can't open this file\n";
		stuinCourse = new stuincourse[1];
	}
	else
	{
		fin >> NstuinCourse;
		stuinCourse = new stuincourse[NstuinCourse + 1];
		
		for (int i = 0; i < NstuinCourse; i++)
		{
			fin.ignore(1000, '\n');
			fin.get();
			getline(fin, stuinCourse[i].id, '\n');
			getline(fin, stuinCourse[i].password, '\n');
			getline(fin, stuinCourse[i].fullname, '\n');
			getline(fin, stuinCourse[i].dob, '\n');
			getline(fin, stuinCourse[i].clas, '\n');
			fin >> stuinCourse[i].midterm;
			fin >> stuinCourse[i].final;
			fin >> stuinCourse[i].bonus;
			fin >> stuinCourse[i].total;
			fin.ignore(1000, '\n');
			for (int j = 0; j < 10; ++j)
				getline(fin, stuinCourse[i].attendance[j], '\n');

		}
	}
	fin.close();
}

void updateClassScheduleTXT(course *khoahoc, int Ncourse, string classschedule)
{
	ofstream f2;

	f2.open(classschedule);
	if (!f2.is_open())
	{
		cout << "cannot open file f2";
	}
	else
	{
		f2 << Ncourse;
		for (int i = 0; i < Ncourse; i++)
		{
			f2 << endl
			   << endl;
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
void loadClassScheduleTXT(course *&khoahoc, int &Ncourse, string classcourses)
{
	ifstream fin;
	fin.open(classcourses);
	if (!fin.is_open())
	{
		cout << "cannot open file\n";
		khoahoc = new course[1];
	}
	else
	{
		fin >> Ncourse;
		fin.ignore(1000, '\n');
		khoahoc = new course[Ncourse + 1];
		for (int i = 0; i < Ncourse; i++)
		{
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

void removeACourse()
{
	ofstream f;
	string acayear, semester, classname, classcourses, tmpCourseID;

	cout << "Enter academic year (yyyy-yyyy): ";
	cin.ignore();
	getline(cin, acayear, '\n');
	cout << "Enter semester: ";
	getline(cin, semester, '\n');
	cout << "Enter class name: ";
	getline(cin, classname, '\n');
	classcourses = acayear + "-" + semester + "-schedule-" + classname + ".txt";

	course *khoahoc = nullptr;
	int Ncourse = 0;

	loadClassScheduleTXT(khoahoc, Ncourse, classcourses);
	cout << "Enter ID of the course needed to removed: ";
	getline(cin, tmpCourseID, '\n');
	for (int i = 0; i < Ncourse; ++i)
	{
		if (khoahoc[i].courseID == tmpCourseID)
		{
			cout << "----------INFORMATION---------" << endl;
			cout << "Course ID: " << khoahoc[i].courseID << endl;
			cout << "Course name: " << khoahoc[i].courseName << endl;
			cout << "Class: " << khoahoc[i].clas << endl;
			cout << "Instructor: " << khoahoc[i].instructor << endl;
			cout << "Instructor username: " << khoahoc[i].instructorUsername << endl;
			cout << "Degree: " << khoahoc[i].degree << endl;
			cout << "Gender: " << khoahoc[i].gender << endl;
			cout << "Start Date: " << khoahoc[i].startDate << endl;
			cout << "End Date: " << khoahoc[i].endDate << endl;
			cout << "Day of week: " << khoahoc[i].dayOfWeek << endl;
			cout << "Start time: " << khoahoc[i].startTime << endl;
			cout << "End time: " << khoahoc[i].endTime << endl;
			cout << "Room: " << khoahoc[i].room << endl;
			break;
		}
	}
	cout << "Do you want to remove this course ? (0.No 1.Yes) ";
	int k;
	cin >> k;
	if (k == 0)
		return;
	f.open(classcourses);
	if (!f.is_open())
	{
		cout << "cannot open file f";
	}
	else
	{
		f << Ncourse - 1;
		for (int i = 0; i < Ncourse; ++i)
		{
			if (khoahoc[i].courseID != tmpCourseID)
			{
				f << endl
				  << endl;
				f << khoahoc[i].courseID << endl;
				f << khoahoc[i].courseName << endl;
				f << khoahoc[i].clas << endl;
				f << khoahoc[i].instructor << endl;
				f << khoahoc[i].instructorUsername << endl;
				f << khoahoc[i].degree << endl;
				f << khoahoc[i].gender << endl;
				f << khoahoc[i].startDate << endl;
				f << khoahoc[i].endDate << endl;
				f << khoahoc[i].dayOfWeek << endl;
				f << khoahoc[i].startTime << endl;
				f << khoahoc[i].endTime << endl;
				f << khoahoc[i].room;
			}
		}
		cout << "This course has been remove !" << endl;
		f.close();
	}
	string coursestudent = acayear + "-" + semester + "-" + classname + "-" + tmpCourseID + "-student.txt";
	f.open(coursestudent);
	if (!f.is_open())
	{
		cout << "cannot open file f";
	}
	else
	{
		f << " ";
		f.close();
	}
}

void updateCourseStudentTXT(string coursestudent, string classname)
{
	stuincourse *hs = nullptr;
	int NStudent;

	ofstream fo3;

	fo3.open(coursestudent);
	if (!fo3.is_open())
	{
		cout << "cannot open file";
	}
	else
	{
		ifstream fi4;
		fi4.open("student-" + classname + ".txt");
		if (!fi4.is_open())
		{
			cout << "cannot open file";
		}
		else
		{
			fi4 >> NStudent;
			fo3 << NStudent;

			hs = new stuincourse[NStudent + 1];

			for (int i = 0; i < NStudent; i++)
			{
				fi4.ignore(1000, '\n');
				fi4.get();

				getline(fi4, hs[i].id, '\n');
				getline(fi4, hs[i].password, '\n');
				getline(fi4, hs[i].fullname, '\n');
				getline(fi4, hs[i].dob, '\n');
				getline(fi4, hs[i].clas, '\n');
				fi4 >> hs[i].status;
				for (int j = 0; j < 10; j++)
					hs[i].attendance[j] = a[j];
				hs[i].midterm = -1;
				hs[i].final = -1;
				hs[i].bonus = -1;
				hs[i].final = -1;

				fo3 << endl
					<< endl;
				fo3 << hs[i].id << endl;
				fo3 << hs[i].password << endl;
				fo3 << hs[i].fullname << endl;
				fo3 << hs[i].dob << endl;
				fo3 << hs[i].clas << endl;
				fo3 << hs[i].midterm << endl;
				fo3 << hs[i].final << endl;
				fo3 << hs[i].bonus << endl;
				fo3 << hs[i].final << endl;
				for (int j = 0; j < 10; ++j)
					fo3 << hs[i].attendance[j] << endl;
			}
		}
		fi4.close();
		fo3.close();
	}

	delete[] hs;
}

void viewLecturer()
{
	cout << left << setw(15) << setfill(' ') << "Username";
	cout << left << setw(24) << setfill(' ') << "Full Name";
	cout << left << setw(13) << setfill(' ') << "Degree";
	cout << left << setw(13) << setfill(' ') << "Gender";
	cout << endl;

	for (int i = 0; i < Nlecturer; i++)
	{
		cout << left << setw(15) << setfill(' ') << giaovien[i].username;
		cout << left << setw(24) << setfill(' ') << giaovien[i].fullname;
		cout << left << setw(13) << setfill(' ') << giaovien[i].degree;
		if (giaovien[i].gender == 1)
			cout << left << setw(13) << setfill(' ') << "Nam";
		else
			cout << left << setw(13) << setfill(' ') << "Nu";
		cout << endl;
	}
}

void lecturerMenuShow()
{
	cout << "Menu: \n";

	cout << "------------------------COURSE------------------------\n";
	cout << "1. View list of courses in the current semester\n";
	cout << "2. View list of students of a course\n";
	cout << "------------------------ATTENDANCE------------------------\n";
	cout << "3. View attendance list of a course\n";
	cout << "4. Edit an attendance\n";
	cout << "------------------------SCOREBOARD------------------------\n";
	cout << "5. Import scoreboard of a course (midterm, final, bonus) from CSV file\n";
	cout << "6. Edit grade of a student\n";
	cout << "7. View a scoreboard\n";

	cout << "Please choose menu (1-7): ";
}
void lecturerFeature(lecturer a)
{
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
	cout << endl
		 << endl;

	lecturerMenuShow();

	int con = 1;
	int t;
	cin >> t;
	while (con == 1)
	{
		switch (t)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		default:
			cout << "Wrong choice\n";
			break;
		}

		cout << "Do you want to continue (0.No 1.Yes): ";
		cin >> con;

		if (con == 1)
		{
			lecturerMenuShow();
			cin >> t;
		}
		else
			return;
	}
}

void studentFeature(student a)
{
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
}

//For Attendance
