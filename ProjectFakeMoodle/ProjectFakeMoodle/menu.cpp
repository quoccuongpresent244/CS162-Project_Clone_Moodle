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
	int index[23];
	index[0] = 1; 
	for (int i = 1; i < 23; ++i)
		index[i] = 0;
	int ptr = 0;
	int keystroke = 0;
	while (keystroke != 13) { // 13: enter
		//system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "------------------------CLASS------------------------\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[0]]);
		cout << "1. Import students of a class\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[1]]);
		cout << "2. Add a new student to a class\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[2]]);
		cout << "3. Edit an existing student\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[3]]);
		cout << "4. Remove a student\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[4]]);
		cout << "5. Change student from a class to another class\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[5]]);
		cout << "6. View list of classes\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[6]]);
		cout << "7. View list of student in a class\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[7]]);
		cout << "8. Change your password\n\n";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "------------------------COURSE------------------------\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[8]]);
		cout << "9. Import a course" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[9]]);
		cout << "10. Manually add a new course" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[10]]);
		cout << "11. Edit an existing course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[11]]);
		cout << "12. Remove a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[12]]);
		cout << "13. Remove a specific student from a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[13]]);
		cout << "14. Add a specific student to a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[14]]);
		cout << "15. View list of courses in the current semester\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[15]]);
		cout << "16. View list students of a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[16]]);
		cout << "17. View attendance list of a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[17]]);
		cout << "18. View list of lecturer\n";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "------------------------SCORE BOARD------------------------\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[18]]);
		cout << "19. Search and view the scoreboard of a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[19]]);
		cout << "20. Export a scoreboard to a csv file\n";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "------------------------ATTENDANCE------------------------\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[20]]);
		cout << "21. Search and view attendance list of a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[21]]);
		cout << "22. Export an attendance list to a csv file\n\n";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[22]]);
		cout << "23. EXIT";

		keystroke = _getch();
		fflush(stdin);
        
        //UP_ARROW: 72
		if (keystroke == 72) {
			index[ptr] = 0;
			if (ptr == 0)
				ptr = 22;
			else
				ptr--;
			index[ptr] = 1;
		}

        //DOWN_ARROW: 80
		else if (keystroke==80) {
			index[ptr] = 0;
			if (ptr == 22)
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