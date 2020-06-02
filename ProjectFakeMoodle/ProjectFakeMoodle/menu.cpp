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
	int index[19];
	index[0] = 1; 
	for (int i = 1; i < 19; ++i)
		index[i] = 0;
	int ptr = 0;
	int keystroke = 0;
	while (keystroke != 13) { // 13: enter
		system("cls");

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

		cout << "------------------------COURSE------------------------\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[8]]);
		cout << "9. Create / update / delete / view academic years, and semesters" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[9]]);
		cout << "10. Import a course" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[10]]);
		cout << "11. Manually add a new course" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[11]]);
		cout << "12. Edit an existing course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[12]]);
		cout << "13. Remove a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[13]]);
		cout << "14. Remove a specific student from a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[14]]);
		cout << "15. Add a specific student to a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[15]]);
		cout << "16. View list of courses in the current semester\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[16]]);
		cout << "17. View list students of a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[17]]);
		cout << "18. View attendance list of a course\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[index[18]]);
		cout << "19. View list of lecturer\n";

		keystroke = _getch();
		fflush(stdin);
        
        //UP_ARROW: 72
		if (keystroke == 72) {
			index[ptr] = 0;
			if (ptr == 0)
				ptr = 18;
			else
				ptr--;
			index[ptr] = 1;
		}

        //DOWN_ARROW: 80
		else if (keystroke==80) {
			index[ptr] = 0;
			if (ptr == 18)
				ptr = 0;
			else
				ptr++;
			index[ptr] = 1;
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	switch (ptr) {
	case 0:
		cout << "Hello" << endl;

		break;
	case 1:
		cout << "Bye" << endl;
		break;
	case 2:
		cout << "See you again" << endl;
		break;
	}



	return 0;
}