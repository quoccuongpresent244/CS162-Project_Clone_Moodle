#include <iomanip>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <string.h>
#include <Windows.h>
#include <conio.h>
using namespace std;


int main()
{
	
	int color[] = { 10, 12 };
	int index[6];
	index[0] = 1; 
	for (int i = 1; i < 6; ++i)
		index[i] = 0;
	int ptr = 0;
	int keystroke = 0;
	while (keystroke != 13) { // 13: enter
		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "------------------------STUDENT------------------------\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[0]]);
		cout << "1. Check-in\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[1]]);
		cout << "2. View check-in result\n";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[2]]);
		cout << "3. View schedules\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[3]]);
		cout << "4. View his/her score of a course\n";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[4]]);
		cout << "5. Change your password\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[5]]);
		cout << "6. EXIT\n";
		


		keystroke = _getch();
		fflush(stdin);
        
        //UP_ARROW: 72
		if (keystroke == 72) {
			index[ptr] = 0;
			if (ptr == 0)
				ptr = 5;
			else
				ptr--;
			index[ptr] = 1;
		}

        //DOWN_ARROW: 80
		else if (keystroke==80) {
			index[ptr] = 0;
			if (ptr == 5)
				ptr = 0;
			else
				ptr++;
			index[ptr] = 1;
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	switch (ptr){
		case 0: 
			cout <<"good!";
			break;
		case 1:
			cout <<"Nice";
			break;
		case 2: 
			cout << "BYE~~";
			break;
	}
	/* switch (ptr) {
		case 0:
			importCSV();
			break;
		case 1:
			addAStudenttoClass();
			break;
		case 2:
			editStudent();
			break;
		case 3:
			RemoveAStudent();
			break;
		case 4:
			ChangeClass();
			break;
		case 5:
			viewListOfClasses();
			break;
		case 6:
			viewListOfStudentsInClass();
			break;
		case 7:
			for (int i = 0; i < Nstaff; i++)
			{
				if (a.username == giaovu[i].username)
				{
					giaovu[i].password = changePassword(a.password);
					break;
				}
			}
			updateStaffTXT();
			break;
		case 8:
			importCourseCSV();
			break;
		case 9:
			addANewCourse();
			break;
		case 10:
			editACourse();
			break;
		case 11:
			removeACourse();
			break;
		case 12:
			RemoveASpecificStu();
			break;
		case 13:
			AddASpecificStu();
			break;
		case 14:
			viewlistofCourse();
			break;
		case 15:
			viewlistofStuinCourse();
			break;
		case 16:
			viewlistofAttendance();
			break;
		case 17:
			viewLecturer();
			break;
		case 18:
			viewScoreBoard();
			break;
		case 19:
			exportSBtoCSV();
			break;
		case 20:
			viewlistofAttendance();
			break;
		case 21:
			break;
		case 22:
			cout << "Thanks for using our software !!!!" << endl;
			return;
		} */
}